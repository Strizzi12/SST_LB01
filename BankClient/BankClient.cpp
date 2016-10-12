// BankClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Logging.h"
#include "Transaction.h"
#include "Customer.h"
#include "Accounts.h"
#include "Datacontrol.h"
#include "SQLcontrol.h"
#include <string>

using namespace std;
#pragma warning(disable:4996)

int main()
{
	char *sql;
	ResultSet result;
	char snum[20];
	sql = "Test;";
	/*sql = "CREATE TABLE COMPANY("  \
		"ID INT PRIMARY KEY     NOT NULL," \
		"NAME           TEXT    NOT NULL," \
		"AGE            INT     NOT NULL," \
		"ADDRESS        CHAR(50)," \
		"SALARY         REAL );";
	*/
	/*sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
		"VALUES (5, 'Neger', 32, 'California', 20000.00 ); " \
		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
		"VALUES (6, 'Allen', 25, 'Texas', 15000.00 ); "     \
		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
		"VALUES (7, 'Teddy', 23, 'Norway', 20000.00 );" \
		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
		"VALUES (8, 'Mark', 25, 'Rich-Mond ', 65000.00 );";
	*/

	logging_printVersion();
	transaction_printVersion();
	
	//cout << Accounts::Functions::createAcc(1, 1, "Funkt") << endl;
			
	logging_logError("Main terminated correctly", __FILE__);

	if (sql_createDatabase("myDatabase") == SQLITE_OK)
		result = sql_execQuery("myDatabase", sql);
	
	char myString[100] = "Error Code: ";
	_itoa(result.errorCode, snum, 10);
	strcat(myString, snum);

	logging_logError(myString,  __FILE__);

    return 0;
}

