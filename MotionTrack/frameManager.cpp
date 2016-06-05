#include "frameManager.h"

//Constructors
//Default
frameManager::frameManager(void):keyFrameUpdateRate(30),keyFrameReset(10),keyFrameUpdateResolution(20),keyFrameUpdateCounter(0),frameCounter(0),updateEnabled(1),currentFrameMovement(0),reset(0)
{
	compareFrames[0]=0;
	compareFrames[1]=0;
	differenceFrame=0;
	errorFrame=0;
    maskFrame=0;
}

//Copy
frameManager::frameManager(const frameManager& src):keyFrameUpdateRate(src.keyFrameUpdateRate),keyFrameReset(src.keyFrameReset),keyFrameUpdateResolution(src.keyFrameUpdateResolution),
    keyFrameUpdateCounter(src.keyFrameUpdateCounter),frameCounter(src.frameCounter),updateEnabled(src.updateEnabled),currentFrameMovement(src.currentFrameMovement),reset(src.reset)
{
	if(src.compareFrames[0]!=0)
	{
		compareFrames[0]=new frame(*src.compareFrames[0]);
	}
	else
	{
		compareFrames[0]=0;
	}
	if(src.compareFrames[1]!=0)
	{
		compareFrames[1]=new frame(*src.compareFrames[1]);
	}
	else
	{
		compareFrames[1]=0;
	}
	if(src.differenceFrame!=0)
	{
		differenceFrame=new frame(*src.differenceFrame);
	}
	else
	{
		differenceFrame=0;
	}
	if(src.errorFrame!=0)
	{
		errorFrame=new frame(*src.errorFrame);
	}
	else
	{
		errorFrame=0;
	}
    if(src.maskFrame!=0)
    {
        maskFrame = new frame(*src.maskFrame);
    }
    else
    {
        maskFrame=0;
    }
}

//Move
frameManager::frameManager(frameManager&& src):keyFrameUpdateRate(src.keyFrameUpdateRate),keyFrameReset(src.keyFrameReset),keyFrameUpdateResolution(src.keyFrameUpdateResolution),
    keyFrameUpdateCounter(src.keyFrameUpdateCounter),frameCounter(src.frameCounter),updateEnabled(src.updateEnabled),currentFrameMovement(src.currentFrameMovement),reset(src.reset)
{
	compareFrames[0]=src.compareFrames[0];
	compareFrames[1]=src.compareFrames[1];
	errorFrame=src.errorFrame;
    maskFrame=src.maskFrame;

	src.keyFrameUpdateRate=0;
	src.keyFrameReset=0;
	src.keyFrameUpdateResolution=0;
	src.keyFrameUpdateCounter=0;
	src.frameCounter=0;
	src.compareFrames[0]=0;
	src.compareFrames[1]=0;
	src.differenceFrame=0;
	src.errorFrame=0;
	src.currentFrameMovement=0;
    src.reset=0;
    src.maskFrame=0;
}

//Data
frameManager::frameManager(const int& inKeyFrameUpdateRate,const float& inKeyFrameUpdateResolution):keyFrameUpdateRate(inKeyFrameUpdateRate),keyFrameReset(0),
    keyFrameUpdateResolution(inKeyFrameUpdateResolution),keyFrameUpdateCounter(0),frameCounter(0),currentFrameMovement(0),reset(0)
{
	compareFrames[0]=0;
	compareFrames[1]=0;
	differenceFrame=0;
	errorFrame=0;
    maskFrame=0;
}

