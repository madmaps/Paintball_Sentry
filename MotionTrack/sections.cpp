#include "sections.h"

//Constructors
//Default
sections::sections(void):locationX(0),locationY(0),ID(0),count(0)
{
	//surroundingSections=new sections*[9];
	int i=0;
	while(i<=8)
	{
		surroundingSections[i]=0;
		i++;
	}

}

//Copy
sections::sections(const sections& src):locationX(src.locationX),locationY(src.locationY),ID(src.ID),count(src.count)
{
	//surroundingSections=new sections*[9];
	int i=0;
	while(i<=8)
	{
		surroundingSections[i]=0;
		i++;
	}
}

//Move
sections::sections(sections&& src):locationX(src.locationX),locationY(src.locationY),ID(src.ID),count(src.count)
{
	//surroundingSections=new sections*[9];
	int i=0;
	while(i<=8)
	{
		surroundingSections[i]=0;
		i++;
	}

}

//Data
sections::sections(float locX,float locY):locationX(locX),locationY(locY),ID(0),count(0)
{
	//surroundingSections=new sections*[9];
	int i=0;
	while(i<=8)
	{
		surroundingSections[i]=0;
		i++;
	}

}


//Operator OverLoading
sections& sections::operator=(const sections& rhs)
{
	if(this==&rhs)
	{
		return *this;
	}
	cleanup();

	locationX=rhs.locationX;
	locationY=rhs.locationY;
	ID=rhs.ID;
	count=rhs.count;
	int i=0;
	while(i<=8)
	{
		surroundingSections[i]=0;
		i++;
	}
	return *this;
}

sections& sections::operator=(sections&& rhs)
{
	if(this==&rhs)
	{
		return *this;
	}
	cleanup();

	locationX=rhs.locationX;
	locationY=rhs.locationY;
	ID=rhs.ID;
	count=rhs.count;
	int i=0;
	while(i<=8)
	{
		surroundingSections[i]=0;
		i++;
	}
	rhs.locationX=0;
	rhs.locationY=0;
	rhs.ID=0;
	rhs.count=0;
	i=0;
	while(i<=8)
	{
		rhs.surroundingSections[i]=0;
		i++;
	}
	return *this;
}

//Getters
float sections::getLocationX()
{
	return locationX;
}

float sections::getLocationY()
{
	return locationY;
}

int sections::getID()
{
	return ID;
}

//Setters
void sections::setLocationX(int locX)
{
	locationX=locX;
}

void sections::setLocationY(int locY)
{
	locationY=locY;
}


//Public Methods
void sections::setSectionsLocation(int locX,int locY,sections& inSections)
{
	surroundingSections[((locY+1)*3)+(locX+1)]=&inSections;
}

sections& sections::getSectionsLocation(const int& locX,const int& locY)
{
	return *surroundingSections[((locY+1)*3)+(locX+1)];
}

void sections::getTarget(accumTarget& inTarget,const int& inID,const units& inUnits,const frame& inFrame)
{
	inTarget.size++;

	ID=inID;
	for(int i=0;i<=8;i++)
	{
		if(surroundingSections[i]!=0 && i!=4)
		{
			if(surroundingSections[i]->getID()!=inID)
			{
				surroundingSections[i]->getTarget(inTarget,inID,inUnits,inFrame);
			}
		}
	}
	inTarget.locX+=locationX;
	inTarget.locY+=locationY;

	const unsigned char* newData=inFrame.getData();
	unsigned long pixCounter=0,i=0,j=0,y=0,x=0;
	int intUnitSize=inUnits.getUnitSize();
	double unitHeight=inUnits.getUnitHeight();
	double unitWidth=inUnits.getUnitWidth();
	double unitSize=inUnits.getUnitSize();
	i=locationY;
	j=locationX;
	y=0;
	while(y<unitHeight-1)
	{
		x=0;
		while(x<unitWidth)
		{
			unsigned long temp=i*unitSize*unitHeight*unitWidth*3+j*unitWidth*3+y*unitSize*unitWidth*3+x*3;
			for(unsigned long location=temp;location<=temp+2;location++)
			{
				switch(location%3)
				{
				case 0:
					inTarget.blue+=newData[location];
					break;
				case 1:
					inTarget.green+=newData[location];
					break;
				case 2:
					inTarget.red+=newData[location];
					break;
				default:
					break;
				}

			}
			inTarget.totalPixilCount++;

			x++;

		}
		y++;
	}
}

//Destructor
sections::~sections(void)
{
	cleanup();
}

//Helper Methods
void sections::cleanup()
{
	locationX=0;
	locationY=0;
	ID=0;
	count=0;
	int i=0;
	while(i<=8)
	{
		surroundingSections[i]=0;
		i++;
	}
}
