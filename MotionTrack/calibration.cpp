#include "calibration.h"

//Constructors
//Default
calibration::calibration(void):target0(0),target1(0),target0LocX(0),target0LocY(0),target0LocZ(0),target1LocX(0),target1LocY(0),target1LocZ(0)
{

}

//Copy
calibration::calibration(const calibration& src):target0(new targetPair(*src.target0)),target1(new targetPair(*src.target1)),
    target0LocX(src.target0LocX),target0LocY(src.target0LocY),target0LocZ(src.target0LocZ),target1LocX(src.target1LocX),target1LocY(src.target1LocY),target1LocZ(src.target1LocZ)
{
}

//Move
calibration::calibration(calibration&& src):target0LocX(src.target0LocX),target0LocY(src.target0LocY),target0LocZ(src.target0LocZ),target1LocX(src.target1LocX),target1LocY(src.target1LocY),target1LocZ(src.target1LocZ)
{
    target0=src.target0;
    target1=src.target1;
    src.target1=0;
    src.target0=0;
}

//Operator Overloading
//Assignment
calibration& calibration::operator=(const calibration& rhs)
{
    if(&rhs==this)
    {
        return *this;
    }
    target0LocX=rhs.target0LocX;
    target0LocY=rhs.target0LocY;
    target0LocZ=rhs.target0LocZ;
    target1LocX=rhs.target1LocX;
    target1LocY=rhs.target1LocY;
    target1LocZ=rhs.target1LocZ;
    cleanup();
    target0=new targetPair(*rhs.target0);
    target1=new targetPair(*rhs.target1);
    return *this;
}

//Assignment Move
calibration& calibration::operator=(calibration&& rhs)
{
    if(&rhs==this)
    {
        return *this;
    }
    target0LocX=rhs.target0LocX;
    target0LocY=rhs.target0LocY;
    target0LocZ=rhs.target0LocZ;
    target1LocX=rhs.target1LocX;
    target1LocY=rhs.target1LocY;
    target1LocZ=rhs.target1LocZ;
    cleanup();
    target0=rhs.target0;
    target1=rhs.target1;
    rhs.target0=0;
    rhs.target1=0;
    return *this;
}


//Getters
double calibration::getTarget0LocX()const
{
    return target0LocX;
}

double calibration::getTarget0LocY()const
{
    return target0LocY;
}

double calibration::getTarget0LocZ()const
{
    return target0LocZ;
}

double calibration::getTarget1LocX()const
{
    return target1LocX;
}

double calibration::getTarget1LocY()const
{
    return target1LocY;
}

double calibration::getTarget1LocZ()const
{
    return target1LocZ;
}

targetPair calibration::getTarget0()const
{
    return *target0;
}

targetPair calibration::getTarget1()const
{
    return *target1;
}

//Setters

//Public Methods
void calibration::setTarget(const int& target,const targetPair& inTarget,const double& inLocX,const double& inLocY,const double& inLocZ)
{
    if(target==0)
    {
        if(target0!=0)
        {
            delete target0;
        }
        target0=new targetPair(inTarget);
        target0LocX=inLocX;
        target0LocY=inLocY;
        target0LocZ=inLocZ;
    }
    else
    {
        if(target1!=0)
        {
            delete target1;
        }
        target1=new targetPair(inTarget);
        target1LocX=inLocX;
        target1LocY=inLocY;
        target1LocZ=inLocZ;

    }
}

cameraSettings calibration::calibrate(const cameraSettings& inCurrentSettings)
{
    cameraSettings newSettings;
    newSettings.calibrateX=inCurrentSettings.calibrateX;
    newSettings.calibrateY=inCurrentSettings.calibrateY;
    newSettings.cameraAngleX=inCurrentSettings.cameraAngleX;
    newSettings.cameraAngleY=inCurrentSettings.cameraAngleY;
    newSettings.cameraDistance=inCurrentSettings.cameraDistance;
    newSettings.xShift=inCurrentSettings.xShift;
    newSettings.yShift=inCurrentSettings.yShift;
    newSettings.width=inCurrentSettings.width;
    newSettings.height=inCurrentSettings.height;

    if(target0!=0 && target1!=0)
    {
        threeDTarget evalTarget;
        double calibrationDifference,calibrationCompairDifference;
        double zDifference,zCompareDifference;
        double calibrationAdder=0.1;
        double angleAdder=0.1;
        bool firstLoop=1,secondLoop=1;
        do
        {
            calibrationAdder=0.1;
            evalTarget=target0->getTarget(newSettings);
            calibrationDifference = fabs(evalTarget.getLocationZ()-target0LocZ);
            newSettings.calibrateX+=calibrationAdder;
            evalTarget=target0->getTarget(newSettings);
            calibrationCompairDifference = fabs(evalTarget.getLocationZ()-target0LocZ);
            if(calibrationDifference>calibrationCompairDifference)
            {
                calibrationAdder=0.1;
                evalTarget=target0->getTarget(newSettings);
                calibrationDifference = fabs(evalTarget.getLocationZ()-target0LocZ);
                newSettings.calibrateX+=calibrationAdder;
                evalTarget=target0->getTarget(newSettings);
                calibrationCompairDifference = fabs(evalTarget.getLocationZ()-target0LocZ);

                while(calibrationDifference>calibrationCompairDifference)
                {
                    calibrationDifference=calibrationCompairDifference;
                    newSettings.calibrateX+=calibrationAdder;
                    evalTarget=target0->getTarget(newSettings);
                    calibrationCompairDifference = fabs(evalTarget.getLocationZ()-target0LocZ);
                }

            }
            else
            {

                calibrationAdder=-0.1;
                evalTarget=target0->getTarget(newSettings);
                calibrationDifference = fabs(evalTarget.getLocationZ()-target0LocZ);
                newSettings.calibrateX+=calibrationAdder;
                evalTarget=target0->getTarget(newSettings);
                calibrationCompairDifference = fabs(evalTarget.getLocationZ()-target0LocZ);
                while(calibrationDifference>calibrationCompairDifference)
                {
                    calibrationDifference=calibrationCompairDifference;
                    newSettings.calibrateX+=calibrationAdder;
                    evalTarget=target0->getTarget(newSettings);
                    calibrationCompairDifference = fabs(evalTarget.getLocationZ()-target0LocZ);
                }
            }
            newSettings.calibrateX-=calibrationAdder;
            evalTarget=target1->getTarget(newSettings);
            zDifference=zCompareDifference;
            zCompareDifference = fabs(evalTarget.getLocationZ()-target1LocZ);
            if(zCompareDifference<0.05)
            {
                return newSettings;
            }

            if(firstLoop)
            {
                firstLoop=0;
                newSettings.cameraAngleX+=angleAdder;
            }
            else
            {
                if(secondLoop)
                {
                    secondLoop=0;
                    if(zDifference>zCompareDifference)
                    {
                        angleAdder=0.1;
                    }
                    else
                    {
                        angleAdder=-0.1;
                    }
                }
                newSettings.cameraAngleX+=angleAdder;
            }


        }while(1);
        newSettings.cameraAngleX-=angleAdder;
    }
    return newSettings;
}

void calibration::clear()
{
    target0LocX=0;
    target0LocY=0;
    target0LocZ=0;
    target1LocX=0;
    target1LocY=0;
    target1LocZ=0;
    cleanup();
}

//Destructor
calibration::~calibration(void)
{
    cleanup();
}

//Helper Methods
void calibration::cleanup()
{
    if(target0!=0)
    {
        delete target0;
        target0=0;
    }
    if(target1!=0)
    {
        delete target1;
        target1=0;
    }
}

