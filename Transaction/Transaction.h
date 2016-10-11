// LOGGING.h - Contains declaration of Function class
#pragma once

#ifdef TRANSACTION_EXPORTS
#define TRANSACTION_API __declspec(dllexport) 
#else
#define TRANSACTION_API __declspec(dllimport) 
#endif


const char *transaction_buildString = "Transaction 1.0 " __DATE__ ", " __TIME__ "\n";

extern "C" TRANSACTION_API void transaction_printVersion();



