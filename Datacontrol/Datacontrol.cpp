// MathLibrary.cpp : Defines the exported functions for the DLL application.
// Compile by using: cl /EHsc /DMATHLIBRARY_EXPORTS /LD MathLibrary.cpp

#include "stdafx.h"
#include <iostream>
#include "Datacontrol.h"

#include "sqlite3.h"

namespace Datacontrol
{
	void Functions::printVersion()
	{
		printf(buildString);
	}
	void Functions::createDatabase() {
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc = sqlite3_open("test.db", &db);
		printf("after rc");
	}

}