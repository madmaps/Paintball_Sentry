#pragma once
#ifndef __THREEDTARGET__
#define __THREEDTARGET__
#include <math.h>

enum{compareSize,compareDistance,compareSpeed};

class threeDTarget
{
public:
	//Constructor
	threeDTarget(void);//Default
	threeDTarget(const threeDTarget& src); //Copy
	threeDTarget(threeDTarget&& src);//Move
	threeDTarget(const double& inLocationX,const double& inLocationY,const double& inLocationZ,
		         const double& inAvgColorRed,const double& inAvgColorGreen,const double& inAvgColorBlue,
				 const double& inDirectionX,const double& inDirectionY,const double& inDirectionZ,
				 const double& inSize,const double& inSpeed,const double& inDistance, const double& inTimeStamp,const int& inCompareMode);//Data

	//Operator Overloading
	virtual threeDTarget& operator=(const threeDTarget& rhs);//Assignment
	virtual threeDTarget& operator=(threeDTarget&& rhs);//Move Assignment
	virtual bool operator>(const threeDTarget& rhs) const;//Greater Than
	virtual bool operator<(const threeDTarget& rhs) const;//Less Than
	virtual bool operator>=(const threeDTarget& rhs) const;//Greater Than or Equal too
	virtual bool operator<=(const threeDTarget& rhs) const;//Less Than or Equal too
	virtual bool operator==(const threeDTarget& rhs) const;//Equal too
	virtual threeDTarget operator+(const threeDTarget& rhs) const;
	virtual threeDTarget operator/(const double& rhs) const;

	//Getters
	virtual double getLocationX() const;
	virtual double getLocationY() const;
	virtual double getLocationZ() const;
	virtual double getAvgColorRed() const;
	virtual double getAvgColorGreen() const;
	virtual double getAvgColorBlue() const;
	virtual double getDirectionX() const;
	virtual double getDirectionY() const;
	virtual double getDirectionZ() const;
	virtual double getSize() const;
	virtual double getSpeed() const;
	virtual double getDistance() const;
	virtual double getTimeStamp() const;
	virtual int getCompareMode() const;

	//Setters
	virtual void setLocationX(const double& inLocationX);
	virtual void setLocationY(const double& inLocationY);
	virtual void setLocationZ(const double& inLocationZ);
	virtual void setAvgColorRed(const double& inAvgColorRed);
	virtual void setAvgColorGreen(const double& inAvgColorGreen);
	virtual void setAvgColorBlue(const double& inAvgColorBlue);
	virtual void setDirectionX(const double& inDirectionX);
	virtual void setDirectionY(const double& inDirectionY);
	virtual void setDirectionZ(const double& inDirectionZ);
	virtual void setSize(const double& inSize);
	virtual void setSpeed(const double& inSpeed);
	virtual void setDistance(const double& inDistance);
	virtual void setTimeStamp(const double& inTimeStamp);
	virtual void setCompareMode(const int& inCompareMode);

	//Public Methods
	virtual threeDTarget getTargetSpeedDirection(const threeDTarget& inPrevLocation)const;

	//Destructor
	virtual ~threeDTarget(void);

protected:
	//Members
	double locationX;
	double locationY;
	double locationZ;
	double avgColorRed;
	double avgColorGreen;
	double avgColorBlue;
	double directionX;
	double directionY;
	double directionZ;
	double size;
	double speed;
	double distance;
	double timeStamp;
	static int compareMode;


	//Helper Methods
	virtual double calculateSpeed(const double& inCurrentX,const double& inCurrentY,const double& inCurrentZ,const double& inPrevX,const double& inPrevY,const double& inPrevZ,const double& inCurrentTimeStamp, const double& inPrevTimeStamp)const;

	virtual void cleanup();
};

#endif

