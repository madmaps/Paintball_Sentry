#pragma once
#ifndef __MOTIONTRACK__
#define __MOTIONTRACK__
#include "frame.h"
#include "motionCapture.h"
#include "twoDTargets.h"
#include "threeDTarget.h"
#include <vector>
#include <math.h>
#include <iostream>
#include "targetPair.h"
#include "targetDatabase.h"
#include "calibration.h"



class motionTrack
{
public:
	//Constructers
	motionTrack(void); //Default
	motionTrack(const motionTrack& src); //Copy
	motionTrack(motionTrack&& src); //Move

	//Operator Overloading
	virtual motionTrack& operator=(const motionTrack& rhs); //Assignment
	virtual motionTrack& operator=(motionTrack&& rhs); //Move Assignment

	//Getters
	virtual double getUnitSize() const;
	virtual double getUnitResolution() const;
	virtual double getPixelResolution() const;
	virtual double getCameraDistance() const;
	virtual double getCameraAngleX() const;
	virtual double getCameraAngleY() const;
	virtual double getMinTargetSize() const;
	virtual double getMaxTargetSize() const;
	virtual double getColorAccuracy() const;
	virtual double getSizeAccuracy() const;
	virtual double getYLocationAccuracy() const;
	virtual double getCalibrateX() const;
	virtual double getCalibrateY() const;
	virtual double getYShift() const;
    virtual double getXShift() const;
    virtual double getWidth() const;
    virtual double getHeight() const;
	virtual int getKeyFrameUpdateRate() const;
	virtual double getKeyFrameUpdateResolution() const;
	virtual double getKeyFrameResetPercent() const;
	virtual double getMinTargetTime() const;
	virtual double getMaxTargetTime() const;
	virtual double getCurrentFrameMovementCamera0() const;
	virtual double getCurrentFrameMovementCamera1() const;
    virtual bool getDebugMode() const;
    virtual bool getViewFrameMode() const;
    virtual double getMaxTargetAverage()const;
    virtual double getMinGradeValue()const;
    virtual double getDataBaseColorAcc()const;
    virtual double getDataBaseLocationAcc()const;


	//Setters
	virtual void setUnitSize(const double& inUnitSize);
	virtual void setUnitReslolution(const double& inUnitResolution);
	virtual void setPixelResolution(const double& inPixelResolution);
	virtual void setCameraDistance(const double& inCameraDistance);
	virtual void setCameraAngleX(const double& inCameraAngleX);
	virtual void setCameraAngleY(const double& inCameraAngleY);
	virtual void setMinTargetSize(const double& inMinTargetSize);
	virtual void setMaxTargetSize(const double& inMaxTargetSize);
	virtual void setColorAccuracy(const double& inColorAccuracy);
	virtual void setSizeAccuracy(const double& inSizeAccuracy);
	virtual void setYLocationAccuracy(const double& inYLocationAccuracy);
	virtual void setCalibrateX(const double& inCalibrateX);
	virtual void setCalibrateY(const double& inCalibrateY);
	virtual void setYShift(const double& inYShift);
    virtual void setXShift(const double& inXShift);
	virtual void setKeyFrameUpdateRate(const int& inKeyFrameUpdateRate);
	virtual void setKeyFrameUpdateResolution(const double& inKeyFrameUpdateResolution);
	virtual void setKeyFrameResetPercent(const double& inKeyFrameResetPerenct);
	virtual void setKeyFrameUpdateResolutionCamera0(const double& inKeyFrameUpdateResolutionPercent);
	virtual void setKeyFrameUpdateResolutionCamera1(const double& inKeyFrameUpdateResolutionPercent);
	virtual void setMinTargetTime(const double& inMinTargetTime);
	virtual void setMaxTargetTime(const double& inMaxTargetTime);
    virtual void setDebugMode(const bool& inDebugMode);
    virtual void setViewFrameMode(const bool& inViewFrameMode);
    virtual void setMaxTargetAverage(const double& inMaxTargetAverage);
    virtual void setMinGradeValue(const double& inMinGradeValue);
    virtual void setDataBaseColorAcc(const double& inDataBaseColorAcc);
    virtual void setDataBaseLocationAcc(const double& inDataBaseLocationAcc);

	//Public Methods
	virtual void disableKeyFrameUpdate();
	virtual void enableKeyFrameUpdate();
	virtual std::vector<threeDTarget> analyze(frame* camera1NextFrame,frame* camera2NextFrame);
	virtual int getDatabaseSize();
    virtual frame* getCamera0DebugFrame();
    virtual frame* getCamera1DebugFrame();
    virtual frame* getCamera0ViewFrame();
    virtual frame* getCamera1ViewFrame();
    virtual void setCalibrationTarget(const int& target,const double& inLocX,const double& inLocY,const double& inLocZ);
    virtual void calibrate();
    virtual void clearCalibration();
    virtual void setCamera0MaskFrame(const frame& inMaskFrame);
    virtual void setCamera1MaskFrame(const frame& inMaskFrame);
    virtual int getNumberOfTargets()const;

	//Destructor
	virtual ~motionTrack(void);

protected:
	//Members
	targetDatabase dataBase;
	motionCapture camera1;
	motionCapture camera2;
    calibration autoCalibrate;
    cameraSettings camSettings;
    double minTargetSize;
    double maxTargetSize;
	double sizeAccuracy;
	double yLocationAccuracy;
	double colorAccuracy;

	//Helper Methods
};

#endif
