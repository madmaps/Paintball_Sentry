#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

private slots:
    void on_pushButton_clicked();
    void on_yShiftSlider_valueChanged(int value);
    void on_xShiftSlider_valueChanged(int value);

    void on_xCalibrationSlider_valueChanged(int value);

    void on_cameraAngleSlider_valueChanged(int value);

    void on_yCalibrationSlider_valueChanged(int value);

    void on_yCameraAngleSlider_valueChanged(int value);

signals:
    void yShiftChanged(int value);
    void xShiftChanged(int value);
    void xCalibrationChanged(int value);
    void xCameraAngleChanged(int value);
    void yCalibrationChanged(int value);
    void yCameraAngleChanged(int value);

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
