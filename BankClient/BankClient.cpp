// BankClient.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include "Logging.h"
#include "Transaction.h"
#include "Customer.h"
#include "Accounts.h"
#include "Datacontrol.h"
#include "XMLControler.h"


using namespace std;

int main()
{
	logging_printVersion();
	transaction_printVersion();
	xmlcontroler_printVersion();

	xmlcontroler_createCustomer("Mike", "Thomas");
	
	//cout << Accounts::Functions::createAcc(1, 1, "Funkt") << endl;
			
	logging_logError("Main terminated correctly", __FILE__);
    return 0;
}

