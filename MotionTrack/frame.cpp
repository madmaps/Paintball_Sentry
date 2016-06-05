#include "frame.h"

//bool createBitmap(int width,int height,int bits,char* data,unsigned long dataSize,char* fileName)
//{
//	std::ofstream outFile;
//	char header[54]={};
//	char* tempCharR;
//	outFile.open(fileName,std::ios::binary);
//	header[0]=0x42;
//	header[1]=0x4d;
//	unsigned long tempLong=dataSize+54;
//	tempCharR=reinterpret_cast<char*>(&tempLong);
//	header[2]=tempCharR[0];
//	header[3]=tempCharR[1];
//	header[4]=tempCharR[2];
//	header[5]=tempCharR[3];
//	header[10]=0x36;
//	header[14]=0x28;
//	tempLong=width;
//	tempCharR=reinterpret_cast<char*>(&tempLong);
//	header[18]=tempCharR[0];
//	header[19]=tempCharR[1];
//	header[20]=tempCharR[2];
//	header[21]=tempCharR[3];
//	tempLong=height;
//	tempCharR=reinterpret_cast<char*>(&tempLong);
//	header[22]=tempCharR[0];
//	header[23]=tempCharR[1];
//	header[24]=tempCharR[2];
//	header[25]=tempCharR[3];
//	header[26]=0x01;
//	header[28]=0x18;
//	tempLong=dataSize;
//	tempCharR=reinterpret_cast<char*>(&tempLong);
//	header[34]=tempCharR[0];
//	header[35]=tempCharR[1];
//	header[36]=tempCharR[2];
//	header[37]=tempCharR[3];
//	outFile.write(header,54);
//	outFile.write(data,dataSize);
//	outFile.close();
//
//	return 1;
//}



//Constructors
//Default
frame::frame(void):height(0),width(0),data(0),sizeOfData(0),timeStamp(0),keyFrame(0)
{}

//Initialize Static Members
double frame::pixelResolution=10;

//Copy
frame::frame(const frame& src):height(src.height),width(src.width),sizeOfData(src.sizeOfData),timeStamp(src.timeStamp),keyFrame(src.keyFrame)
{
	data=new unsigned char[src.sizeOfData];
	unsigned long i=0;
	while(i<src.sizeOfData)
	{
		data[i]=src.data[i];
		i++;
	}
}

//Move
frame::frame(frame&& src)
{
	height=src.height;
	width=src.width;
	data=src.data;
	sizeOfData=src.sizeOfData;
	timeStamp=src.timeStamp;
	keyFrame=src.keyFrame;

	src.height=0;
	src.width=0;
	src.data=0;
	src.sizeOfData=0;
	src.timeStamp=0;
	src.keyFrame=0;
}

//Data
frame::frame(const int& inHeight,const int& inWidth,unsigned char* inData,const unsigned long& inSizeOfData,const double& inTimeStamp,const bool& inKeyFrame):height(inHeight),width(inWidth),data(inData),sizeOfData(inSizeOfData),timeStamp(inTimeStamp),keyFrame(inKeyFrame)
{}

frame::frame(const cv::Mat& inFrame,const double& inTimeStamp,const bool& inKeyFrame):height(inFrame.rows),width(inFrame.cols),sizeOfData(inFrame.rows*inFrame.cols*3),timeStamp(inTimeStamp),keyFrame(inKeyFrame)
{
	data=new unsigned char[sizeOfData];
	unsigned long i=0;
	while(i<sizeOfData)
	{
		data[i]=inFrame.data[i];//-128;
		i++;
	}
}



//Operator Overloading

//Assignment
frame& frame::operator=(const frame& rhs)
{
	if(&rhs==this)
	{
		return *this;
	}
	height=rhs.height;
	width=rhs.width;
	cleanup();
	data=new unsigned char[rhs.sizeOfData];
	unsigned long i=0;
	while(i<rhs.sizeOfData)
	{
		data[i]=rhs.data[i];
		i++;
	}
	sizeOfData=rhs.sizeOfData;
	timeStamp=rhs.timeStamp;
	keyFrame=rhs.keyFrame;
	return *this;
}

//Move Assignment
frame& frame::operator=(frame&& rhs)
{
	if(this==&rhs)
	{
		return *this;
	}
	height=rhs.height;
	width=rhs.width;
	cleanup();
	data=rhs.data;
	sizeOfData=rhs.sizeOfData;
	timeStamp=rhs.timeStamp;
	keyFrame=rhs.keyFrame;

	rhs.height=0;
	rhs.width=0;
	rhs.data=0;
	rhs.sizeOfData=0;
	rhs.timeStamp=0;
	rhs.keyFrame=0;
	return *this;
}

