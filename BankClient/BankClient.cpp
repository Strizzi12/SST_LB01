// BankClient.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include "Logging.h"
#include "SQLcontrol.h"
#include <string>
#include "XMLControler.h"
#include "BankControl.h"

using namespace std;
#pragma warning(disable:4996)

int main()
{
	logging_printVersion();
	//xmlcontroler_createCustomer("Mike", "Thomas", "5020 Salzburg", "strassenname", 10);
	//xmlcontroler_createCustomer("Random", "Guy", "4840 Timelkam", "sName", 100);
	//xmlcontroler_createCustomer("Specific", "Girl", "4840 Voecklabruck", "anothername", 1);

	//xmlcontroler_createAccount(0, 100.0f);
	//xmlcontroler_createAccount(0, 100.0f);
	//xmlcontroler_createAccount(0, 100.0f);
	//xmlcontroler_createAccount(0, 100.0f);
	//xmlcontroler_createAccount(0, -100.0f);

	//xmlcontroler_attachAccount(1, 0);
	//xmlcontroler_attachAccount(0, 1);
	//xmlcontroler_attachAccount(1, 1);
	//xmlcontroler_attachAccount(2, 1);
	//xmlcontroler_attachAccount(3, 1);
	//xmlcontroler_attachAccount(4, 1);

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


	//xmlcontroler_depositMoney(0, 100.0f);
	//xmlcontroler_depositMoney(1, 111.0f);

	//xmlcontroler_withdrawMoney(0, 100000.0f);
	//xmlcontroler_withdrawMoney(0, 100.0f);
	//xmlcontroler_depositMoney(0, 1000.0f);
	//xmlcontroler_transferMoney(0, 1, 222.0f);

	//xmlcontroler_getBankStatement(0);
	//xmlcontroler_getBalance(1);

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
		"VALUE FLOAT NOT NULL," \
		"FOREIGN KEY(FROMACC) REFERENCES ACCOUNT(ACCID)," \
		"FOREIGN KEY(TOACC) REFERENCES ACCOUNT(ACCID));";

	char *sqlCreateJoinAccountsTable = "CREATE TABLE JOINTABLEACCOUNTS( " \
		"ACCID INTEGER NOT NULL," \
		"CUSTID INTEGER NOT NULL," \
		"primary key(CUSTID, ACCID)," \
		"foreign key(CUSTID)" \
		"references CUSTOMER(CUSTID)," \
		"foreign key(ACCID)" \
		"references ACCOUNT(ACCID));";

	sql_execQuery("Bank", sqlCreateTableAccounts);
	sql_execQuery("Bank", sqlCreateTableCustomer);
	sql_execQuery("Bank", sqlCreateTableTransactions);
	sql_execQuery("Bank", sqlCreateJoinAccountsTable);

	bankControl_createAcc(1, "MyAcc1", 100);
	bankControl_createAcc(1, "MyAcc2", 100);
	bankControl_createAcc(1, "MyAcc3", 100);
	//bankControl_deleteAcc(2);
	bankControl_createCustomer("Mike", "Ich", "12.34.4567", "test", "test Straﬂe", "12a");
	bankControl_createCustomer("Hugo", "Wer", "987.987654", "Dieser Block", "Jene Straﬂe", "12a");
	//bankControl_renameAcc(1, "NewAccName");
	/*bankControl_addUserToAcc(1, 1);
	bankControl_addUserToAcc(1, 3);
	bankControl_addUserToAcc(3, 1);
	bankControl_addUserToAcc(1, 2);
	bankControl_removeUserFromAcc(2, 1);*/
	bankControl_createCustomer("Andi", "Ich", "07.11.1992", "Mein Block", "Meine Straﬂe", "12a");
	/*bankControl_modifyCustomer(1, "Sepp", "Du", "usw", "Mein Block", "Meine Straﬂe", "12a");
	bankControl_deleteCustomer(1);
	bankControl_depositMoney(1, 215);
	bankControl_transferMoney(1,3,35);
	bankControl_depositMoney(1,15);
	bankControl_withdrawMoney(1,15);
	bankControl_getBankStatement(3);*/

	logging_logError("Main terminated correctly", __FILE__);
	
    return 0;
}

