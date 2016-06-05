#include "targetDatabase.h"
//Construtors
//Default
targetDatabase::targetDatabase(void):minTargetTime(.5),maxTargetTime(3),maxTargetAverage(3),minGradeValue(50),dataBaseColorAcc(10),dataBaseLocationAcc(50)
{
}

//Copy
targetDatabase::targetDatabase(const targetDatabase& src):minTargetTime(src.minTargetTime),maxTargetTime(src.maxTargetTime),maxTargetAverage(src.maxTargetAverage),dataLists(src.dataLists),
                                                          minGradeValue(src.minGradeValue),dataBaseColorAcc(src.dataBaseColorAcc),dataBaseLocationAcc(src.dataBaseLocationAcc)
{
}

targetDatabase::targetDatabase(targetDatabase& src):minTargetTime(src.minTargetTime),maxTargetTime(src.maxTargetTime),maxTargetAverage(src.maxTargetAverage),dataLists(src.dataLists),
                                                    minGradeValue(src.minGradeValue),dataBaseColorAcc(src.dataBaseColorAcc),dataBaseLocationAcc(src.dataBaseLocationAcc)
{
}

//Move
targetDatabase::targetDatabase(targetDatabase&& src):minTargetTime(src.minTargetTime),maxTargetTime(src.maxTargetTime),maxTargetAverage(src.maxTargetAverage),dataLists(src.dataLists),
                                                     minGradeValue(src.minGradeValue),dataBaseColorAcc(src.dataBaseColorAcc),dataBaseLocationAcc(src.dataBaseLocationAcc)

{
}

//Operator Overloading
//Assignment
targetDatabase& targetDatabase::operator=(const targetDatabase& rhs)
{
    if(&rhs==this)
    {
        return *this;
    }
    maxTargetTime=rhs.maxTargetTime;
    minTargetTime=rhs.minTargetTime;
    maxTargetAverage=rhs.maxTargetAverage;
    minGradeValue=rhs.minGradeValue;
    dataBaseColorAcc=rhs.dataBaseColorAcc;
    dataBaseLocationAcc=rhs.dataBaseLocationAcc;
    dataLists=rhs.dataLists;
    return *this;
}

targetDatabase& targetDatabase::operator=(targetDatabase&& rhs)
{
    if(&rhs==this)
    {
        return *this;
    }
    maxTargetTime=rhs.maxTargetTime;
    minTargetTime=rhs.minTargetTime;
    maxTargetAverage=rhs.maxTargetAverage;
    minGradeValue=rhs.minGradeValue;
    dataBaseColorAcc=rhs.dataBaseColorAcc;
    dataBaseLocationAcc=rhs.dataBaseLocationAcc;
    dataLists=rhs.dataLists;
    return *this;
}

//Getters
double targetDatabase::getMaxTargetTime()const
{
    return maxTargetTime;
}

double targetDatabase::getMinTargetTime()const
{
    return minTargetTime;
}

double targetDatabase::getMaxTargetAverage()const
{
    return maxTargetAverage;
}

double targetDatabase::getMinGradeValue()const
{
    return minGradeValue;
}

double targetDatabase::getDataBaseColorAcc()const
{
    return dataBaseColorAcc;
}

double targetDatabase::getDataBaseLocationAcc()const
{
    return dataBaseLocationAcc;
}



//Setters
void targetDatabase::setMaxTargetTime(const double& inMaxTargetTime)
{
    maxTargetTime=inMaxTargetTime;
}

void targetDatabase::setMinTargetTime(const double& inMinTargetTime)
{
    minTargetTime=inMinTargetTime;
}

void targetDatabase::setMaxTargetAverage(const double& inMaxTargetAverage)
{
    maxTargetAverage=inMaxTargetAverage;
}

void targetDatabase::setMinGradeValue(const double& inMinGradeValue)
{
    minGradeValue=inMinGradeValue;
}

void targetDatabase::setDataBaseColorAcc(const double& inDataBaseColorAcc)
{
    dataBaseColorAcc=inDataBaseColorAcc;
}

void targetDatabase::setDataBaseLocationAcc(const double& inDataBaseLocationAcc)
{
    dataBaseLocationAcc=inDataBaseLocationAcc;
}