//Difference
frame& frame::operator-(const frame& rhs)throw(std::logic_error)
{
	if(sizeOfData!=rhs.sizeOfData || height!=rhs.height || width!=rhs.width)
	{
		cleanup();
		throw std::logic_error("frames are not of equal value in operator-");
	}
	unsigned char* newData=new unsigned char[sizeOfData];
	unsigned long i=0,j=0;
	unsigned short tempChar[5]={};
	while(i<sizeOfData/3)
	{
		for(j=0;j<=2;j++)
		{
			tempChar[j]=abs(((short)rhs.data[i*3+j])-((short)data[i*3+j]));
			if(tempChar[j]<pixelResolution)
			{
				tempChar[j]=0;
			}
			newData[i*3+j]=tempChar[j];
		}
		i++;
	}
	//createBitmap(640,480,8,newData,sizeOfData,"c:/Users/Matt/Desktop/Preview.bmp");
	frame* returnFrame=new frame(height,width,newData,sizeOfData,timeStamp,false);
	return *returnFrame;

}

//Getters
int frame::getHeight() const
{
	return height;
}

int frame::getWidth() const
{
	return width;
}

unsigned char* frame::getData() const
{
	return data;
}

unsigned long frame::getSizeOfData() const
{
	return sizeOfData;
}

double frame::getPixelResolution() const
{
	return pixelResolution;
}

double frame::getTimeStamp() const
{
	return timeStamp;
}

bool frame::getKeyFrame() const
{
	return keyFrame;
}

//Setters
void frame::setHeight(const int& inHeight)throw(std::out_of_range)
{
	if(inHeight<0)
	{
		cleanup();
		throw std::out_of_range("Height cannot be a Negitive Number");
	}
	height=inHeight;
}

void frame::setWidth(const int& inWidth)throw(std::out_of_range)
{
	if(inWidth<0)
	{
		cleanup();
		throw std::out_of_range("Width cannot be a Negitive Number");
	}
	width=inWidth;
}

void frame::setData(unsigned char*const& inData)throw(std::out_of_range)
{
	if(inData<0)
	{
		cleanup();
		throw std::out_of_range("Data cannot be a Negitive Number");
	}
	cleanup();
	data=inData;
}

void frame::setSizeOfData(const unsigned long& inSizeOfData)
{
	sizeOfData=inSizeOfData;
}

void frame::setPixelResolution(const double& inPixelResolution)throw(std::out_of_range)
{
	if(inPixelResolution<0 || inPixelResolution>255)
	{
		throw std::out_of_range("PixelResolution cannot be set the that value");
	}
	pixelResolution=inPixelResolution;
}

void frame::setTimeStamp(const double& inTimeStamp)
{
	timeStamp=inTimeStamp;
}

void frame::setKeyFrame(const bool& inKeyFrame)throw(std::out_of_range)
{
	//if(inKeyFrame!=true || inKeyFrame!=false)
	//{
	//	throw std::out_of_range("keyFrame has to be a 1 or a 0");
	//}
	keyFrame=inKeyFrame;
}

//Public Methods
void frame::releaseData(frame& inFrame)
{
    if(this==&inFrame)
    {
        return;
    }
    inFrame.height=height;
    inFrame.width=width;
    inFrame.cleanup();
    inFrame.data=data;
    inFrame.sizeOfData=sizeOfData;
    inFrame.timeStamp=timeStamp;
    inFrame.keyFrame=keyFrame;

    height=0;
    width=0;
    data=0;
    sizeOfData=0;
    timeStamp=0;
    keyFrame=0;
}

void frame::releaseData()
{
    height=0;
    width=0;
    data=0;
    sizeOfData=0;
    timeStamp=0;
    keyFrame=0;
}

frame& frame::difference(const frame& inFrame,const frame& inMask)const throw(std::logic_error)
{
    if(sizeOfData!=inFrame.sizeOfData || height!=inFrame.height || width!=inFrame.width)
    {
        throw std::logic_error("frames are not of equal value in operator-");
    }

    unsigned char* newData=new unsigned char[sizeOfData];
    unsigned char* maskData=inMask.getData();
    unsigned long i=0,j=0;
    unsigned short tempChar[5]={};
    while(i<sizeOfData/3)
    {
        for(j=0;j<=2;j++)
        {
            tempChar[j]=abs(((short)inFrame.data[i*3+j])-((short)data[i*3+j]));
            if(tempChar[j]<pixelResolution)
            {
                tempChar[j]=0;
            }
            if(maskData[i*3+j]>128)
            {
                newData[i*3+j]=0;
            }
            else
            {

                newData[i*3+j]=tempChar[j];
            }
        }
        i++;
    }
    //createBitmap(640,480,8,newData,sizeOfData,"c:/Users/Matt/Desktop/Preview.bmp");
    frame* returnFrame=new frame(height,width,newData,sizeOfData,timeStamp,false);
    return *returnFrame;

}


//Helper Methods

void frame::cleanup()
{
	if(data!=0)
	{
		delete[] data;//**************************************************************
		data=0;
	}
}


//Destructor
frame::~frame(void)
{
	cleanup();
}
