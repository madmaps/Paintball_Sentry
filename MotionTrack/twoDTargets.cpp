#include "twoDTargets.h"

//Constructors
//Default
twoDTargets::twoDTargets(void):locationX(0),locationY(0),size(0),avgColorRed(0),avgColorGreen(0),avgColorBlue(0),timeStamp(0),possiblyIncomplete(0)
{
}

//Copy
twoDTargets::twoDTargets(const twoDTargets& src):locationX(src.locationX),locationY(src.locationY),size(src.size),avgColorRed(src.avgColorRed),avgColorGreen(src.avgColorGreen),avgColorBlue(src.avgColorBlue),timeStamp(src.timeStamp),possiblyIncomplete(src.possiblyIncomplete)
{
}

//Move
twoDTargets::twoDTargets(twoDTargets&& src):locationX(src.locationX),locationY(src.locationY),size(src.size),avgColorRed(src.avgColorRed),avgColorGreen(src.avgColorGreen),avgColorBlue(src.avgColorBlue),timeStamp(src.timeStamp),possiblyIncomplete(src.possiblyIncomplete)
{
	src.locationX=0;
	src.locationY=0;
	src.size=0;
	src.avgColorRed=0;
	src.avgColorGreen=0;
	src.avgColorBlue=0;
	src.timeStamp=0;
	src.possiblyIncomplete=0;
}

//Data
twoDTargets::twoDTargets(const double& inLocationX,const double& inLocationY,const double& inSize,const double& inAvgColorRed, const double& inAvgColorGreen,const double& inAvgColorBlue,const double& inTimeStamp,const bool& inPossiblyIncomplete):
	locationX(inLocationX),locationY(inLocationY),size(inSize),avgColorRed(inAvgColorRed),avgColorGreen(inAvgColorGreen),avgColorBlue(inAvgColorBlue),timeStamp(inTimeStamp),possiblyIncomplete(inPossiblyIncomplete)
{
}

//Operator OverLoading
//Assignment
twoDTargets& twoDTargets::operator=(const twoDTargets& rhs)
{
	if(&rhs==this)
	{
		return *this;
	}
	locationX=rhs.locationX;
	locationY=rhs.locationY;
	size=rhs.size;
	avgColorRed=rhs.avgColorRed;
	avgColorGreen=rhs.avgColorGreen;
	avgColorBlue=rhs.avgColorBlue;
	timeStamp=rhs.timeStamp;
	possiblyIncomplete=rhs.possiblyIncomplete;
	return *this;
}

//Move
twoDTargets& twoDTargets::operator=(twoDTargets&& rhs)
{
	if(&rhs==this)
	{
		return *this;
	}
	locationX=rhs.locationX;
	locationY=rhs.locationY;
	size=rhs.size;
	avgColorRed=rhs.avgColorRed;
	avgColorGreen=rhs.avgColorGreen;
	avgColorBlue=rhs.avgColorBlue;
	timeStamp=rhs.timeStamp;
	possiblyIncomplete=rhs.possiblyIncomplete;

	rhs.locationX=0;
	rhs.locationY=0;
	rhs.size=0;
	rhs.avgColorRed=0;
	rhs.avgColorGreen=0;
	rhs.avgColorBlue=0;
	rhs.timeStamp=0;
	rhs.possiblyIncomplete=0;
	return *this;
}

bool twoDTargets::operator>(const twoDTargets& rhs) const
{
    if(size>rhs.getSize())
    {
        return 1;
    }
    return 0;
}

bool twoDTargets::operator>=(const twoDTargets& rhs) const
{
    if(size>=rhs.getSize())
    {
        return 1;
    }
    return 0;
}

bool twoDTargets::operator<(const twoDTargets& rhs) const
{
    if(size<rhs.getSize())
    {
        return 1;
    }
    return 0;
}

bool twoDTargets::operator<=(const twoDTargets& rhs) const
{
    if(size<=rhs.getSize())
    {
        return 1;
    }
    return 0;
}




