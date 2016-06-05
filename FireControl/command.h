#pragma once
#ifndef __COMMAND__
#define __COMMAND__

enum{MOVE_X,MOVE_Y,PAUSE,FIRE,CLEAR_LAST,CLEAR_QUE,SET_SPEED,DEFAULT_SPEED,QUIT,SYNC_TIME};

class command
{
public:
	//Constructors
	command(void);//Default
	command(const command& src);//Copy
	command(command&& src);//Move
	command(const int& inCommandType,const double& inValue,const double& inTime,const bool& inSync,const int& inPriority,const int& inErrorCode,const double& inStartTime,const double& inEndTime);//Data

	//Operator Overloading
	virtual command& operator=(const command& rhs);//Assignment
	virtual command& operator=(command&& rhs);//Move Assignment
	virtual bool operator<(const command& rhs);//Greater Than

	//Getters
	virtual int getCommandType() const;
	virtual double getValue() const;
	virtual double getTime() const;
	virtual bool getSync() const;
	virtual int getPriority() const;
	virtual int getErrorCode() const;
	virtual double getStartTime() const;
	virtual double getEndTime() const;

	//Setters
	virtual void setCommandType(const int& inCommandType);
	virtual void setValue(const double& inValue);
	virtual void setTime(const double& inTime);
	virtual void setSync(const bool& inSync);
	virtual void setPriority(const int& inPriority);
	virtual void setErrorCode(const int& inErrorCode);
	virtual void setStartTime(const double& inStartTime);
	virtual void setEndTime(const double& inEndTime);


	//Public Methods

	//Destructor
	virtual ~command(void);
protected:
	//Members
	int commandType;
	double value;
	double time;
	bool sync;
	int priority;
	int errorCode;
	double startTime;
	double endTime;
	//Helper Methods
	virtual void cleanup();
};

#endif

