#pragma once
#ifndef __SECTIONS__
#define __SECTIONS__
#include <vector>
#include "accumTarget.h"
#include "frame.h"
#include "units.h"

class sections
{
public:
	//Constructors
	sections(void); //Default
	sections(const sections& src); //Copy
	sections(sections&& src); //Move
	sections(float locX,float locY); //Data

	//Operator OverLoading
	virtual sections& operator=(const sections& rhs); //Assignment
	virtual sections& operator=(sections&& rhs); //Move Assignment
	

	//Getters
	virtual float getLocationX();
	virtual float getLocationY();
	virtual int getID();

	//Setters
	virtual void setLocationX(int locX);
	virtual void setLocationY(int locY);

	//Public Methods
	virtual void setSectionsLocation(int locX,int locY,sections& inSections);
	virtual sections& getSectionsLocation(const int& locX,const int& locY);
	virtual void getTarget(accumTarget& inTarget,const int& inID,const units& inUnit,const frame& inFrame);

	//Destructor
	virtual ~sections(void);


protected:
	//Members
	float locationX;
	float locationY;
	int ID;
	int count;
	sections* surroundingSections[9];
	
	//Helper Methods
	virtual void cleanup();

};

#endif