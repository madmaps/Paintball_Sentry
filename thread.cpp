#include "thread.h"


Thread::Thread(QObject *parent) :
    QThread(parent),unitCuttoffVar(20),motor(),laser(),FC(),CTS()
{
    //Setup MotionTrack
    MT.setViewFrameMode(1);
    MT.setCalibrateX(-30);//62.3);//Shifts Camera 1 to Give you the Correct Depth
    MT.setCalibrateY(0);//Shifts Camera 1 to Line up the 2 cameras with each other
    MT.setYShift(0);//Shifts both Cameras evenly to Calibrate objects on the Y Axis
    //MT.setCameraAngleX(45);//49.5);//Sets the Camera Angles in the X, Used with CalibrateX to Correct for Depth(Z Axis)
    //MT.setCameraAngleY(31);//Sets the Camera Angles in the Y, Used to Calibrate Y Axis
    MT.setCameraAngleX(49.134);
    MT.setCameraAngleY(36.851);
    MT.setCameraDistance(4);//The distance between the 2 Camera Lenses, Also the Scale for all other measured Distance
    MT.setMaxTargetSize(100);//The maximum Size of the Target relating to the percent of the screen
    MT.setMinTargetSize(0.1);//The minimum Size of the target relating to the percent of the screen
    MT.setKeyFrameResetPercent(50);//What percent the key frame rate counter is reset to if it breaches the frame rate resolution
    MT.setKeyFrameUpdateRate(30);//Number of frames between key frame updates
    MT.setKeyFrameUpdateResolutionCamera0(1.7);
    MT.setKeyFrameUpdateResolutionCamera1(2);
    MT.setColorAccuracy(0.20);//The Color Accuracy for picking out targets between previous frames and between the 2 cameras
    MT.setSizeAccuracy(0.50);//The size Accuracy for picking out a target for the 2 cameras on the same timeStamp
    MT.setYLocationAccuracy(0.30);//The Accuracy of the Y location of a target on the screen for the 2 cameras on the same timestamp
    MT.setUnitReslolution(10);//The percent of the pixels that have to be on in a unit to be considered part of a target
    MT.setPixelResolution(20);//This number is subtracted from all pixels after the previous frames have been subtracted to get rid of minimal specs of light
    MT.setUnitSize(200);//The division of the screen in the X and in the Y Axis for the Units
    MT.setMinTargetTime(.5);//Minimum Time tracking a target before returning Target information
    MT.setMaxTargetTime(2);//Cuttoff time tracking a target
    MT.setMaxTargetAverage(3);//Maximum Number of Targets to Average together
    MT.setMinGradeValue(50);//Minimum Grade Value to pass Grading in the Database
    MT.setDataBaseColorAcc(0.50);//Used for Grading in the DataBase class
    MT.setDataBaseLocationAcc(5);//50);Used for Grading in the Database class
    MT.disableKeyFrameUpdate();
    cv::Mat maskFrame0,maskFrame1;
    maskFrame0 = cv::imread("mask0.jpg",CV_LOAD_IMAGE_COLOR);
    maskFrame1 = cv::imread("mask1.jpg",CV_LOAD_IMAGE_COLOR);
    frame* mask0 = new frame(maskFrame0,0,0);
    frame* mask1 = new frame(maskFrame1,0,0);
    //MT.setCamera0MaskFrame(*mask0);
    //MT.setCamera1MaskFrame(*mask1);
    delete mask0;
    delete mask1;

    //Aim Setup

    //MotorSimulator Setup
    motor.setStep(4);
    motor.setTimeDelay(8);

    //FireControl Setup
    FC.setMotorSimulator(&motor);
    FC.setAim(&laser);
    FC.setOutLookCutOff(3);
    FC.setBufferTime(0.2);
    FC.setMaxQueLength(5);
    FC.setMountX(0);
    FC.setMountY(0.8);
    FC.setMountZ(0.8);

    //CommandToSerial Setup
    CTS.setupSerialPort("/dev/ttyACM0");
    CTS.startCommandUpload();




    stopped = true;
}

