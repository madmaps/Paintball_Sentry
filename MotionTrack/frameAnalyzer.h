#pragma once
#ifndef __FRAMEANALYZER__
#define __FRAMEANALYZER__
#include <exception>
#include <stdexcept>
#include "frame.h"
#include "sections.h"
#include "unitsToTargets.h"
#include "twoDTargets.h"

class frameAnalyzer
{
public:
	//Constructors
	frameAnalyzer(void); //Default
	frameAnalyzer(const frameAnalyzer& src); //Copy
	frameAnalyzer(frameAnalyzer&& src); //Move

	//Operator Overloading
	virtual frameAnalyzer& operator=(const frameAnalyzer& rhs); //Assignment
	virtual frameAnalyzer& operator=(frameAnalyzer&& rhs); //Move Assignment
	//virtual std::vector<twoDTargets>& operator>>(frame& inFrame);
    virtual std::list<twoDTargets>& operator>>(frame& inFrame);

	//Getters
	virtual double getUnitSize() const;
	virtual double getUnitResolution() const;
	virtual double getPixelResolution() const;
    virtual bool getDebugMode() const;
    virtual bool getViewFrameMode() const;

	//Setters
	virtual void setUnitSize(const double& inUnitSize);
	virtual void setUnitResolution(const double& inUnitResolution);
    virtual void setUttUnitResolution(const double& inUnitResolution);
	virtual void setPixelResolution(const double& inPixelResolution);
    virtual void setDebugMode(const bool& inDebugMode);
    virtual void setViewFrameMode(const bool& inViewFrame);
    virtual void setMaskFrame(const frame& inMaskFrame);

	//Public Methods
    virtual frame* getDebugFrame();
    virtual frame* getCurrentFrame();



	//Destructor
	virtual ~frameAnalyzer(void);

protected:
	//Members
	units analyzeUnits;
	unitsToTargets utt;
	frame* comparedFrame;
	frame* keyFrame;
	double pixelResolution;
    bool viewFrame;
    frame* returnFrame;


	//Helper Methods
	void cleanup();
};
#endif

