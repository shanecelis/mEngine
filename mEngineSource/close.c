/*
 * close.c
 *
 * Wrapper of the MatLab Engine API engClose
 * for call from Mathematica
 *
 * Revision 2003.3.18
 *
 * Robert
 *	
 */

#include "mathlink.h"
#include "engine.h"

extern Engine* Eng;
extern void msg(const char* m);


void engclose(void)
{
	bool SUCCESS = true;		//success flag

	if (NULL == Eng)	//if closed
	{
		msg("eng::noMLB");	//message MATLAB closed
		SUCCESS = false;
	}
	else
	{
		engClose(Eng);
		Eng = NULL;
	}

	if(SUCCESS)
		MLPutSymbol(stdlink, "Null");
	else
		MLPutSymbol(stdlink, "$Failed");

}

