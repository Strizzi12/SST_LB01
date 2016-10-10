// XML.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <iostream>
#include "XML.h"

using namespace std;

namespace Xml
{
	void Functions::printVersion()
	{
		printf(buildString);
	}
}
