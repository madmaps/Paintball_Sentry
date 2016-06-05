#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QGLWidget>
#include <QListWidget>
#include "settings.h"
#include "thread.h"
#include "MotionTrack/frame.h"
#include "calibrate.h"

typedef std::vector<threeDTarget> threeDTargetArray;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void changeText(QString inSpeed,QString inLocX,QString inLocY,QString inLocZ);
    void on_checkBox_clicked();
    void setDebugImage(frame* inFrame,frame* inFrame2);
    void setViewImage(frame* inFrame,frame* inFrame2);
    void on_horizontalSlider_sliderMoved(int position);
    void on_horizontalSlider_2_sliderMoved(int position);
    void setCameraMovement(const double& inCameraMovement0,const double& inCameraMovement1);
    void sendTargetsToUI(threeDTargetArray inTargets);
    void on_yAccSlider_valueChanged(int value);
    void on_sizeAccSlider_valueChanged(int value);
    void on_colorAccSlider_valueChanged(int value);
    void on_updateKeyCheckbox_clicked(bool checked);
    void on_camera0ResetSlider_valueChanged(int value);
    void on_camera1ResetSlider_valueChanged(int value);
    void on_settingsButton_clicked();
    void on_autoCalibrateButton_clicked();
    void setDatabaseSize(int inSize);
    void setMotorAngleXY(double inMotorX,double inMotorY);


    void on_timeBuffer_valueChanged(int value);

signals:
    void setDebugMode(const bool& inDebugMode);
    void changePixelCuttoff(const int& inPixelCuttoff);
    void changeUnitCuttoff(const int& inUnitCuttoff);
    void changeColorAcc(int postion);
    void changeYAcc(int postion);
    void changeSizeAcc(int position);
    void changeKeyFrameUpdate(bool outUpdate);
    void changeCamera0Reset(const double& inValue);
    void changeCamera1Reset(const double& inValue);
    void changeTimeBuffer(const int inValue);


private:
    Ui::MainWindow *ui;
    Thread* behindThread;
    Settings* theSettings;
    calibrate* autoCalibrate;

};

#endif // MAINWINDOW_H
