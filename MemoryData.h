
#include "Const.h"

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
	char data[CHARS_NUMBER];
};

#endif /* MEMORYDATA_H_ */
