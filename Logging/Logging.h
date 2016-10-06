// LOGGING.h - Contains declaration of Function class
#pragma once

#ifdef LOGGING_EXPORTS
#define LOGGING_API __declspec(dllexport) 
#else
#define LOGGING_API __declspec(dllimport) 
#endif



namespace Logging
{
	const char *buildString = "Logging 1.0 " __DATE__ ", " __TIME__ "\n";
	// This class is exported from the LOGGING.dll
	class Functions
	{
	public:
		// Returns a + b
		static LOGGING_API void printVersion();
	};


}