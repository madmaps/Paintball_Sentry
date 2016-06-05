#ifndef __DRVMOTORSIM__
#define __DRVMOTORSIM__
#include <list>
#include "command.h"
#include "motorSimulator.h"
#include <math.h>
#include <iostream>

class drvMotorSim : public motorSimulator
{
public:
    //Constructors
    drvMotorSim();//Default
    drvMotorSim(const drvMotorSim& src);//Copy
    drvMotorSim(drvMotorSim&& src);//Move

    //Operator Overloading
    virtual drvMotorSim& operator=(const drvMotorSim& rhs);//Assignment
    virtual drvMotorSim& operator=(drvMotorSim&& rhs);//Move Assignment

    //Getters
    virtual double getStepDeg()const;
    virtual double getDegreePerStep()const;
    virtual int getMaxDegreeStep()const;
    virtual int getMinDegreeStep()const;
    virtual int getTimeDelay()const;
    virtual double getWantedX()const;
    virtual double getWantedY()const;

    //Setters
    virtual void setMotorLocationX(const double& inMotorLocationX);
    virtual void setMotorLocationY(const double& inMotorLocationY);
    virtual void setStepDeg(const double& inStepDeg);
    virtual void setDegreePerStep(const double& inDegreePerStep);
    virtual void setMaxDegreeStep(const int& inMaxDegreeStep);
    virtual void setMinDegreeStep(const int& inMinDegreeStep);
    virtual void setTimeDelay(const int& inTimeDelay);
    virtual void setStep(const int& inStep);

    //Public Methods
    virtual double getCurrentX()const;
    virtual double getCurrentY()const;
    virtual double getMotorLocationX(const double& inTime) const;
    virtual double getMotorLocationY(const double& inTime) const;
    virtual double getFireTime() const;
    virtual double timeUntilLocation(const double& inCurrentLocationX,const double& inCurrentLocationY,const double& inWantedLocationX,const double& inWantedLocationY)const;
    virtual void inCompletedCommands(const std::list<command>& inCommands,const double& inTime);
    virtual void inRunningCommands(const std::list<command>& inCommands,const double& inTime);

    //Destructor
    virtual ~drvMotorSim();
protected:
    //Members
    double currentX;
    double currentY;
    double wantedX;
    double wantedY;
    double lastCommandTime;
    double fireTime;
    double syncTime;
    double mutable stepDeg;
    double degPerStep;
    int maxDegreeStep;
    int minDegreeStep;
    int timeDelay;


    //Helper Methods
    double moveTo(double inAngle);
    double timeToMoveTo(const double& inAngle)const;
    void changeStep(const int& inStep)const;
};

#endif // __DRVMOTORSIM__
