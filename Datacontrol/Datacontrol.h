// LOGGING.h - Contains declaration of Function class
#pragma once

#ifdef DATACONTROL_EXPORTS
#define DATACONTROL_API __declspec(dllexport) 
#else
#define DATACONTROL_API __declspec(dllimport) 
#endif



namespace Datacontrol
{
	const char *buildString = "Datacontrol 1.0 " __DATE__ ", " __TIME__ "\n";
	// This class is exported from the LOGGING.dll
	class Functions
	{
	public:
		static DATACONTROL_API void printVersion();
		static void DATACONTROL_API createDatabase();
	};


}