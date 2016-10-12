#pragma once
#include "sqlite3.h"

#ifdef SQLCONTROL_EXPORTS
#define SQLCONTROL_API __declspec(dllexport) 
#else
#define SQLCONTROL_API __declspec(dllimport) 
#endif

struct ResultSet
{
	int rows;
	char **columns;
	char **data;
	int errorCode;
	//data?
};
typedef ResultSet Resultset;

const char *buildString = "SQLontrol 1.0 " __DATE__ ", " __TIME__ "\n";

static int callback(void *data, int argc, char **argv, char **azColName);

extern "C" SQLCONTROL_API void SQLcontrol_printVersion();
extern "C" SQLCONTROL_API int sql_createDatabase(char *dbName);
extern "C" SQLCONTROL_API ResultSet sql_execQuery(char *dbName, char *sqlStatement);
