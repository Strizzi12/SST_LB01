// BankClient.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include "Logging.h"
#include "Transaction.h"
#include "Customer.h"
#include "Accounts.h"
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
	
	xmlcontroler_createCustomer("Mike", "Thomas");
			
	logging_logError("Main terminated correctly", __FILE__);

    return 0;
}

