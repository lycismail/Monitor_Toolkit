/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QMessageBox>
#include "../include/testgui/main_window.hpp"
#include "../include/testgui/dialog_sensorcheck.hpp"
#include <iostream>
#include "ui_dialog_sensorcheck.h"
#include <ros/package.h>
#include <string.h>
using namespace std;
extern "C"
{
}


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace testgui {

using namespace Qt;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent)
	, qnode(argc,argv)
{
    cout << "-10" << endl;
    QTimer * output_t = new QTimer(this);
    QTimer * hz_t = new QTimer(this);
//    a = new Dialog_sensorcheck;
    connect(output_t, SIGNAL(timeout()), this, SLOT(show_throttle()));
    connect(output_t, SIGNAL(timeout()), this, SLOT(show_G4_NET_status()));
    connect(output_t, SIGNAL(timeout()), this, SLOT(show_IBEO_ECU_status()));
    connect(output_t, SIGNAL(timeout()), this, SLOT(show_VLP16FL_status()));
    connect(output_t, SIGNAL(timeout()), this, SLOT(show_VLP16FR_status()));
    connect(output_t, SIGNAL(timeout()), this, SLOT(show_VLP16R_status()));
    connect(output_t, SIGNAL(timeout()), this, SLOT(show_VLP16L_status()));
    connect(output_t, SIGNAL(timeout()), this, SLOT(show_VLP16REAR_status()));
    connect(output_t, SIGNAL(timeout()), this, SLOT(show_SICK_status()));
    connect(output_t, SIGNAL(timeout()), this, SLOT(show_PANDAR_status()));
    connect(output_t, SIGNAL(timeout()), this, SLOT(show_CAN_status()));
    connect(output_t, SIGNAL(timeout()), this, SLOT(show_RTK_status()));
    connect(hz_t, SIGNAL(timeout()), this, SLOT(show_sensor_hz()));
    connect(output_t, SIGNAL(timeout()), this, SLOT(show_sensor_msgs()));
//    connect(output_t, SIGNAL(timeout()), this, SLOT(qnode.steer_status()));
//    connect(output_t, SIGNAL(timeout()), this, SLOT(qnode.brake_status()));
//    connect(output_t, SIGNAL(timeout()), this, SLOT(qnode.throttle_status()));

    sensor_ping.start();

    cout << "-30" << endl;
    output_t->start(500);
    hz_t->start(1000);

	ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.
    QObject::connect(ui.actionAbout_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt())); // qApp is a global variable for the application
    ReadSettings();
	setWindowIcon(QIcon(":/images/icon.png"));
    //ui.tabWidget->setCurrentIndex(0); // ensure the first tab is showing - qt-designer should have this already hardwired, but often loses it (settings?).
    QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));




    /*********************
    ** Auto Start
    **********************/
    if ( ui.checkbox_remember_settings->isChecked() ) {
        on_button_connect_clicked(true);
    }
}

MainWindow::~MainWindow() {}

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/

void MainWindow::show_throttle()
{
    //cout << "jinru" << endl;
    //ui.label_4->setText("555555");
    ui.label_4->setText(QString::number(qnode.throttle_sub,10,4));
}

void MainWindow::showNoMasterMessage() {
	QMessageBox msgBox;
	msgBox.setText("Couldn't find the ros master.");
	msgBox.exec();
    close();
}

/*
 * These triggers whenever the button is clicked, regardless of whether it
 * is already checked or not.
 */

void MainWindow::on_button_connect_clicked(bool check ) {
	if ( ui.checkbox_use_environment->isChecked() ) {
		if ( !qnode.init() ) {
			showNoMasterMessage();
		} else {
			ui.button_connect->setEnabled(false);
		}
	} else {
		if ( ! qnode.init(ui.line_edit_master->text().toStdString(),
				   ui.line_edit_host->text().toStdString()) ) {
			showNoMasterMessage();
		} else {
			ui.button_connect->setEnabled(false);
			ui.line_edit_master->setReadOnly(true);
			ui.line_edit_host->setReadOnly(true);
			ui.line_edit_topic->setReadOnly(true);
		}
	}
}


void MainWindow::on_checkbox_use_environment_stateChanged(int state) {
	bool enabled;
	if ( state == 0 ) {
		enabled = true;
	} else {
		enabled = false;
	}
	ui.line_edit_master->setEnabled(enabled);
	ui.line_edit_host->setEnabled(enabled);
	//ui.line_edit_topic->setEnabled(enabled);
}

/*****************************************************************************
** Implemenation [Slots][manually connected]
*****************************************************************************/

/**
 * This function is signalled by the underlying model. When the model changes,
 * this will drop the cursor down to the last line in the QListview to ensure
 * the user can always see the latest log message.
 */
//void MainWindow::updateLoggingView() {
//        ui.view_logging->scrollToBottom();
//}

