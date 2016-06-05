#ifndef CALIBRATE_H
#define CALIBRATE_H

#include <QDialog>

namespace Ui {
class calibrate;
}

class calibrate : public QDialog
{
    Q_OBJECT

public:
    explicit calibrate(QWidget *parent = 0);
    ~calibrate();
signals:
    void setTarget0Calibration(const double& value);
    void setTarget1Calibration(const double& value);
    void startCalibration();

private slots:
    void on_captureTarget0Button_clicked();

    void on_captureTarget1Button_clicked();

    void on_calibrateButton_clicked();

private:
    Ui::calibrate *ui;
};

#endif // CALIBRATE_H
