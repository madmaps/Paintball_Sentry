#include "threeDTarget.h"

//Static Members Initializer
int threeDTarget::compareMode=0;

//Constructors
//Default
threeDTarget::threeDTarget(void):locationX(0),locationY(0),locationZ(0),avgColorRed(0),avgColorGreen(0),avgColorBlue(0),directionX(0),directionY(0),directionZ(0),size(0),speed(0),distance(0),timeStamp(0)
{
}

//Copy
threeDTarget::threeDTarget(const threeDTarget& src):locationX(src.locationX),locationY(src.locationY),locationZ(src.locationZ),
	                                                avgColorRed(src.avgColorRed),avgColorGreen(src.avgColorGreen),avgColorBlue(src.avgColorBlue),
													directionX(src.directionX),directionY(src.directionY),directionZ(src.directionZ),
													size(src.size),speed(src.speed),distance(src.distance),timeStamp(src.timeStamp)
{
}

//Move
threeDTarget::threeDTarget(threeDTarget&& src):locationX(src.locationX),locationY(src.locationY),locationZ(src.locationZ),
	                                                avgColorRed(src.avgColorRed),avgColorGreen(src.avgColorGreen),avgColorBlue(src.avgColorBlue),
													directionX(src.directionX),directionY(src.directionY),directionZ(src.directionZ),
													size(src.size),speed(src.speed),distance(src.distance),timeStamp(src.timeStamp)
{
	src.locationX=0;
	src.locationY=0;
	src.locationZ=0;
	src.avgColorRed=0;
	src.avgColorGreen=0;
	src.avgColorBlue=0;
	src.directionX=0;
	src.directionY=0;
	src.directionZ=0;
	src.size=0;
	src.speed=0;
	src.distance=0;
	src.timeStamp=0;
}

//Data
threeDTarget::threeDTarget(const double& inLocationX,const double& inLocationY,const double& inLocationZ,
						   const double& inAvgColorRed,const double& inAvgColorGreen,const double& inAvgColorBlue,
				           const double& inDirectionX,const double& inDirectionY,const double& inDirectionZ,
				           const double& inSize,const double& inSpeed,const double& inDistance,const double& inTimeStamp,const int& inCompareMode):
						   locationX(inLocationX),locationY(inLocationY),locationZ(inLocationZ),
						   avgColorRed(inAvgColorRed),avgColorGreen(inAvgColorGreen),avgColorBlue(inAvgColorBlue),
						   directionX(inDirectionX),directionY(inDirectionY),directionZ(inDirectionZ),
						   size(inSize),speed(inSpeed),distance(inDistance),timeStamp(inTimeStamp)
{
}

//Operator Overloading
//Assignment
threeDTarget& threeDTarget::operator=(const threeDTarget& rhs)
{
	if(this==&rhs)
	{
		return *this;
	}
	locationX=rhs.locationX;
	locationY=rhs.locationY;
	locationZ=rhs.locationZ;
	avgColorRed=rhs.avgColorRed;
	avgColorGreen=rhs.avgColorGreen;
	avgColorBlue=rhs.avgColorBlue;
	directionX=rhs.directionX;
	directionY=rhs.directionY;
	directionZ=rhs.directionZ;
	size=rhs.size;
	speed=rhs.speed;
	distance=rhs.distance;
	timeStamp=rhs.timeStamp;
	return *this;
}

//Move Assignment
threeDTarget& threeDTarget::operator=(threeDTarget&& rhs)
{
	if(this==&rhs)
	{
		return *this;
	}
	locationX=rhs.locationX;
	locationY=rhs.locationY;
	locationZ=rhs.locationZ;
	avgColorRed=rhs.avgColorRed;
	avgColorGreen=rhs.avgColorGreen;
	avgColorBlue=rhs.avgColorBlue;
	directionX=rhs.directionX;
	directionY=rhs.directionY;
	directionZ=rhs.directionZ;
	size=rhs.size;
	speed=rhs.speed;
	distance=rhs.distance;
	timeStamp=rhs.timeStamp;

	rhs.locationX=0;
	rhs.locationY=0;
	rhs.locationZ=0;
	rhs.avgColorRed=0;
	rhs.avgColorGreen=0;
	rhs.avgColorBlue=0;
	rhs.directionX=0;
	rhs.directionY=0;
	rhs.directionZ=0;
	rhs.size=0;
	rhs.speed=0;
	rhs.distance=0;
	rhs.timeStamp=0;
	return *this;
}

