// BankClient.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include "Logging.h"
#include "SQLcontrol.h"
#include <string>
#include "XMLControler.h"

using namespace std;
#pragma warning(disable:4996)

int main()
{
	logging_printVersion();










































































	char *sql2;
	char *sql3;
	ResultSet result;

	char *sqlCreateTableCustomer = "CREATE TABLE CUSTOMER(" \
		"CUSTID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT," \
		"FIRSTNAME CHAR(100) NOT NULL," \
		"LASTNAME CHAR(100) NOT NULL," \
		"BIRTHDATE CHAR(100) NOT NULL," \
		"PLZLOCATION CHAR(100) NOT NULL," \
		"STREET CHAR(100) NOT NULL," \
		"HOUSENR CHAR(100) NOT NULL);";

	char *sqlCreateTableAccounts = "CREATE TABLE ACCOUNT(" \
		"ACCID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT," \
		"NAME CHAR(100) NOT NULL," \
		"TYPE INT NOT NULL," \
		"VALUE FLOAT NULL);";

	char *sqlCreateTableTransactions = "CREATE TABLE TRANSACTIONS(" \
		"ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT," \
		"FROMACC INT NOT NULL," \
		"TOACC INT NOT NULL," \
		"VALUE FLOAT NULL," \
		"FOREIGN KEY(FROMACC) REFERENCES ACCOUNT(ACCID)," \
		"FOREIGN KEY(TOACC) REFERENCES ACCOUNT(ACCID));";


	sql2 = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
		"VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
		"VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
		"VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
		"VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

	sql3 = "SELECT * from COMPANY";

	if (sql_createDatabase("my") == SQLITE_OK)
	{
		//result = sql_execQuery("my", sql);
		//result = sql_execQuery("my", sql2);
		result = sql_execQuery("my", sql3);
	}
	else
		result = ResultSet{ NULL, 0, 0 };

	for (unsigned int j = 0; j < result.rows; j++)
	{
		for (unsigned int k = 0; k < result.cols; k++)
		{
			printf("%s ", result.data[j][k]);
		}
		printf("\n");
	}
	logging_logError("Main terminated correctly", __FILE__);
	
    return 0;
}

