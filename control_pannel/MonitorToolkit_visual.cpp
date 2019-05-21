/*
 * Copyright (c) 2011, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h> //pthread_t , pthread_attr_t and so on.
#include <stdio.h>

#include <linux/types.h>
#include <netinet/in.h> //structure sockaddr_in
#include <arpa/inet.h>  //Func : htonl; htons; ntohl; ntohs
#include <assert.h>     //Func :assert
#include <string.h>     //Func :memset
#include <unistd.h>     //Func :close,write,read
#include <time.h>
#include <netdb.h>
#include <sys/wait.h>
#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <sys/prctl.h>
#include <signal.h>
#include <string.h>
#include <QPixmap>
#include <QMatrix>
#include <QSize>
#include <QBitmap>
#include <QPainter>

#include <QThread>

#include "MonitorToolkit_visual.h"

using namespace MonitorToolkit_display;
using namespace Qt;
using namespace std;
using namespace tinyxml2;
double throttle_sub = 0;
double brake_sub = 0;
double steer_sub = 0;
extern "C"
{
}

namespace MonitorToolkit_display
{

MonitorToolkitDisplay::~MonitorToolkitDisplay()
{

}

MonitorToolkitDisplay::MonitorToolkitDisplay(QWidget *parent)
    : rviz::Panel(parent)
{
    //open the picture
    QString filename_progress((ros::package::getPath("rviz_plugins") + "/meshes/picture1.jpg").c_str()); // brake and throttle progress picture path
    QString filename_steer((ros::package::getPath("rviz_plugins") + "/meshes/steer.jpg").c_str()); //steer picture path
    img_progress.load(filename_progress); //load pic
    pixmap.load(filename_steer); //load pic
    pixmap = pixmap.scaled(200,200,Qt::IgnoreAspectRatio, Qt::SmoothTransformation); // set pic scale 200*200
    pixmap = PixmapToRound(pixmap,100); // change shape from rect to round

    //throttle status bar
    throttle_status_pctg = new QProgressBar;
    throttle_status_pctg->setOrientation(Qt::Horizontal); //display direction
    throttle_status_pctg->setMinimum(0); // range
    throttle_status_pctg->setMaximum(100);
    throttle_status_pctg->setTextVisible(false); //text dont show

    //brake status bar
    brake_status_pctg = new QProgressBar;
    brake_status_pctg->setOrientation(Qt::Horizontal);
    brake_status_pctg->setMinimum(0);
    brake_status_pctg->setMaximum(100);
    brake_status_pctg->setTextVisible(false);

    //label for status
    brake_status_label = new QLabel;
    throttle_status_label = new QLabel;

    //label for steer
    steer_angle_label = new QLabel;

    // build a new layout
    layout = new QVBoxLayout;
    // add horizontal widget
    QHBoxLayout *control_status = new QHBoxLayout;
    control_status->addWidget(throttle_status_pctg);
    control_status->addWidget(brake_status_pctg);
    layout->addLayout(control_status);
    // add horizontal widget
    QHBoxLayout *control_status_label = new QHBoxLayout;
    control_status_label->addWidget(throttle_status_label);
    control_status_label->addWidget(brake_status_label);
    layout->addLayout(control_status_label);
    // add horizontal widget
    QHBoxLayout *steer_angle = new QHBoxLayout;
    steer_angle->addWidget(steer_angle_label);
    layout->addLayout(steer_angle);

    // ros subscriber
    car_control_sub = nh1.subscribe("/car/control",20,&MonitorToolkitDisplay::GetCarControlCallback,this);


//    QHBoxLayout *modeselect = new QHBoxLayout;
//    QLabel *mode = new QLabel("MODE:");
//    add_trajectory_points_rbtn = new QRadioButton("Way Points");
//    add_trajectory_points_rbtn->setChecked(true);
//    nh_.setParam("/click_type", "add_trajectory_points");
//    add_trigger_point_rbtn = new QRadioButton("Trigger Area");

//    modeselect->addWidget(mode);
//    modeselect->addWidget(add_trajectory_points_rbtn);
//    modeselect->addWidget(add_trigger_point_rbtn);
//    layout->addLayout(modeselect);

    //add horizontal widget
    QHBoxLayout *start_stop_layout = new QHBoxLayout;
    startBtn = new QPushButton();  // widget for start button
    startBtn->setText("start");
    start_stop_layout->addWidget(startBtn);
    layout->addLayout(start_stop_layout);



//    QHBoxLayout *confirm_layout = new QHBoxLayout;
//    add_btn = new QPushButton();
//    add_btn->setText("Add car");
//    delete_btn = new QPushButton();
//    delete_btn->setText("Delete car");
//    nh_.setParam("/change", "false");

//    confirm_layout->addWidget(add_btn);
//    confirm_layout->addWidget(delete_btn);
//    layout->addLayout(confirm_layout);


//    QHBoxLayout *input_layout = new QHBoxLayout;
//    QLabel* carid = new QLabel("Obstacle ID:");
//    id_cBox = new QComboBox();
//    QLabel* radius = new QLabel("TriggerRadius:");
//    lineChangeR = new QLineEdit();
//    lineChangeR->setText("5.0");
//    QLabel* speed = new QLabel("ObsSpeed:");
//    lineChangeSpeed = new QLineEdit();
//    lineChangeSpeed->setText("1.0");

//    nh_.setParam("/changeid", id_cBox->currentText().toStdString());
//    nh_.setParam("/changeR", lineChangeR->text().toStdString());
//    nh_.setParam("/changeSpeed", lineChangeSpeed->text().toStdString());
//    nh_.setParam("/change", "false");
//    input_layout->addWidget(carid);
//    input_layout->addWidget(id_cBox);
//    input_layout->addWidget(radius);
//    input_layout->addWidget(lineChangeR);
//    input_layout->addWidget(speed);
//    input_layout->addWidget(lineChangeSpeed);
//    layout->addLayout(input_layout);

//    QHBoxLayout *button_layout = new QHBoxLayout;
//    change_trajectory_btn = new QPushButton();
//    change_trajectory_btn->setText("Change Traj");
//    change_trigger_btn = new QPushButton();
//    change_trigger_btn->setText("Change Trigger");
//    change_shape_btn = new QPushButton();
//    change_shape_btn->setText("Change Shape");
//    change_speed_btn = new QPushButton();
//    change_speed_btn->setText("Change Speed");
//    button_layout->addWidget(change_trajectory_btn);
//    button_layout->addWidget(change_trigger_btn);
//    button_layout->addWidget(change_shape_btn);
//    button_layout->addWidget(change_speed_btn);
//    layout->addLayout(button_layout);

//    QHBoxLayout *status_layout = new QHBoxLayout;
//    status_log = new QLabel();
//    status_log->setText("Welcome!");

//    status_layout->addWidget(status_log);
//    layout->addLayout(status_layout);

//    // QHBoxLayout *choose_layout = new QHBoxLayout;
//    // cbox = new QComboBox();

//    // choose_layout->addWidget(cbox);
//    // layout->addLayout(choose_layout);


    // set layout
    setLayout(layout);

    // timer for trigger
    update_timer = new QTimer(this);
    update_timer->setInterval(100);
    update_timer->start();




//    update_ui();

    // set events

//    connect(add_trajectory_points_rbtn, SIGNAL(clicked()), this, SLOT(add_trajectory_points()));
//    connect(add_trigger_point_rbtn, SIGNAL(clicked()), this, SLOT(add_trigger_point()));
//    connect(add_btn, SIGNAL(clicked()), this, SLOT(add()));
//    connect(delete_btn, SIGNAL(clicked()), this, SLOT(delete_car()));
//    connect(change_trigger_btn, SIGNAL(clicked()), this, SLOT(change_trigger()));
//    connect(change_trajectory_btn, SIGNAL(clicked()), this, SLOT(change_trajectory()));
//    connect(change_shape_btn, SIGNAL(clicked()), this, SLOT(change_shape()));
//    connect(change_speed_btn, SIGNAL(clicked()), this, SLOT(change_speed()));
//    connect(update_timer, SIGNAL(timeout()), this, SLOT(update_visual()));


    // add connection foe Signal and Slot
    connect(update_timer, SIGNAL(timeout()), this, SLOT(brake_status()));
    connect(update_timer, SIGNAL(timeout()), this, SLOT(throttle_status()));
    connect(update_timer, SIGNAL(timeout()), this, SLOT(steer_status()));

}

// display throttle status by time trigger
void MonitorToolkitDisplay::throttle_status()
{
    // use QString for setStyleSheet for progressbar
    QString qss= "QProgressBar{"
               "border: 1px solid rgb(16, 135, 209);"
               "background: rgba(248,248,255,180);"
               "border-radius: 6px; }"
               "QProgressBar::chunk:enabled {"
               "border-radius: 4px; "
               "background: qlineargradient(x1:0, y1:0, x2:1, y2:0" ;
    double v = 100;
    double EndColor = static_cast<double>(throttle_sub*100)/v;
    // set color pixel
    for(int i=0;i<100;i++)
    {
     double Current = EndColor*i/100;
     QRgb rgb = img_progress.pixel((img_progress.width()-1)*Current,img_progress.height()/2);
     QColor c(rgb);
     qss.append(QString(",stop:%1  rgb(%2,%3,%4)").arg(Current).arg(c.red()).arg(c.green()).arg(c.blue()));
    }
    qss.append(");}");
    throttle_status_pctg->setStyleSheet(qss);
    throttle_status_pctg->setValue(throttle_sub*100);
    throttle_status_label->setText(QString("throttle   %1%").arg(throttle_sub*100));
    throttle_status_label->setMinimumWidth(40);

}


// display throttle status by time trigger
void MonitorToolkitDisplay::brake_status()
{
    QString qss= "QProgressBar{"
               "border: 1px solid rgb(16, 135, 209);"
               "background: rgba(248,248,255,180);"
               "border-radius: 6px; }"
               "QProgressBar::chunk:enabled {"
               "border-radius: 4px; "
               "background: qlineargradient(x1:0, y1:0, x2:1, y2:0" ;
//    cout << qss.toStdString().data()<< endl ;
    double v = 100;
    double EndColor=static_cast<double>(brake_sub*100)/v ;
    for(int i=0;i<100;i++)
    {
     double Current = EndColor*i/100;
//     cout << "Current" << Current << endl;
//     cout << "height" << img_progress.height() << endl;
     QRgb rgb = img_progress.pixel((img_progress.width()-1)*Current,img_progress.height()/2);
//     cout << "pixel_x" << (img_progress.height()-1)*Current << endl;
//     cout << "pixel_y" << img_progress.width()/2 << endl;
     QColor c(rgb);
     qss.append(QString(",stop:%1  rgb(%2,%3,%4)").arg(Current).arg(c.red()).arg(c.green()).arg(c.blue()));
    }
    qss.append(");}");
//    cout << qss.toStdString().data()<< endl;
    brake_status_pctg->setStyleSheet(qss);
    brake_status_pctg->setValue(double(brake_sub)*100);
    brake_status_label->setText(QString("brake    %1%").arg(brake_sub*100));
    brake_status_label->setMinimumWidth(40);
}

// display throttle status by time trigger
void MonitorToolkitDisplay::steer_status()
{
    QMatrix matrix;
    matrix.rotate(steer_sub*100);
    steer_angle_label->setAlignment(Qt::AlignCenter);
    steer_angle_label->setPixmap(pixmap.transformed(matrix,Qt::SmoothTransformation));
}


// CarControlCallback
void MonitorToolkitDisplay::GetCarControlCallback(const autodrive_msgs::Control::ConstPtr &_msg)
{
    throttle_sub = _msg->throttle;
    brake_sub = _msg->brake;
    steer_sub = _msg->steer_target;
}


// change shape of a picture which loaded by pixmap
QPixmap MonitorToolkitDisplay::PixmapToRound(QPixmap &src, int radius)
{
    if (src.isNull())
    {
        return QPixmap();
    }
    QSize size(2*radius, 2*radius);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), 99, 99);
    QPixmap image = src.scaled(size);
    image.setMask(mask);
    return image;
}



//void LogSimDisplay::add_trajectory_points() {
//    nh_.setParam("/click_type", "add_trajectory_points");
//}

//void LogSimDisplay::add_trigger_point() {
//    nh_.setParam("/click_type", "add_trigger_point");
//}

//void LogSimDisplay::add() {
//    nh_.setParam("/change", "add");
//    QTime _Timer = QTime::currentTime().addMSecs(1000);
//    while( QTime::currentTime() < _Timer ) {}
//    update_ui();
//}

//void LogSimDisplay::delete_car() {
//    nh_.setParam("/changeid", id_cBox->currentText().toStdString());
//    nh_.setParam("/change", "delete");
//    QTime _Timer = QTime::currentTime().addMSecs(1000);
//    while( QTime::currentTime() < _Timer ) {}
//    update_ui();
//}

//void LogSimDisplay::change_shape() {
//    nh_.setParam("/changeid", id_cBox->currentText().toStdString());
//    nh_.setParam("/change", "shape");
//    QTime _Timer = QTime::currentTime().addMSecs(1000);
//    while( QTime::currentTime() < _Timer ) {}
//    update_ui();
//}

//void LogSimDisplay::change_trajectory() {
//    nh_.setParam("/changeid", id_cBox->currentText().toStdString());
//    nh_.setParam("/change", "trajectory");
//    QTime _Timer = QTime::currentTime().addMSecs(1000);
//    while( QTime::currentTime() < _Timer ) {}
//    update_ui();
//}

//void LogSimDisplay::change_trigger() {
//    nh_.setParam("/changeid", id_cBox->currentText().toStdString());
//    nh_.setParam("/changeR", lineChangeR->text().toStdString());
//    nh_.setParam("/change", "trigger");
//    QTime _Timer = QTime::currentTime().addMSecs(1000);
//    while( QTime::currentTime() < _Timer ) {}
//    update_ui();
//}

//void LogSimDisplay::change_speed() {
//    nh_.setParam("/changeid", id_cBox->currentText().toStdString());
//    nh_.setParam("/changeSpeed", lineChangeSpeed->text().toStdString());
//    nh_.setParam("/change", "speed");
//    QTime _Timer = QTime::currentTime().addMSecs(1000);
//    while( QTime::currentTime() < _Timer ) {}
//    update_ui();
//}

//int LogSimDisplay::readXML(const string xmlPath) {
//    if(doc.LoadFile(xmlPath.c_str()) != 0)
//    {
//        cout<<"load xml file failed"<<endl;
//        return 0;
//    }
//    id_list.clear();
//    XMLElement* obstacleNode=doc.RootElement();
//    XMLElement* carNode = obstacleNode->FirstChildElement("routecar");
//    while(carNode != NULL)
//    {
//        id_list.push_back(std::atoi( (carNode->FirstChildElement("id"))->GetText() ));
//        carNode = carNode->NextSiblingElement();
//    }
//    return doc.SaveFile(xmlPath.c_str());
//}

//void LogSimDisplay::update_ui() {
//    readXML(xml_path);
//    visualXML(xml_path);
//    id_cBox->clear();
//    for (int i = 0; i < id_list.size(); i++) {
//        id_cBox->addItem(to_string(id_list[i]).c_str());
//    }
//}

//void LogSimDisplay::update_visual() {
//    visualXML(xml_path);
//}

//int LogSimDisplay::visualXML(const string xmlPath) {
//    if(doc.LoadFile(xmlPath.c_str()) != 0)
//    {
//        cout<<"load xml file failed"<<endl;
//        return 0;
//    }
//    XMLElement* obstacleNode=doc.RootElement();
//    XMLElement* carNode = obstacleNode->FirstChildElement("routecar");
//    visualization_msgs::MarkerArray routecar_configs;
//    while(carNode != NULL)
//    {
////part 1
//        visualization_msgs::Marker routecar_config_path;
//        routecar_config_path.header.frame_id = "/map";
//        routecar_config_path.header.stamp = ros::Time::now();
//        routecar_config_path.ns = "zz";
//        routecar_config_path.id = std::atoi( (carNode->FirstChildElement("id"))->GetText() );
//        routecar_config_path.action = visualization_msgs::Marker::ADD;
//        routecar_config_path.scale.x = routecar_config_path.scale.y = routecar_config_path.scale.z = 0.2;
//        routecar_config_path.color.a = 1.0;
//        routecar_config_path.color.r = 1.0;
//        routecar_config_path.color.g = 1.0;
//        routecar_config_path.color.b = 0.0;
//        routecar_config_path.type = visualization_msgs::Marker::LINE_STRIP;
//        routecar_config_path.pose.orientation.w = 1.0;

//        XMLElement* trajNode = carNode->FirstChildElement("trajectory");
//        XMLElement* pointNode = trajNode->FirstChildElement("point");
//        while (pointNode != NULL) {
//            geometry_msgs::Point traj_point;
//            traj_point.x = std::atof( pointNode->Attribute("x") );
//            traj_point.y = std::atof( pointNode->Attribute("y") );
//            traj_point.z = 5.0;
//            routecar_config_path.points.push_back(traj_point);
//            pointNode = pointNode->NextSiblingElement();
//        }
//        routecar_configs.markers.push_back(routecar_config_path);

////part 2
//        visualization_msgs::Marker routecar_config_trigger;
//        routecar_config_trigger.header.frame_id = "/map";
//        routecar_config_trigger.header.stamp = ros::Time::now();
//        routecar_config_trigger.ns = "zz";
//        routecar_config_trigger.id = std::atoi( (carNode->FirstChildElement("id"))->GetText() ) + 1000;
//        routecar_config_trigger.action = visualization_msgs::Marker::ADD;
//        routecar_config_trigger.scale.x = 1.0;
//        routecar_config_trigger.scale.y = 1.0;
//        routecar_config_trigger.scale.z = 1.0;
//        routecar_config_trigger.color.a = 0.4;
//        routecar_config_trigger.color.r = 1.0;
//        routecar_config_trigger.color.g = 1.0;
//        routecar_config_trigger.color.b = 0.0;
//        routecar_config_trigger.type = visualization_msgs::Marker::SPHERE;
//        routecar_config_trigger.pose.orientation.w = 1.0;

//        visualization_msgs::Marker routecar_config_id;
//        routecar_config_id.header.frame_id = "/map";
//        routecar_config_id.header.stamp = ros::Time::now();
//        routecar_config_id.ns = "zz";
//        routecar_config_id.id = std::atoi( (carNode->FirstChildElement("id"))->GetText() ) + 2000;
//        routecar_config_id.action = visualization_msgs::Marker::ADD;
//        routecar_config_id.scale.z = 1.0;
//        routecar_config_id.color.a = 1.0;
//        routecar_config_id.color.r = 1.0;
//        routecar_config_id.color.g = 1.0;
//        routecar_config_id.color.b = 0.0;
//        routecar_config_id.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
//        routecar_config_id.pose.orientation.w = 1.0;

//        XMLElement* triggerNode = carNode->FirstChildElement("trigger");

//        routecar_config_trigger.pose.position.x  = std::atof( triggerNode->Attribute("x") );
//        routecar_config_trigger.pose.position.y  = std::atof( triggerNode->Attribute("y") );
//        routecar_config_trigger.pose.position.z  = std::atof( triggerNode->Attribute("z") );
//        routecar_config_trigger.scale.x = 2 * std::atof( triggerNode->Attribute("radius") );//diameters
//        routecar_config_trigger.scale.y = 2 * std::atof( triggerNode->Attribute("radius") );
//        routecar_config_trigger.scale.z = 0.1;
//        routecar_configs.markers.push_back(routecar_config_trigger);

//        routecar_config_id.pose.position.x  = std::atof( triggerNode->Attribute("x") );
//        routecar_config_id.pose.position.y  = std::atof( triggerNode->Attribute("y") );
//        routecar_config_id.pose.position.z  = 5.0;
//        routecar_config_id.scale.z = 2.0;
//        // routecar_config_id.scale.z = std::atof( triggerNode->Attribute("radius") );
//        routecar_config_id.text = carNode->FirstChildElement("id")->GetText();
//        routecar_configs.markers.push_back(routecar_config_id);

//        carNode = carNode->NextSiblingElement();
//    }
//    pub_routecar.publish(routecar_configs);
//    return doc.SaveFile(xmlPath.c_str());
//}

} // namespace soc_panel_display


// Tell pluginlib about this class.  Every class which should be
// loadable by pluginlib::ClassLoader must have these two lines
// compiled in its .cpp file, outside of any namespace scope.
#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(MonitorToolkit_display::MonitorToolkitDisplay, rviz::Panel)
// END_TUTORIAL
