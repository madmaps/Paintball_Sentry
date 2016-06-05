#pragma once
#ifndef __ACCUMTARGET__
#define __ACCUMTARGET__

class accumTarget
{
public:
	accumTarget(void);
	unsigned long locX;
	unsigned long locY;
	unsigned long size;
	unsigned long red;
	unsigned long green;
	unsigned long blue;
	unsigned long totalPixilCount;

	void clear();
	~accumTarget(void);
};

#endif

