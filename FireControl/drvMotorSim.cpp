#include "drvMotorSim.h"

//Constructors
//Default
drvMotorSim::drvMotorSim(void):currentX(0),currentY(0),wantedX(0),wantedY(0),lastCommandTime(0),fireTime(0),syncTime(0),
                               stepDeg(1),degPerStep(1.8),maxDegreeStep(1),minDegreeStep(32),timeDelay(8)
{
}

//Copy
drvMotorSim::drvMotorSim(const drvMotorSim& src):currentX(src.currentX),currentY(src.currentY),wantedX(src.wantedX),wantedY(src.wantedY),lastCommandTime(src.lastCommandTime),
                                                 fireTime(src.fireTime),syncTime(src.syncTime),stepDeg(src.stepDeg),degPerStep(src.degPerStep),maxDegreeStep(src.maxDegreeStep),
                                                 minDegreeStep(src.minDegreeStep),timeDelay(src.timeDelay)
{
}

//Move
drvMotorSim::drvMotorSim(drvMotorSim&& src):currentX(src.currentX),currentY(src.currentY),wantedX(src.wantedX),wantedY(src.wantedY),lastCommandTime(src.lastCommandTime),
                                                 fireTime(src.fireTime),syncTime(src.syncTime),stepDeg(src.stepDeg),degPerStep(src.degPerStep),maxDegreeStep(src.maxDegreeStep),
                                                 minDegreeStep(src.minDegreeStep),timeDelay(src.timeDelay)
{
}

//Operator Overloading
//Assignment
drvMotorSim& drvMotorSim::operator=(const drvMotorSim& rhs)
{
    if(this==&rhs)
    {
        return *this;
    }
    currentX=rhs.currentX;
    currentY=rhs.currentY;
    wantedX=rhs.wantedX;
    wantedY=rhs.wantedY;
    lastCommandTime=rhs.lastCommandTime;
    fireTime=rhs.fireTime;
    syncTime=rhs.syncTime;
    stepDeg=rhs.stepDeg;
    degPerStep=rhs.degPerStep;
    maxDegreeStep=rhs.maxDegreeStep;
    minDegreeStep=rhs.minDegreeStep;
    timeDelay=rhs.timeDelay;
    return *this;
}

drvMotorSim& drvMotorSim::operator=(drvMotorSim&& rhs)
{
    if(this==&rhs)
    {
        return *this;
    }
    currentX=rhs.currentX;
    currentY=rhs.currentY;
    wantedX=rhs.wantedX;
    wantedY=rhs.wantedY;
    lastCommandTime=rhs.lastCommandTime;
    fireTime=rhs.fireTime;
    syncTime=rhs.syncTime;
    stepDeg=rhs.stepDeg;
    degPerStep=rhs.degPerStep;
    maxDegreeStep=rhs.maxDegreeStep;
    minDegreeStep=rhs.minDegreeStep;
    timeDelay=rhs.timeDelay;
    return *this;
}

//Getters
double drvMotorSim::getStepDeg()const
{
    return stepDeg;
}

double drvMotorSim::getDegreePerStep()const
{
    return degPerStep;
}

int drvMotorSim::getMaxDegreeStep()const
{
    return maxDegreeStep;
}

int drvMotorSim::getMinDegreeStep()const
{
    return minDegreeStep;
}

int drvMotorSim::getTimeDelay()const
{
    return timeDelay;
}

double drvMotorSim::getWantedX()const
{
    return wantedX;
}

double drvMotorSim::getWantedY()const
{
    return wantedY;
}

//Setters
void drvMotorSim::setMotorLocationX(const double& inMotorLocationX)
{
    currentX=inMotorLocationX;
}

void drvMotorSim::setMotorLocationY(const double& inMotorLocationY)
{
    currentY=inMotorLocationY;
}

void drvMotorSim::setStepDeg(const double& inStepDeg)
{
    changeStep(inStepDeg);
}

void drvMotorSim::setDegreePerStep(const double& inDegreePerStep)
{
    degPerStep=inDegreePerStep;
}

void drvMotorSim::setMaxDegreeStep(const int& inMaxDegreeStep)
{
    maxDegreeStep=inMaxDegreeStep;
}

