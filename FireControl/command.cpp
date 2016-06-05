#include "command.h"

//Constructors
//Default
command::command(void):commandType(-1),value(0),time(0),sync(0),priority(0),errorCode(0),startTime(0),endTime(0)
{
}

//Copy
command::command(const command& src):commandType(src.commandType),value(src.value),time(src.time),sync(src.sync),priority(src.priority),errorCode(src.errorCode),startTime(src.startTime),endTime(src.endTime)
{
}

//Move
command::command(command&& src):commandType(src.commandType),value(src.value),time(src.time),sync(src.sync),priority(src.priority),errorCode(src.errorCode),startTime(src.startTime),endTime(src.endTime)
{
}

//Data
command::command(const int& inCommandType,const double& inValue,const double& inTime,const bool& inSync,const int& inPriority,const int& inErrorCode,const double& inStartTime,const double& inEndTime):commandType(inCommandType),value(inValue),time(inTime),sync(inSync),priority(inPriority),errorCode(inErrorCode),startTime(inStartTime),endTime(inEndTime)
{
}

//Operator Overloading
//Assignment
command& command::operator=(const command& rhs)
{
	if(this==&rhs)
	{
		return *this;
	}
	commandType=rhs.commandType;
	value=rhs.value;
	time=rhs.time;
	sync=rhs.sync;
	priority=rhs.priority;
	errorCode=rhs.errorCode;
	startTime=rhs.startTime;
	endTime=rhs.endTime;
	return *this;
}

//Move Assignment
command& command::operator=(command&& rhs)
{
	if(this==&rhs)
	{
		return *this;
	}
	commandType=rhs.commandType;
	value=rhs.value;
	time=rhs.time;
	sync=rhs.sync;
	priority=rhs.priority;
	errorCode=rhs.errorCode;
	startTime=rhs.startTime;
	endTime=rhs.endTime;

	return *this;
}

bool command::operator<(const command& rhs)
{
    if(priority<rhs.priority)
    {
        return true;
    }
    if(priority==rhs.priority && time>rhs.time)
    {
        return true;
    }
    return false;
}

//Getters
int command::getCommandType() const
{
	return commandType;
}

double command::getValue() const
{
	return value;
}

double command::getTime() const
{
	return time;
}

bool command::getSync() const
{
	return sync;
}

int command::getPriority() const
{
    return priority;
}

int command::getErrorCode() const
{
    return errorCode;
}

double command::getStartTime() const
{
    return startTime;
}

double command::getEndTime() const
{
    return endTime;
}

//Setters
void command::setCommandType(const int& inCommandType)
{
	commandType=inCommandType;
}

void command::setValue(const double& inValue)
{
	value=inValue;
}

void command::setTime(const double& inTime)
{
	time=inTime;
}

void command::setSync(const bool& inSync)
{
	sync=inSync;
}

void command::setPriority(const int& inPriority)
{
    priority=inPriority;
}

void command::setErrorCode(const int& inErrorCode)
{
    errorCode=inErrorCode;
}

void command::setStartTime(const double& inStartTime)
{
    startTime=inStartTime;
}

void command::setEndTime(const double& inEndTime)
{
    endTime=inEndTime;
}

//Public Methods

//Destructor
command::~command(void)
{
	cleanup();
}

//Helper Methods
void command::cleanup()
{
}
