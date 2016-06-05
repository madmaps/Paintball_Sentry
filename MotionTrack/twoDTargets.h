#pragma once
#ifndef __TWODTARGETS__
#define __TWODTARGETS__
#include <exception>
#include <stdexcept>

class twoDTargets
{
public:
	//Constructors
	twoDTargets(void); //Default
	twoDTargets(const twoDTargets& src); //Copy
	twoDTargets(twoDTargets&& src); //Move
	twoDTargets(const double& inLocationX,const double& inLocationY,const double& inSize,const double& inAvgColorRed,const double& inAvgColorGreen,const double& inAvgColorBlue,const double& inTimeStamp, const bool& inPossiblyIncomplete); //Data

	//Operator Overloading
	virtual twoDTargets& operator=(const twoDTargets& rhs); //Assignment
	virtual twoDTargets& operator=(twoDTargets&& rhs); //Move Assignment
	virtual bool operator>(const twoDTargets& rhs) const;// Greater Than
	virtual bool operator>=(const twoDTargets& rhs) const;
	virtual bool operator<(const twoDTargets& rhs) const;
	virtual bool operator<=(const twoDTargets& rhs) const;
    virtual bool isEqual(const twoDTargets& rhs,const double& inSizeAcc,const double& inYLocAcc,const double& inColorAcc) const;
    virtual twoDTargets operator+(const twoDTargets& rhs)const;
    virtual twoDTargets operator/(const double& rhs)const;

	//Getters
	virtual double getLocationX() const;
	virtual double getLocationY() const;
	virtual double getSize() const;
	virtual double getAvgColorRed() const;
	virtual double getAvgColorGreen() const;
	virtual double getAvgColorBlue() const;
	virtual double getTimeStamp() const;
	virtual bool getPossiblyIncomplete() const;

	//Setters
	virtual void setLocationX(const double& inLocationX);
	virtual void setLocationY(const double& inLocationY);
	virtual void setSize(const double& inSize);
	virtual void setAvgColorRed(const double& inAvgColorRed);
	virtual void setAvgColorGreen(const double& inAvgColorGreen);
	virtual void setAvgColorBlue(const double& inAvgColorBlue);
	virtual void setTimeStamp(const double& inTimeStamp);
	virtual void setPossiblyIncomplete(const bool& inPossiblyIncomplete);



	//Public Methods

	//Destructer
	virtual ~twoDTargets(void);

protected:
	//Members
	double locationX;
	double locationY;
	double size;
	double avgColorRed;
	double avgColorGreen;
	double avgColorBlue;
	double timeStamp;
	bool possiblyIncomplete;


	//Helper Methods
	virtual void cleanup();
};

#endif

