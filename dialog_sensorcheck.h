#ifndef DIALOG_SENSORCHECK_H
#define DIALOG_SENSORCHECK_H

#include <QDialog>

namespace Ui {
class Dialog_sensorcheck;
}

class Dialog_sensorcheck : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_sensorcheck(QWidget *parent = 0);
    ~Dialog_sensorcheck();

private:
    Ui::Dialog_sensorcheck *ui;
};

#endif // DIALOG_SENSORCHECK_H
