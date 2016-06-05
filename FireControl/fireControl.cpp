#include "fireControl.h"

//Constructors
//Default
fireControl::fireControl(void):aimControl(0),motorFunctions(0),bufferTime(.2),outLookCutOff(3),
							   mountX(0),mountY(0),mountZ(0),calibrationX(0),calibrationY(0),
							   targetSelection(0),maxQueLength(5),onHold(0)
{
}

//Copy
fireControl::fireControl(const fireControl& src):aimControl(src.aimControl),motorFunctions(src.motorFunctions),bufferTime(src.bufferTime),outLookCutOff(src.outLookCutOff),
												 mountX(src.mountX),mountY(src.mountY),mountZ(src.mountZ),calibrationX(src.calibrationX),calibrationY(src.calibrationY),
												 targetSelection(src.targetSelection),maxQueLength(src.maxQueLength),onHold(src.onHold),targetQue(src.targetQue)
{
}

//Move
fireControl::fireControl(fireControl&& src):aimControl(src.aimControl),motorFunctions(src.motorFunctions),bufferTime(src.bufferTime),outLookCutOff(src.outLookCutOff),
											mountX(src.mountX),mountY(src.mountY),mountZ(src.mountZ),calibrationX(src.calibrationX),calibrationY(src.calibrationY),
											targetSelection(src.targetSelection),maxQueLength(src.maxQueLength),onHold(src.onHold),targetQue(src.targetQue)
{
}

//Operator Overloading
//Assignment
fireControl& fireControl::operator=(const fireControl& rhs)
{
	if(this==&rhs)
	{
		return *this;
	}
	aimControl=rhs.aimControl;
	motorFunctions=rhs.motorFunctions;
	targetQue=rhs.targetQue;
	bufferTime=rhs.bufferTime;
	outLookCutOff=rhs.outLookCutOff;
	mountX=rhs.mountX;
	mountY=rhs.mountY;
	mountZ=rhs.mountZ;
	calibrationX=rhs.calibrationX;
	calibrationY=rhs.calibrationY;
	targetSelection=rhs.targetSelection;
	maxQueLength=rhs.maxQueLength;
	onHold=rhs.onHold;
	return *this;
}

//Move Assignment
fireControl& fireControl::operator=(fireControl&& rhs)
{
	if(this==&rhs)
	{
		return *this;
	}
	aimControl=rhs.aimControl;
	motorFunctions=rhs.motorFunctions;
	targetQue=rhs.targetQue;
	bufferTime=rhs.bufferTime;
	outLookCutOff=rhs.outLookCutOff;
	mountX=rhs.mountX;
	mountY=rhs.mountY;
	mountZ=rhs.mountZ;
	calibrationX=rhs.calibrationX;
	calibrationY=rhs.calibrationY;
	targetSelection=rhs.targetSelection;
	maxQueLength=rhs.maxQueLength;
	onHold=rhs.onHold;
	return *this;
}

//Getters
aim* fireControl::getAim() const
{
	return aimControl;
}

motorSimulator* fireControl::getMotorSimulator() const
{
	return motorFunctions;
}

double fireControl::getMotorAngleX(const double& inTime) const
{
	if(motorFunctions!=0)
	{
		return motorFunctions->getMotorLocationX(inTime);
	}
	return 0;
}

double fireControl::getMotorAngleY(const double& inTime) const
{
	if(motorFunctions!=0)
	{
		return motorFunctions->getMotorLocationY(inTime);
	}
	return 0;
}

double fireControl::getOutLookCutOff() const
{
	return outLookCutOff;
}

double fireControl::getMountX() const
{
	return mountX;
}

double fireControl::getMountY() const
{
	return mountY;
}

double fireControl::getMountZ() const
{
	return mountZ;
}

double fireControl::getCalibrationX() const
{
	return calibrationX;
}

double fireControl::getCalibrationY() const
{
	return calibrationY;
}

int fireControl::getTargetSelection() const
{
	return targetSelection;
}

int fireControl::getMaxQueLength() const
{
	return maxQueLength;
}

bool fireControl::getOnHold() const
{
	return onHold;
}

//Setters
void fireControl::setAim(aim* inAim)
{
	aimControl=inAim;
}

void fireControl::setMotorSimulator(motorSimulator* inMotorSimulator)
{
	motorFunctions=inMotorSimulator;
}

void fireControl::setMotorAngleX(const double& inMotorAngleX)
{
	if(motorFunctions!=0)
	{
		motorFunctions->setMotorLocationX(inMotorAngleX);
	}
}

void fireControl::setMotorAngleY(const double& inMotorAngleY)
{
	if(motorFunctions!=0)
	{
		motorFunctions->setMotorLocationY(inMotorAngleY);
	}
}

void fireControl::setBufferTime(const double& inBufferTime)
{
	bufferTime=inBufferTime;
}

void fireControl::setOutLookCutOff(const double& inOutLookCutOff)
{
	outLookCutOff=inOutLookCutOff;
}

void fireControl::setMountX(const double& inMountX)
{
	mountX=inMountX;
}

