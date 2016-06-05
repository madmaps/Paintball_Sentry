#pragma once
#ifndef __FRAME__
#define __FRAME__
#include <exception>
#include <stdexcept>
#include <fstream>
#include <opencv2/opencv.hpp>

class frame
{
public:
	//Constructors
	frame(void); //Default
	frame(const frame& src); //Copy
	frame(frame&& src); //Move
	frame(const int& inHeight,const int& inWidth,unsigned char* inData,const unsigned long& inSizeOfData,const double& inTimeStamp,const bool& inKeyFrame); //Data
	frame(const cv::Mat& inFrame,const double& inTimeStamp,const bool& inKeyFrame);

	//Operator Overloading
	virtual frame& operator=(const frame& rhs); //Assignment
	virtual frame& operator=(frame&& rhs); //Move Assignment
	virtual frame& operator-(const frame& rhs)throw(std::logic_error);//Difference

	//Getters
	virtual int getHeight() const;
	virtual int getWidth()  const;
    virtual unsigned char* getData() const;
	virtual unsigned long getSizeOfData() const;
	virtual double getPixelResolution() const;
	virtual double getTimeStamp() const;
	virtual bool getKeyFrame() const;

	//Setters
	virtual void setHeight(const int& inHeight)throw(std::out_of_range);
	virtual void setWidth(const int& inWidth)throw(std::out_of_range);
	virtual void setData(unsigned char*const& inData)throw(std::out_of_range);
	virtual void setSizeOfData(const unsigned long& inSizeOfData);
	virtual void setPixelResolution(const double& inPixelResolution)throw(std::out_of_range);
	virtual void setTimeStamp(const double& inTimeStamp);
	virtual void setKeyFrame(const bool& inKeyFrame)throw(std::out_of_range);

	//Public Methods
    void releaseData(frame& inFrame);
    void releaseData();
    frame& difference(const frame& inFrame,const frame& inMask)const throw(std::logic_error);

	//Destructer
	virtual ~frame(void);

protected:
	//Members
	int height;//Height of image
	int width;//Width of image
	unsigned char* data;//Image data
	unsigned long sizeOfData;//Size in char of Image data
	static double pixelResolution;//Cutoff for Difference formula
	double timeStamp;
	bool keyFrame;

	//Helper Methods
	virtual void cleanup();
};

#endif

