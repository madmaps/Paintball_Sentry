#include "motionTrack.h"

//Constructer
//Default
motionTrack::motionTrack(void):minTargetSize(0),maxTargetSize(0),sizeAccuracy(0),yLocationAccuracy(0),colorAccuracy(0)
{
    camSettings.calibrateX=0;
    camSettings.calibrateY=0;
    camSettings.cameraAngleX=0;
    camSettings.cameraAngleY=0;
    camSettings.cameraDistance=0;
    camSettings.xShift=0;
    camSettings.yShift=0;
    camSettings.width=0;
    camSettings.height=0;
}

//Copy
motionTrack::motionTrack(const motionTrack& src):camera1(src.camera1),camera2(src.camera2),minTargetSize(src.minTargetSize),maxTargetSize(src.maxTargetSize),
    sizeAccuracy(src.sizeAccuracy),yLocationAccuracy(src.yLocationAccuracy),colorAccuracy(src.colorAccuracy),dataBase(src.dataBase),autoCalibrate(src.autoCalibrate)
{
    camSettings.calibrateX=src.camSettings.calibrateX;
    camSettings.calibrateY=src.camSettings.calibrateY;
    camSettings.cameraAngleX=src.camSettings.cameraAngleX;
    camSettings.cameraAngleY=src.camSettings.cameraAngleY;
    camSettings.cameraDistance=src.camSettings.cameraDistance;
    camSettings.xShift=src.camSettings.xShift;
    camSettings.yShift=src.camSettings.yShift;
    camSettings.width=src.camSettings.width;
    camSettings.height=src.camSettings.height;
}

//Move
motionTrack::motionTrack(motionTrack&& src):camera1(src.camera1),camera2(src.camera2),minTargetSize(src.minTargetSize),maxTargetSize(src.maxTargetSize),
    sizeAccuracy(src.sizeAccuracy),yLocationAccuracy(src.yLocationAccuracy),colorAccuracy(src.colorAccuracy),dataBase(src.dataBase),autoCalibrate(src.autoCalibrate)
{
    camSettings.calibrateX=src.camSettings.calibrateX;
    camSettings.calibrateY=src.camSettings.calibrateY;
    camSettings.cameraAngleX=src.camSettings.cameraAngleX;
    camSettings.cameraAngleY=src.camSettings.cameraAngleY;
    camSettings.cameraDistance=src.camSettings.cameraDistance;
    camSettings.xShift=src.camSettings.xShift;
    camSettings.yShift=src.camSettings.yShift;
    camSettings.width=src.camSettings.width;
    camSettings.height=src.camSettings.height;

}

//Operator Overloading
//Assignment
motionTrack& motionTrack::operator=(const motionTrack& rhs)
{
	if(this==&rhs)
	{
		return *this;
	}
    camSettings.calibrateX=rhs.camSettings.calibrateX;
    camSettings.calibrateY=rhs.camSettings.calibrateY;
    camSettings.cameraAngleX=rhs.camSettings.cameraAngleX;
    camSettings.cameraAngleY=rhs.camSettings.cameraAngleY;
    camSettings.cameraDistance=rhs.camSettings.cameraDistance;
    camSettings.xShift=rhs.camSettings.xShift;
    camSettings.yShift=rhs.camSettings.yShift;
    camSettings.width=rhs.camSettings.width;
    camSettings.height=rhs.camSettings.height;

	minTargetSize=rhs.minTargetSize;
	maxTargetSize=rhs.maxTargetSize;
	sizeAccuracy=rhs.sizeAccuracy;
	yLocationAccuracy=rhs.yLocationAccuracy;
	colorAccuracy=rhs.colorAccuracy;
	camera1=rhs.camera1;
	camera2=rhs.camera2;
	dataBase=rhs.dataBase;
    autoCalibrate=rhs.autoCalibrate;
	return *this;
}

