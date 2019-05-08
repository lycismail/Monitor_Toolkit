#include "../include/testgui/dialog_sensorcheck.hpp"
#include "ui_dialog_sensorcheck.h"
#include "../include/testgui/qnode.hpp"
#include "../include/testgui/main_window.hpp"
//using namespace testgui;
Dialog_sensorcheck::Dialog_sensorcheck(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_sensorcheck)
{
    ui->setupUi(this);
}

Dialog_sensorcheck::~Dialog_sensorcheck()
{
    delete ui;
}
