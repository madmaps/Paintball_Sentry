#pragma once
#ifndef __UNITS__
#define __UNITS__
#include <exception>
#include <stdexcept>
#include <math.h>
#include "frame.h"
//#define __DEBUG__


class units
{
public:
	//Constructors
	units(void); //Default
	units(const units& src); //Copy
	units(units&& src); //Move
	units(const double& inUnitSize,const double& inUnitResolution); //Data
	
	//Operator Overloading
	virtual units& operator=(const units& rhs); //Assignment
	virtual units& operator=(units&& rhs); //Move Assignment
	virtual units& operator>>(frame& inFrame);

	//Getters
	virtual double getUnitSize() const;
	virtual double getUnitResolution() const;
	virtual double* getUnitArray() const;
	virtual int getUnitCount() const;
	virtual double getTrueUnitHeight() const;
	virtual double getUnitWidth() const;
	virtual double getUnitHeight() const;
    virtual bool getDebugMode() const;

	

	//Setters
	virtual void setUnitSize(const double& inUnitSize)throw(std::out_of_range);
	virtual void setUnitResolution(const double& unitResolution)throw(std::out_of_range);
    virtual void setDebugMode(const bool& inDebugMode);
    virtual void setMaskFrame(const frame& inMaskFrame);

	//Public Methods
    virtual frame* getDebugFrame();

	//Destructer
	virtual ~units(void);

protected:
	//Members
	double unitSize;
	double unitResolution;
	int imageWidth;
	int imageHeight;
	double unitWidth;
	double unitHeight;
	double trueUnitHeight;
	int unitCount;
	double* unitArray;
    frame* debugFrame;
    bool debugMode;
    frame* maskFrame;

	//Helper Methods
	virtual void initialize(const int& inImageWidth,const int& inImageHeight)throw(std::out_of_range);
	virtual void cleanup();
};

#endif

