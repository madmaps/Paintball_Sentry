#include "aim.h"

//Constructors

//Operator Overloading

//Getters

//Setters

//Public Methods

//Destructor

//Helper Methods


//double aim::calculateX(const double& inMountX,const double& inMountY,const double& inMountZ,
//					   const double& inTargetLocationX,const double& inTargetLocationY,const double& inTargetLocationZ) const
//{
//	double angle=0;
//	double x=inTargetLocationX-inMountX;
//	double z=inTargetLocationZ-inMountZ;
//	if(z!=0)
//	{
//		angle=atan(x/z);
//	}
//	else
//	{
//		return 0;
//	}
//	angle=360*(angle/(3.1415926535*2));
//	return angle;
//}
//
//double aim::calculateY(const double& inMountX,const double& inMountY,const double& inMountZ,
//							  const double& inTargetLocationX,const double& inTargetLocationY,const double& inTargetLocationZ) const
//{
//	double angle=0;
//	double x=inTargetLocationZ-inMountZ;
//	double y=inTargetLocationY-inMountY;
//	if(x!=0)
//	{
//		angle=atan((pow(velocity,2)+sqrt(pow(velocity,4)-gravity*((gravity*pow(x,2))+(2*y*pow(velocity,2)))))/(gravity*x));
//	}
//	else
//	{
//		return 0;
//	}
//	angle=360*(angle/(3.1415926535*2));
//	return angle;
//
//}
//
//Destructor

aim::aim(void)
{
}

aim::~aim(void)
{
}

//Helper Methods

