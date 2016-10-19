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
	xmlcontroler_createCustomer("Mike", "Thomas", "5020 Salzburg", "strassenname", 10);
	xmlcontroler_createCustomer("Random", "Guy", "4840 Timelkam", "sName", 100);
	//xmlcontroler_createCustomer("Specific", "Girl", "4840 Voecklabruck", "anothername", 1);

	xmlcontroler_createAccount(0, 100.0f);
	xmlcontroler_createAccount(0, 100.0f);
	xmlcontroler_createAccount(0, 100.0f);
	xmlcontroler_createAccount(0, 100.0f);
	xmlcontroler_createAccount(0, -100.0f);

	xmlcontroler_attachAccount(1, 0);
	xmlcontroler_attachAccount(0, 1);
	xmlcontroler_attachAccount(1, 1);
	xmlcontroler_attachAccount(2, 1);
	xmlcontroler_attachAccount(3, 1);
	xmlcontroler_attachAccount(4, 1);

	//xmlcontroler_dettachAccount(1, 2);

	//xmlcontroler_closeAccount(1);

	//xmlcontroler_deleteCustomerByID(1);
	//xmlcontroler_deleteCustomerByUUID("sidfoisdhf-akdh1243-123fhjahsj");

	//xmlcontroler_updateCustomer(2,"", "", "update", "update", 1337);
	//xmlcontroler_renameCustomer(0, "Betty", "Katzi");

	//xmlcontroler_createAccount(0, 0);	
	//xmlcontroler_manageAccount(0, 1);
	//xmlcontroler_closeAccount(0);

	//xmlcontroler_createAccount(0, 123.1f);
	//xmlcontroler_createAccount(0, 123323.22f);
	//xmlcontroler_attachAccount(0, 2);
	//xmlcontroler_dettachAccount(0, 2);
	//xmlcontroler_attachAccount(0, 2);
	//xmlcontroler_attachAccount(0, 2);
	//xmlcontroler_attachAccount(1, 2);

	//xmlcontroler_createAccount(0, 100.0f);
	//xmlcontroler_createAccount(0, 0.0f);
	//xmlcontroler_transferMoney(0,1,50.0f);

	//xmlcontroler_closeAccount(0);


	xmlcontroler_depositMoney(0, 100.0f);
	//xmlcontroler_depositMoney(1, 111.0f);

	//xmlcontroler_withdrawMoney(0, 100000.0f);
	//xmlcontroler_withdrawMoney(0, 100.0f);
	//xmlcontroler_depositMoney(0, 1000.0f);
	//xmlcontroler_transferMoney(0, 1, 222.0f);

	//xmlcontroler_getBankStatement(0);
	xmlcontroler_getBalance(1);

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
		"TYPE INTEGER NOT NULL," \
		"VALUE FLOAT NULL);";

	char *sqlCreateTableTransactions = "CREATE TABLE TRANSACTIONS(" \
		"ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT," \
		"FROMACC INTEGER NOT NULL," \
		"TOACC INTEGER NOT NULL," \
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

