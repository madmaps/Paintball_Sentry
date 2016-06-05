#include "commandToSerial.h"
//Constructers
//Default
commandToSerial::commandToSerial():port(0),exiting(1)
{
}

//Copy
commandToSerial::commandToSerial(const commandToSerial& src):syncQueList(src.syncQueList),nonSyncQueList(src.nonSyncQueList),
    shortInQue(src.shortInQue),completedCommandList(src.completedCommandList),port(src.port),exiting(1)
{
    //portSettings.c_cc=src.portSettings.c_cc;
    portSettings.c_cflag=src.portSettings.c_cflag;
    portSettings.c_iflag=src.portSettings.c_iflag;
    portSettings.c_ispeed=src.portSettings.c_ispeed;
    portSettings.c_lflag=src.portSettings.c_lflag;
    portSettings.c_line=src.portSettings.c_line;
    portSettings.c_oflag=src.portSettings.c_oflag;
    portSettings.c_ospeed=src.portSettings.c_ospeed;

    oldPortSettings.c_cflag=src.oldPortSettings.c_cflag;
    oldPortSettings.c_iflag=src.oldPortSettings.c_iflag;
    oldPortSettings.c_ispeed=src.oldPortSettings.c_ispeed;
    oldPortSettings.c_lflag=src.oldPortSettings.c_lflag;
    oldPortSettings.c_line=src.oldPortSettings.c_line;
    oldPortSettings.c_oflag=src.oldPortSettings.c_oflag;
    oldPortSettings.c_ospeed=src.oldPortSettings.c_ospeed;


}

//Move
commandToSerial::commandToSerial(commandToSerial&& src):syncQueList(src.syncQueList),nonSyncQueList(src.nonSyncQueList),
    shortInQue(src.shortInQue),completedCommandList(src.completedCommandList),port(src.port),exiting(1)
{
    //portSettings.c_cc=src.portSettings.c_cc;
    portSettings.c_cflag=src.portSettings.c_cflag;
    portSettings.c_iflag=src.portSettings.c_iflag;
    portSettings.c_ispeed=src.portSettings.c_ispeed;
    portSettings.c_lflag=src.portSettings.c_lflag;
    portSettings.c_line=src.portSettings.c_line;
    portSettings.c_oflag=src.portSettings.c_oflag;
    portSettings.c_ospeed=src.portSettings.c_ospeed;

    oldPortSettings.c_cflag=src.oldPortSettings.c_cflag;
    oldPortSettings.c_iflag=src.oldPortSettings.c_iflag;
    oldPortSettings.c_ispeed=src.oldPortSettings.c_ispeed;
    oldPortSettings.c_lflag=src.oldPortSettings.c_lflag;
    oldPortSettings.c_line=src.oldPortSettings.c_line;
    oldPortSettings.c_oflag=src.oldPortSettings.c_oflag;
    oldPortSettings.c_ospeed=src.oldPortSettings.c_ospeed;


}

//Operator OverLoading
//Assignment
commandToSerial& commandToSerial::operator=(const commandToSerial& rhs)
{
    if(this==&rhs)
    {
        return *this;
    }
    syncQueList=rhs.syncQueList;
    nonSyncQueList=rhs.nonSyncQueList;
    shortInQue=rhs.shortInQue;
    completedCommandList=rhs.completedCommandList;
    port=rhs.port;

    portSettings.c_cflag=rhs.portSettings.c_cflag;
    portSettings.c_iflag=rhs.portSettings.c_iflag;
    portSettings.c_ispeed=rhs.portSettings.c_ispeed;
    portSettings.c_lflag=rhs.portSettings.c_lflag;
    portSettings.c_line=rhs.portSettings.c_line;
    portSettings.c_oflag=rhs.portSettings.c_oflag;
    portSettings.c_ospeed=rhs.portSettings.c_ospeed;

    oldPortSettings.c_cflag=rhs.oldPortSettings.c_cflag;
    oldPortSettings.c_iflag=rhs.oldPortSettings.c_iflag;
    oldPortSettings.c_ispeed=rhs.oldPortSettings.c_ispeed;
    oldPortSettings.c_lflag=rhs.oldPortSettings.c_lflag;
    oldPortSettings.c_line=rhs.oldPortSettings.c_line;
    oldPortSettings.c_oflag=rhs.oldPortSettings.c_oflag;
    oldPortSettings.c_ospeed=rhs.oldPortSettings.c_ospeed;

    exiting=1;
    return *this;
}

