#pragma once
#ifndef __FRAMEMANAGER__
#define __FRAMEMANAGER__
#include <exception>
#include <stdexcept>
#include "frame.h"

class frameManager
{
public:
	//Constructors
	frameManager(void); //Default
	frameManager(const frameManager& src); //Copy
	frameManager(frameManager&& src); //Move
	frameManager(const int& inKeyFrameUpdateRate,const float& inKeyFrameUpdateResolution); //Data

	//Operator Overloading
	virtual frameManager& operator=(const frameManager& rhs); //Assignment
	virtual frameManager& operator=(frameManager&& rhs); //Move Assignment
	virtual frame& operator>>(frame& inFrame)throw(std::logic_error,std::out_of_range,std::invalid_argument); //Input image, Output framePackage

	//Getters
	virtual int getKeyFrameUpdateRate() const;
	virtual float getKeyFrameUpdateResolution() const;
	virtual double getKeyFrameReset() const;
	virtual double getCurrentFrameMovement() const;

	//Setters
	virtual void setKeyFrameUpdateRate(const int& inKeyFrameUpdateRate)throw(std::out_of_range);
	virtual void setKeyFrameUpdateResolution(const float& inKeyFrameUpdateResolution)throw(std::out_of_range);
	virtual void setKeyFrameReset(const double& inKeyFrameReset);
    virtual void setMaskFrame(const frame& inMaskFrame);

	//Public Methods
	virtual void disableUpdate();
	virtual void enableUpdate();
    virtual bool willResetNextFrame() const;
    virtual void forceReset();

	//virtual void updateKeyFrame(); //Make next Image in a keyFrame

	//Destructor
	virtual ~frameManager(void);

protected:
	//Members
	double currentFrameMovement;
	int keyFrameUpdateRate;//Number of frames that contain no movement until keyFrameUpdate
	double keyFrameReset;
	float keyFrameUpdateResolution;//Cutoff value when detecting movement for keyFrameUpdate
	int keyFrameUpdateCounter;//Counter for keyFrameUpdate
	int frameCounter;//Counter used to rotate frames
	frame* compareFrames[2];//Bitmap of 2 compareImages that Rotate and Compare to each other for keyFrameUpdate
	frame* differenceFrame;//Frame to store the difference between the 2 compareFrames
	frame* errorFrame;//Frame storing first image in information to check for errors
	bool updateEnabled;
    bool reset;
    frame* maskFrame;

	//Helper Methods
	virtual double compareCompareFrames()throw(std::logic_error,std::out_of_range);
	virtual void cleanup();
};

#endif
