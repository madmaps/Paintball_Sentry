#ifndef __TARGETPAIR__
#define __TARGETPAIR__
#include <list>
#include "twoDTargets.h"
#include "threeDTarget.h"
#include "cameraSettings.h"
#include <math.h>

class targetPair
{
public:
    //Constructers
    targetPair(void);//Default
    targetPair(targetPair& src);//Copy
    targetPair(const targetPair& src);
    targetPair(targetPair&& src);//Move

    //Operator Overloading
    virtual targetPair& operator=(const targetPair& rhs);//Assignment
    virtual targetPair& operator=(targetPair&& rhs);//Move Assignment
    virtual bool operator>(const targetPair& rhs)const;//Greater Than
    virtual bool operator>=(const targetPair& rhs) const;//Greater or Equal
    virtual bool operator<=(const targetPair& rhs) const;//Less or Equal
    virtual bool operator<(const targetPair& rhs) const;//Less Than
    virtual bool isEqual(const targetPair& rhs,const double& inColorAccuracy) const;

    //Getters
    virtual twoDTargets* getFirstTarget()const;
    virtual twoDTargets* getSecondTarget()const;
    virtual double getTimeStamp()const;

    //Setters
    virtual void setFirstTarget(twoDTargets& inTarget);
    virtual void setSecondTarget(twoDTargets& inTarget);

    //Public Methods
    virtual threeDTarget getTarget(const cameraSettings& inCameraSettings)const;
    virtual double grade(const std::list<targetPair>& inList,const double& inColorAcc,const double& inLocationAcc,const cameraSettings& inSettings)const;

    //Destructor
    virtual ~targetPair();

    protected:
    private:
    twoDTargets* firstTarget;
    twoDTargets* secondTarget;

    //Helper Methods
    virtual double calculateXAngle(const double& inLocationX,const double& inCameraAngle,const double& inWidth,const double& inCalibrate) const;
	virtual double calculateYAngle(const double& inLocationY,const double& inCameraAngle,const double& inHeight,const double& inYShift,const double& inCalibrateY) const;
	virtual double calculateDistance(const double& inAngle1,const double& inAngle2,const double& inYAngle,const double& inCameraDistance) const;
	virtual double calculateX(const double& inAngle1,const double& inAngle2,const double& cameraDistance) const;
	virtual double calculateY(const double& inAngle1,const double& inAngle2,const double& inYAngle,const double& cameraDistance) const;
	virtual double calculateZ(const double& inAngle1,const double& inAngle2,const double& cameraDistance) const;


    virtual void cleanup();

};

#endif // __TARGETPAIR__
