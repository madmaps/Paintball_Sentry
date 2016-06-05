#include "units.h"

//Constructors
//Default
units::units(void):unitSize(64),unitResolution(20),imageWidth(0),imageHeight(0),unitWidth(0),unitHeight(0),trueUnitHeight(0),unitCount(0),unitArray(0),debugFrame(0),debugMode(0),maskFrame(0)
{
}

//Copy
units::units(const units& src):unitSize(src.unitSize),unitResolution(src.unitResolution),imageWidth(src.imageWidth),imageHeight(src.imageHeight),
    unitWidth(src.unitWidth),unitHeight(src.unitHeight),trueUnitHeight(src.trueUnitHeight),unitCount(src.unitCount),debugFrame(src.debugFrame),debugMode(src.debugMode),maskFrame(src.maskFrame)
{
	unitArray=new double[src.unitCount];
	for(int i=0;i<=unitCount-1;i++)
	{
		unitArray[i]=src.unitArray[i];
	}
}

//Move
units::units(units&& src)
{
	unitSize=src.unitSize;
	unitResolution=src.unitResolution;
	imageWidth=src.imageWidth;
	imageHeight=src.imageHeight;
	unitWidth=src.unitWidth;
	unitHeight=src.unitHeight;
	trueUnitHeight=src.trueUnitHeight;
	unitCount=src.unitCount;
	unitArray=src.unitArray;
    src.debugFrame->releaseData(*debugFrame);
    debugMode=src.debugMode;
    if(src.maskFrame!=0)
    {
        src.maskFrame->releaseData(*maskFrame);
    }
    else
    {
        maskFrame=0;
    }


	src.unitSize=0;
	src.unitResolution=0;
	src.imageWidth=0;
	src.imageHeight=0;
	src.unitWidth=0;
	src.unitHeight=0;
	src.trueUnitHeight=0;
	src.unitCount=0;
	src.unitArray=0;
    src.debugMode=0;
}

//Data
units::units(const double& inUnitSize,const double& inUnitResolution):unitSize(inUnitSize),unitResolution(inUnitResolution),imageWidth(0),imageHeight(0),unitWidth(0),unitHeight(0),trueUnitHeight(0),unitCount(0),unitArray(0),
debugFrame(0),debugMode(0),maskFrame(0)
{
}

//Operator Overloading
//Assignment
units& units::operator=(const units& rhs)
{
	if(&rhs==this)
	{
		return *this;
	}
	unitSize=rhs.unitSize;
	unitResolution=rhs.unitResolution;
	imageWidth=rhs.imageWidth;
	imageHeight=rhs.imageHeight;
	unitWidth=rhs.unitWidth;
	unitHeight=rhs.unitHeight;
	trueUnitHeight=rhs.trueUnitHeight;
	unitCount=rhs.unitCount;
    debugMode=rhs.debugMode;
	cleanup();

    debugFrame = new frame(*rhs.debugFrame);
    if(rhs.maskFrame!=0)
    {
        maskFrame=new frame(*rhs.maskFrame);
    }
    else
    {
        maskFrame=0;
    }
	unitArray=new double[rhs.unitCount];
	for(int i=0;i<=unitCount-1;i++)
	{
		unitArray[i]=rhs.unitArray[i];
	}

	return *this;
}

//Move Assignment
units& units::operator=(units&& rhs)
{
	if(&rhs==this)
	{
		return *this;
	}
	unitSize=rhs.unitSize;
	unitResolution=rhs.unitResolution;
	imageWidth=rhs.imageWidth;
	imageHeight=rhs.imageHeight;
	unitWidth=rhs.unitWidth;
	unitHeight=rhs.unitHeight;
	trueUnitHeight=rhs.trueUnitHeight;
	unitCount=rhs.unitCount;
    debugMode=rhs.debugMode;
	cleanup();
    rhs.debugFrame->releaseData(*debugFrame);
    if(rhs.maskFrame!=0)
    {
        rhs.maskFrame->releaseData(*maskFrame);
    }
    else
    {
        maskFrame=0;
    }
	unitArray=rhs.unitArray;

	rhs.unitSize=0;
	rhs.unitResolution=0;
	rhs.imageWidth=0;
	rhs.imageHeight=0;
	rhs.unitWidth=0;
	rhs.unitHeight=0;
	rhs.trueUnitHeight=0;
	rhs.unitCount=0;
	rhs.unitArray=0;

	return *this;
}

