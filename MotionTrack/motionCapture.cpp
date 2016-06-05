#include "motionCapture.h"

//Constructors
//Default
motionCapture::motionCapture(void)
{
}

//Copy
motionCapture::motionCapture(const motionCapture& src):FM(src.FM),FA(src.FA)
{
}

//Move
motionCapture::motionCapture(motionCapture&& src):FM(src.FM),FA(src.FA)
{
}

//Operator OverLoading
motionCapture& motionCapture::operator=(const motionCapture& rhs)
{
	if(this==&rhs)
	{
		return *this;
	}
	FM=rhs.FM;
	FA=rhs.FA;
	return *this;
}

motionCapture& motionCapture::operator=(motionCapture&& rhs)
{
	if(this==&rhs)
	{
		return *this;
	}
	FM=rhs.FM;
	FA=rhs.FA;
	return *this;
}

/*std::vector<twoDTargets>& motionCapture::operator>>(frame& inFrame)
{
	return FA >> (FM >> inFrame);
}*/

std::list<twoDTargets>& motionCapture::operator>>(frame& inFrame)
{
    return FA >> (FM >> inFrame);
}

//Getters
double motionCapture::getUnitSize() const
{
	return FA.getUnitSize();
}

double motionCapture::getUnitResolution() const
{
	return FA.getUnitResolution();
}

double motionCapture::getPixelResolution() const
{
	return FA.getPixelResolution();
}

int motionCapture::getKeyFrameUpdateRate() const
{
	return FM.getKeyFrameUpdateRate();
}

double motionCapture::getKeyFrameUpdateResolution() const
{
	return FM.getKeyFrameUpdateResolution();
}

double motionCapture::getKeyFrameReset() const
{
	return FM.getKeyFrameReset();
}

double motionCapture::getCurrentFrameMovement() const
{
    return FM.getCurrentFrameMovement();
}

bool motionCapture::getDebugMode() const
{
    return FA.getDebugMode();
}

bool motionCapture::getViewFrameMode() const
{
    return FA.getViewFrameMode();
}
//Setters
void motionCapture::setUnitSize(const double& inUnitSize)
{
	FA.setUnitSize(inUnitSize);
}

void motionCapture::setUnitResolution(const double& inUnitResolution)
{
	FA.setUnitResolution(inUnitResolution);
}

void motionCapture::setPixelResolution(const double& inPixelResolution)
{
	FA.setPixelResolution(inPixelResolution);
}

void motionCapture::setKeyFrameUpdateRate(const int& inKeyFrameUpdateRate)
{
	FM.setKeyFrameUpdateRate(inKeyFrameUpdateRate);
}

void motionCapture::setKeyFrameUpdateResolution(const double& inKeyFrameUpdateResolution)
{
	FM.setKeyFrameUpdateResolution(inKeyFrameUpdateResolution);
}

void motionCapture::setKeyFrameReset(const double& inKeyFrameRateReset)
{
	FM.setKeyFrameReset(inKeyFrameRateReset);
}

void motionCapture::setDebugMode(const bool& inDebugMode)
{
    FA.setDebugMode(inDebugMode);
}

void motionCapture::setViewFrameMode(const bool& inViewFrameMode)
{
    FA.setViewFrameMode(inViewFrameMode);
}

void motionCapture::setMaskFrame(const frame& inMaskFrame)
{
    FA.setMaskFrame(inMaskFrame);
    FM.setMaskFrame(inMaskFrame);
}

//Public Methods
void motionCapture::disableKeyFrameUpdate()
{
	FM.disableUpdate();
}

void motionCapture::enableKeyFrameUpdate()
{
	FM.enableUpdate();
}

frame* motionCapture::getDebugFrame()
{
    return FA.getDebugFrame();
}

frame* motionCapture::getViewFrame()
{
    return FA.getCurrentFrame();
}

bool motionCapture::willResetNextFrame() const
{
    return FM.willResetNextFrame();
}

void motionCapture::forceReset()
{
    FM.forceReset();
}

//Destructor
motionCapture::~motionCapture(void)
{
	cleanup();
}

//Helper Methods
void motionCapture::cleanup()
{
}
