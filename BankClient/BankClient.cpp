// BankClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "Logging.h"
#include "Transaction.h"
#include "Customer.h"
#include "Accounts.h"
#include "Datacontrol.h"

using namespace std;

int main()
{
	Logging::Functions::printVersion();
	Customer::Functions::printVersion();
	Accounts::Functions::printVersion();
	Transaction::Functions::printVersion();
	Logging::Functions::printVersion();

	cout << Accounts::Functions::createAcc(1, 1, "Funkt") << endl;
			
	Logging::Functions::logError("Main terminated correctly", __FILE__);
    return 0;
}

