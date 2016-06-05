#ifndef __TARGETDATABASE__
#define __TARGETDATABASE__
#include "targetPair.h"
#include "threeDTarget.h"
#include "cameraSettings.h"
#include <vector>
#include <list>
#include <math.h>
#include <iostream>


class targetDatabase
{
public:
    //Constructors
    targetDatabase(void);//Default
    targetDatabase(const targetDatabase& src);//Copy
    targetDatabase(targetDatabase& src);
    targetDatabase(targetDatabase&& src);//Move

    //Operator Overloading
    virtual targetDatabase& operator=(const targetDatabase& rhs);//Assignment
    virtual targetDatabase& operator=(targetDatabase&& rhs);//Move Assignment

    //Getters
    virtual double getMaxTargetTime()const;
    virtual double getMinTargetTime()const;
    virtual double getMaxTargetAverage()const;
    virtual double getMinGradeValue()const;
    virtual double getDataBaseColorAcc()const;
    virtual double getDataBaseLocationAcc()const;

    //Setters
    virtual void setMaxTargetTime(const double& inMaxTargetTime);
    virtual void setMinTargetTime(const double& inMinTargetTime);
    virtual void setMaxTargetAverage(const double& inMaxTargetAverage);
    virtual void setMinGradeValue(const double& inMinGradeValue);
    virtual void setDataBaseColorAcc(const double& inDataBaseColorAcc);
    virtual void setDataBaseLocationAcc(const double& inDataBaseLocationAcc);

    //Public Methods
    /*virtual void addNewTargets(std::list<targetPair>& inTargetList,const double& inCameraAngleX,const double& inCameraAngleY,
                               const double& inCalibrateX,const double& inCalibrateY,const double& inYShift,const double& inXShift,
                               const double& inWidth,const double& inHeight,const double& inCameraDistance);*/
    virtual void addNewTargets(std::list<targetPair>& inTargetList,const cameraSettings& inSettings);
    virtual void updateData(const double& inTimeStamp);
    virtual std::vector<threeDTarget> retrieveTargets(const double& inTimeStamp,const cameraSettings& inSettings);
    virtual targetPair getLargestTargetPair()const;
    virtual int getSize();
    virtual int getNumberOfTargets()const;



    //Destructor
    virtual ~targetDatabase();

protected:
private:
    //Members
    std::list<std::list<targetPair>> dataLists;
    double maxTargetTime;
    double minTargetTime;
    double maxTargetAverage;
    double minGradeValue;
    double dataBaseColorAcc;
    double dataBaseLocationAcc;
    //Helper Methods
    std::list<std::list<double>> calculateGrades(const std::list<targetPair>& inTargetPairs,const cameraSettings& inSettings)const;
    //virtual void cleanup();
};

#endif // __TARGETDATABASE__