////Constructors
////Default
//aim::aim(void):motorSpeed(0),motorLocationX(0),motorLocationY(0),bufferTime(0),averageBufferSize(0),outLookCutOff(0),projectileWeight(0),
//			   projectileSize(0),projectileShape(0),projectileRotation(0),projectileVelocity(0),barametricPressure(0),windSpeed(0),windDirection(0),
//			   mountX(0),mountY(0),mountZ(0),calibrationX(0),calibrationY(0),targetSelection(0)
//{
//}
//
////Copy
//aim::aim(const aim& src):motorSpeed(src.motorSpeed),motorLocationX(src.motorLocationX),motorLocationY(src.motorLocationY),bufferTime(src.bufferTime),
//	                     averageBufferSize(src.averageBufferSize),outLookCutOff(src.outLookCutOff),projectileWeight(src.projectileWeight),projectileSize(src.projectileSize),
//						 projectileShape(src.projectileShape),projectileRotation(src.projectileRotation),projectileVelocity(src.projectileVelocity),
//						 barametricPressure(src.barametricPressure),windSpeed(src.windSpeed),windDirection(src.windDirection),mountX(src.mountX),mountY(src.mountY),
//						 mountZ(src.mountZ),calibrationX(src.calibrationX),calibrationY(src.calibrationY),targetSelection(src.targetSelection)
//{
//}
//
////Move
//aim::aim(aim&& src):motorSpeed(src.motorSpeed),motorLocationX(src.motorLocationX),motorLocationY(src.motorLocationY),bufferTime(src.bufferTime),
//	                     averageBufferSize(src.averageBufferSize),outLookCutOff(src.outLookCutOff),projectileWeight(src.projectileWeight),projectileSize(src.projectileSize),
//						 projectileShape(src.projectileShape),projectileRotation(src.projectileRotation),projectileVelocity(src.projectileVelocity),
//						 barametricPressure(src.barametricPressure),windSpeed(src.windSpeed),windDirection(src.windDirection),mountX(src.mountX),mountY(src.mountY),
//						 mountZ(src.mountZ),calibrationX(src.calibrationX),calibrationY(src.calibrationY),targetSelection(src.targetSelection)
//{
//}
//
////Operator Overloading
////Assignment
//aim& aim::operator=(const aim& rhs)
//{
//	if(&rhs==this)
//	{
//		return *this;
//	}
//	motorSpeed=rhs.motorSpeed;
//	motorLocationX=rhs.motorLocationX;
//	motorLocationY=rhs.motorLocationY;
//	bufferTime=rhs.bufferTime;
//	averageBufferSize=rhs.averageBufferSize;
//	outLookCutOff=rhs.outLookCutOff;
//	projectileWeight=rhs.projectileWeight;
//	projectileSize=rhs.projectileSize;
//	projectileShape=rhs.projectileShape;
//	projectileRotation=rhs.projectileRotation;
//	projectileVelocity=rhs.projectileVelocity;
//	barametricPressure=rhs.barametricPressure;
//	windSpeed=rhs.windSpeed;
//	windDirection=rhs.windDirection;
//	mountX=rhs.mountX;
//	mountY=rhs.mountY;
//	mountZ=rhs.mountZ;
//	calibrationX=rhs.calibrationX;
//	calibrationY=rhs.calibrationY;
//	targetSelection=rhs.targetSelection;
//
//	return *this;
//}
//
////Move Assignment
//aim& aim::operator=(aim&& rhs)
//{
//	if(&rhs==this)
//	{
//		return *this;
//	}
//	motorSpeed=rhs.motorSpeed;
//	motorLocationX=rhs.motorLocationX;
//	motorLocationY=rhs.motorLocationY;
//	bufferTime=rhs.bufferTime;
//	averageBufferSize=rhs.averageBufferSize;
//	outLookCutOff=rhs.outLookCutOff;
//	projectileWeight=rhs.projectileWeight;
//	projectileSize=rhs.projectileSize;
//	projectileShape=rhs.projectileShape;
//	projectileRotation=rhs.projectileRotation;
//	projectileVelocity=rhs.projectileVelocity;
//	barametricPressure=rhs.barametricPressure;
//	windSpeed=rhs.windSpeed;
//	windDirection=rhs.windDirection;
//	mountX=rhs.mountX;
//	mountY=rhs.mountY;
//	mountZ=rhs.mountZ;
//	calibrationX=rhs.calibrationX;
//	calibrationY=rhs.calibrationY;
//	targetSelection=rhs.targetSelection;
//
//	return *this;
//}
//
////Getters
//double aim::getMotorSpeed() const
//{
//	return motorSpeed;
//}
//
//double aim::getMotorLocationX() const
//{
//	return motorLocationX;
//}
//
//double aim::getMotorLocationY() const
//{
//	return motorLocationY;
//}
//
//double aim::getBufferTime() const
//{
//	return bufferTime;
//}
//
//int aim::getAvgBufferSize() const
//{
//	return averageBufferSize;
//}
//
//int aim::getOutLookCutOff() const
//{
//	return outLookCutOff;
//}
//
//double aim::getProjectileWeight() const
//{
//	return projectileWeight;
//}
//
//double aim::getProjectileSize() const
//{
//	return projectileSize;
//}
//
//int aim::getProjectileShape() const
//{
//	return projectileShape;
//}
//
//double aim::getProjectileRotation() const
//{
//	return projectileRotation;
//}
//
//double aim::getProjectileVelocity() const
//{
//	return projectileVelocity;
//}
//
//double aim::getBarametricPressure() const
//{
//	return barametricPressure;
//}
//
//double aim::getWindSpeed() const
//{
//	return windSpeed;
//}
//
//double aim::getWindDirection() const
//{
//	return windDirection;
//}
//
//double aim::getMountX() const
//{
//	return mountX;
//}
//
//double aim::getMountY() const
//{
//	return mountY;
//}
//
//double aim::getMountZ() const
//{
//	return mountZ;
//}
//
//double aim::getCalibrationX() const
//{
//	return calibrationX;
//}
//
//double aim::getCalibrationY() const
//{
//	return calibrationY;
//}
//
//int aim::getTargetSelection() const
//{
//	return targetSelection;
//}
//
////Setters
//void aim::setMotorSpeed(const double& inMotorSpeed)
//{
//	motorSpeed=inMotorSpeed;
//}
//
//void aim::setMotorLocationX(const double& inMotorLocationX)
//{
//	motorLocationX=inMotorLocationX;
//}
//
//void aim::setMotorLocationY(const double& inMotorLocationY)
//{
//	motorLocationY=inMotorLocationY;
//}
//
//void aim::setBufferTime(const double& inBufferTime)
//{
//	bufferTime=inBufferTime;
//}
//
//void aim::setAverageBufferSize(const int& inAverageBufferSize)
//{
//	averageBufferSize=inAverageBufferSize;
//}
//
//void aim::setOutLookCutOff(const int& inOutLookCutOff)
//{
//	outLookCutOff=inOutLookCutOff;
//}
//
//void aim::setProjectileWeight(const double& inProjectileWeight)
//{
//	projectileWeight=inProjectileWeight;
//}
//
//void aim::setProjectileSize(const double& inProjectileSize)
//{
//	projectileSize=inProjectileSize;
//}
//
//void aim::setProjectileShape(const int& inProjectileShape)
//{
//	projectileShape=inProjectileShape;
//}
//
//void aim::setProjectileRotation(const double& inProjectileRotation)
//{
//	projectileRotation=inProjectileRotation;
//}
//
//void aim::setProjectileVelocity(const double& inProjectileVelocity)
//{
//	projectileVelocity=inProjectileVelocity;
//}
//
//void aim::setBarametricPressure(const double& inBarametricPressure)
//{
//	barametricPressure=inBarametricPressure;
//}
//
//void aim::setWindSpeed(const double& inWindSpeed)
//{
//	windSpeed=inWindSpeed;
//}
//
//void aim::setWindDirection(const double& inWindDirection)
//{
//	windDirection=inWindDirection;
//}
//
//void aim::setMountX(const double& inMountX)
//{
//	mountX=inMountX;
//}
//
//void aim::setMountY(const double& inMountY)
//{
//	mountY=inMountY;
//}
//
//void aim::setMountZ(const double& inMountZ)
//{
//	mountZ=inMountZ;
//}
//
//void aim::setCalibrationX(const double& inCalibrationX)
//{
//	calibrationX=inCalibrationX;
//}
//
//void aim::setCalibrationY(const double& inCalibrationY)
//{
//	calibrationY=inCalibrationY;
//}
//
//void aim::setTargetSelection(const int& inTargetSelection)
//{
//	targetSelection=inTargetSelection;
//}
//
////Public Methods
//
////Destructor
//aim::~aim(void)
//{
//	cleanup();
//}
//
////Helper Methods
//void aim::cleanup()
//{
//}
