#include "laserAim.h"

//Constructors
//Default
laserAim::laserAim(void)
{
}

laserAim::laserAim(const laserAim& src)
{
}

laserAim::laserAim(laserAim&& src)
{
}

//Operator OverLoading
laserAim& laserAim::operator=(const laserAim& rhs)
{
    return *this;
}

laserAim& laserAim::operator=(laserAim&& rhs)
{
    return *this;
}

//Getters

//Setters

//Public Methods
double laserAim::calculateX(const double& inMountX,const double& inMountY,const double& inMountZ,
                              const double& inTargetLocationX,const double& inTargetLocationY,const double& inTargetLocationZ) const
{
    double angle=0;
	double x=inTargetLocationX-inMountX;
	double z=-inTargetLocationZ-inMountZ;
	if(z!=0)
	{
		angle=atan(x/z);
	}
	else
	{
		return 0;
	}
	angle=360*(angle/(3.1415926535*2));
	return angle;
}

double laserAim::calculateY(const double& inMountX,const double& inMountY,const double& inMountZ,
                              const double& inTargetLocationX,const double& inTargetLocationY,const double& inTargetLocationZ) const
{
    double angle=0;
	double x=inTargetLocationY-inMountY;
	double z=-inTargetLocationZ-inMountZ;
	if(z!=0)
	{
		angle=atan(x/z);
	}
	else
	{
		return 0;
	}
	angle=360*(angle/(3.1415926535*2));
	return angle;
}

double laserAim::calculateTime(const double& inMountX,const double& inMountY,const double& inMountZ,
                               const double& inTargetLocationX,const double& inTargetLocationY,const double& inTargetLocationZ) const
{
    return 0;
}



laserAim::~laserAim()
{
    //dtor
}
