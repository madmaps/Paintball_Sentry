#include "accumTarget.h"


accumTarget::accumTarget(void):locX(0),locY(0),size(0),red(0),green(0),blue(0),totalPixilCount(0)
{
}

void accumTarget::clear()
{
	locX=0;
	locY=0;
	size=0;
	red=0;
	green=0;
	blue=0;
	totalPixilCount=0;
}


accumTarget::~accumTarget(void)
{
}
