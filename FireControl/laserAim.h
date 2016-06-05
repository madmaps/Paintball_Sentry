#ifndef __LASERAIM__
#define __LASERAIM__

#include "aim.h"


class laserAim : public aim
{
public:
    //Constructors
    laserAim(void);//Default
    laserAim(const laserAim& src);//Copy
    laserAim(laserAim&& src);//Move

    //Operator Overloading
    virtual laserAim& operator=(const laserAim& rhs);//Assignment
    virtual laserAim& operator=(laserAim&& rhs);//Move Assignment

    //Getters

    //Setters

    //Public Methods
    virtual double calculateX(const double& inMountX,const double& inMountY,const double& inMountZ,
                              const double& inTargetLocationX,const double& inTargetLocationY,const double& inTargetLocationZ) const;
    virtual double calculateY(const double& inMountX,const double& inMountY,const double& inMountZ,
                              const double& inTargetLocationX,const double& inTargetLocationY,const double& inTargetLocationZ) const;
    virtual double calculateTime(const double& inMountX,const double& inMountY,const double& inMountZ,
                                 const double& inTargetLocationX,const double& inTargetLocationY,const double& inTargetLocationZ) const;


    //Destructor
    virtual ~laserAim();

protected:
    //Members

    //Helper Methods
};

#endif // __LASERAIM__
