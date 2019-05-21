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
#ifndef MONITORTOOLKIT_VISUAL_H
#define MONITORTOOLKIT_VISUAL_H

#ifndef Q_MOC_RUN
#include <ros/ros.h>
#include <ros/package.h>
#include <rviz/panel.h>
#endif

#include <string>
#include <Qt>
#include <QImage>
#include <QPainter>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTime>
#include <QTimer>
#include <QPushButton>
#include <QPalette>
#include <QPixmap>
#include <QRadioButton>
#include <QCheckBox>
#include <QListWidget>
#include <QTextEdit>
#include <QSpacerItem>
#include <QMessageBox>
#include <QButtonGroup>
#include <QDebug>
#include <QString>
#include <QDoubleSpinBox>
#include <QThread>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QApplication>
#include <QRadioButton>
#include <QProgressBar>
#include <pthread.h>
#include <ros/package.h>
#include <QWidget>
#include <QPainter>
#include <QPixmap>

#include <QSpacerItem>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>


#include <math.h>
#include "autodrive_msgs/Control.h"

//#include "MonitorToolkit_pthread.h"
#include "tinyxml2.h"
#include "visualization_msgs/MarkerArray.h"

using namespace Qt;
using namespace std;
using namespace tinyxml2;

namespace MonitorToolkit_display
{

class MonitorToolkitDisplay: public rviz::Panel
{

public:

Q_OBJECT

public:

    MonitorToolkitDisplay( QWidget* parent = 0 );
    ~MonitorToolkitDisplay();

    ros::Subscriber car_control_sub;//for throttle,brake and steer
    void GetCarControlCallback(const autodrive_msgs::Control::ConstPtr & _msg ); //call back from car control
    QPixmap PixmapToRound(QPixmap &src, int radius); //for steer picture change shape from rect to round

//    RenderThread3 render;

protected Q_SLOTS:
  // The control area, DriveWidget, sends its output to a Qt signal
  // for ease of re-use, so here we declare a Qt slot to receive it.
    void throttle_status();
    void brake_status();
    void steer_status();


protected:
  // The ROS publisher for the command velocity.
  // The ROS node handle.
    ros::NodeHandle nh1;
    QImage img_progress;
    QPixmap pixmap;
  //Qt parameter

    QTimer * update_timer;

    QProgressBar * throttle_status_pctg;
    QProgressBar * brake_status_pctg;
    QVBoxLayout * layout;
    QPushButton * startBtn;
    QLabel * brake_status_label;
    QLabel * throttle_status_label;
    QLabel * steer_angle_label;


    QWidget *centralWidget;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *lab_name;
    QLabel *lab_msgs_16;
    QSpacerItem *horizontalSpacer;
    QLabel *lab_msgs;
    QLabel *lab_hz;
    QLabel *lab_status;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_16;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *message1;
    QLabel *label_2;
    QLabel *label_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

};

} // end namespace rviz_plugin_tutorials

#endif