void fireControl::setMountY(const double& inMountY)
{
	mountY=inMountY;
}

void fireControl::setMountZ(const double& inMountZ)
{
	mountZ=inMountZ;
}

void fireControl::setCalibrationX(const double& inCalibrationX)
{
	calibrationX=inCalibrationX;
}

void fireControl::setCalibrationY(const double& inCalibrationY)
{
	calibrationY=inCalibrationY;
}

void fireControl::setTargetSelection(const int& inTargetSelection)
{
	targetSelection=inTargetSelection;
}

void fireControl::setMaxQueLength(const int& inMaxQueLength)
{
	maxQueLength=inMaxQueLength;
}

//Public Methods
std::vector<command> fireControl::process(std::vector<threeDTarget> inTargets,const double& inTimeStamp)
{
	if(inTargets.size()>0 && (aimControl!=0 || motorFunctions!=0))
	{
		updateQue(selectTarget(inTargets),inTimeStamp);
		std::array<double,3> fireSolution=calculateFireSolution(chooseTarget(inTimeStamp),inTimeStamp);
		if(onHold || fireSolution.at(0)==-1)
		{
			std::vector<command> tempCommands;
			return tempCommands;
		}
		else
		{
			return packageCommands(fireSolution,inTimeStamp);
		}
	}
	else
	{
		std::vector<command> tempCommands;
		return tempCommands;
	}
}

void fireControl::inFinishedCommands(std::list<command> inFinishedCommands,const double& inTime)
{
    motorFunctions->inCompletedCommands(inFinishedCommands,inTime);
}

void fireControl::inRunningCommands(std::list<command> inRunningCommands,const double& inTime)
{
    motorFunctions->inRunningCommands(inRunningCommands,inTime);
}

void fireControl::hold()
{
	onHold=1;
}

void fireControl::unHold()
{
	onHold=0;
}

double fireControl::getCommandFinishTime() const
{
    return lastCommandTime;
}

//Destructor
fireControl::~fireControl(void)
{
	cleanup();
}

//Helper Methods
void fireControl::cleanup()
{
}

std::vector<threeDTarget>::iterator fireControl::selectTarget(std::vector<threeDTarget>& inTargets) const
{
	int targetMode=floor((double)targetSelection/2);
	inTargets.at(0).setCompareMode(targetMode);
	if(targetSelection%2)
	{
		return std::min_element(inTargets.begin(),inTargets.end());
	}
	return std::max_element(inTargets.begin(),inTargets.end());
}

void fireControl::updateQue(std::vector<threeDTarget>::iterator inTarget,const double& inTimeStamp)
{
	int i=targetQue.size()-1;
	while(i>0)
	{
		if(targetQue.at(i).getTimeStamp()+outLookCutOff<inTimeStamp)
		{
			targetQue.pop_back();
		}
		else
		{
			break;
		}
		i--;
	}
	if(targetQue.size()>maxQueLength-1)
	{
		targetQue.pop_back();
	}
	if(outLookCutOff-(inTimeStamp-inTarget->getTimeStamp())>0)
	{
		targetQue.push_front(*inTarget);
	}
}

std::deque<threeDTarget>::iterator fireControl::chooseTarget(const double& inTime)
{
	std::array<double,3> fireSolution;
	double avgDenominator=0;
	double timeChange=0;
	double avgX=0;
	double avgY=0;

	for(std::deque<threeDTarget>::iterator itor=targetQue.begin();itor<targetQue.end();itor++)
	{
		fireSolution=calculateFireSolution(itor,inTime);
		if(fireSolution.at(0)>=0)
		{
			timeChange=(inTime+outLookCutOff)-fireSolution.at(0);
			//std::cout << "****************************************" << std::endl << "timeChange: " << timeChange << std::endl;
			timeChange=3.141592653589*pow(timeChange,2);
			//std::cout << "timeChange: " << timeChange << std::endl;
			avgX+=timeChange*fireSolution.at(1);
			avgY+=timeChange*fireSolution.at(2);
			//std::cout << "avgX: " << avgX << "   avgY: " << avgY << std::endl;
			avgDenominator+=timeChange;
			//std::cout << "avgDenominator: " << avgDenominator << std::endl;
			//std::cout << "avgX: " << avgX << "    avgY: " << avgY << std::endl << "****************************************" << std::endl;

		}
	}

    avgX=avgX/avgDenominator;
    avgY=avgY/avgDenominator;


	double m=(motorFunctions->getMotorLocationY(inTime)-avgY)/(motorFunctions->getMotorLocationX(inTime)-avgX);
	double b=avgY-(m*avgX);
	double firstDistance,secondDistance,bestDistance;
	bestDistance=999999999;
	std::deque<threeDTarget>::iterator best=targetQue.end();
	for(std::deque<threeDTarget>::iterator itor=targetQue.begin();itor<targetQue.end();itor++)
	{
		fireSolution=calculateFireSolution(itor,inTime);
		if(fireSolution.at(0)>=0)
		{
			firstDistance=abs(fireSolution.at(2)-(m*fireSolution.at(1))-b)/sqrt(pow(m,2)+1);
			secondDistance=sqrt(pow(motorFunctions->getMotorLocationX(inTime)-fireSolution.at(1),2)+pow(motorFunctions->getMotorLocationY(inTime)-fireSolution.at(2),2));
			if(bestDistance>firstDistance+secondDistance*2)
			{
				bestDistance=firstDistance+secondDistance*2;
				best=itor;
			}
		}
	}
	return best;

}

