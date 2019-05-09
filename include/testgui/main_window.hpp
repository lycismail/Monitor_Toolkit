/**
 * @file /include/testgui/main_window.hpp
 *
 * @brief Qt based gui for testgui.
 *
 * @date November 2010
 **/
#ifndef testgui_MAIN_WINDOW_H
#define testgui_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui/QMainWindow>
#include "ui_main_window.h"
#include "qnode.hpp"
#include <QTimer>
#include "sensor_status.hpp"
#include <iostream>
#include "dialog_sensorcheck.hpp"
using namespace std;

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace testgui {

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(int argc, char** argv, QWidget *parent = 0);
	~MainWindow();

	void ReadSettings(); // Load up qt program settings at startup
	void WriteSettings(); // Save qt program settings when closing

	void closeEvent(QCloseEvent *event); // Overloaded function
	void showNoMasterMessage();
    void set_ping_status_btn();
    QTimer * output_t;
    QTimer * hz_t;
    MyThread sensor_ping;

    QPixmap pixmap;
    QImage img_progress;
    QPixmap PixmapToRound(QPixmap &src, int radius); //for steer picture change shape from rect to round


    //Dialog_sensorcheck * a;
    //void show_RTK_status();

public Q_SLOTS:
	/******************************************
	** Auto-connections (connectSlotsByName())
	*******************************************/
	void on_actionAbout_triggered();
	void on_button_connect_clicked(bool check );
	void on_checkbox_use_environment_stateChanged(int state);
    void show_throttle();

    /******************************************
    ** Manual connections
    *******************************************/
//    void updateLoggingView(); // no idea why this can't connect automatically

    void on_pushButton_clicked();

    void on_pingallsensor_clicked();


    void show_G4_NET_status();
    void show_IBEO_ECU_status();
    void show_VLP16FL_status();
    void show_VLP16FR_status();
    void show_VLP16R_status();
    void show_VLP16L_status();
    void show_VLP16REAR_status();
    void show_SICK_status();
    void show_PANDAR_status();
    void show_CAN_status();
    void show_RTK_status();

    void show_sensor_hz();
    void show_sensor_msgs();

    void error_beep();

//    void throttle_ProBar();
//    void brake_ProBar();
//    void steer_picshow();


    void on_actionSensors_triggered();

private:
	Ui::MainWindowDesign ui;
	QNode qnode;
};

}  // namespace testgui

#endif // testgui_MAIN_WINDOW_H
