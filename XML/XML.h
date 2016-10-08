// XML.h - Contains declaration of Function class
#pragma once

#ifdef XML_EXPORTS
#define XML_API __declspec(dllexport) 
#else
#define XML_API __declspec(dllimport) 
#endif



namespace Xml
{
	const char *buildString = "Xml 1.0 " __DATE__ ", " __TIME__ "\n";
	// This class is exported from the LOGGING.dll
	class Functions
	{
	public:
		static XML_API void printVersion();
	};


}