//Move Assignment
motionTrack& motionTrack::operator=(motionTrack&& rhs)
{
	if(this==&rhs)
	{
		return *this;
	}
    camSettings.calibrateX=rhs.camSettings.calibrateX;
    camSettings.calibrateY=rhs.camSettings.calibrateY;
    camSettings.cameraAngleX=rhs.camSettings.cameraAngleX;
    camSettings.cameraAngleY=rhs.camSettings.cameraAngleY;
    camSettings.cameraDistance=rhs.camSettings.cameraDistance;
    camSettings.xShift=rhs.camSettings.xShift;
    camSettings.yShift=rhs.camSettings.yShift;
    camSettings.width=rhs.camSettings.width;
    camSettings.height=rhs.camSettings.height;
	minTargetSize=rhs.minTargetSize;
	maxTargetSize=rhs.maxTargetSize;
	sizeAccuracy=rhs.sizeAccuracy;
	yLocationAccuracy=rhs.yLocationAccuracy;
	colorAccuracy=rhs.colorAccuracy;
	camera1=rhs.camera1;
	camera2=rhs.camera2;
	dataBase=rhs.dataBase;
    autoCalibrate=rhs.autoCalibrate;
	return *this;
}

//Getters
double motionTrack::getUnitSize() const
{
	return camera1.getUnitSize();
}

double motionTrack::getUnitResolution() const
{
	return camera1.getUnitResolution();
}

double motionTrack::getPixelResolution() const
{
	return camera1.getPixelResolution();
}

double motionTrack::getCameraDistance() const
{
    return camSettings.cameraDistance;
}

double motionTrack::getCameraAngleX() const
{
    return camSettings.cameraAngleX;
}

double motionTrack::getCameraAngleY() const
{
    return camSettings.calibrateY;
}

double motionTrack::getMinTargetSize() const
{
	return minTargetSize;
}

double motionTrack::getMaxTargetSize() const
{
	return maxTargetSize;
}

double motionTrack::getColorAccuracy() const
{
	return colorAccuracy;
}

double motionTrack::getSizeAccuracy() const
{
	return sizeAccuracy;
}

double motionTrack::getYLocationAccuracy() const
{
	return yLocationAccuracy;
}

double motionTrack::getCalibrateX() const
{
    return camSettings.calibrateX;
}

double motionTrack::getCalibrateY() const
{
    return camSettings.calibrateY;
}

double motionTrack::getYShift() const
{
    return camSettings.yShift;
}

int motionTrack::getKeyFrameUpdateRate() const
{
	return camera1.getKeyFrameUpdateRate();
}

double motionTrack::getKeyFrameUpdateResolution() const
{
	return camera1.getKeyFrameUpdateResolution();
}

double motionTrack::getKeyFrameResetPercent() const
{
	return camera1.getKeyFrameReset();
}

double motionTrack::getMinTargetTime() const
{
    return dataBase.getMinTargetTime();
}

double motionTrack::getMaxTargetTime() const
{
    return dataBase.getMaxTargetTime();
}

double motionTrack::getCurrentFrameMovementCamera0() const
{
    return camera1.getCurrentFrameMovement();
}

double motionTrack::getCurrentFrameMovementCamera1() const
{
    return camera2.getCurrentFrameMovement();
}

bool motionTrack::getDebugMode() const
{
    return camera1.getDebugMode();
}

bool motionTrack::getViewFrameMode() const
{
    return camera1.getViewFrameMode();
}

double motionTrack::getMaxTargetAverage()const
{
    return dataBase.getMaxTargetAverage();
}

double motionTrack::getMinGradeValue()const
{
    return dataBase.getMinGradeValue();
}

double motionTrack::getDataBaseColorAcc()const
{
    return dataBase.getDataBaseColorAcc();
}

double motionTrack::getDataBaseLocationAcc()const
{
    return dataBase.getDataBaseLocationAcc();
}

double motionTrack::getXShift()const
{
    return camSettings.xShift;
}

double motionTrack::getWidth()const
{
    return camSettings.width;
}

double motionTrack::getHeight()const
{
    return camSettings.height;
}

//Setters
void motionTrack::setUnitSize(const double& inUnitSize)
{
	camera1.setUnitSize(inUnitSize);
	camera2.setUnitSize(inUnitSize);
}

void motionTrack::setUnitReslolution(const double& inUnitResolution)
{
	camera1.setUnitResolution(inUnitResolution);
	camera2.setUnitResolution(inUnitResolution);
}

void motionTrack::setPixelResolution(const double& inPixelResolution)
{
	camera1.setPixelResolution(inPixelResolution);
	camera2.setPixelResolution(inPixelResolution);
}

