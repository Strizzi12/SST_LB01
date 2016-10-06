// MathLibrary.cpp : Defines the exported functions for the DLL application.
// Compile by using: cl /EHsc /DMATHLIBRARY_EXPORTS /LD MathLibrary.cpp


#include "stdafx.h"
#include <iostream>
#include "Transaction.h"


namespace Transaction
{
	void Functions::printVersion()
	{
		printf(buildString);
	}

}