//Greater Than
bool threeDTarget::operator>(const threeDTarget& rhs) const
{
	switch(compareMode)
	{
	case compareSize:
		return size>rhs.size;
		break;
	case compareDistance:
		return distance>rhs.distance;
		break;
	case compareSpeed:
		return speed>rhs.speed;
		break;
	default:
		return 0;
		break;
	}
	return 0;
}

//Less Than
bool threeDTarget::operator<(const threeDTarget& rhs) const
{
	switch(compareMode)
	{
	case compareSize:
		return size<rhs.size;
		break;
	case compareDistance:
		return distance<rhs.distance;
		break;
	case compareSpeed:
		return speed<rhs.speed;
		break;
	default:
		return 0;
		break;
	}
	return 0;
}

//Greater Than or Equal too
bool threeDTarget::operator>=(const threeDTarget& rhs) const
{
	switch(compareMode)
	{
	case compareSize:
		return size>=rhs.size;
		break;
	case compareDistance:
		return distance>=rhs.distance;
		break;
	case compareSpeed:
		return speed>=rhs.speed;
		break;
	default:
		return 0;
		break;
	}
	return 0;
}

//Less Than or Equal too
bool threeDTarget::operator<=(const threeDTarget& rhs) const
{
	switch(compareMode)
	{
	case compareSize:
		return size<=rhs.size;
		break;
	case compareDistance:
		return distance<=rhs.distance;
		break;
	case compareSpeed:
		return speed<=rhs.speed;
		break;
	default:
		return 0;
		break;
	}
	return 0;
}

//Equal too
bool threeDTarget::operator==(const threeDTarget& rhs) const
{
	switch(compareMode)
	{
	case compareSize:
		return size==rhs.size;
		break;
	case compareDistance:
		return distance==rhs.distance;
		break;
	case compareSpeed:
		return speed==rhs.speed;
		break;
	default:
		return 0;
		break;
	}
	return 0;
}

threeDTarget threeDTarget::operator+(const threeDTarget& rhs) const
{
    threeDTarget returnTarget;
    returnTarget.locationX=locationX+rhs.locationX;
    returnTarget.locationY=locationY+rhs.locationY;
    returnTarget.locationZ=locationZ+rhs.locationZ;
    returnTarget.avgColorBlue=avgColorBlue+rhs.avgColorBlue;
    returnTarget.avgColorRed=avgColorRed+rhs.avgColorRed;
    returnTarget.avgColorGreen=avgColorGreen+rhs.avgColorGreen;
    returnTarget.directionX=directionX+rhs.directionX;
    returnTarget.directionY=directionY+rhs.directionY;
    returnTarget.directionZ=directionZ+rhs.directionZ;
    returnTarget.size=size+rhs.size;
    returnTarget.speed=speed+rhs.speed;
    returnTarget.distance=distance+rhs.distance;
    returnTarget.timeStamp=timeStamp+rhs.timeStamp;
    returnTarget.compareMode=compareMode;
    return returnTarget;
}

threeDTarget threeDTarget::operator/(const double& rhs) const
{
    if(rhs==0)
    {
        return *this;
    }
    threeDTarget returnTarget;
    returnTarget.locationX=locationX/rhs;
    returnTarget.locationY=locationY/rhs;
    returnTarget.locationZ=locationZ/rhs;
    returnTarget.avgColorBlue=avgColorBlue/rhs;
    returnTarget.avgColorRed=avgColorRed/rhs;
    returnTarget.avgColorGreen=avgColorGreen/rhs;
    returnTarget.directionX=directionX/rhs;
    returnTarget.directionY=directionY/rhs;
    returnTarget.directionZ=directionZ/rhs;
    returnTarget.size=size/rhs;
    returnTarget.speed=speed/rhs;
    returnTarget.distance=distance/rhs;
    returnTarget.timeStamp=timeStamp/rhs;
    returnTarget.compareMode=compareMode;
    return returnTarget;
}


//Getters
double threeDTarget::getLocationX() const
{
	return locationX;
}

double threeDTarget::getLocationY() const
{
	return locationY;
}

double threeDTarget::getLocationZ() const
{
	return locationZ;
}

double threeDTarget::getAvgColorRed() const
{
	return avgColorRed;
}

double threeDTarget::getAvgColorGreen() const
{
	return avgColorGreen;
}

