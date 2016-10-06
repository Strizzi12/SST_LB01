// LOGGING.h - Contains declaration of Function class
#pragma once

#ifdef CUSTOMER_EXPORTS
#define CUSTOMER_API __declspec(dllexport) 
#else
#define CUSTOMER_API __declspec(dllimport) 
#endif



namespace Customer
{
	const char *buildString = "Customer 1.0 " __DATE__ ", " __TIME__ "\n";
	// This class is exported from the LOGGING.dll
	class Functions
	{
	public:
		// Returns a + b
		static CUSTOMER_API void printVersion();
	};


}