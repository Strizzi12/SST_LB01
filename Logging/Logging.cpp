// MathLibrary.cpp : Defines the exported functions for the DLL application.
// Compile by using: cl /EHsc /DMATHLIBRARY_EXPORTS /LD MathLibrary.cpp

#include "stdafx.h"
#include <iostream>
#include "Logging.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
#include <stdlib.h>
#include <Windows.h>


using namespace std;
#pragma warning(disable:4996)

namespace Logging
{
	void Functions::printVersion()
	{
		printf(buildString);
	}

	void Functions::logError(char* errorText, const char* fileName)
	{
		ofstream logFile;
		logFile.exceptions(ofstream::failbit | ofstream::badbit);

		try
		{
			logFile.open("LogFile.txt", fstream::app);
			logFile << "[" << __DATE__ << ", " __TIME__ << "] - "<< errorText << endl;
			logFile.close();
		}
		//general ex handling -> not nice but works, use carefully
		catch (...)
		{
			cout << "Exception opening/writing Logfile!" << endl;
			return;
		}
	}



}