#include "targetPair.h"

//Constructors
//Default
targetPair::targetPair(void):firstTarget(0),secondTarget(0)
{

}

targetPair::targetPair(targetPair& src)
{
   firstTarget=new twoDTargets(*src.firstTarget);
   secondTarget=new twoDTargets(*src.secondTarget);
}

targetPair::targetPair(const targetPair& src)
{
    firstTarget=new twoDTargets(*src.firstTarget);
    secondTarget=new twoDTargets(*src.secondTarget);
}

targetPair::targetPair(targetPair&& src):firstTarget(src.firstTarget),secondTarget(src.secondTarget)
{
    src.firstTarget=0;
    src.secondTarget=0;
}

//Operator Overloading
targetPair& targetPair::operator=(const targetPair& rhs)
{
    if(&rhs==this)
    {
        return *this;
    }
    cleanup();
    firstTarget=new twoDTargets(*rhs.firstTarget);
    secondTarget=new twoDTargets(*rhs.secondTarget);
    return *this;
}

targetPair& targetPair::operator=(targetPair&& rhs)
{
    if(&rhs==this)
    {
        return *this;
    }
    cleanup();
    firstTarget=rhs.firstTarget;
    secondTarget=rhs.secondTarget;
    rhs.firstTarget=0;
    rhs.secondTarget=0;
    return *this;
}

bool targetPair::operator>(const targetPair& rhs) const
{
    if(firstTarget!=0 && secondTarget!=0 && rhs.firstTarget!=0 && rhs.secondTarget!=0)
    {
        if(firstTarget->getSize()+secondTarget->getSize()>rhs.firstTarget->getSize()+rhs.secondTarget->getSize())
        {
            return 1;
        }
    }
    return 0;
}

bool targetPair::operator>=(const targetPair& rhs) const
{
    if(firstTarget!=0 && secondTarget!=0 && rhs.firstTarget!=0 && rhs.secondTarget!=0)
    {
        if(firstTarget->getSize()+secondTarget->getSize()>=rhs.firstTarget->getSize()+rhs.secondTarget->getSize())
        {
            return 1;
        }
    }
    return 0;
}

bool targetPair::operator<=(const targetPair& rhs) const
{
    if(firstTarget!=0 && secondTarget!=0 && rhs.firstTarget!=0 && rhs.secondTarget!=0)
    {
        if(firstTarget->getSize()+secondTarget->getSize()<=rhs.firstTarget->getSize()+rhs.secondTarget->getSize())
        {
            return 1;
        }
    }
    return 0;
}

bool targetPair::operator<(const targetPair& rhs) const
{
    if(firstTarget!=0 && secondTarget!=0 && rhs.firstTarget!=0 && rhs.secondTarget!=0)
    {
        if(firstTarget->getSize()+secondTarget->getSize()<rhs.firstTarget->getSize()+rhs.secondTarget->getSize())
        {
            return 1;
        }
    }
    return 0;
}

bool targetPair::isEqual(const targetPair& rhs,const double& inColorAccuracy) const
{
    if(firstTarget!=0 && secondTarget!=0 && rhs.firstTarget!=0 && rhs.secondTarget!=0)
    {
        double baseline0=0,baseline1=0;
        double redOver0,greenOver0,blueOver0,redOver1,greenOver1,blueOver1;
        baseline0=(firstTarget->getAvgColorRed()+firstTarget->getAvgColorBlue()+firstTarget->getAvgColorGreen()+
                   secondTarget->getAvgColorRed()+secondTarget->getAvgColorBlue()+secondTarget->getAvgColorGreen())/3;
        baseline1=(rhs.firstTarget->getAvgColorRed()+rhs.firstTarget->getAvgColorBlue()+rhs.firstTarget->getAvgColorGreen()+
                   rhs.secondTarget->getAvgColorRed()+rhs.secondTarget->getAvgColorBlue()+rhs.secondTarget->getAvgColorGreen())/3;

        redOver0=(firstTarget->getAvgColorRed()+secondTarget->getAvgColorRed())/baseline0;
        greenOver0=(firstTarget->getAvgColorGreen()+secondTarget->getAvgColorGreen())/baseline0;
        blueOver0=(firstTarget->getAvgColorBlue()+secondTarget->getAvgColorBlue())/baseline0;

        redOver1=(rhs.firstTarget->getAvgColorRed()+rhs.secondTarget->getAvgColorRed())/baseline1;
        greenOver1=(rhs.firstTarget->getAvgColorGreen()+rhs.secondTarget->getAvgColorGreen())/baseline1;
        blueOver1=(rhs.firstTarget->getAvgColorBlue()+rhs.secondTarget->getAvgColorBlue())/baseline1;

        if(redOver0 * (1+inColorAccuracy) > redOver1 && redOver0 * (1-inColorAccuracy) < redOver1 &&
           greenOver0 * (1+inColorAccuracy) > greenOver1 && greenOver0 * (1-inColorAccuracy) < greenOver1 &&
           blueOver0 * (1+inColorAccuracy) > blueOver1 && blueOver0 * (1-inColorAccuracy) < blueOver1)
        {
            return 1;
        }
    }

    return 0;
}

