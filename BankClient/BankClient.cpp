// BankClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "Logging.h"
#include "Transaction.h"
#include "Customer.h"
#include "Accounts.h"

using namespace std;

int main()
{



	Logging::Functions::printVersion();
	Customer::Functions::printVersion();
	Accounts::Functions::printVersion();
	Transaction::Functions::printVersion();
	char* tmp = "TestText!";
	Logging::Functions::printError(tmp);
	Accounts::Functions::createAcc(1, 1, "TestAcc");

	getchar();

    return 0;
	
}