/*****************************************************************************
** Implementation [Menu]
*****************************************************************************/

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, tr("About ..."),tr("<h2>PACKAGE_NAME Test Program 0.10</h2><p>Copyright Yujin Robot</p><p>This package needs an about description.</p>"));
}

/*****************************************************************************
** Implementation [Configuration]
*****************************************************************************/

void MainWindow::ReadSettings() {
    cout<< "jinru readsettings" << endl;
    QSettings settings("Qt-Ros Package", "testgui");
    //restoreGeometry(settings.value("geometry").toByteArray());
    //restoreState(settings.value("windowState").toByteArray());
    QString master_url = settings.value("master_url",QString("http://lyc-ThinkPad-T480:11311/")).toString();
    QString host_url = settings.value("host_url", QString("192.168.1.3")).toString();
    cout << master_url.toStdString().data()<< endl;
    //QString topic_name = settings.value("topic_name", QString("/chatter")).toString();
    ui.line_edit_master->setText(master_url);
    ui.line_edit_host->setText(host_url);
    //ui.line_edit_topic->setText(topic_name);
    bool remember = settings.value("remember_settings", false).toBool();
    ui.checkbox_remember_settings->setChecked(remember);
    bool checked = settings.value("use_environment_variables", false).toBool();
    ui.checkbox_use_environment->setChecked(checked);
    if ( checked ) {
    	ui.line_edit_master->setEnabled(false);
    	ui.line_edit_host->setEnabled(false);
    	//ui.line_edit_topic->setEnabled(false);
    }
}

void MainWindow::WriteSettings() {
    QSettings settings("Qt-Ros Package", "testgui");
    settings.setValue("master_url",ui.line_edit_master->text());
    settings.setValue("host_url",ui.line_edit_host->text());
    //settings.setValue("topic_name",ui.line_edit_topic->text());
    settings.setValue("use_environment_variables",QVariant(ui.checkbox_use_environment->isChecked()));
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    settings.setValue("remember_settings",QVariant(ui.checkbox_remember_settings->isChecked()));

}

void MainWindow::closeEvent(QCloseEvent *event)
{
	WriteSettings();
//    sensor_ping.stop;
	QMainWindow::closeEvent(event);
}

//void MainWindow::set_ping_status_btn()
//{
//    cout << "set size" << endl;
//    this->ui.net_status->setFixedSize(20,20);
//}

void MainWindow::on_pushButton_clicked()
{
    std::cout << "1234" << endl;
}

void MainWindow::on_pingallsensor_clicked()
{
    cout << "-40" << endl;
    //sensor_ping.run();
}

void MainWindow::show_G4_NET_status()
{
    int status = sensor_ping.net_flag[G4_NET];    
    if( status == 0)
    {
        this->ui.net_status->setStyleSheet("background-color: rgb(0, 255, 0)");
//        this->ui.net_status->setText("OK");
    }else{
        this->ui.net_status->setStyleSheet("background-color: rgb(255, 0, 0)");
//        this->ui.net_status->setText("ERROR");
    }

}
void MainWindow::show_IBEO_ECU_status()
{
    int status = sensor_ping.net_flag[IBEO_ECU];
    if( status == 0)
    {
        this->ui.ibeo_ECU_status->setStyleSheet("background-color: rgb(0, 255, 0) ");
    }else{
        this->ui.ibeo_ECU_status->setStyleSheet("background-color: rgb(255, 0, 0) ");
    }
}
void MainWindow::show_VLP16FL_status()
{
    int status = sensor_ping.net_flag[VLP16FL];
    if( status == 0)
    {
        this->ui.velodyne_frontleft_status->setStyleSheet("background-color: rgb(0, 255, 0) ");
    }else{
        this->ui.velodyne_frontleft_status->setStyleSheet("background-color: rgb(255, 0, 0) ");
    }
}
void MainWindow::show_VLP16FR_status()
{
    int status = sensor_ping.net_flag[VLP16FR];
    if( status == 0)
    {
        this->ui.velodyne_frontright_status->setStyleSheet("background-color: rgb(0, 255, 0) ");
    }else{
        this->ui.velodyne_frontright_status->setStyleSheet("background-color: rgb(255, 0, 0) ");
    }
}
void MainWindow::show_VLP16R_status()
{
    int status = sensor_ping.net_flag[VLP16R];
    if( status == 0)
    {
        this->ui.velodyne_right_status->setStyleSheet("background-color: rgb(0, 255, 0) ");
    }else{
        this->ui.velodyne_right_status->setStyleSheet("background-color: rgb(255, 0, 0) ");
    }
}
void MainWindow::show_VLP16L_status()
{
    int status = sensor_ping.net_flag[VLP16L];
    if( status == 0)
    {
        this->ui.velodyne_left_status->setStyleSheet("background-color: rgb(0, 255, 0) ");
    }else{
        this->ui.velodyne_left_status->setStyleSheet("background-color: rgb(255, 0, 0) ");
    }
}
void MainWindow::show_VLP16REAR_status()
{
    int status = sensor_ping.net_flag[VLP16REAR];
    if( status == 0)
    {
        this->ui.velodyne_rear_status->setStyleSheet("background-color: rgb(0, 255, 0) ");
    }else{
        this->ui.velodyne_rear_status->setStyleSheet("background-color: rgb(255, 0, 0) ");
    }
}
void MainWindow::show_SICK_status()
{
    int status = sensor_ping.net_flag[SICK];
    if( status == 0)
    {
        this->ui.sick_status->setStyleSheet("background-color: rgb(0, 255, 0) ");
    }else{
        this->ui.sick_status->setStyleSheet("background-color: rgb(255, 0, 0) ");
    }
}
void MainWindow::show_PANDAR_status()
{
    int status = sensor_ping.net_flag[PANDAR];
    if( status == 0)
    {
        this->ui.pandar_status->setStyleSheet("background-color: rgb(0, 255, 0) ");
    }else{
        this->ui.pandar_status->setStyleSheet("background-color: rgb(255, 0, 0) ");
    }
}
void MainWindow::show_CAN_status()
{
    int status = sensor_ping.net_flag[CAN];
    if( status == 0)
    {
        this->ui.CAN_status->setStyleSheet("background-color: rgb(0, 255, 0) ");
    }else{
        this->ui.CAN_status->setStyleSheet("background-color: rgb(255, 0, 0) ");
    }
}
void MainWindow::show_RTK_status()
{
    int status = sensor_ping.net_flag[RTK];
    if( status == 0)
    {
        this->ui.GNSS_status->setStyleSheet("background-color: rgb(0, 255, 0) ");
    }else{
        this->ui.GNSS_status->setStyleSheet("background-color: rgb(255, 0, 0) ");
    }
}