void Thread::run()
{
    stopped=false;
    int counter=0;
    double locationX=0,locationY=0;
    while(!stopped)
    {

        auto durationTimeStamp(std::chrono::high_resolution_clock::now());
        auto d1=durationTimeStamp.time_since_epoch();
        auto startTime=durationTimeStamp.time_since_epoch();
        double timeStamp=0;

        //Setting up CommandToSerial*************
        durationTimeStamp = std::chrono::high_resolution_clock::now();
        d1=durationTimeStamp.time_since_epoch()-startTime;
        timeStamp=(double)d1.count()/1000000000;
        std::vector<command>timeSetupVector;
        command timeSetup;
        timeSetup.setCommandType(SYNC_TIME);
        timeSetup.setValue(timeStamp);
        timeSetup.setSync(1);
        timeSetupVector.push_back(timeSetup);
        CTS.pushCommands(timeSetupVector);
        int numberOfRunningCommands=1;
        std::vector<command> theCommands;
        //*****************************************


        unitCuttoffVar=10;
        frame* cam0Frame=0;
        frame* cam1Frame=0;
        cv::Mat frame0,frame1;

        std::vector<threeDTarget> theTargets;
        //cv::VideoCapture cap0(0),cap1(1);
        cv::VideoCapture cap0,cap1;
        cap0.open("test0.avi");
        cap1.open("test1.avi");
        if(!cap0.isOpened() || !cap1.isOpened())
        {
            stopped=1;
        }
        else
        {

            do
            {
                MT.setUnitReslolution(unitCuttoffVar);
                /*durationTimeStamp = std::chrono::high_resolution_clock::now();
                d1=durationTimeStamp.time_since_epoch()-startTime;
                timeStamp=(double)d1.count()/1000000000;*/
                timeStamp=(double)counter*.03333333;

                cap0.read(frame0);
                cap1.read(frame1);

                cam0Frame=new frame(frame0,timeStamp,0);
                cam1Frame=new frame(frame1,timeStamp,0);

                theTargets=MT.analyze(cam1Frame,cam0Frame);
                sendDatabaseSize(MT.getNumberOfTargets());

                if(theTargets.size()>0)
                {
                    changeText(QString(QString::number(theTargets.at(0).getSpeed(),'f',1)),QString::number(theTargets.at(0).getLocationX(),'f',1),QString::number(theTargets.at(0).getLocationY(),'f',1),QString::number(theTargets.at(0).getLocationZ(),'f',1));
                }
                else
                {
                    changeText(QString(tr("")),QString(tr("")),QString(tr("")),QString(tr("")));
                }
                if(MT.getDebugMode())
                {
                    setDebugImage(MT.getCamera0DebugFrame(),MT.getCamera1DebugFrame());
                }
                if(1)
                {
                    setViewImage(MT.getCamera0ViewFrame(),MT.getCamera1ViewFrame());
                }
                setCameraMovement(MT.getCurrentFrameMovementCamera0(),MT.getCurrentFrameMovementCamera1());
                sendTargets(theTargets);
                //sendMotorXY(FC.getMotorAngleX(timeStamp),FC.getMotorAngleY(timeStamp));
                //sendMotorXY(motor.getWantedX(),motor.getWantedY());


                durationTimeStamp = std::chrono::high_resolution_clock::now();
                d1=durationTimeStamp.time_since_epoch()-startTime;
                timeStamp=(double)d1.count()/1000000000;

                //****Getting a vector of a list of Running Commands and a list of Completed commands*******
                auto runningCommands=CTS.completedAndRunningCommandList();
                //*************************************************************

                //********Subtracting the amount of running commands by the list of finished commands*************
                numberOfRunningCommands-=runningCommands.at(1).size();
                //************************************************************************************************

                //*********Updateing the FireControl Class with the Finished commands and the Current running commands***********
                if(runningCommands.at(1).size()>0)
                {
                    FC.inFinishedCommands(runningCommands.at(1),timeStamp);
                }
                if(runningCommands.at(0).size()>0)
                {
                    FC.inRunningCommands(runningCommands.at(0),timeStamp);
                }
                //*****************************************************************************************************************

                //*****************Passing in a Vector of Targets to FireControl and getting a Vector of Commands*************
                theCommands=FC.process(theTargets,timeStamp);
                theTargets.clear();
                //************************************************************************************************************

                //************If there are no current Commands running Push more Commands to the CommandtoSerial Class************
                if(numberOfRunningCommands==0)// || (numberOfRunningCommands == 3 && FC.getCommandFinishTime()+timeBuffer>timeStamp))//numberOfRunningCommands==3 || numberOfRunningCommands==0) && FC.getCommandFinishTime()+10>timeStamp)// && go==1)
                {
                    if(theCommands.size()>1)
                    {
                        locationX+=theCommands.at(0).getValue();
                        locationY+=theCommands.at(1).getValue();
                        sendMotorXY(locationX,locationY);
                    }
                    numberOfRunningCommands+=theCommands.size();
                    CTS.pushCommands(theCommands);
                }
               /* if(numberOfRunningCommands>3)
                {
                    std::cout << "WORKING!";
                }*/
                //********************************************

                theCommands.clear();









                counter++;
            }while(!stopped);
        }
        cap0.release();
        cap1.release();
    }

    changeText(QString(tr("")),QString(tr("")),QString(tr("")),QString(tr("")));

}

