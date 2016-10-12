// Datacontrol.h - Contains declaration of Function class
#pragma once
#include "sqlite3.h"

#ifdef DATACONTROL_EXPORTS
#define DATACONTROL_API __declspec(dllexport) 
#else
#define DATACONTROL_API __declspec(dllimport) 
#endif

//const char *buildString = "Datacontrol 1.0 " __DATE__ ", " __TIME__ "\n";

/*
struct ResultSet
{
	int rows;
	char **columns;
	char **data;
	int errorCode;
	//data?
};
typedef ResultSet Resultset;



static int callback(void *data, int argc, char **argv, char **azColName);

extern "C" DATACONTROL_API void datacontrol_printVersion();
extern "C" DATACONTROL_API int createDatabase(char *dbName);
extern "C" DATACONTROL_API ResultSet execQuery(char *dbName, char *sqlStatement);
*/