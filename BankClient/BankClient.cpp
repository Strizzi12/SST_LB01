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

using namespace std;
#pragma warning(disable:4996)

int main()
{
	logging_printVersion();
	transaction_printVersion();
	
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

	logging_logError("Main terminated correctly", __FILE__);
	
    return 0;
}