void motionTrack::setCameraDistance(const double& inCameraDistance)
{
    camSettings.cameraDistance=inCameraDistance;
}

void motionTrack::setCameraAngleX(const double& inCameraAngleX)
{
    camSettings.cameraAngleX=inCameraAngleX;
}

void motionTrack::setCameraAngleY(const double& inCameraAngleY)
{
    camSettings.cameraAngleY=inCameraAngleY;
}

void motionTrack::setMinTargetSize(const double& inMinTargetSize)
{
	minTargetSize=inMinTargetSize;
}

void motionTrack::setMaxTargetSize(const double& inMaxTargetSize)
{
	maxTargetSize=inMaxTargetSize;
}

void motionTrack::setColorAccuracy(const double& inColorAccuracy)
{
	colorAccuracy=inColorAccuracy;
}

void motionTrack::setSizeAccuracy(const double& inSizeAccuracy)
{
	sizeAccuracy=inSizeAccuracy;
}

void motionTrack::setYLocationAccuracy(const double& inYLocationAccuracy)
{
	yLocationAccuracy=inYLocationAccuracy;
}

void motionTrack::setCalibrateX(const double& inCalibrateX)
{
    camSettings.calibrateX=inCalibrateX;
}

void motionTrack::setCalibrateY(const double& inCalibrateY)
{
    camSettings.calibrateY=inCalibrateY;
}

void motionTrack::setYShift(const double& inYShift)
{
    camSettings.yShift=inYShift;
}

void motionTrack::setKeyFrameUpdateRate(const int& inKeyFrameUpdateRate)
{
	camera1.setKeyFrameUpdateRate(inKeyFrameUpdateRate);
	camera2.setKeyFrameUpdateRate(inKeyFrameUpdateRate);
}

void motionTrack::setKeyFrameUpdateResolution(const double& inKeyFrameUpdateResolution)
{
	camera1.setKeyFrameUpdateResolution(inKeyFrameUpdateResolution);
	camera2.setKeyFrameUpdateResolution(inKeyFrameUpdateResolution);
}

void motionTrack::setKeyFrameResetPercent(const double& inKeyFrameResetPercent)
{
	camera1.setKeyFrameReset(inKeyFrameResetPercent);
	camera2.setKeyFrameReset(inKeyFrameResetPercent);
}

void motionTrack::setKeyFrameUpdateResolutionCamera0(const double& inKeyFrameUpdateResolutionPercent)
{
    camera1.setKeyFrameUpdateResolution(inKeyFrameUpdateResolutionPercent);
}

void motionTrack::setKeyFrameUpdateResolutionCamera1(const double& inKeyFrameUpdateResolutionPercent)
{
    camera2.setKeyFrameUpdateResolution(inKeyFrameUpdateResolutionPercent);
}


void motionTrack::setMinTargetTime(const double& inMinTargetTime)
{
    dataBase.setMinTargetTime(inMinTargetTime);
}

void motionTrack::setMaxTargetTime(const double& inMaxTargetTime)
{
    dataBase.setMaxTargetTime(inMaxTargetTime);
}

void motionTrack::setDebugMode(const bool& inDebugMode)
{
    camera1.setDebugMode(inDebugMode);
    camera2.setDebugMode(inDebugMode);
}

void motionTrack::setViewFrameMode(const bool& inViewFrameMode)
{
    camera1.setViewFrameMode(inViewFrameMode);
    camera2.setViewFrameMode(inViewFrameMode);
}

void motionTrack::setMaxTargetAverage(const double& inMaxTargetAverage)
{
    dataBase.setMaxTargetAverage(inMaxTargetAverage);
}

void motionTrack::setMinGradeValue(const double& inMinGradeValue)
{
    dataBase.setMinGradeValue(inMinGradeValue);
}

void motionTrack::setDataBaseColorAcc(const double& inDataBaseColorAcc)
{
    dataBase.setDataBaseColorAcc(inDataBaseColorAcc);
}

void motionTrack::setDataBaseLocationAcc(const double& inDataBaseLocationAcc)
{
    dataBase.setDataBaseLocationAcc(inDataBaseLocationAcc);
}

void motionTrack::setXShift(const double& inXShift)
{
    camSettings.xShift=inXShift;
}

//Public Methods
void motionTrack::disableKeyFrameUpdate()
{
	camera1.disableKeyFrameUpdate();
	camera2.disableKeyFrameUpdate();
}

