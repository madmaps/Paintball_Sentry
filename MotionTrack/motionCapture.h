#pragma once
#ifndef __MOTIONCAPTURE__
#define __MOTIONCAPTURE__
#include "frameManager.h"
#include "frameAnalyzer.h"
#include "frame.h"
#include "twoDTargets.h"
#include <vector>

class motionCapture
{
public:
	//Constructers
	motionCapture(void); //Default
	motionCapture(const motionCapture& src); //Copy
	motionCapture(motionCapture&& src); //Move

	//Operator Overloading
	virtual motionCapture& operator=(const motionCapture& rhs); //Assignment
	virtual motionCapture& operator=(motionCapture&& rhs); //Move Assignment
	//virtual std::vector<twoDTargets>& operator>>(frame& inFrame);
	virtual std::list<twoDTargets>& operator>>(frame& inFrame);

	//Getters
	virtual double getUnitSize() const;
	virtual double getUnitResolution() const;
	virtual double getPixelResolution() const;
	virtual int getKeyFrameUpdateRate() const;
	virtual double getKeyFrameUpdateResolution() const;
	virtual double getKeyFrameReset() const;
	virtual double getCurrentFrameMovement() const;
    virtual bool getDebugMode() const;
    virtual bool getViewFrameMode() const;

	//Setters
	virtual void setUnitSize(const double& inUnitSize);
	virtual void setUnitResolution(const double& inUnitResolution);
	virtual void setPixelResolution(const double& inPixelResolution);
	virtual void setKeyFrameUpdateRate(const int& inKeyFrameUpdateRate);
	virtual void setKeyFrameUpdateResolution(const double& inKeyFrameUpdateResolution);
	virtual void setKeyFrameReset(const double& inKeyFrameReset);
    virtual void setDebugMode(const bool& inDebugMode);
    virtual void setViewFrameMode(const bool& inViewFrameMode);
    virtual void setMaskFrame(const frame& inMaskFrame);

	//Public Methods
	virtual void disableKeyFrameUpdate();
	virtual void enableKeyFrameUpdate();
    virtual frame* getDebugFrame();
    virtual frame* getViewFrame();
    virtual bool willResetNextFrame() const;
    virtual void forceReset();


	//Destructor
	virtual ~motionCapture(void);

protected:
	//Members
	frameManager FM;
	frameAnalyzer FA;

	//Helper Methods
	virtual void cleanup();
};

#endif