std::array<double,3> fireControl::calculateFireSolution(const std::deque<threeDTarget>::iterator inTarget,const double& inTime)
{
	int solved=0;
	std::array<double,3> outArray;
	double aimMoveTime;
	std::array<double,3> aimPoint;

	if(inTarget!=targetQue.end())
	{
	    double cutDownBuffer=(outLookCutOff-(inTime-inTarget->getTimeStamp()));
		double targetMoveTime=outLookCutOff-(inTime-inTarget->getTimeStamp());
		//std::cout << "cutDownBuffer: " << cutDownBuffer << std::endl << "targetMoveTime: " << targetMoveTime << std::endl;
		std::array<double,3> prediction;


		do
		{
			prediction=targetPredictor(inTarget,inTime+targetMoveTime);
			aimPoint.at(0)=aimControl->calculateX(mountX,mountY,mountZ,prediction.at(0),prediction.at(1),prediction.at(2));
			aimPoint.at(1)=aimControl->calculateY(mountX,mountY,mountZ,prediction.at(0),prediction.at(1),prediction.at(2));
			aimPoint.at(2)=aimControl->calculateTime(mountX,mountY,mountZ,prediction.at(0),prediction.at(1),prediction.at(2));

			if(aimPoint.at(0)!=-9999 && aimPoint.at(1)!=-9999 && aimPoint.at(2)!=-9999 && cutDownBuffer>.00001)
			{
				aimMoveTime=aimPoint.at(2)+motorFunctions->timeUntilLocation(motorFunctions->getMotorLocationX(inTime),motorFunctions->getMotorLocationY(inTime),aimPoint.at(0),aimPoint.at(1));
				cutDownBuffer/=2;
				if(aimMoveTime<targetMoveTime && targetMoveTime<aimMoveTime+bufferTime)
				{
					solved=1;
				}
				else
				{
					if(aimMoveTime<targetMoveTime)
					{
						targetMoveTime-=cutDownBuffer;
					}
					else
					{
						targetMoveTime+=cutDownBuffer;
					}
				}
                //std::cout << "aimMoveTime: " << aimMoveTime << std::endl << "outLookCutOff-(inTime-inTarget->getTimeStamp()): " << outLookCutOff-(inTime-inTarget->getTimeStamp()) << std::endl;
				if(aimMoveTime>outLookCutOff-(inTime-inTarget->getTimeStamp()))
				{
					solved=-1;
				}
			}
			else
			{
				solved=-1;
			}

		}while(!(solved==1 || solved==-1));
	}
	else
	{
		solved=-1;
	}
	if(solved==1)
	{
		outArray.at(0)=(aimMoveTime+inTime)-aimPoint.at(2);
		outArray.at(1)=aimPoint.at(0);
		outArray.at(2)=aimPoint.at(1);
	}
	else
	{
		outArray.at(0)=-1;
		outArray.at(1)=0;
		outArray.at(2)=0;
	}
	return outArray;

}

std::array<double,3> fireControl::targetPredictor(const std::deque<threeDTarget>::iterator inTarget,const double& inTime)
{
	std::array<double,3> outArray;
	double timeChange=inTime-inTarget->getTimeStamp();
	outArray.at(0)=inTarget->getLocationX()+(inTarget->getDirectionX()*(timeChange));
	outArray.at(1)=inTarget->getLocationY()+(inTarget->getDirectionY()*(timeChange));
	outArray.at(2)=inTarget->getLocationZ()+(inTarget->getDirectionZ()*(timeChange));
	return outArray;
}

std::vector<command> fireControl::packageCommands(const std::array<double,3>& inFireSolution,const double& inTime)
{
	std::vector<command> outCommands;
	command tempCommand;
	tempCommand.setCommandType(MOVE_X);
	tempCommand.setSync(0);
	tempCommand.setTime(inTime);
    tempCommand.setValue(inFireSolution.at(1)-motorFunctions->getMotorLocationX(inTime));
    tempCommand.setPriority(3);
	outCommands.push_back(tempCommand);

	tempCommand.setCommandType(MOVE_Y);
	tempCommand.setSync(0);
	tempCommand.setTime(inTime);
	tempCommand.setValue(inFireSolution.at(2)-motorFunctions->getMotorLocationY(inTime));
	tempCommand.setPriority(3);
	outCommands.push_back(tempCommand);

    tempCommand.setCommandType(FIRE);
    tempCommand.setSync(0);
    tempCommand.setTime(inTime);
    tempCommand.setValue(inFireSolution.at(0));
    tempCommand.setPriority(3);
    outCommands.push_back(tempCommand);
    lastCommandTime=inFireSolution.at(0);

	return outCommands;
}

