// MathLibrary.cpp : Defines the exported functions for the DLL application.
// Compile by using: cl /EHsc /DMATHLIBRARY_EXPORTS /LD MathLibrary.cpp

#include "stdafx.h"
#include <iostream>
#include "Logging.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>


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
			string onlyFileName;
			string strPath(fileName);

			//retrieving filename from fullpath (http://stackoverflow.com/questions/5523042/how-to-get-the-stem-of-a-filename-from-a-path)
			size_t pos = strPath.find_last_of("\\");
			if (pos != std::string::npos)
			{
				onlyFileName.assign(strPath.begin() + pos + 1, strPath.end());
			}
			else
			{
				onlyFileName = strPath;
			}

			logFile.open("LogFile.txt", fstream::app);
			logFile << "[" << __DATE__ << ", " __TIME__ << "] - " << onlyFileName << " - " << errorText << endl;
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