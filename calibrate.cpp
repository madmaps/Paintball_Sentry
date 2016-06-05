#include "calibrate.h"
#include "ui_calibrate.h"

calibrate::calibrate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::calibrate)
{
    ui->setupUi(this);
}

calibrate::~calibrate()
{
    delete ui;
}

void calibrate::on_captureTarget0Button_clicked()
{
    QString temp = QString(ui->target0LocZ->text());
    double value=temp.toDouble();
    setTarget0Calibration(value);
}

void calibrate::on_captureTarget1Button_clicked()
{
    QString temp = QString(ui->target1LocZ->text());
    double value=temp.toDouble();
    setTarget1Calibration(value);
}

void calibrate::on_calibrateButton_clicked()
{
    startCalibration();
}