bool Thread::isRunning() const
{
    return !stopped;
}

void Thread::stop()
{
    stopped = true;
}

void Thread::setDebugMode(const bool& inDebugMode)
{
    MT.setDebugMode(inDebugMode);
}

void Thread::setPixelCuttoff(const int& inPixelCuttoff)
{
    MT.setPixelResolution(inPixelCuttoff);
}

void Thread::setUnitCuttoff(const int& inUnitCuttoff)
{
    unitCuttoffVar=inUnitCuttoff;
}

void Thread::yAccChange(int value)
{
    double inValue=(double)(value)/100;
    MT.setYLocationAccuracy(inValue);
}

void Thread::sizeAccChange(int value)
{
    double inValue=(double)(value)/100;
    MT.setSizeAccuracy(inValue);
}

void Thread::colorAccChange(int value)
{
    double inValue=(double)(value)/100;
    MT.setColorAccuracy(inValue);
}

void Thread::changeKeyFrameUpdate(bool inValue)
{
    if(inValue)
    {
        MT.enableKeyFrameUpdate();
    }
    else
    {
        MT.disableKeyFrameUpdate();
    }
}

void Thread::setCamera0Reset(const double &inValue)
{
    MT.setKeyFrameUpdateResolutionCamera0((double)(inValue)/10);
}

void Thread::setCamera1Reset(const double &inValue)
{
    MT.setKeyFrameUpdateResolutionCamera1((double)(inValue)/10);
}

void Thread::yShiftChanged(int value)
{

    MT.setYShift(value);
}

void Thread::xShiftChanged(int value)
{
    MT.setXShift(value);
}

void Thread::xCalibrationChanged(int value)
{
    MT.setCalibrateX(value);
}

void Thread::xCameraAngleChanged(int value)
{
    MT.setCameraAngleX(value);
}

void Thread::yCalibrationChanged(int value)
{
    MT.setCalibrateY(value);
}

void Thread::yCameraAngleChanged(int value)
{
    MT.setCameraAngleY(value);
}

void Thread::setTarget1Calibration(const double& value)
{
    MT.setCalibrationTarget(1,0,0,value);
}

void Thread::startCalibration()
{
    MT.calibrate();
}

void Thread::setTarget0Calibration(const double& value)
{
    MT.setCalibrationTarget(0,0,0,value);
}

void Thread::changeTimeBuffer(int value)
{
    timeBuffer=(double)value/100;
}


