// BankClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Logging.h"
#include "Transaction.h"
#include "Customer.h"
#include "Accounts.h"
#include "XML.h"

using namespace std;

int main()
{
	Logging::Functions::printVersion();
	Customer::Functions::printVersion();
	Accounts::Functions::printVersion();
	Transaction::Functions::printVersion();
	Xml::Functions::printVersion();
	
	
	Logging::Functions::logError("Main terminated correctly", __FILE__);
    return 0;
}

