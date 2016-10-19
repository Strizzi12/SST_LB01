

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
	char * str3 = (char *)malloc(1 + strlen(dbName) + strlen(".db"));
	strcpy(str3, dbName);
	strcat(str3, ".db");

	int rc = sqlite3_open(str3, &db);
	if (rc != SQLITE_OK)
		return -1;
	else
		return 0;
}

SQLCONTROL_API char*** sql_execQuery(char *dbName, char *sqlStatement)
{
	sqlite3 *db;
	char *zErrMsg = 0;
	struct mytable a = { NULL, 0 };
	
	/* Open database */
	char *str3 = (char *)malloc(1 + strlen(dbName) + strlen(".db"));
	strcpy(str3, dbName);
	strcat(str3, ".db");

	int rc = sqlite3_open(str3, &db);
	if (rc != SQLITE_OK)
		return NULL;

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sqlStatement, callback, &a, &zErrMsg);

	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < 5; k++)
		{
			printf("%s ", a.data[j][k]);
		}
		printf("\n");
	}
	if (rc != SQLITE_OK)
	{
		logging_logError("SQL error: %s\n", zErrMsg);	//Write to logfile
		sqlite3_free(zErrMsg);							
		return NULL;
	}
	else //SUCCESS
		return a.data;

	sqlite3_close(db);
	return a.data;
}

/**
* The callback is called for each row of the result of the executed SQL statement.
* @Params:
	*data is a pointer to something were the data can be stored.
	argc is the amount of columns in this row.
	**argv contains the data of this row.
	**azColName contains the corresponding column name for this row.
*/
static int callback(void *data, int argc, char **argv, char **azColName)
{
	struct mytable *old = (mytable *)data;
	char ***temp;

	old->dim++;
	temp = (char ***)realloc(old->data, old->dim * sizeof(*old->data));
	if (temp) 
	{
		old->data = temp;
		old->data[old->dim - 1] = NULL;
	}
	else 
	{
		logging_logError("Kein virtueller RAM mehr vorhanden ... !", __FILE__);
		return EXIT_FAILURE;
	}

	for (int i = 0; i < old->dim; i++) 
	{
		char **temp2 = (char **)realloc(old->data[i], sizeof(argv) * sizeof(*old->data[i]));
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
	/*Storing the data in the 2D array*/
	for (int i = 0; i < argc; i++)
		temp[old->dim - 1][i] = strdup(argv[i]);	//Duplicates the strings from argv, because when we return from the callback function, the memory of those strings is freed.
	
	return 0;
}