//Operator Overloading
//Assignment
frameManager& frameManager::operator=(const frameManager& rhs)
{
	if(this==&rhs)
	{
		return *this;
	}
	keyFrameUpdateRate=rhs.keyFrameUpdateRate;
	keyFrameReset=rhs.keyFrameReset;
	keyFrameUpdateResolution=rhs.keyFrameUpdateResolution;
	keyFrameUpdateCounter=rhs.keyFrameUpdateCounter;
	frameCounter=rhs.frameCounter;
	updateEnabled=rhs.updateEnabled;
	currentFrameMovement=rhs.currentFrameMovement;
    reset=rhs.reset;
	cleanup();
	if(rhs.compareFrames[0]!=0)
	{
		compareFrames[0]=new frame(*rhs.compareFrames[0]);
	}
    else
    {
        compareFrames[0]=0;
    }
	if(rhs.compareFrames[1]!=0)
	{
		compareFrames[1]=new frame(*rhs.compareFrames[1]);
	}
    else
    {
        compareFrames[1]=0;
    }
	if(rhs.differenceFrame!=0)
	{
		differenceFrame=new frame(*rhs.differenceFrame);
	}
    else
    {
        differenceFrame=0;
    }
	if(rhs.errorFrame!=0)
	{
		errorFrame=new frame(*rhs.errorFrame);
	}
    else
    {
        errorFrame=0;
    }
    if(rhs.maskFrame!=0)
    {
        maskFrame = new frame(*rhs.maskFrame);
    }
    else
    {
        maskFrame=0;
    }
	return *this;
}

//Move Assignment
frameManager& frameManager::operator=(frameManager&& rhs)
{
	if(this==&rhs)
	{
		return *this;
	}
	keyFrameUpdateRate=rhs.keyFrameUpdateRate;
	keyFrameReset=rhs.keyFrameReset;
	keyFrameUpdateResolution=rhs.keyFrameUpdateResolution;
	keyFrameUpdateCounter=rhs.keyFrameUpdateCounter;
	frameCounter=rhs.frameCounter;
	updateEnabled=rhs.updateEnabled;
    reset=rhs.reset;
	cleanup();
	compareFrames[0]=rhs.compareFrames[0];
	compareFrames[1]=rhs.compareFrames[1];
	differenceFrame=rhs.differenceFrame;
	errorFrame=rhs.errorFrame;
	currentFrameMovement=rhs.currentFrameMovement;
    maskFrame=rhs.maskFrame;

	rhs.keyFrameUpdateRate=0;
	rhs.keyFrameReset=0;
	rhs.keyFrameUpdateResolution=0;
	rhs.keyFrameUpdateCounter=0;
	rhs.frameCounter=0;
	rhs.compareFrames[0]=0;
	rhs.compareFrames[1]=0;
	rhs.differenceFrame=0;
	rhs.errorFrame=0;
	rhs.currentFrameMovement=0;
    rhs.reset=0;
    rhs.maskFrame=0;

	return *this;
}

frame& frameManager::operator>>(frame& inFrame)throw(std::logic_error,std::out_of_range,std::invalid_argument)
{
	//Create framePackage
	//Initialize
	if(frameCounter==0)
	{
		compareFrames[0]=&inFrame;
		inFrame.setKeyFrame(true);
		unsigned char* tempChar=new unsigned char[1];
		errorFrame=new frame(inFrame.getHeight(),inFrame.getWidth(),tempChar,inFrame.getSizeOfData(),0,false);
		differenceFrame=new frame();
	}
	else//Rotate compareFrames
	{
		if(inFrame.getHeight()!=errorFrame->getHeight() || inFrame.getWidth()!=errorFrame->getWidth() || inFrame.getSizeOfData()!=errorFrame->getSizeOfData())
		{
			cleanup();
			throw(std::invalid_argument("Invalid Frame"));
		}
		compareFrames[(frameCounter)%2]=&inFrame;
	}

	//Increase frame count and reset if it goes over 1000
	frameCounter++;
	if(frameCounter>1000)
	{
		frameCounter=1;
	}
	//Update keyframe if conditions are right
    if(frameCounter>1)
    {
        currentFrameMovement=compareCompareFrames();
    }
	if(frameCounter>1 && updateEnabled)
	{
        if(reset)
        {
            keyFrameUpdateCounter=keyFrameReset;
            reset=0;
        }
        if(currentFrameMovement<keyFrameUpdateResolution)
		{
			keyFrameUpdateCounter++;
		}
		else
		{
            //keyFrameUpdateCounter=keyFrameReset;
            reset=1;
		}
		if(keyFrameUpdateCounter>keyFrameUpdateRate)
		{
            inFrame.setKeyFrame(true);
			keyFrameUpdateCounter=0;
		}
	}
	frame* tempReturn=compareFrames[(frameCounter)%2];
	compareFrames[(frameCounter)%2]=0;

	return *tempReturn;
}



