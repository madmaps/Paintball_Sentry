#ifndef __COMMANDTOSERIAL__
#define __COMMANDTOSERIAL__
#include "../FireControl/command.h"
#include <list>
#include <algorithm>
#include <vector>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <iterator>
#include <string.h>
#include <string>
#include <thread>
#include <iostream>




class commandToSerial
{
public:
    //Constructers
    commandToSerial(void);//Default
    commandToSerial(const commandToSerial& src);//Copy
    commandToSerial(commandToSerial&& src);//Move

    //Operator Overloading
    virtual commandToSerial& operator=(const commandToSerial& rhs);//Assignment
    virtual commandToSerial& operator=(commandToSerial&& rhs);//Move Assignment

    //Getters

    //Setters

    //Public Methods

    virtual void pushCommands(std::vector<command> inCommands);
    virtual bool setupSerialPort(std::string inPort,std::string inPortSpeed="B9600");

    virtual std::vector<std::list<command>> completedAndRunningCommandList();
    //virtual int numberOfCompletedCommands() const;
    virtual void startCommandUpload();
    virtual void stopCommandUpload();

    //Destructor
    virtual ~commandToSerial(void);

protected:
    //Members
    std::list<command> syncQueList;
    std::list<command> nonSyncQueList;
    std::mutex inMutex;
    std::list<command> shortInQue;
    std::list<command> completedCommandList;
    int port;
    struct termios portSettings;
    struct termios oldPortSettings;
    bool exiting;
    std::thread serialThread;

    //Helper Methods
    virtual void serialCommunication(void);
    virtual void shutDownPort(void);
};

#endif // __COMMANDTOSERIAL__
