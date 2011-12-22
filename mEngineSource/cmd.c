/*
 * cmd.c
 *
 * Wrapper of the MatLab Engine API engEvalString
 * for call from Mathematica
 *
 * Revision 2003.3.11
 *
 * Robert
 *	
 */

#include "mathlink.h"
#include "engine.h"

#define  BUFSIZE (20*1024)	//20k for output buffer

extern Engine* Eng;
extern void msg(const char* m);

void engcmd(const char* command)
{
	char buffer[BUFSIZE];	//MatLab output buffer
	bool SUCCESS = true;		//success flag

	if (NULL == Eng)	//if not opened yet
	{
		msg("eng::noMLB");	//message 
		SUCCESS = false;
	}
	else
	{
		engOutputBuffer(Eng, buffer, BUFSIZE);	//for return output
		//issue command
		if(engEvalString(Eng, command))	//if unsucessful
		{
			msg("engCmd::erexe");
			SUCCESS = false;
		}
	}

	if(SUCCESS)
		MLPutByteString(stdlink, buffer, strlen(buffer));
	else
		MLPutSymbol(stdlink, "$Failed");

}