commandToSerial& commandToSerial::operator=(commandToSerial&& rhs)
{
    if(this==&rhs)
    {
        return *this;
    }
    syncQueList=rhs.syncQueList;
    nonSyncQueList=rhs.nonSyncQueList;
    shortInQue=rhs.shortInQue;
    completedCommandList=rhs.completedCommandList;
    port=rhs.port;

    portSettings.c_cflag=rhs.portSettings.c_cflag;
    portSettings.c_iflag=rhs.portSettings.c_iflag;
    portSettings.c_ispeed=rhs.portSettings.c_ispeed;
    portSettings.c_lflag=rhs.portSettings.c_lflag;
    portSettings.c_line=rhs.portSettings.c_line;
    portSettings.c_oflag=rhs.portSettings.c_oflag;
    portSettings.c_ospeed=rhs.portSettings.c_ospeed;

    oldPortSettings.c_cflag=rhs.oldPortSettings.c_cflag;
    oldPortSettings.c_iflag=rhs.oldPortSettings.c_iflag;
    oldPortSettings.c_ispeed=rhs.oldPortSettings.c_ispeed;
    oldPortSettings.c_lflag=rhs.oldPortSettings.c_lflag;
    oldPortSettings.c_line=rhs.oldPortSettings.c_line;
    oldPortSettings.c_oflag=rhs.oldPortSettings.c_oflag;
    oldPortSettings.c_ospeed=rhs.oldPortSettings.c_ospeed;

    exiting=1;
    return *this;
}

//Getters

//Setters

//Public Methods
void commandToSerial::pushCommands(std::vector<command> inCommands)
{
    std::list<command> tempSyncList;
    std::list<command> tempNonSyncList;
    copy_if(inCommands.begin(),inCommands.end(),back_inserter(tempSyncList),[](command theCommand){return theCommand.getSync();});
    copy_if(inCommands.begin(),inCommands.end(),back_inserter(tempNonSyncList),[](command inCommand){return !inCommand.getSync();});
    std::lock_guard<std::mutex> lock(inMutex);
    syncQueList.splice(syncQueList.end(),tempSyncList);
    nonSyncQueList.splice(nonSyncQueList.end(),tempNonSyncList);
    syncQueList.sort();
    nonSyncQueList.sort();
}

bool commandToSerial::setupSerialPort(std::string inPort,std::string inPortSpeed)
{
    port = open(inPort.c_str(),O_RDWR | O_NOCTTY | O_NDELAY);
    if(port<0)
    {
        return 0;
    }
    tcgetattr(port,&oldPortSettings);
    memset(&portSettings,0,sizeof(portSettings));
    //****************ADD PORTSPEEDSETTINGS******************************
    portSettings.c_cflag = B9600 | CS8;
    tcflush(port,TCIOFLUSH);
    tcsetattr(port,TCSANOW,&portSettings);
    return 1;
}


std::vector<std::list<command>> commandToSerial::completedAndRunningCommandList()
{
    std::vector<std::list<command>> outVector;

    inMutex.lock();
    outVector.push_back(shortInQue);
    outVector.push_back(completedCommandList);
    completedCommandList.clear();
    inMutex.unlock();

    return outVector;
}


void commandToSerial::startCommandUpload()
{
    if(exiting!=0)
    {
        exiting=0;
        serialThread=std::thread{&commandToSerial::serialCommunication,this};
    }

}

void commandToSerial::stopCommandUpload()
{
    if(exiting==0)
    {
        exiting=1;
        serialThread.join();
    }
}

//Destructor
commandToSerial::~commandToSerial()
{
    stopCommandUpload();
    shutDownPort();
}

