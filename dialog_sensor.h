#ifndef DIALOG_SENSOR_H
#define DIALOG_SENSOR_H

#include <QDialog>

namespace Ui {
class dialog_sensor;
}

class dialog_sensor : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_sensor(QWidget *parent = 0);
    ~dialog_sensor();

private:
    Ui::dialog_sensor *ui;
};

#endif // DIALOG_SENSOR_H
