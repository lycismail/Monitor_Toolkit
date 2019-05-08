#include "dialog_sensor.h"
#include "ui_dialog_sensor.h"

dialog_sensor::dialog_sensor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_sensor)
{
    ui->setupUi(this);
}

dialog_sensor::~dialog_sensor()
{
    delete ui;
}
