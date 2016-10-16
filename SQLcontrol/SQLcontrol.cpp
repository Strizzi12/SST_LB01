

#include "stdafx.h"
#include <iostream>
#include <string>

#include "SQLcontrol.h"
#include "Logging.h"
#include "sqlite3.h"

using namespace std;
#pragma warning(disable:4996)


SQLCONTROL_API void SQLcontrol_printVersion()
{
	printf(buildString);
}

SQLCONTROL_API int sql_createDatabase(char *dbName)
{
	sqlite3 *db;
	/* Open database */
	//string databaseName = *dbName + ".db";
	//rc = sqlite3_open(databaseName.c_str(), &db);

	char * str3 = (char *)malloc(1 + strlen(dbName) + strlen(".db"));
	strcpy(str3, dbName);
	strcat(str3, ".db");

	int rc = sqlite3_open(str3, &db);
	if (rc != SQLITE_OK)
		return -1;
	else
		return 0;
}

SQLCONTROL_API Result sql_execQuery(char *dbName, char *sqlStatement)
{
	ResultSet result;
	ResultSet *resultPtr = &result;
	Result myResult;
	sqlite3 *db;
	char *zErrMsg = 0;

	/* Open database */
	char * str3 = (char *)malloc(1 + strlen(dbName) + strlen(".db"));
	strcpy(str3, dbName);
	strcat(str3, ".db");

	int rc = sqlite3_open(str3, &db);
	if (rc != SQLITE_OK)
	{
		result.errorCode = -1;
		return myResult;
	}

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sqlStatement, callback, (void *)&myResult, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		logging_logError("SQL error: %s\n", zErrMsg);	//Write to logfile
		sqlite3_free(zErrMsg);
		result.errorCode = -2;							//Errorcode -2 = SQL statement execution failure
		return myResult;
	}
	else //SUCCESS
		result.errorCode = 0;

	sqlite3_close(db);
	return myResult;
}

static int callback(void *data, int argc, char **argv, char **azColName)
{
	//ResultSet *resultPtr = (ResultSet *)data;
	Result *myResult = (Result *)data;
	myResult->rows = argc;
	for (int i = 0; i < argc; i++)
	{
		myResult->addColumns(azColName[i]);
		myResult->addData(argv[i]);
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}	
	return 0;
}

void Result::addColumns(string toAdd)
{
	nameOfColumnsList.push_back(toAdd);
}

void Result::addData(string toAdd)
{
	dataList.push_back(toAdd);
}