double threeDTarget::getAvgColorBlue() const
{
	return avgColorBlue;
}

double threeDTarget::getDirectionX() const
{
	return directionX;
}

double threeDTarget::getDirectionY() const
{
	return directionY;
}

double threeDTarget::getDirectionZ() const
{
	return directionZ;
}

double threeDTarget::getSize() const
{
	return size;
}

double threeDTarget::getSpeed() const
{
	return speed;
}

double threeDTarget::getDistance() const
{
	return distance;
}

double threeDTarget::getTimeStamp() const
{
	return timeStamp;
}

int threeDTarget::getCompareMode() const
{
	return compareMode;
}

//Setters
void threeDTarget::setLocationX(const double& inLocationX)
{
	locationX=inLocationX;
}

void threeDTarget::setLocationY(const double& inLocationY)
{
	locationY=inLocationY;
}

void threeDTarget::setLocationZ(const double& inLocationZ)
{
	locationZ=inLocationZ;
}

void threeDTarget::setAvgColorRed(const double& inAvgColorRed)
{
	avgColorRed=inAvgColorRed;
}

void threeDTarget::setAvgColorGreen(const double& inAvgColorGreen)
{
	avgColorGreen=inAvgColorGreen;
}

void threeDTarget::setAvgColorBlue(const double& inAvgColorBlue)
{
	avgColorBlue=inAvgColorBlue;
}

void threeDTarget::setDirectionX(const double& inDirectionX)
{
	directionX=inDirectionX;
}

void threeDTarget::setDirectionY(const double& inDirectionY)
{
	directionY=inDirectionY;
}

void threeDTarget::setDirectionZ(const double& inDirectionZ)
{
	directionZ=inDirectionZ;
}

void threeDTarget::setSize(const double& inSize)
{
	size=inSize;
}

void threeDTarget::setSpeed(const double& inSpeed)
{
	speed=inSpeed;
}

void threeDTarget::setDistance(const double& inDistance)
{
	distance=inDistance;
}

void threeDTarget::setTimeStamp(const double& inTimeStamp)
{
	timeStamp=inTimeStamp;
}

void threeDTarget::setCompareMode(const int& inCompareMode)
{
	compareMode=inCompareMode;
}

//Public Methods

threeDTarget threeDTarget::getTargetSpeedDirection(const threeDTarget& inPrevLocation)const
{
    threeDTarget returnTarget;
    returnTarget.locationX=locationX;
    returnTarget.locationY=locationY;
    returnTarget.locationZ=locationZ;
    returnTarget.avgColorBlue=avgColorBlue;
    returnTarget.avgColorGreen=avgColorGreen;
    returnTarget.avgColorRed=avgColorRed;
    returnTarget.size=size;
    returnTarget.distance=distance;
    returnTarget.timeStamp=timeStamp;
    if(&inPrevLocation==this)
    {
        returnTarget.directionX=0;
        returnTarget.directionY=0;
        returnTarget.directionZ=0;
        returnTarget.speed=0;
    }
    else
    {
        returnTarget.directionX=(locationX-inPrevLocation.locationX)/(timeStamp-inPrevLocation.timeStamp);
        returnTarget.directionY=(locationY-inPrevLocation.locationY)/(timeStamp-inPrevLocation.timeStamp);
        returnTarget.directionZ=(locationZ-inPrevLocation.locationZ)/(timeStamp-inPrevLocation.timeStamp);
        returnTarget.speed=calculateSpeed(locationX,locationY,locationZ,inPrevLocation.locationX,inPrevLocation.locationY,inPrevLocation.locationZ,timeStamp,inPrevLocation.timeStamp);
    }
    return returnTarget;


}

//Destructor
threeDTarget::~threeDTarget(void)
{
	cleanup();
}

//Helper Methods
double threeDTarget::calculateSpeed(const double& inCurrentX,const double& inCurrentY,const double& inCurrentZ,const double& inPrevX,const double& inPrevY,const double& inPrevZ,const double& inCurrentTimeStamp,const double& inPrevTimeStamp) const
{
	double distance=sqrt(pow(inCurrentX-inPrevX,2)+pow(inCurrentY-inPrevY,2)+pow(inCurrentZ-inPrevZ,2));
	double theTime=inCurrentTimeStamp-inPrevTimeStamp;
	if(theTime==0)
	{
		return 0;
	}
	return distance/theTime;
}


void threeDTarget::cleanup()
{
}



