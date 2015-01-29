
#include "Cons.h"

#ifndef MEMORYDATA_H_
#define MEMORYDATA_H_

struct animation
{
	//length in steps
	uint8_t length;
	//pointer to the animation function - it will take a char[] as a parameter

};

struct animationData
{
	char data[8];
};

#endif /* MEMORYDATA_H_ */
