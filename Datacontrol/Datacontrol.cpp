
#include "stdafx.h"
#include <iostream>
#include "Datacontrol.h"
#include "sqlite3.h"


DATACONTROL_API void datacontrol_printVersion()
{
	printf(buildString);
}

DATACONTROL_API int createDatabase(char *dbName)
{
	sqlite3 *db;
	int rc = sqlite3_open(dbName, &db);
	if (rc != SQLITE_OK)
		return -1;
	else
		return 0;
}

DATACONTROL_API ResultSet execQuery(char *dbName, char *sqlStatement)
{
	ResultSet result;
	ResultSet *resultPtr = &result;
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

	/* Open database */
	rc = sqlite3_open(dbName, &db);
	if(rc != SQLITE_OK)	
	{
		result.errorCode = -1;
		return result;
	}

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sqlStatement, callback, (void *)resultPtr, &zErrMsg);
	if (rc != SQLITE_OK) 
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		//Write to logfile
		sqlite3_free(zErrMsg);
		result.errorCode = -2;
		return result;
	}
	else //SUCCESS
		result.errorCode = 0;

	sqlite3_close(db);
	return result;
}

static int callback(void *data, int argc, char **argv, char **azColName) 
{
	ResultSet *resultPtr = (ResultSet *)data;
	resultPtr->rows = argc;
	resultPtr->columns = azColName;
	resultPtr->data = argv;
	return 0;
}