//Input
units& units::operator>>(frame& inFrame)
{
	if(inFrame.getHeight()!=imageHeight || inFrame.getWidth()!=imageWidth)
	{
		try
		{
			initialize(inFrame.getWidth(),inFrame.getHeight());
		}
		catch(std::out_of_range& e)
		{
			throw e;
		}
	}
	const unsigned char* newData=inFrame.getData();
    unsigned char* debugScreenShotData=0;
    if(debugMode)
    {
        debugScreenShotData = new unsigned char[inFrame.getSizeOfData()];
        for(unsigned long i=0; i<=inFrame.getSizeOfData();i++)
        {
            debugScreenShotData[i]=0;
        }
    }
    const unsigned char* maskData=0;
    if(maskFrame!=0)
    {
        maskData=maskFrame->getData();
    }
	unsigned long pixCounter=0,i=0,j=0,y=0,x=0;
	int total=0;
	int intUnitSize=unitSize;
	unitCount=0;
	while(i<trueUnitHeight)
	{
		j=0;
		while(j<unitSize)
		{
			y=0;
			while(y<unitHeight-1)
			{
				x=0;
				while(x<unitWidth)
				{
					unsigned long temp=i*unitSize*unitHeight*unitWidth*3+j*unitWidth*3+y*unitSize*unitWidth*3+x*3;
					for(unsigned long location=temp;location<=temp+2;location++)
					{
                        if(maskFrame!=0)
                        {
                            if(maskData[location]>128)
                            {
                                pixCounter++;
                            }
                            else
                            {
                                pixCounter++;
                                total+=newData[location];
                            }
                        }
                        else
                        {
                            pixCounter++;
                            total+=newData[location];
                        }
					}
					x++;
				}
				y++;
			}
			unitArray[i*intUnitSize+j]=total/pixCounter;

			if(total/pixCounter>=unitResolution)
			{
				unitCount++;
                if(debugMode)
                {
                    y=0;
                    while(y<unitHeight-1)
                    {
                        x=0;
                        while(x<unitWidth)
                        {
                            unsigned long temp=i*unitSize*unitHeight*unitWidth*3+j*unitWidth*3+y*unitSize*unitWidth*3+x*3;
                            for(unsigned long location=temp;location<=temp+2;location++)
                            {
                                if(maskFrame!=0)
                                {
                                    if(maskData[location]<=128)
                                    {
                                        debugScreenShotData[location]=255;
                                    }
                                }
                                else
                                {
                                debugScreenShotData[location]=255;
                                }
                            }
                            x++;
                        }
                        y++;
                    }
                }

			}
            else
            {
                if(debugMode)
                {
                    y=0;
                    while(y<unitHeight-1)
                    {
                        x=0;
                        while(x<unitWidth)
                        {
                            unsigned long temp=i*unitSize*unitHeight*unitWidth*3+j*unitWidth*3+y*unitSize*unitWidth*3+x*3;
                            for(unsigned long location=temp;location<=temp+2;location++)
                            {
                                debugScreenShotData[location]=0;
                            }
                            x++;
                        }
                        y++;
                    }
                }
            }
			pixCounter=0;
			total=0;
			j++;
		}
		i++;
	}
    if(debugMode)
    {
        debugFrame = new frame(inFrame.getHeight(),inFrame.getWidth(),debugScreenShotData,inFrame.getSizeOfData(),inFrame.getTimeStamp(),0);
    }

	return *this;
}

//Getters
double units::getUnitSize() const
{
	return unitSize;
}

double units::getUnitResolution() const
{
	return unitResolution;
}

double* units::getUnitArray() const
{
	return unitArray;
}

int units::getUnitCount() const
{
	return unitCount;
}

double units::getTrueUnitHeight() const
{
	return trueUnitHeight;
}

double units::getUnitWidth() const
{
	return unitWidth;
}

double units::getUnitHeight() const
{
	return unitHeight;
}

bool units::getDebugMode() const
{
    return debugMode;
}

//Setters
void units::setUnitSize(const double& inUnitSize)throw(std::out_of_range)
{
	if(inUnitSize<=0)
	{
		cleanup();
		throw std::out_of_range("unitSize can not be a negitive Number");
	}
	unitSize=inUnitSize;
}

void units::setUnitResolution(const double& inUnitResolution)throw(std::out_of_range)
{
	if(inUnitResolution<0)
	{
		throw std::out_of_range("unitResolution can not be a negitive Number");
	}
	unitResolution=inUnitResolution;
}

void units::setDebugMode(const bool& inDebugMode)
{
    debugMode=inDebugMode;
}

void units::setMaskFrame(const frame &inMaskFrame)
{
    if(maskFrame!=0)
    {
        delete maskFrame;
        maskFrame=0;
    }
    maskFrame=new frame(inMaskFrame);
}

//Public Methods

frame* units::getDebugFrame()
{
    if(debugFrame!=0)
    {
        frame* returnFrame=new frame();
        debugFrame->releaseData(*returnFrame);
        return returnFrame;
    }
    return 0;
}

//Destructer
units::~units(void)
{
	cleanup();
}

//Helper Methods
//Initialize
void units::initialize(const int& inImageWidth,const int& inImageHeight)throw(std::out_of_range)
{
	if(inImageWidth<=0 || inImageHeight<=0)
	{
		throw std::out_of_range("inImageWidth or inImageHeight is less than or equal to 0");
	}
	imageWidth=inImageWidth;
	imageHeight=inImageHeight;
	if(unitSize<=0)
	{
		throw std::out_of_range("unitSize is less than or equal to 0");
	}
	unitWidth=imageWidth/unitSize;
	unitHeight=floor(imageHeight/unitSize);
	trueUnitHeight=unitSize+floor((imageHeight-(unitHeight*unitSize))/unitHeight);
	int divSquared=unitSize*trueUnitHeight;
	if(unitArray!=0)
	{
		delete[] unitArray;
		unitArray=0;
	}
    unitArray=new double[divSquared];
}

//Cleanup
void units::cleanup()
{
	if(unitArray!=0)
	{
		delete[] unitArray;
		unitArray=0;
	}
    if(debugFrame!=0)
    {
        delete debugFrame;
        debugFrame=0;
    }
    if(maskFrame!=0)
    {
        delete maskFrame;
        maskFrame=0;
    }
}
