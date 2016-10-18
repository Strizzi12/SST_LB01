#pragma once
#include "sqlite3.h"
#include <list>
#include <string>

#ifdef SQLCONTROL_EXPORTS
#define SQLCONTROL_API __declspec(dllexport) 
#else
#define SQLCONTROL_API __declspec(dllimport) 
#endif

using namespace std;

const char *buildString = "SQLontrol 1.0 " __DATE__ ", " __TIME__ "\n";

struct mytable 
{
	char ***data;
	size_t dim;
};

static int callback(void *data, int argc, char **argv, char **azColName);

extern "C" SQLCONTROL_API void SQLcontrol_printVersion();
extern "C" SQLCONTROL_API int sql_createDatabase(char *dbName);
extern "C" SQLCONTROL_API char*** sql_execQuery(char *dbName, char *sqlStatement);