//Getters
twoDTargets* targetPair::getFirstTarget()const
{
    return firstTarget;
}

twoDTargets* targetPair::getSecondTarget()const
{
    return secondTarget;
}

double targetPair::getTimeStamp()const
{
    if(firstTarget!=0)
    {
        return firstTarget->getTimeStamp();
    }
    return 0;
}

void targetPair::setFirstTarget(twoDTargets& inTarget)
{
    firstTarget=new twoDTargets(inTarget);

}

void targetPair::setSecondTarget(twoDTargets& inTarget)
{
    secondTarget=new twoDTargets(inTarget);
}

//Public Methods
threeDTarget targetPair::getTarget(const cameraSettings& inCameraSettings) const
{
    threeDTarget returnTarget;
    double current1AngleX,current2AngleX,current1AngleY,current2AngleY;

    returnTarget.setTimeStamp(getTimeStamp());
    current1AngleX=calculateXAngle(firstTarget->getLocationX()+inCameraSettings.xShift,inCameraSettings.cameraAngleX,inCameraSettings.width,0);
    current2AngleX=calculateXAngle(secondTarget->getLocationX()+inCameraSettings.xShift,inCameraSettings.cameraAngleX,inCameraSettings.width,inCameraSettings.calibrateX);
    current1AngleY=calculateYAngle(firstTarget->getLocationY(),inCameraSettings.cameraAngleY,inCameraSettings.height,inCameraSettings.yShift,0);
    current2AngleY=calculateYAngle(secondTarget->getLocationY(),inCameraSettings.cameraAngleY,inCameraSettings.height,inCameraSettings.yShift,inCameraSettings.calibrateY);

    returnTarget.setLocationX(calculateX(current1AngleX,current2AngleX,inCameraSettings.cameraDistance));
    returnTarget.setLocationY(calculateY(current1AngleX,current2AngleX,(current1AngleY+current2AngleY)/2,inCameraSettings.cameraDistance));
    returnTarget.setLocationZ(calculateZ(current1AngleX,current2AngleX,inCameraSettings.cameraDistance));


    returnTarget.setDirectionX(0);
    returnTarget.setDirectionY(0);
    returnTarget.setDirectionZ(0);

    returnTarget.setSpeed(0);
    returnTarget.setDistance(calculateDistance(current1AngleX,current2AngleX,(current1AngleY+current2AngleY)/2,inCameraSettings.cameraDistance));
    returnTarget.setSize((firstTarget->getSize()+secondTarget->getSize())/2);
    returnTarget.setAvgColorBlue((firstTarget->getAvgColorBlue()+secondTarget->getAvgColorBlue())/2);
    returnTarget.setAvgColorRed((firstTarget->getAvgColorRed()+secondTarget->getAvgColorRed())/2);
    returnTarget.setAvgColorGreen((firstTarget->getAvgColorGreen()+secondTarget->getAvgColorGreen())/2);
    return returnTarget;
}