//Helper Methods
void commandToSerial::serialCommunication(void)
{
    int commandRunning=0;
    int result=0;
    char inBuffer[255];
    char outBuffer[255];
    char tempBuffer[255];
    //int shortInQueSize=0;

    if(port>0)
    {
        do
        {
            if(shortInQue.size()==0)
            {
                if(inMutex.try_lock())
                {
                    if(nonSyncQueList.size()>0)
                    {
                        shortInQue.splice(shortInQue.end(),nonSyncQueList);
                    }
                    if(syncQueList.size()>0)
                    {
                        shortInQue.push_front(*syncQueList.begin());
                        //std::cout << "syncQueList to shortInQue(QueLength:" << syncQueList.size() << ")" << std::endl;
                        syncQueList.pop_front();
                    }

                    inMutex.unlock();
                }
            }



            if(!commandRunning && shortInQue.size()>0)
            {
                for(int i=0;i<=255;i++)
                {
                    outBuffer[i]=0;
                }
                for(auto tempCommand : shortInQue)
                {
                    switch(tempCommand.getCommandType())
                    {
                    case MOVE_X:
                        strcat(outBuffer,"X");//outBuffer+="X";
                        sprintf(tempBuffer,"%.3f",tempCommand.getValue());
                        strcat(outBuffer,tempBuffer);
                        commandRunning++;
                        break;
                    case MOVE_Y:
                        strcat(outBuffer,"Y");//outBuffer+="X";
                        sprintf(tempBuffer,"%.3f",tempCommand.getValue());
                        strcat(outBuffer,tempBuffer);
                        commandRunning++;
                        break;
                    case FIRE:
                        strcat(outBuffer,"F");//outBuffer+="X";
                        sprintf(tempBuffer,"%.3f",tempCommand.getValue());
                        strcat(outBuffer,tempBuffer);
                        commandRunning++;
                        break;
                    case PAUSE:
                        strcat(outBuffer,"P");//outBuffer+="X";
                        sprintf(tempBuffer,"%.3f",tempCommand.getValue());
                        strcat(outBuffer,tempBuffer);
                        commandRunning++;
                        break;
                    case QUIT:
                        exiting=1;
                        break;
                    case SET_SPEED:
                        strcat(outBuffer,"S");//outBuffer+="X";
                        sprintf(tempBuffer,"%.3f",tempCommand.getValue());
                        strcat(outBuffer,tempBuffer);
                        commandRunning++;
                        break;
                    case CLEAR_QUE:
                        inMutex.lock();
                        syncQueList.clear();
                        nonSyncQueList.clear();
                        inMutex.unlock();
                        break;
                    case SYNC_TIME:
                        strcat(outBuffer,"T");//outBuffer+="X";
                        sprintf(tempBuffer,"%.3f",tempCommand.getValue());
                        strcat(outBuffer,tempBuffer);
                        commandRunning++;
                        break;
                    default:
                        break;
                    }

                }
                //std::cout << "("<< strlen(outBuffer) << ") " << outBuffer << std::endl;
                write(port,outBuffer,strlen(outBuffer));
            }

            if(commandRunning>0)
            {
                strcpy(inBuffer,"                                  ");
                result=read(port,inBuffer,255);
                if(result>0)
                {
                //std::cout << inBuffer << std::endl;

                    inMutex.lock();
                    auto iter=shortInQue.begin();
                    for(int i=0;i<=result-1;i++)
                    {
                        if(inBuffer[i]=='1')
                        {
                            commandRunning++;
                        }
                        else
                        {
                            completedCommandList.push_back(*iter);
                            iter++;
                            //std::cout << "shortInQue Pop" << std::endl;
                            shortInQue.pop_front();
                        }
                    }
                    inMutex.unlock();
                    commandRunning-=result;
                }
            }
        }while(!exiting);
    }

}


void commandToSerial::shutDownPort(void)
{
    if(port<0)
    {
        tcsetattr(port,TCSANOW,&oldPortSettings);
        close(port);
        port=0;
    }
}