//Public Methods
void targetDatabase::addNewTargets(std::list<targetPair>& inTargetList,const cameraSettings& inSettings)
{
    if(dataLists.size()>0)
    {
        std::list<std::list<double>> theGradeList = calculateGrades(inTargetList,inSettings);
        std::list<targetPair>::iterator targetIter;
        std::list<std::list<double>>::iterator outerIter;
        std::list<double>::iterator currentTarget;
        double bestMatchValue=0;
        double maxValue=100;
        int counter=0;
        bool endLoop=0;
        int targetCounterValue=0;
        int dataBaseCount=0;
        std::list<std::list<double>>::iterator currentTargetList = theGradeList.begin();
        while(currentTargetList!=theGradeList.end())
        {
            maxValue=100;
            do
            {
                currentTarget = currentTargetList->begin();
                counter = 0;
                targetCounterValue = 0;
                bestMatchValue = -1;
                endLoop = 0;
                while(currentTarget != currentTargetList->end())
                {
                    if(*currentTarget > minGradeValue && *currentTarget < maxValue && *currentTarget > bestMatchValue)
                    {
                        bestMatchValue = *currentTarget;
                        targetCounterValue = counter;
                    }
                    counter++;
                    currentTarget++;
                }
                outerIter = theGradeList.begin();
                if(bestMatchValue != -1)
                {
                    while(outerIter!=theGradeList.end())
                    {
                        counter = 0;
                        currentTarget = outerIter->begin();
                        while(currentTarget!=outerIter->end())
                        {
                            if(counter==targetCounterValue)
                            {
                                if(*currentTarget>bestMatchValue)
                                {
                                    maxValue = bestMatchValue;
                                    endLoop=1;
                                }
                            }
                            counter++;
                            currentTarget++;
                        }
                        outerIter++;
                    }
                }
            }while(endLoop);

            if(bestMatchValue!=-1)
            {
                int theCurrentCount=0;
                std::list<std::list<targetPair>>::iterator dataBaseIter = dataLists.begin();
                while(dataBaseIter != dataLists.end())
                {
                    if(dataBaseCount == theCurrentCount)
                    {
                        counter = 0;
                        targetIter = inTargetList.begin();
                        while(targetIter!=inTargetList.end())
                        {
                            if(counter==targetCounterValue)
                            {
                                dataBaseIter->push_back(*targetIter);
                                targetIter=--inTargetList.erase(targetIter);
                            }
                            counter++;
                            targetIter++;
                        }
                    }
                    theCurrentCount++;
                    dataBaseIter++;
                }

                outerIter = theGradeList.begin();
                counter = 0;
                while(outerIter != theGradeList.end())
                {
                    currentTarget = outerIter->begin();
                    counter=0;
                    while(currentTarget != outerIter->end())
                    {
                        if(counter == targetCounterValue)
                        {
                            currentTarget = --outerIter->erase(currentTarget);
                        }
                        counter++;
                        currentTarget++;
                    }
                    outerIter++;
                }
            }
        dataBaseCount++;
        currentTargetList++;
        }
    }
    std::list<targetPair> tempPairList;
    std::list<targetPair>::iterator addOnList=inTargetList.begin();
    while(addOnList!=inTargetList.end())
    {
        tempPairList.push_back(*addOnList);
        dataLists.push_back(tempPairList);
        tempPairList.clear();
        addOnList++;
    }
}

void targetDatabase::updateData(const double& inTimeStamp)
{
    int targetCount=0;
    double cutOffTime=inTimeStamp-maxTargetTime;
    std::list<std::list<targetPair>>::iterator outIter=dataLists.begin();
    while(outIter!=dataLists.end())
    {
        std::list<targetPair>::iterator inIter = outIter->begin();
        while(inIter!=outIter->end())
        {
            targetCount++;
            if(inIter->getTimeStamp()<cutOffTime)
            {
                inIter=--outIter->erase(inIter);
            }
            inIter++;
        }
        if(outIter->size()==0)//*************************Size-1???
        {
            outIter=dataLists.erase(outIter);
        }
        outIter++;
    }
}

