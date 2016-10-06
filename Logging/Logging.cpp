// MathLibrary.cpp : Defines the exported functions for the DLL application.
// Compile by using: cl /EHsc /DMATHLIBRARY_EXPORTS /LD MathLibrary.cpp


#include "stdafx.h"
#include <iostream>
#include "Logging.h"
#include <fstream>

using namespace std;

namespace Logging
{
	void Functions::printVersion()
	{
		printf(buildString);
	}

	void Functions::printError(char* errorText)
	{
		ofstream myfile;
		myfile.open("LogFile.txt", fstream::app);
		myfile << "[" << __DATE__ << ", " __TIME__ << "] " << errorText << endl;
		myfile.close();	
	}

}