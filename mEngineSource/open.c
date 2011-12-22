/*
 * open.c
 *
 * Wrapper of the MatLab Engine API engOpen
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

void engopen(void)
{
	bool SUCCESS = true;		//success flag

	if (NULL == Eng)	//if not opened yet, open it
	{
		msg("eng::stMLB");	//message starting MATLAB
		if (!(Eng = engOpen(NULL)))	//start failure
		{
			msg("eng::erMLB");
			SUCCESS = false;
		}
		else
			engSetVisible(Eng, false);	//default hide
	}
	else
	{
		msg("eng::aoMLB");
		SUCCESS = false;
	}

	if(SUCCESS)
		MLPutSymbol(stdlink, "Null");
	else
		MLPutSymbol(stdlink, "$Failed");

}