double targetPair::grade(const std::list<targetPair>& inList,const double& inColorAcc,const double& inLocationAcc,const cameraSettings& inSettings)const
{
    double returnAnswer=0;
    threeDTarget mainTarget = getTarget(inSettings);
    threeDTarget compareTarget;
    double difference=0,targetDistance=0,locReturnInfo=0;
    double baseLine,secondBaseLine;
    double redDiff,blueDiff,greenDiff;
    double redAnswer,blueAnswer,greenAnswer;
    double colReturnInfo=0;



    if(inList.size()>1)
    {
        std::list<targetPair>::const_iterator inTargets = ++inList.begin();
        threeDTarget prevTarget;
        double tempLocationX,tempLocationY,tempLocationZ;
        double timeLapse=0;
        while(inTargets!=inList.end())
        {
            compareTarget=inTargets->getTarget(inSettings);
            inTargets--;
            prevTarget=inTargets->getTarget(inSettings);
            inTargets++;
            compareTarget.getTargetSpeedDirection(prevTarget);
            timeLapse=mainTarget.getTimeStamp()-compareTarget.getTimeStamp();
            tempLocationX=(timeLapse*prevTarget.getDirectionX())+prevTarget.getLocationX();
            tempLocationY=(timeLapse*prevTarget.getDirectionY())+prevTarget.getLocationY();
            tempLocationZ=(timeLapse*prevTarget.getDirectionZ())+prevTarget.getLocationZ();
            targetDistance = sqrt(pow((mainTarget.getLocationX()-tempLocationX),2)+pow((mainTarget.getLocationY()-tempLocationY),2)+pow((mainTarget.getLocationZ()-tempLocationZ),2));
            difference = inLocationAcc - targetDistance;
            if(difference < 0)
            {
                locReturnInfo=0;
            }
            else
            {
                locReturnInfo=(difference/inLocationAcc)*50;
            }
            baseLine = (mainTarget.getAvgColorRed()+mainTarget.getAvgColorGreen()+mainTarget.getAvgColorBlue())/3;
            secondBaseLine = (compareTarget.getAvgColorRed()+compareTarget.getAvgColorGreen()+compareTarget.getAvgColorBlue())/3;
            redDiff=fabs((mainTarget.getAvgColorRed()/baseLine)-(compareTarget.getAvgColorRed()/secondBaseLine));
            greenDiff=fabs((mainTarget.getAvgColorGreen()/baseLine)-(compareTarget.getAvgColorGreen()/secondBaseLine));
            blueDiff=fabs((mainTarget.getAvgColorBlue()/baseLine)-(compareTarget.getAvgColorBlue()/secondBaseLine));
            if((inColorAcc - redDiff) < 0)
            {
                redAnswer=0;
            }
            else
            {
                redAnswer=((inColorAcc-redDiff)/inColorAcc)*(50/3);
            }

            if((inColorAcc - blueDiff) < 0)
            {
                blueAnswer=0;
            }
            else
            {
                blueAnswer=((inColorAcc-blueDiff)/inColorAcc)*(50/3);
            }

            if((inColorAcc - greenDiff) < 0)
            {
                greenAnswer=0;
            }
            else
            {
                greenAnswer=((inColorAcc-greenDiff)/inColorAcc)*(50/3);
            }
            colReturnInfo=redAnswer+blueAnswer+greenAnswer;
            if(returnAnswer<locReturnInfo+colReturnInfo)
            {
                returnAnswer=locReturnInfo+colReturnInfo;
            }
            inTargets++;
        }
    }
    else
    {
        if(inList.size()==0)
        {
            return 0;
        }
        std::list<targetPair>::const_iterator inTargets = inList.begin();
        compareTarget=inTargets->getTarget(inSettings);
        targetDistance = sqrt(pow((mainTarget.getLocationX()-compareTarget.getLocationX()),2)+pow((mainTarget.getLocationY()-compareTarget.getLocationY()),2)+pow((mainTarget.getLocationZ()-compareTarget.getLocationZ()),2));
        difference = (inLocationAcc*30) - targetDistance;
        if(difference < 0)
        {
            locReturnInfo=0;
        }
        else
        {
            locReturnInfo=(difference/(inLocationAcc*30))*25;
        }
        baseLine = (mainTarget.getAvgColorRed()+mainTarget.getAvgColorGreen()+mainTarget.getAvgColorBlue())/3;
        secondBaseLine = (compareTarget.getAvgColorRed()+compareTarget.getAvgColorGreen()+compareTarget.getAvgColorBlue())/3;
        redDiff=fabs((mainTarget.getAvgColorRed()/baseLine)-(compareTarget.getAvgColorRed()/secondBaseLine));
        greenDiff=fabs((mainTarget.getAvgColorGreen()/baseLine)-(compareTarget.getAvgColorGreen()/secondBaseLine));
        blueDiff=fabs((mainTarget.getAvgColorBlue()/baseLine)-(compareTarget.getAvgColorBlue()/secondBaseLine));
        if((inColorAcc - redDiff) < 0)
        {
            redAnswer=0;
        }
        else
        {
            redAnswer=((inColorAcc-redDiff)/inColorAcc)*(75/3);
        }

        if((inColorAcc - blueDiff) < 0)
        {
            blueAnswer=0;
        }
        else
        {
            blueAnswer=((inColorAcc-blueDiff)/inColorAcc)*(75/3);
        }

        if((inColorAcc - greenDiff) < 0)
        {
            greenAnswer=0;
        }
        else
        {
            greenAnswer=((inColorAcc-greenDiff)/inColorAcc)*(75/3);
        }
        colReturnInfo=redAnswer+blueAnswer+greenAnswer;
        returnAnswer=colReturnInfo+locReturnInfo;
    }
    return returnAnswer;
}