//Getters
int frameManager::getKeyFrameUpdateRate() const
{
	return keyFrameUpdateRate;
}

float frameManager::getKeyFrameUpdateResolution() const
{
	return keyFrameUpdateResolution;
}

double frameManager::getKeyFrameReset() const
{
	return keyFrameReset;
}

double frameManager::getCurrentFrameMovement() const
{
    return currentFrameMovement;
}

//Setters
void frameManager::setKeyFrameUpdateRate(const int& inKeyFrameUpdateRate)throw(std::out_of_range)
{
	if(inKeyFrameUpdateRate<0)
	{
		throw(std::out_of_range("keyFrameUpdateRate can not be a negative number"));
	}
	keyFrameUpdateRate=inKeyFrameUpdateRate;
}

void frameManager::setKeyFrameUpdateResolution(const float& inKeyFrameUpdateResolution)throw(std::out_of_range)
{
	if(inKeyFrameUpdateResolution<0)
	{
		throw(std::out_of_range("keyFrameUpdateResolution can not be a negative number"));
	}
	keyFrameUpdateResolution=inKeyFrameUpdateResolution;
}

void frameManager::setKeyFrameReset(const double& inKeyFrameReset)
{
	double temp1=keyFrameUpdateRate;
	double temp2=inKeyFrameReset;
	keyFrameReset=temp1*(temp2/100);
}

void frameManager::setMaskFrame(const frame& inMaskFrame)
{
    if(maskFrame!=0)
    {
        delete maskFrame;
        maskFrame=0;
    }
    maskFrame=new frame(inMaskFrame);
}

//Public Methods

void frameManager::disableUpdate()
{
	updateEnabled=0;
}

void frameManager::enableUpdate()
{
	updateEnabled=1;
}

bool frameManager::willResetNextFrame() const
{
    return reset;
}

void frameManager::forceReset()
{
    reset=1;
}

//Helper Methods
double frameManager::compareCompareFrames()throw(std::logic_error,std::out_of_range)
{
	//try
	//{
    compareFrames[0]->setPixelResolution(0);//keyFrameUpdateResolution);
	if(differenceFrame!=0)
	{
		delete differenceFrame;
		differenceFrame=0;
	}
    if(maskFrame!=0)
    {
        differenceFrame=&compareFrames[0]->difference(*compareFrames[1],*maskFrame);
    }
    else
    {
        differenceFrame=&(*compareFrames[0]-*compareFrames[1]);
    }
	//}
	//catch(std::out_of_range M)
	//{
	//	cleanup();
	//	throw M;
	//}
	//catch(std::logic_error M)
	//{
	//	cleanup();
	//	throw M;
	//}
	const unsigned char* differenceData=differenceFrame->getData();
	unsigned long adder=0;
	int i=0;
	while(i<compareFrames[0]->getSizeOfData())
	{
		adder+=differenceData[i++];
	}
	if(compareFrames[0]->getSizeOfData()<=0)
	{
		cleanup();
		throw(std::logic_error("Division by 0 in frameManager::compareCompareFrames"));
	}
    double temp=((double)adder*100)/((double)compareFrames[0]->getSizeOfData()*255);
	return temp;
}

//Destructor
frameManager::~frameManager(void)
{
	cleanup();
}

void frameManager::cleanup()
{
	if(compareFrames[0]!=0)
	{
		delete compareFrames[0];
		compareFrames[0]=0;
	}
	if(compareFrames[1]!=0)
	{
		delete compareFrames[1];
		compareFrames[1]=0;
	}
	if(differenceFrame!=0)
	{
		delete differenceFrame;
		differenceFrame=0;
	}
	if(errorFrame!=0)
	{
		delete errorFrame;
		errorFrame=0;
	}
    if(maskFrame!=0)
    {
        delete maskFrame;
        maskFrame=0;
    }
}