void drvMotorSim::setMinDegreeStep(const int& inMinDegreeStep)
{
    minDegreeStep=inMinDegreeStep;
}

void drvMotorSim::setTimeDelay(const int& inTimeDelay)
{
    timeDelay=inTimeDelay;
}

void drvMotorSim::setStep(const int& inStep)
{
    changeStep(inStep);
}

//Public Methods
double drvMotorSim::getCurrentX()const
{
    return currentX;
}

double drvMotorSim::getCurrentY()const
{
    return currentY;
}

double drvMotorSim::getMotorLocationX(const double& inTime) const
{
    //return moveTo(wantedX);
    //return currentX;

    double angleX=wantedX-currentX;
    double timeDiff=inTime-lastCommandTime;
    double returnAngle=0;
    if(timeToMoveTo(angleX)<=timeDiff)
    {
        //return wantedX;
        return currentX;
    }
    else
    {
        double steps=timeDiff/(double)timeDelay;
        if(angleX>=0)
        {
            returnAngle=currentX+(steps*degPerStep*maxDegreeStep);
            if(returnAngle>wantedX)
            {
                return wantedX;
            }
            return returnAngle;
        }
        else
        {
            returnAngle=currentX-(steps*degPerStep*maxDegreeStep);
            if(returnAngle<wantedX)
            {
                return wantedX;
            }
            return returnAngle;
        }
    }

}

double drvMotorSim::getMotorLocationY(const double& inTime) const
{
    //return moveTo(wantedY);
    //return currentY;

    double angleX=wantedX-currentX;
    double angleY=wantedY-currentY;
    double timeDiff=inTime-lastCommandTime;
    double returnAngle=0;
    if(timeToMoveTo(angleX)<=timeDiff)
    {
        return currentY;
    }
    else
    {
        timeDiff-=timeToMoveTo(angleX);
        if(timeToMoveTo(angleY)<=timeDiff)
        {
            return currentY;
            //return wantedY;
        }
        else
        {
            double steps=timeDiff/timeDelay;
            if(angleY>=0)
            {
                returnAngle=currentY+(steps*degPerStep*maxDegreeStep);
                if(returnAngle>wantedY)
                {
                    return wantedY;
                }
                return returnAngle;
            }
            else
            {
                returnAngle=currentY-(steps*degPerStep*maxDegreeStep);
                if(returnAngle<wantedY)
                {
                    return wantedY;
                }
                return returnAngle;
            }
        }
    }

}

double drvMotorSim::getFireTime()const
{
    return fireTime;
}

double drvMotorSim::timeUntilLocation(const double& inCurrentLocationX,const double& inCurrentLocationY,const double& inWantedLocationX,const double& inWantedLocationY)const
{
    double angleX=inWantedLocationX-inCurrentLocationX;
    double angleY=inWantedLocationY-inCurrentLocationY;
    return timeToMoveTo(angleX)+timeToMoveTo(angleY);
}

void drvMotorSim::inCompletedCommands(const std::list<command>& inCommands,const double& inTime)
{
    for(auto iter:inCommands)
    {
        switch(iter.getCommandType())
        {
        case MOVE_X:
            currentX+=moveTo(iter.getValue());
            wantedX=currentX;
            //lastCommandTime=inTime;
            break;
        case MOVE_Y:
            currentY+=moveTo(iter.getValue());
            wantedY=currentY;
            //lastCommandTime=inTime;
            break;
        case FIRE:
            fireTime=iter.getValue();
            lastCommandTime=inTime;
            break;
        case SYNC_TIME:
            syncTime=iter.getValue();
            //lastCommandTime=inTime;
            std::cout << "Clocks Syncronized" << std::endl;
            break;
        default:
            break;
        }
    }
}

