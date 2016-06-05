#include "frameAnalyzer.h"

//Constructers
//Default
frameAnalyzer::frameAnalyzer(void):analyzeUnits(),utt(),comparedFrame(0),keyFrame(0),pixelResolution(0),returnFrame(0)
{
}

//Copy
frameAnalyzer::frameAnalyzer(const frameAnalyzer& src):analyzeUnits(src.analyzeUnits),utt(src.utt),comparedFrame(src.comparedFrame),keyFrame(src.keyFrame),pixelResolution(src.pixelResolution),returnFrame(src.returnFrame)
{
}

//Move
frameAnalyzer::frameAnalyzer(frameAnalyzer&& src)
{
	analyzeUnits=src.analyzeUnits;
	utt=src.utt;
	comparedFrame=src.comparedFrame;
	keyFrame=src.keyFrame;
	src.comparedFrame=0;
	src.keyFrame=0;
	pixelResolution=src.pixelResolution;
    returnFrame=src.returnFrame;
    src.returnFrame=0;
}

//Operator Overloading
frameAnalyzer& frameAnalyzer::operator=(const frameAnalyzer& rhs)
{
	if(this==&rhs)
	{
		return *this;
	}
	cleanup();

	analyzeUnits=rhs.analyzeUnits;
	utt=rhs.utt;
	pixelResolution=rhs.pixelResolution;
	if(rhs.comparedFrame!=0)
	{
		comparedFrame=new frame(*rhs.comparedFrame);
	}
	else
	{
		comparedFrame=0;
	}
	if(rhs.keyFrame!=0)
	{
		keyFrame=new frame(*rhs.keyFrame);
	}
	else
	{
		keyFrame=0;
	}
    if(rhs.returnFrame!=0)
    {
        returnFrame=new frame(*rhs.returnFrame);
    }
    else
    {
        returnFrame=0;
    }
	return *this;
}

frameAnalyzer& frameAnalyzer::operator=(frameAnalyzer&& rhs)
{
	if(this==&rhs)
	{
		return *this;
	}
	cleanup();
	analyzeUnits=rhs.analyzeUnits;
	utt=rhs.utt;
	comparedFrame=rhs.comparedFrame;
	keyFrame=rhs.keyFrame;
	pixelResolution=rhs.pixelResolution;
    returnFrame=rhs.returnFrame;

	rhs.comparedFrame=0;
	rhs.keyFrame=0;
    rhs.returnFrame=0;

	return *this;
}

//std::vector<twoDTargets>& frameAnalyzer::operator>>(frame& inFrame)
std::list<twoDTargets>& frameAnalyzer::operator>>(frame& inFrame)
{
	//std::vector<twoDTargets>* returnTarget;
	std::list<twoDTargets>* returnTargets;
	if(&inFrame!=0)
	{
		if(inFrame.getKeyFrame())
		{
			if(keyFrame!=0)
			{
                if(viewFrame)
                {
                    returnFrame=new frame();
                    keyFrame->releaseData(*returnFrame);
                }
                else
                {
                    delete keyFrame;
                }
                keyFrame=0;
			}
			keyFrame=&inFrame;
		}
		else
		{
			if(comparedFrame!=0)
			{
                if(viewFrame)
                {
                    returnFrame=new frame();
                    comparedFrame->releaseData(*returnFrame);
                }
                else
                {
                    delete comparedFrame;
                }
                comparedFrame=0;
			}
            else
            {
                returnFrame=0;
            }
			comparedFrame=&inFrame;
		}
		if(comparedFrame==0 || keyFrame==0)
		{
			//returnTarget = new std::vector<twoDTargets>;
			returnTargets=new std::list<twoDTargets>;
			return *returnTargets;
		}
	comparedFrame->setPixelResolution(pixelResolution);
	//frame tempFrame(*keyFrame-*comparedFrame);//MEMORY LEAK???***********************
	frame* tempFrame=&(*keyFrame-*comparedFrame);
	returnTargets=&utt.convert(*comparedFrame,analyzeUnits >> *tempFrame);
	delete tempFrame;
	return *returnTargets;//utt.convert(*comparedFrame,analyzeUnits >> tempFrame);
	}
	//returnTarget = new std::vector<twoDTargets>;
	returnTargets=new std::list<twoDTargets>;
	return *returnTargets;

}

//Getters
double frameAnalyzer::getUnitSize() const
{
	return analyzeUnits.getUnitSize();
}

double frameAnalyzer::getUnitResolution() const
{
	return analyzeUnits.getUnitResolution();
}

double frameAnalyzer::getPixelResolution() const
{
	return pixelResolution;
}

bool frameAnalyzer::getDebugMode() const
{
    return analyzeUnits.getDebugMode();
}

bool frameAnalyzer::getViewFrameMode() const
{
    return viewFrame;
}

//Setters
void frameAnalyzer::setUnitSize(const double& inUnitSize)
{
	analyzeUnits.setUnitSize(inUnitSize);
}

void frameAnalyzer::setUnitResolution(const double& inUnitResolution)
{
	analyzeUnits.setUnitResolution(inUnitResolution);
    utt.setUnitResolution(inUnitResolution);

}

void frameAnalyzer::setPixelResolution(const double& inPixelResolution)
{
	pixelResolution=inPixelResolution;
}

void frameAnalyzer::setDebugMode(const bool& inDebugMode)
{
    analyzeUnits.setDebugMode(inDebugMode);
}

void frameAnalyzer::setUttUnitResolution(const double& inUnitResolution)
{
    utt.setUnitResolution(inUnitResolution);
}

void frameAnalyzer::setViewFrameMode(const bool& inViewFrame)
{
    viewFrame=inViewFrame;
}

void frameAnalyzer::setMaskFrame(const frame &inMaskFrame)
{
    analyzeUnits.setMaskFrame(inMaskFrame);
}


//Public Methods

frame* frameAnalyzer::getDebugFrame()
{
    return analyzeUnits.getDebugFrame();
}

frame* frameAnalyzer::getCurrentFrame()
{
    if(viewFrame!=0 && returnFrame!=0)
    {
        frame* sendBackFrame = new frame();
        returnFrame->releaseData(*sendBackFrame);
        return sendBackFrame;
    }
    return 0;
}

//Destructor
frameAnalyzer::~frameAnalyzer(void)
{
	cleanup();
}

//Helper Methods
void frameAnalyzer::cleanup()
{
	if(comparedFrame!=0)
	{
		delete comparedFrame;
		comparedFrame=0;
	}
	if(keyFrame!=0)
	{
		delete keyFrame;
		keyFrame=0;
	}
    if(returnFrame!=0)
    {
        delete returnFrame;
        returnFrame=0;
    }
}
