#ifndef CALIBRATION_H
#define CALIBRATION_H
#include <vector>
#include <math.h>
#include "threeDTarget.h"
#include "cameraSettings.h"
#include "targetPair.h"


class calibration
{
public:
    //Constructors
    calibration(void);//Default
    calibration(const calibration& src);//Copy
    calibration(calibration&& src);//Move

    //Operator Overloading
    virtual calibration& operator=(const calibration& rhs);//Assignment
    virtual calibration& operator=(calibration&& rhs);//Move Assignment

    //Getters
    virtual double getTarget0LocX()const;
    virtual double getTarget0LocY()const;
    virtual double getTarget0LocZ()const;
    virtual double getTarget1LocX()const;
    virtual double getTarget1LocY()const;
    virtual double getTarget1LocZ()const;
    virtual targetPair getTarget0()const;
    virtual targetPair getTarget1()const;

    //Setters

    //Public Methods
    virtual void setTarget(const int& target,const targetPair& inTarget,const double& inLocX,const double& inLocY,const double& inLocZ);
    virtual cameraSettings calibrate(const cameraSettings& inCurrentSettings);
    virtual void clear();
    //Destructor
    virtual ~calibration(void);
protected:
    //Members
    targetPair* target0;
    targetPair* target1;
    double target0LocX;
    double target0LocY;
    double target0LocZ;
    double target1LocX;
    double target1LocY;
    double target1LocZ;
    //Helper Methods
    virtual void cleanup();
};


#endif // CALIBRATION_H
