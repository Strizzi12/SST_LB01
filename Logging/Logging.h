// LOGGING.h - Contains declaration of Function class
#pragma once

#ifdef LOGGING_EXPORTS
#define LOGGING_API __declspec(dllexport) 
#else
#define LOGGING_API __declspec(dllimport) 
#endif

const char *logging_buildString = "Logging 1.0 " __DATE__ ", " __TIME__ "\n";

extern "C" LOGGING_API void logging_printVersion();
extern "C" LOGGING_API void logging_logError(char*, const char*);



