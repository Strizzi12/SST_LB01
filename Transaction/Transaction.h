// LOGGING.h - Contains declaration of Function class
#pragma once

#ifdef TRANSACTION_EXPORTS
#define TRANSACTION_API __declspec(dllexport) 
#else
#define TRANSACTION_API __declspec(dllimport) 
#endif



namespace Transaction
{
	const char *buildString = "Transaction 1.0 " __DATE__ ", " __TIME__ "\n";
	// This class is exported from the LOGGING.dll
	class Functions
	{
	public:
		// Returns a + b
		static TRANSACTION_API void printVersion();
	};


}