std::vector<threeDTarget> targetDatabase::retrieveTargets(const double& inTimeStamp,const cameraSettings& inSettings)
{
    std::vector<threeDTarget> returnTargets;
    std::list<targetPair>::iterator tempIter;
    bool breakLoop=0;
    std::list<std::list<targetPair>>::iterator outIter=dataLists.begin();
    while(outIter!=dataLists.end())
    {
        breakLoop=0;
        if(outIter->size()>1)
        {
            tempIter=--outIter->end();
            if(tempIter->getTimeStamp()==inTimeStamp)//Check size here
            {
                std::list<targetPair>::iterator inIter = outIter->begin();
                while(inIter!=outIter->end() && !breakLoop)
                {
                    if(inTimeStamp-inIter->getTimeStamp()<maxTargetTime && inTimeStamp-inIter->getTimeStamp()>minTargetTime)
                    {
                        threeDTarget currentTarget,prevTarget;
                        std::list<targetPair>::iterator countIter =outIter->begin();
                        std::list<targetPair>::iterator endIter=outIter->begin();
                        double counter=0;
                        int count=(int)floor(outIter->size()/2);
                        int i=0;
                        while(i<count  && i<maxTargetAverage)
                        {
                            endIter++;
                            i++;
                        }
                        while(countIter!=endIter)
                        {
                            prevTarget = prevTarget+countIter->getTarget(inSettings);
                            countIter++;
                            counter++;
                        }
                        prevTarget=prevTarget/counter;
                        counter=0;
                        endIter=--outIter->end();
                        i=0;
                        while(i<count && i<maxTargetAverage)
                        {
                            endIter--;
                            i++;
                        }

                        countIter=endIter;
                        while(countIter!=outIter->end())
                        {
                            currentTarget = currentTarget+countIter->getTarget(inSettings);
                            countIter++;
                            counter++;
                        }
                        currentTarget=currentTarget/counter;
                        currentTarget=currentTarget.getTargetSpeedDirection(prevTarget);
                        returnTargets.push_back(currentTarget);
                        breakLoop=1;
                    }
                    inIter++;
                }
            }
        }
        outIter++;
    }
    return returnTargets;
}

targetPair targetDatabase::getLargestTargetPair() const
{
    targetPair returnPair;
    int counter=0;
    int answer=-1;
    int largest=0;
    std::list<std::list<targetPair>>::const_iterator pairIter=dataLists.begin();
    while(pairIter!=dataLists.end())
    {
        if(pairIter->size()>largest)
        {
            largest=pairIter->size();
            answer=counter;
        }
        counter++;
        pairIter++;
    }
    pairIter=dataLists.begin();
    counter = 0;
    while(pairIter!=dataLists.end())
    {
        if(counter==answer)
        {
            returnPair = *(--pairIter->end());
        }
        pairIter++;
        counter++;
    }
    return returnPair;
}

int targetDatabase::getSize()
{
    int targetCount=0;
    std::list<std::list<targetPair>>::iterator outIter=dataLists.begin();
    while(outIter!=dataLists.end())
    {
        std::list<targetPair>::iterator inIter = outIter->begin();
        while(inIter!=outIter->end())
        {
            targetCount++;
            inIter++;
        }
        outIter++;
    }
    return targetCount;
}

int targetDatabase::getNumberOfTargets()const
{
    return dataLists.size();
}






targetDatabase::~targetDatabase()
{
    //dtor
}

//Helper Methods
std::list<std::list<double>> targetDatabase::calculateGrades(const std::list<targetPair>& inTargetPairs,const cameraSettings& inSettings)const
{
    std::list<std::list<double>> returnList;
    double tempValue=0;
    std::list<double> tempInList;
    std::list<std::list<targetPair>>::const_iterator outIter = dataLists.begin();
    std::list<targetPair>::const_iterator inTarget;
    while(outIter!=dataLists.end())
    {
        inTarget = inTargetPairs.begin();
        tempInList.clear();
        while(inTarget != inTargetPairs.end())
        {
            tempValue=inTarget->grade(*outIter,dataBaseColorAcc,dataBaseLocationAcc,inSettings);
            tempInList.push_back(tempValue);
            inTarget++;
        }
        returnList.push_back(tempInList);
        outIter++;
    }
    return returnList;
}