void drvMotorSim::inRunningCommands(const std::list<command>& inCommands,const double& inTime)
{
    bool ignore=0;
    for(auto iter:inCommands)
    {
        if(!ignore)
        {
            switch(iter.getCommandType())
            {
            case MOVE_X:
                if(wantedX!=iter.getValue())
                {
                    //double tempValue=moveTo(iter.getValue());
                    wantedX+=moveTo(iter.getValue());
                    //wantedX+=moveTo(iter.getValue());
                    //lastCommandTime=inTime;
                }
                break;
            case MOVE_Y:
                if(wantedY!=iter.getValue())
                {
                    wantedY+=moveTo(iter.getValue());
                    //wantedY+=moveTo(iter.getValue());
                    //lastCommandTime=inTime;
                }
                break;
            case FIRE:
                fireTime=iter.getValue();
                //lastCommandTime=inTime;
                ignore=1;
                break;
            case SYNC_TIME:
                syncTime=iter.getValue();

                break;
            default:
                break;
            }
        }
    }
}

//Destructor
drvMotorSim::~drvMotorSim(void)
{
}

//Helper Methods

double drvMotorSim::moveTo(double inAngle)
{
    bool dir=0;
	if(inAngle>=0)
	{
		dir=0;
	}
	else
	{
		dir=1;
	}
	inAngle=fabs(inAngle);

	double numberOfSteps=floor(inAngle/(stepDeg*degPerStep));

	double returnAngle=numberOfSteps*stepDeg*degPerStep;

	if(dir==0)
	{
		return returnAngle;
	}
	return -returnAngle;
}

double drvMotorSim::timeToMoveTo(const double& inAngle) const
{
    double tempAngle=fabs(inAngle);
    double returnTime=(tempAngle/(stepDeg*degPerStep)*(double)timeDelay)/1000;
    //double testReturnTime =
    return returnTime;//(floor(tempAngle/(stepDeg*degPerStep))*timeDelay)/1000;
}

/*double drvMotorSim::moveTo(double inAngle)
{
    double tempAngle=0;

    bool dir=0;

    if(inAngle>=0)
	{
		dir=0;
	}
	else
	{
		dir=1;
	}
	tempAngle=fabs(inAngle);
	int stepper=maxDegreeStep;
	changeStep(stepper);
	double returnAngle=0;
	int numberOfSteps=0;


	do
	{
        do
        {
           	numberOfSteps=floor(tempAngle/(stepDeg*degPerStep));

            if(numberOfSteps==0)
            {
                stepper*=2;
                changeStep(stepper);
            }
        }while(numberOfSteps==0 && stepper<=minDegreeStep);
		if(numberOfSteps!=0)
		{
            returnAngle+=numberOfSteps*stepDeg*degPerStep;
            tempAngle-=numberOfSteps*stepDeg*degPerStep;
        }

	}while(stepper<=minDegreeStep);
	if(dir==0)
	{
		return returnAngle;
	}
	return -returnAngle;
}

double drvMotorSim::timeToMoveTo(const double& inAngle)const
{
    double tempAngle=0;
    bool dir=0;
    double returnTime=0;

    if(tempAngle>=0)
	{
		dir=0;
	}
	else
	{
		dir=1;
	}
	tempAngle=fabs(inAngle);
	int stepper=maxDegreeStep;
	changeStep(stepper);
	double returnAngle=0;
	int numberOfSteps=0;


	do
	{
        do
        {
           	numberOfSteps=floor(tempAngle/(stepDeg*degPerStep));

            if(numberOfSteps==0)
            {
                stepper*=2;
                changeStep(stepper);
            }
        }while(numberOfSteps==0 && stepper<=minDegreeStep);
		if(numberOfSteps!=0)
		{
            returnAngle+=numberOfSteps*stepDeg*degPerStep;
            tempAngle-=numberOfSteps*stepDeg*degPerStep;
            returnTime=returnTime+numberOfSteps*timeDelay;
        }

	}while(stepper<=minDegreeStep);
    return returnTime/1000;
}
*/
void drvMotorSim::changeStep(const int& inStep)const
{
	switch(inStep)
	{
	case 2:
		stepDeg=.5;
		break;
	case 4:
		stepDeg=.25;
		break;
	case 8:
		stepDeg=.125;
		break;
	case 16:
		stepDeg=.0625;
		break;
	case 32:
		stepDeg=0.03125;
		break;
	case 1:
	default:
		stepDeg=1;
		break;
	}
}






