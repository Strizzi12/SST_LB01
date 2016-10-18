// BankClient.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include "Logging.h"
#include "Transaction.h"
#include "Customer.h"
#include "Datacontrol.h"
#include "SQLcontrol.h"
#include <string>
#include "XMLControler.h"
#include "CurrencyExchange.h"

using namespace std;
#pragma warning(disable:4996)

int main()
{
	logging_printVersion();
	transaction_printVersion();
	/*
	xmlcontroler_createCustomer("Mike", "Thomas", "5020 Salzburg", "strassenname", 10);
	xmlcontroler_createCustomer("Random", "Guy", "4840 Timelkam", "sName", 100);
	xmlcontroler_createCustomer("Specific", "Girl", "4840 Voecklabruck", "anothername", 1);
	xmlcontroler_deleteCustomerByID(1);
	xmlcontroler_deleteCustomerByUUID("sidfoisdhf-akdh1243-123fhjahsj");

	xmlcontroler_updateCustomer(2,"", "", "update", "update", 1337);
	xmlcontroler_renameCustomer(0, "Betty", "Katzi");

	//xmlcontroler_createAccount(0, 0);	
	//xmlcontroler_closeAccount(0);
	
	xmlcontroler_createAccount(0, 123.1);
	xmlcontroler_createAccount(0, 12323232323.22);
	xmlcontroler_attachAccount(0, 2);
	xmlcontroler_dettachAccount(0, 2);
	xmlcontroler_attachAccount(0, 2);
	xmlcontroler_attachAccount(0, 2);
	//xmlcontroler_attachAccount(1, 2);
	*/
	char *sql;
	char *sql2;
	char *sql3;
	char ***result;

	sql = "CREATE TABLE COMPANY("  \
		"ID INT PRIMARY KEY     NOT NULL," \
		"NAME           TEXT    NOT NULL," \
		"AGE            INT     NOT NULL," \
		"ADDRESS        CHAR(50)," \
		"SALARY         REAL );";

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
		result = NULL;

	double oldAmount = 3.57;
	double newAmount = currencyExchange_exchange(oldAmount, 0, 1);

	printf("Betrag in Euro: %f, in USD = %f \n", oldAmount, newAmount);

	
	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < 5; k++)
		{
			printf("%s ", result[j][k]);
		}
		printf("\n");
	}
	logging_logError("Main terminated correctly", __FILE__);
	
    return 0;
}

