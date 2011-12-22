/*
 * put.c
 *
 * Wrapper of the MatLab Engine API engPutVariable
 * for call from Mathematica
 *
 * Revision 2003.3.11
 *
 * Robert
 *	
 */

#include "mathlink.h"
#include "engine.h"

extern Engine* Eng;
extern void msg(const char* m);

// put a real array to the MatLab workspace
void engputr(const char* VarName,
		     const int* Dim, int Depth,
		     const double* Val, int ValLen)
{
	mxArray* MxVar = NULL;		//the variable to be put
	bool SUCCESS = true;		//success flag

	if (NULL == Eng)	//if not opened yet
	{
		msg("eng::noMLB");	//message 
		SUCCESS = false;
		goto epilog;
	}
	
	//create mxArray 
	MxVar = mxCreateNumericArray(Depth, Dim, mxDOUBLE_CLASS, mxREAL);
	if (NULL == MxVar)
	{
		msg("engPut::ercrt");
		SUCCESS = false;
		goto epilog;
	}
	//and populate
	memcpy((void *)(mxGetPr(MxVar)), (void *)Val, ValLen * sizeof(double));
	
	//put
	if(engPutVariable(Eng, VarName, MxVar))	//not successful
	{
		msg("engPut::erput");
		SUCCESS = false;
		goto epilog;
	}
	
epilog:
	if (MxVar != NULL)
		mxDestroyArray(MxVar);

	if(SUCCESS)
		MLPutString(stdlink, VarName);
	else
		MLPutSymbol(stdlink, "$Failed");
}

//put a complex array
void engputc(const char* VarName,
		     const int* Dim, int Depth,
		     const double* Re, int ReLen,
		     const double* Im, int ImLen)
{
	mxArray* MxVar = NULL;		//the variable to be put
	bool SUCCESS = true;		//success flag

	if (NULL == Eng)	//if not opened yet, open it
	{
		msg("eng::noMLB");	//message 
		SUCCESS = false;
		goto epilog;
	}
	
	//create mxArray 
	MxVar = mxCreateNumericArray(Depth, Dim, mxDOUBLE_CLASS, mxCOMPLEX);
	if (NULL == MxVar)
	{
		msg("engPut::ercrt");
		SUCCESS = false;
		goto epilog;
	}
	//and populate
	memcpy((void *)(mxGetPr(MxVar)), (void *)Re, ReLen * sizeof(double));
	memcpy((void *)(mxGetPi(MxVar)), (void *)Im, ImLen * sizeof(double));

	//put
	if(engPutVariable(Eng, VarName, MxVar))	//not successful
	{
		msg("engPut::erput");
		SUCCESS = false;
		goto epilog;
	}
	
epilog:
	if (MxVar != NULL)
		mxDestroyArray(MxVar);

	if(SUCCESS)
		MLPutString(stdlink, VarName);
	else
		MLPutSymbol(stdlink, "$Failed");
}

