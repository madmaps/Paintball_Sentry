#pragma once
#ifndef __UNITSTOTARGETS__
#define __UNITSTOTARGETS__
#include <vector>
#include <list>
#include <exception>
#include <stdexcept>
#include "frame.h"
#include "units.h"
#include "sections.h"
#include "twoDTargets.h"
#include "accumTarget.h"


class unitsToTargets
{
public:
	//Constructors
	unitsToTargets(void); //Default
	unitsToTargets(const unitsToTargets& src); //Copy
	unitsToTargets(unitsToTargets&& src); //Move

	//Operator Overloading
	virtual unitsToTargets& operator=(const unitsToTargets& rhs); //Assignment
	virtual unitsToTargets& operator=(unitsToTargets&& rhs); //Move Assignment

	//Getters
    virtual double getUnitResolution() const;

	//Setters
    virtual void setUnitResolution(const double& inUnitResolution);


	//Public Methods
	//std::vector<twoDTargets>& convert(const frame& inFrame,const units& inUnits);
	std::list<twoDTargets>& convert(const frame& inFrame,const units& inUnits);

	//Destructer
	virtual ~unitsToTargets(void);

protected:
	//Memebers
	int* sectionLookupTable;
	int sizeOfLookupTable;
	int sizeOfSections;
    double unitResolution;
	sections* theSections;

	//Helper Methods
	virtual void setupSections(const units& inUnits);
	virtual int findSectionLocation(const int& inX,const int& inY,const int& inUnitSize,const int& inUnitCount);
	virtual void cleanup();
};

#endif