QPixmap MainWindow::PixmapToRound(QPixmap &src, int radius)
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

void MainWindow::show_sensor_hz()
{
    for(int i=0; i<SENSER_MAX; i++)
    {
        qnode.msg_speed[i] = qnode.sensor_msg_count[i] - qnode.last_msg_count[i];
        qnode.last_msg_count[i] = qnode.msg_speed[i];
    }
    this->ui.ibeo_ECU_hz->setText(QString::number(qnode.msg_speed[IBEO_ECU],10));
    this->ui.velodyne_frontleft_hz->setText(QString::number(qnode.msg_speed[VLP16FL],10));
    this->ui.velodyne_frontright_hz->setText(QString::number(qnode.msg_speed[VLP16FR],10));
    this->ui.velodyne_right_hz->setText(QString::number(qnode.msg_speed[VLP16R],10));
    this->ui.velodyne_left_hz->setText(QString::number(qnode.msg_speed[VLP16L],10));
    this->ui.velodyne_rear_hz->setText(QString::number(qnode.msg_speed[VLP16REAR],10));
    this->ui.sick_hz->setText(QString::number(qnode.msg_speed[SICK],10));
    this->ui.pandar_hz->setText(QString::number(qnode.msg_speed[PANDAR],10));
    this->ui.CAN_hz->setText(QString::number(qnode.msg_speed[CAN],10));
    this->ui.GNSS_hz->setText(QString::number(qnode.msg_speed[RTK],10));
}
void MainWindow::show_sensor_msgs()
{
    this->ui.ibeo_ECU_msg->setText(QString::number(qnode.sensor_msg_count[IBEO_ECU],10));
    this->ui.velodyne_frontleft_msg->setText(QString::number(qnode.sensor_msg_count[VLP16FL],10));
    this->ui.velodyne_frontright_msg->setText(QString::number(qnode.sensor_msg_count[VLP16FR],10));
    this->ui.velodyne_right_msg->setText(QString::number(qnode.sensor_msg_count[VLP16R],10));
    this->ui.velodyne_left_msg->setText(QString::number(qnode.sensor_msg_count[VLP16L],10));
    this->ui.velodyne_rear_msg->setText(QString::number(qnode.sensor_msg_count[VLP16REAR],10));
    this->ui.sick_msg->setText(QString::number(qnode.sensor_msg_count[SICK],10));
    this->ui.pandar_msg->setText(QString::number(qnode.sensor_msg_count[PANDAR],10));
    this->ui.CAN_msg->setText(QString::number(qnode.sensor_msg_count[CAN],10));
    this->ui.GNSS_msg->setText(QString::number(qnode.sensor_msg_count[RTK],10));
}



}  // namespace testgui







void testgui::MainWindow::on_actionSensors_triggered()
{
    cout << "enter action" << endl;
    Dialog_sensorcheck a;
    //a.ui->label->setText(QString::number(qnode.throttle_sub,10,4));
    a.exec();
}
