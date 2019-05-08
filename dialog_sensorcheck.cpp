#include "dialog_sensorcheck.h"
#include "ui_dialog_sensorcheck.h"

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
