#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_pushButton_clicked()
{
    this->hide();
}

void Settings::on_yShiftSlider_valueChanged(int value)
{
    ui->yShiftLabel->setText(QString::number(value));
    yShiftChanged(value);
}

void Settings::on_xShiftSlider_valueChanged(int value)
{
    ui->xShiftLabel->setText(QString::number(value));
    xShiftChanged(value);
}

void Settings::on_xCalibrationSlider_valueChanged(int value)
{
    ui->xCalibrateLabel->setText(QString::number(value));
    xCalibrationChanged(value);
}

void Settings::on_cameraAngleSlider_valueChanged(int value)
{
    ui->cameraAngleLabel->setText(QString::number(value));
    xCameraAngleChanged(value);
}

void Settings::on_yCalibrationSlider_valueChanged(int value)
{
    ui->yCalibrateLabel->setText(QString::number(value));
    yCalibrationChanged(value);
}

void Settings::on_yCameraAngleSlider_valueChanged(int value)
{
    ui->yCameraAngleLabel->setText(QString::number(value));
    yCameraAngleChanged(value);
}
