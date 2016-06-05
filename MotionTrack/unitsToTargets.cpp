#include "unitsToTargets.h"

//Constructor
//Default
unitsToTargets::unitsToTargets(void):sectionLookupTable(0),theSections(0),sizeOfLookupTable(0),sizeOfSections(0),unitResolution(20)
{
}

//Copy
unitsToTargets::unitsToTargets(const unitsToTargets& src):sizeOfLookupTable(src.sizeOfLookupTable),theSections(src.theSections),sizeOfSections(src.sizeOfSections),unitResolution(src.unitResolution)
{
	int i=0;
	sectionLookupTable=new int[sizeOfLookupTable];
	while(i<sizeOfLookupTable)
	{
		sectionLookupTable[i]=src.sectionLookupTable[i];
		i++;
	}

}

//Move
unitsToTargets::unitsToTargets(unitsToTargets&& src):sizeOfLookupTable(src.sizeOfLookupTable),sizeOfSections(src.sizeOfSections),unitResolution(src.unitResolution)
{
	sectionLookupTable=src.sectionLookupTable;
	theSections=src.theSections;

	src.sectionLookupTable=0;
	src.sizeOfLookupTable=0;
	src.sizeOfSections=0;
	src.theSections=0;
    src.unitResolution=0;
}

//Operator Overloading
//Assignment
unitsToTargets& unitsToTargets::operator=(const unitsToTargets& rhs)
{
	if(this==&rhs)
	{
		return *this;
	}
	cleanup();
    unitResolution=rhs.unitResolution;
	sizeOfLookupTable=rhs.sizeOfLookupTable;
	sectionLookupTable=new int[sizeOfLookupTable];
	int i=0;
	while(i<sizeOfLookupTable)
	{
		sectionLookupTable[i]=rhs.sectionLookupTable[i];
		i++;
	}
	sizeOfSections=rhs.sizeOfSections;
	theSections=new sections[sizeOfSections];
	i=0;
	while(i<sizeOfSections)
	{
		theSections[i]=rhs.theSections[i];
		i++;
	}

	return *this;
}

//Move Assignment
unitsToTargets& unitsToTargets::operator=(unitsToTargets&& rhs)
{
	if(this==&rhs)
	{
		return *this;
	}
	cleanup();
    unitResolution=rhs.unitResolution;
	sizeOfLookupTable=rhs.sizeOfLookupTable;
	sectionLookupTable=rhs.sectionLookupTable;
	sizeOfSections=rhs.sizeOfSections;
	theSections=rhs.theSections;

	rhs.sectionLookupTable=0;
	rhs.sizeOfLookupTable=0;
	rhs.sizeOfSections=0;
	rhs.theSections=0;
    rhs.unitResolution=0;
	return *this;
}

//Getters
double unitsToTargets::getUnitResolution()const
{
    return unitResolution;
}

//Setters
void unitsToTargets::setUnitResolution(const double& inUnitResolution)
{
    unitResolution=inUnitResolution;
}


//Public Methods
//std::vector<twoDTargets>& unitsToTargets::convert(const frame& inFrame,const units& inUnits)
std::list<twoDTargets>& unitsToTargets::convert(const frame& inFrame,const units& inUnits)
{
	setupSections(inUnits);
	accumTarget runningTarget;
	//std::vector<twoDTargets>* returnTargets = new std::vector<twoDTargets>;
	std::list<twoDTargets>* returnTargets= new std::list<twoDTargets>;
	twoDTargets tempTarget;
	double temp1=0,temp2=0;

	int unitCount=inUnits.getUnitCount();
	int i=0,j=1;
	while(i<unitCount)
	{
		if(!theSections[i].getID())
		{
			theSections[i].getTarget(runningTarget,j,inUnits,inFrame);
			temp1=runningTarget.locX;
			temp2=runningTarget.size;
			tempTarget.setLocationX((((temp1/temp2)+.5)/inUnits.getUnitSize())*inFrame.getWidth());
			temp1=runningTarget.locY;
			tempTarget.setLocationY(inFrame.getHeight()-(((temp1/temp2)+.5)/inUnits.getTrueUnitHeight())*inFrame.getHeight());
			temp1=runningTarget.red;
			temp2=runningTarget.totalPixilCount;
			tempTarget.setAvgColorRed(temp1/temp2);
			temp1=runningTarget.green;
			tempTarget.setAvgColorGreen(temp1/temp2);
			temp1=runningTarget.blue;
			tempTarget.setAvgColorBlue(temp1/temp2);
			tempTarget.setSize(runningTarget.size*100/(inUnits.getUnitSize()*inUnits.getTrueUnitHeight()));
			tempTarget.setTimeStamp(inFrame.getTimeStamp());
			returnTargets->push_back(tempTarget);
			runningTarget.clear();
			j++;
		}
		i++;
	}
	return *returnTargets;

}

//Destructer
unitsToTargets::~unitsToTargets(void)
{
	cleanup();
}

//Helper Methods
void unitsToTargets::setupSections(const units& inUnits)
{
	cleanup();

	sizeOfSections=inUnits.getUnitCount();
	sizeOfLookupTable=inUnits.getUnitCount();
	if(sizeOfSections!=0)
	{
		theSections=new sections[inUnits.getUnitCount()];
		sectionLookupTable=new int[inUnits.getUnitCount()];
	}
	double* unitArray=inUnits.getUnitArray();
	int intUnitSize=inUnits.getUnitSize();
	double trueUnitHeight=inUnits.getTrueUnitHeight();
	double unitSize=inUnits.getUnitSize();
	int tempSectionCount=0,i=0,j=0;

	i=0;
	while(i<trueUnitHeight)
	{
		j=0;
		while(j<unitSize)
		{
            if(unitArray[i*intUnitSize+j]>=unitResolution)
			{
				sectionLookupTable[tempSectionCount]=i*intUnitSize+j;
				theSections[tempSectionCount].setLocationX(j);
				theSections[tempSectionCount].setLocationY(i);
				tempSectionCount++;
			}
			j++;
		}
		i++;
	}

	int secLoc=0;
	int m=0;
	int unitCount=inUnits.getUnitCount();

	while(m<tempSectionCount)
	{
		for(i=-1;i<=1;i++)
		{
			for(j=-1;j<=1;j++)
			{
				secLoc=findSectionLocation(theSections[m].getLocationX()+i,theSections[m].getLocationY()+j,intUnitSize,unitCount);
				if(secLoc!=-1 && !(i==0 && j==0))
				{
					theSections[m].setSectionsLocation(i,j,theSections[secLoc]);
				}

			}
		}
		m++;
	}
}

int unitsToTargets::findSectionLocation(const int& inX,const int& inY,const int& inUnitSize,const int& inUnitCount)
{
	int temp=inY*inUnitSize+inX;
	int i=0;
	while(i<=inUnitCount-1)
	{
		if(sectionLookupTable[i]==temp)
		{
			return i;
		}
		i++;
	}
	return -1;
}

void unitsToTargets::cleanup()
{
	if(theSections!=0)
	{
		delete[] theSections;
		theSections=0;
	}
	if(sectionLookupTable!=0)
	{
		delete[] sectionLookupTable;
		sectionLookupTable=0;
	}
	sizeOfLookupTable=0;
	sizeOfSections=0;
}

