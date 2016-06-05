#pragma once
#ifndef __FIRECONTROL__
#define __FIRECONTROL__
#include "aim.h"
#include "../MotionTrack/threeDTarget.h"
#include "command.h"
#include <vector>
#include <deque>
#include <array>
#include <algorithm>
#include "motorSimulator.h"
#include <iostream>

class fireControl
{
public:
	//Constructors
	fireControl(void);//Default
	fireControl(const fireControl& src);//Copy
	fireControl(fireControl&& src);//Move

	//Operator Overloading
	virtual fireControl& operator=(const fireControl& rhs);//Assignment
	virtual fireControl& operator=(fireControl&& rhs);//Move Assignment

	//Getters
	virtual aim* getAim() const;
	virtual motorSimulator* getMotorSimulator() const;
	virtual double getMotorAngleX(const double& inTime) const;
	virtual double getMotorAngleY(const double& inTime) const;
	virtual double getOutLookCutOff() const;
	virtual double getMountX() const;
	virtual double getMountY() const;
	virtual double getMountZ() const;
	virtual double getCalibrationX() const;
	virtual double getCalibrationY() const;
	virtual int getTargetSelection() const;
	virtual int getMaxQueLength() const;
	virtual bool getOnHold() const;

	//Setters
	virtual void setAim(aim* inAim);
	virtual void setMotorSimulator(motorSimulator* inMotorSimulator);
	virtual void setMotorAngleX(const double& inMotorAngleX);
	virtual void setMotorAngleY(const double& inMotorAngleY);
	virtual void setBufferTime(const double& inBufferTime);
	virtual void setOutLookCutOff(const double& inOutLookCutOff);
	virtual void setMountX(const double& inMountX);
	virtual void setMountY(const double& inMountY);
	virtual void setMountZ(const double& inMountZ);
	virtual void setCalibrationX(const double& inCalibrationX);
	virtual void setCalibrationY(const double& inCalibrationY);
	virtual void setTargetSelection(const int& inTargetSelection);
	virtual void setMaxQueLength(const int& inMaxQueLength);

	//Public Methods
	virtual std::vector<command> process(std::vector<threeDTarget> inTargets,const double& inTimeStamp);
	virtual void inFinishedCommands(std::list<command> inFinishedCommands,const double& inTime);
	virtual void inRunningCommands(std::list<command> inRunningCommands,const double& inTime);
	virtual void hold();
	virtual void unHold();
    virtual double getCommandFinishTime() const;

	//Destructor
	virtual ~fireControl(void);

protected:
	//Members
	aim* aimControl;
	motorSimulator* motorFunctions;
	std::deque<threeDTarget> targetQue;
	double bufferTime;
	double outLookCutOff;
	double mountX;
	double mountY;
	double mountZ;
	double calibrationX;
	double calibrationY;
	int targetSelection;
	int maxQueLength;
	bool onHold;
    double lastCommandTime;

	//Helper Methods
	virtual void cleanup();
	virtual std::vector<threeDTarget>::iterator selectTarget(std::vector<threeDTarget>& inTargets) const;
	virtual void updateQue(std::vector<threeDTarget>::iterator inTarget,const double& inTimeStamp);
	virtual std::deque<threeDTarget>::iterator chooseTarget(const double& inTime);
	virtual std::array<double,3> calculateFireSolution(const std::deque<threeDTarget>::iterator inTarget,const double& inTime);
	virtual std::vector<command> packageCommands(const std::array<double,3>& inFireSolution,const double& inTime);
	virtual std::array<double,3> targetPredictor(const std::deque<threeDTarget>::iterator inTarget,const double& inTime);
	//virtual std::vector<command> motorInputDirector(const std::vector<command>& inCommands);
};

#endif

//	//Members
//	double motorSpeed;
//	double motorLocationX;
//	double motorLocationY;
//	double bufferTime;
//	int averageBufferSize;
//	int outLookCutOff;
//	double projectileWeight;
//	double projectileSize;
//	int projectileShape;
//	double projectileRotation;
//	double projectileVelocity;
//	double barametricPressure;
//	double windSpeed;
//	double windDirection;
//	double mountX;
//	double mountY;
//	double mountZ;
//	double calibrationX;
//	double calibrationY;
//	int targetSelection;
//	//std::vector<fireSolution> fireSolutionQue;