//Destructor
targetPair::~targetPair()
{
    cleanup();
}

void targetPair::cleanup()
{
    if(firstTarget!=NULL)
    {
        delete firstTarget;
        firstTarget=0;
    }
    if(secondTarget!=NULL)
    {
        delete secondTarget;
        secondTarget=0;
    }
}

//Helper Methods
double targetPair::calculateXAngle(const double& inLocationX,const double& inCameraAngle,const double& inWidth,const double& inCalibrate) const
{
	return 90+(((inLocationX+inCalibrate)*inCameraAngle)/inWidth)-(inCameraAngle/2);
}

double targetPair::calculateYAngle(const double& inLocationY,const double& inCameraAngle,const double& inHeight,const double& inYShift,const double& inCalibrateY) const
{
	return (inCameraAngle/2)-(((inLocationY+inYShift+inCalibrateY)*inCameraAngle)/inHeight);
}

double targetPair::calculateDistance(const double& inAngle1,const double& inAngle2,const double& inYAngle,const double& inCameraDistance) const
{
	double angle1=(3.14159265358979*2)*(inAngle1/360);
	double angle2=(3.14159265358979*2)*(inAngle2/360);
	double angle3=(3.14159265358979*2)*(inYAngle/360);
	double M=((inCameraDistance*sin(angle1))/tan(angle2-angle1))+(inCameraDistance*cos(angle1));
	double W=M*cos(angle1)-(inCameraDistance/2);
	double L=M*sin(angle1);
	double Y=tan(angle3)*sqrt(pow(W,2)+pow(L,2));
	return sqrt(pow(W,2)+pow(L,2)+pow(Y,2));
}

double targetPair::calculateX(const double& inAngle1,const double& inAngle2,const double& cameraDistance) const
{
	double angle1=(3.14159265358979*2)*(inAngle1/360);
	double angle2=(3.14159265358979*2)*(inAngle2/360);
	double M=((cameraDistance*sin(angle1))/tan(angle2-angle1))+(cameraDistance*cos(angle1));
	double W=M*cos(angle1)-(cameraDistance/2);
	return W;
}

double targetPair::calculateY(const double& inAngle1,const double& inAngle2,const double& inYAngle,const double& inCameraDistance) const
{
	double angle1=(3.14159265358979*2)*(inAngle1/360);
	double angle2=(3.14159265358979*2)*(inAngle2/360);
	double angle3=(3.14159265358979*2)*(inYAngle/360);
	double M=((inCameraDistance*sin(angle1))/tan(angle2-angle1))+(inCameraDistance*cos(angle1));
	double W=M*cos(angle1)-(inCameraDistance/2);
	double L=M*sin(angle1);
	double Y=tan(angle3)*sqrt(pow(W,2)+pow(L,2));
	return -Y;
}




double targetPair::calculateZ(const double& inAngle1,const double& inAngle2,const double& cameraDistance) const
{
    double angle1=(3.14159265358979*2)*(inAngle1/360);
	double angle2=(3.14159265358979*2)*(inAngle2/360);
	double M=((cameraDistance*sin(angle1))/tan(angle2-angle1))+(cameraDistance*cos(angle1));
	double L=M*sin(angle1);
    return L;
}


