#pragma once
#ifndef __AIM__
#define __AIM__
#include<math.h>

class aim
{
public:
	//Constructors
	aim(void);
	//Operator Overloading

	//Getters

	//Setters
	
	//Public Methods
	virtual double calculateX(const double& inMountX,const double& inMountY,const double& inMountZ,
							  const double& inTargetLocationX,const double& inTargetLocationY,const double& inTargetLocationZ) const=0;
	virtual double calculateY(const double& inMountX,const double& inMountY,const double& inMountZ,
							  const double& inTargetLocationX,const double& inTargetLocationY,const double& inTargetLocationZ) const=0;
	virtual double calculateTime(const double& inMountX,const double& inMountY,const double& inMountZ,
		                         const double& inTargetLocationX,const double& inTargetLocationY,const double& inTargetLocationZ) const=0;
	//Destructor
	virtual ~aim(void);

protected:
	//Members

	//Helper Methods
};


#endif
//#include "threeDTarget.h"
//#include <vector>
//#include "timer.h"
////#include "command.h"
//
//class aim
//{
//public:
//	//Constructors
//	aim(void);//Default
//	aim(const aim& src);//Copy
//	aim(aim&& src);//Move
//
//	//Operator Overloading
//	virtual aim& operator=(const aim& rhs);//Assignment
//	virtual aim& operator=(aim&& rhs);//Move Assignment
//	//virtual std::vector<command>& operator>>(const std::vector<threeDTarget>& inTargetList);
//
//	//Getters
//	virtual double getMotorSpeed() const;
//	virtual double getMotorLocationX() const;
//	virtual double getMotorLocationY() const;
//	virtual double getBufferTime() const;
//	virtual int getAvgBufferSize() const;
//	virtual int getOutLookCutOff() const;
//	virtual double getProjectileWeight() const;
//	virtual double getProjectileSize() const;
//	virtual int getProjectileShape() const;
//	virtual double getProjectileRotation() const;
//	virtual double getProjectileVelocity() const;
//	virtual double getBarametricPressure() const;
//	virtual double getWindSpeed() const;
//	virtual double getWindDirection() const;
//	virtual double getMountX() const;
//	virtual double getMountY() const;
//	virtual double getMountZ() const;
//	virtual double getCalibrationX() const;
//	virtual double getCalibrationY() const;
//	virtual int getTargetSelection() const;
//
//	//Setters
//	virtual void setMotorSpeed(const double& inMotorSpeed);
//	virtual void setMotorLocationX(const double& inMotorLocationX);
//	virtual void setMotorLocationY(const double& inMotorLocationY);
//	virtual void setBufferTime(const double& inBufferTime);
//	virtual void setAverageBufferSize(const int& inAverageBufferSize);
//	virtual void setOutLookCutOff(const int& inOutLookCutOff);
//	virtual void setProjectileWeight(const double& inProjectileWeight);
//	virtual void setProjectileSize(const double& inProjectileSize);
//	virtual void setProjectileShape(const int& inProjectileShape);
//	virtual void setProjectileRotation(const double& inProjectileRotation);
//	virtual void setProjectileVelocity(const double& inProjectileVelocity);
//	virtual void setBarametricPressure(const double& inBarametricPressure);
//	virtual void setWindSpeed(const double& inWindSpeed);
//	virtual void setWindDirection(const double& inWindDirection);
//	virtual void setMountX(const double& inMountX);
//	virtual void setMountY(const double& inMountY);
//	virtual void setMountZ(const double& inMountZ);
//	virtual void setCalibrationX(const double& inCalibrationX);
//	virtual void setCalibrationY(const double& inCalibrationY);
//	virtual void setTargetSelection(const int& inTargetSelection);
//
//
//	//Public Methods
//
//	//Destructor
//	virtual ~aim(void);
//	
//protected:
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
//
//	//Helper Methods
//	virtual int pickTarget();
//	virtual double calculateX();
//	virtual double calculateY();
//	virtual void cleanup();
//	
//
//};
//
//#endif
//
