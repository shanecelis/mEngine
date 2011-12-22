/*
 * isopen.c
 *
 * Checks whether the MATLAB Engine is opened
 *
 * Revision 2003.3.18
 *
 * Robert
 *	
 */

#include "mathlink.h"
#include "engine.h"

extern Engine* Eng;

void engisopen(void)
{
	if (NULL == Eng)	//if closed
		MLPutSymbol(stdlink, "False");
	else
		MLPutSymbol(stdlink, "True");

}

