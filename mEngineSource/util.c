/*
 * util.c
 *
 * Utility functions for other modules of the program mLink.exe
 *
 * Revision 2003.3.11
 *
 * Robert
 *	
 */


#include <string.h>
#include "mathlink.h"

void msg(const char* m)
{
	char cmd[100] = "Message[";
	strcat(strcat(cmd, m), "]");
	MLEvaluateString(stdlink, cmd);
}
