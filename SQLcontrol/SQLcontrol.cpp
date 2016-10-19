#include "stdafx.h"
#include <iostream>
#include <string>

#include "SQLcontrol.h"
#include "Logging.h"
#include "sqlite3.h"

using namespace std;
#pragma warning(disable:4996)

/**
* Prints the version of the .dll
*
*/
SQLCONTROL_API void SQLcontrol_printVersion()
{
	printf(buildString);
}

/**
* Creates the Database with the given name.
*
* @params: dbName Name of the database which should be created.
*/
SQLCONTROL_API int sql_createDatabase(char *dbName)
{
	sqlite3 *db;

	/* Open database */
	char * str3 = (char *)malloc(1 + strlen(dbName) + strlen(".db"));
	strcpy(str3, dbName);
	strcat(str3, ".db");

	int rc = sqlite3_open(str3, &db);
	if (rc != SQLITE_OK)
		return -1;
	else
		return 0;
}

/**
* The sql_execQuery executes a SQL statement.
*
* @params: dbName Name of the database where the statement should be executed.
* @params: sqlStatement The SQL Statement.
*/
SQLCONTROL_API ResultSet sql_execQuery(char *dbName, const char *sqlStatement)
{
	sqlite3 *db;
	char *zErrMsg = 0;
	struct ResultSet a = { NULL, 0, 0 };
	
	/* Open database */
	char *str3 = (char *)malloc(1 + strlen(dbName) + strlen(".db"));
	strcpy(str3, dbName);
	strcat(str3, ".db");

	int rc = sqlite3_open(str3, &db);
	if (rc != SQLITE_OK)
		return a;

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sqlStatement, callback, &a, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		logging_logError((char *)string("SQL error: " + string(zErrMsg)).c_str(), __FILE__);	//Write to logfile
		sqlite3_free(zErrMsg);							
		return a;
	}
	else //SUCCESS
		return a;

	sqlite3_close(db);
	return a;
}

/**
* The callback is called for each row of the result of the executed SQL statement.
*
* @params: *data is a pointer to something were the data can be stored.
* @params: argc is the amount of columns in this row.
* @params: **argv contains the data of this row.
* @params: **azColName contains the corresponding column name for this row.
*/
static int callback(void *data, int argc, char **argv, char **azColName)
{
	struct ResultSet *old = (ResultSet *)data;
	char ***temp;

	old->rows++;
	temp = (char ***)realloc(old->data, old->rows * sizeof(*old->data));
	if (temp) 
	{
		old->data = temp;
		old->data[old->rows - 1] = NULL;
	}
	else 
	{
		logging_logError("Kein virtueller RAM mehr vorhanden ... !", __FILE__);
		return EXIT_FAILURE;
	}

	for (unsigned int i = 0; i < old->rows; i++)
	{
		char **temp2 = (char **)realloc(old->data[i], argc * sizeof(argv) * sizeof(*old->data[i]));
		if (temp2) 
		{
			old->data[i] = temp2;
			old->data[i][argc - 1] = NULL;
		}
		else 
		{
			logging_logError("Kein virtueller RAM mehr vorhanden ... !", __FILE__);
			return EXIT_FAILURE;
		}
	}
	old->cols = argc;
	/*Storing the data in the 2D array*/
	for (int i = 0; i < argc; i++)
		temp[old->rows - 1][i] = strdup(argv[i] ? argv[i] : "NULL" );	//Duplicates the strings from argv, because when we return from the callback function, the memory of those strings is freed.
	
	return 0;
}