void motionTrack::enableKeyFrameUpdate()
{
	camera1.enableKeyFrameUpdate();
	camera2.enableKeyFrameUpdate();
}


std::vector<threeDTarget> motionTrack::analyze(frame* camera1NextFrame,frame* camera2NextFrame)
{
    double currentTimeStamp=0;
    camSettings.width=(double)camera1NextFrame->getWidth();
    camSettings.height=(double)camera1NextFrame->getHeight();
    if(camera1.willResetNextFrame())
    {
        camera2.forceReset();
    }
    if(camera2.willResetNextFrame())
    {
        camera1.forceReset();
    }
    auto camera0List = &(camera1 >> *camera1NextFrame);
    auto camera1List = &(camera2 >> *camera2NextFrame);
    std::vector<threeDTarget> returnTargets;

    if(camera0List->size()>0)
    {
        std::list<twoDTargets>::iterator iter = camera0List->begin();
        currentTimeStamp=iter->getTimeStamp();
    }

    camera0List->sort();
    camera1List->sort();
    std::list<targetPair> tempList;
    targetPair tempPair;
    if(camera0List->size()>0 && camera1List->size()>0)
    {
        bool loopBreak=0;
        std::list<twoDTargets>::iterator targetCompare0 = camera0List->begin();
        while(targetCompare0!=camera0List->end())
        {
            loopBreak=0;
            std::list<twoDTargets>::iterator targetCompare1 =camera1List->begin();
            while(targetCompare1 !=camera1List->end() && !loopBreak)
            {
                if(targetCompare0->isEqual(*targetCompare1,sizeAccuracy,yLocationAccuracy,colorAccuracy) && targetCompare0->getSize()>minTargetSize && targetCompare0->getSize()<maxTargetSize && targetCompare1->getSize() > minTargetSize && targetCompare1->getSize() < maxTargetSize)
                {
    //************************Potential Memeroy Problems(I think it's okay)**************************
                    tempPair.setFirstTarget(*targetCompare0);
                    tempPair.setSecondTarget(*targetCompare1);
                    targetCompare1=camera1List->erase(targetCompare1);
                    tempList.push_back(tempPair);
                    loopBreak=1;//Add Break look var here*************
                }
                targetCompare1++;
            }
            targetCompare0++;
        }

        tempList.sort();
        dataBase.updateData(currentTimeStamp);
        dataBase.addNewTargets(tempList,camSettings);
        returnTargets=dataBase.retrieveTargets(currentTimeStamp,camSettings);



    }
    camera0List->clear();
    camera1List->clear();
    if(camera0List!=0)
    {
        delete camera0List;
        camera0List=0;
    }
    if(camera1List!=0)
    {
        delete camera1List;
        camera1List=0;
    }
    return returnTargets;
}

int motionTrack::getDatabaseSize()
{
    return dataBase.getSize();
}

frame* motionTrack::getCamera0DebugFrame()
{
    return camera1.getDebugFrame();
}

frame* motionTrack::getCamera1DebugFrame()
{
    return camera2.getDebugFrame();
}

frame* motionTrack::getCamera0ViewFrame()
{
    return camera1.getViewFrame();
}

frame* motionTrack::getCamera1ViewFrame()
{
    return camera2.getViewFrame();
}

void motionTrack::setCalibrationTarget(const int& target,const double& inLocX,const double& inLocY,const double& inLocZ)
{
    targetPair tempTargetPair = dataBase.getLargestTargetPair();
    autoCalibrate.setTarget(target,tempTargetPair,inLocX,inLocY,inLocZ);
}

void motionTrack::calibrate()
{
    camSettings = autoCalibrate.calibrate(camSettings);
}

void motionTrack::clearCalibration()
{
    autoCalibrate.clear();
}

void motionTrack::setCamera0MaskFrame(const frame& inMaskFrame)
{
    camera1.setMaskFrame(inMaskFrame);
}

void motionTrack::setCamera1MaskFrame(const frame& inMaskFrame)
{
    camera2.setMaskFrame(inMaskFrame);
}

int motionTrack::getNumberOfTargets()const
{
    return dataBase.getNumberOfTargets();
}

//Destructor
motionTrack::~motionTrack(void)
{
}

//Helper Methods
