#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <chrono>
#include <opencv2/opencv.hpp>
#include "MotionTrack/motionTrack.h"
#include "FireControl/fireControl.h"
#include "FireControl/drvMotorSim.h"
#include "FireControl/laserAim.h"
#include "CommandToSerial/commandToSerial.h"


typedef std::vector<threeDTarget> threeDTargetArray;

class Thread : public QThread
{
    Q_OBJECT
public:
    explicit Thread(QObject *parent = 0);
    void stop();
    bool isRunning() const;



signals:
    void changeText(QString inSpeed,QString inLocX,QString inLocY,QString inLocZ);
    void setDebugImage(frame* outFrame,frame* outFrame2);
    void setViewImage(frame* outFrame,frame* outFrame2);
    void setCameraMovement(const double& outCameraMovement0,const double& outCameraMovement1);
    void sendTargets(threeDTargetArray outTargets);
    void sendMotorXY(double outAngleX,double outAngleY);
    void sendDatabaseSize(int outDataSize);

public slots:
    void setDebugMode(const bool& inDebugMode);
    void setPixelCuttoff(const int& inPixelCuttoff);
    void setUnitCuttoff(const int& inUnitCuttoff);
    void yAccChange(int value);
    void sizeAccChange(int value);
    void colorAccChange(int value);
    void changeKeyFrameUpdate(bool inValue);
    void setCamera0Reset(const double& inValue);
    void setCamera1Reset(const double& inValue);
    void yShiftChanged(int value);
    void xShiftChanged(int value);
    void xCalibrationChanged(int value);
    void xCameraAngleChanged(int value);
    void yCalibrationChanged(int value);
    void yCameraAngleChanged(int value);
    void setTarget0Calibration(const double& value);
    void setTarget1Calibration(const double& value);
    void startCalibration();
    void changeTimeBuffer(int value);


protected:
    void run();
private:
    volatile bool stopped;
    double unitCuttoffVar;
    motionTrack MT;
    drvMotorSim motor;
    laserAim laser;
    fireControl FC;
    commandToSerial CTS;
    double timeBuffer;



};

#endif // THREAD_H