bool twoDTargets::isEqual(const twoDTargets& rhs,const double& inSizeAcc,const double& inYLocAcc,const double& inColorAcc) const
{
    double baseline0=0,baseline1=0;
    double redOver0,greenOver0,blueOver0,redOver1,greenOver1,blueOver1;
    baseline0=(avgColorRed+avgColorBlue+avgColorGreen)/3;
    baseline1=(rhs.getAvgColorBlue()+rhs.getAvgColorGreen()+rhs.getAvgColorRed())/3;

    redOver0=avgColorRed/baseline0;
    greenOver0=avgColorGreen/baseline0;
    blueOver0=avgColorBlue/baseline0;

    redOver1=rhs.getAvgColorRed()/baseline1;
    greenOver1=rhs.getAvgColorGreen()/baseline1;
    blueOver1=rhs.getAvgColorBlue()/baseline1;

    if(size*(1+inSizeAcc) > rhs.getSize() &&
       size*(1-inSizeAcc) < rhs.getSize() &&
       locationY*(1+inYLocAcc) > rhs.getLocationY() &&
       locationY*(1-inYLocAcc) < rhs.getLocationY() &&

       redOver0 * (1+inColorAcc) > redOver1 && redOver0 * (1-inColorAcc) < redOver1 &&
       greenOver0 * (1+inColorAcc) > greenOver1 && greenOver0 * (1-inColorAcc) < greenOver1 &&
       blueOver0 * (1+inColorAcc) > blueOver1 && blueOver0 * (1-inColorAcc) < blueOver1)
    {
        return 1;
    }


    return 0;
}

twoDTargets twoDTargets::operator+(const twoDTargets& rhs)const
{
    twoDTargets returnTarget;
    if(&rhs==this)
    {
        return *this;
    }
    returnTarget.locationX=locationX+rhs.locationX;
    returnTarget.locationY=locationY+rhs.locationY;
    returnTarget.size=size+rhs.size;
    returnTarget.timeStamp=timeStamp+rhs.timeStamp;
    returnTarget.avgColorBlue=avgColorBlue+rhs.avgColorBlue;
    returnTarget.avgColorGreen=avgColorGreen+rhs.avgColorGreen;
    returnTarget.avgColorRed=avgColorRed+rhs.avgColorRed;
    returnTarget.possiblyIncomplete=0;


    return returnTarget;
}

twoDTargets twoDTargets::operator/(const double& rhs)const
{
    twoDTargets returnTargets;
    if(rhs==0)
    {
        return *this;
    }
    returnTargets.locationX=locationX/rhs;
    returnTargets.locationY=locationY/rhs;
    returnTargets.size=size/rhs;
    returnTargets.timeStamp=timeStamp/rhs;
    returnTargets.avgColorBlue=avgColorBlue/rhs;
    returnTargets.avgColorGreen=avgColorGreen/rhs;
    returnTargets.avgColorRed=avgColorRed/rhs;
    returnTargets.possiblyIncomplete=0;
    return returnTargets;
}


//Getters
double twoDTargets::getLocationX() const
{
	return locationX;
}

double twoDTargets::getLocationY() const
{
	return locationY;
}

double twoDTargets::getSize() const
{
	return size;
}

double twoDTargets::getAvgColorRed() const
{
	return avgColorRed;
}

double twoDTargets::getAvgColorGreen() const
{
	return avgColorGreen;
}

double twoDTargets::getAvgColorBlue() const
{
	return avgColorBlue;
}

double twoDTargets::getTimeStamp() const
{
	return timeStamp;
}

bool twoDTargets::getPossiblyIncomplete() const
{
	return possiblyIncomplete;
}

//Setters
void twoDTargets::setLocationX(const double& inLocationX)
{
	locationX=inLocationX;
}

void twoDTargets::setLocationY(const double& inLocationY)
{
	locationY=inLocationY;
}

void twoDTargets::setSize(const double& inSize)
{
	size=inSize;
}

void twoDTargets::setAvgColorRed(const double& inAvgColorRed)
{
	avgColorRed=inAvgColorRed;
}

void twoDTargets::setAvgColorGreen(const double& inAvgColorGreen)
{
	avgColorGreen=inAvgColorGreen;
}

void twoDTargets::setAvgColorBlue(const double& inAvgColorBlue)
{
	avgColorBlue=inAvgColorBlue;
}

void twoDTargets::setTimeStamp(const double& inTimeStamp)
{
	timeStamp=inTimeStamp;
}

void twoDTargets::setPossiblyIncomplete(const bool& inPossiblyIncomplete)
{
	possiblyIncomplete=inPossiblyIncomplete;
}

//Public Methods



//Destructer
twoDTargets::~twoDTargets(void)
{
	cleanup();
}

//Helper Methods
void twoDTargets::cleanup()
{
}
