// LOGGING.h - Contains declaration of Function class
#pragma once

#ifdef ACCOUNTS_EXPORTS
#define ACCOUNTS_API __declspec(dllexport) 
#else
#define ACCOUNTS_API __declspec(dllimport) 
#endif



namespace Accounts
{
	const char *buildString = "Accounts 1.0 " __DATE__ ", " __TIME__ "\n";
	// This class is exported from the LOGGING.dll
	class Functions
	{
	public:
		// Returns a + b
		static ACCOUNTS_API void printVersion();
	};


}