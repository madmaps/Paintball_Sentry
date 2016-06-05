#ifndef __MOTORSIMULATOR__
#define __MOTORSIMULATOR__
#include <list>
#include "command.h"


class motorSimulator
{
public:
    //Constructors
    motorSimulator();//Default

    //Operator Overloading

    //Getters

    //Setters

    //Public Methods
    virtual void setMotorLocationX(const double& inMotorLocationX)=0;
    virtual void setMotorLocationY(const double& inMotorLocationY)=0;
    virtual double getMotorLocationX(const double& inTime) const=0;
    virtual double getMotorLocationY(const double& inTime) const=0;
    virtual double getFireTime() const=0;
    virtual double timeUntilLocation(const double& inCurrentLocationX,const double& inCurrentLocationY,const double& inWantedAngleX,const double& inWantedAngleY)const=0;
    virtual void inCompletedCommands(const std::list<command>& inCommands,const double& inTime)=0;
    virtual void inRunningCommands(const std::list<command>& inCommands,const double& inTime)=0;

    //Destructor
    virtual ~motorSimulator();

protected:
    //Members

    //Helper Methods
};

#endif // __MOTORSIMULATOR__
