// CurrencyExchange.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Logging.h"
#include <iostream>
#include <string>
#include "CurrencyExchange.h"


using namespace std;
#pragma warning(disable:4996)

CURRENCYEXCHANGE_API void currencyExchange_printVersion()
{
	printf(currency_buildString);
}

CURRENCYEXCHANGE_API void currencyExchange_info()
{
	printf(currency_buildString);
}


/*
To select a currency, please insert the integer from below.

EUR = 0
USD = 1
GBP = 2
INR = 3
JPY = 4
*/
CURRENCYEXCHANGE_API double currencyExchange_exchange(double amount, int from, int to)
{
	double newAmount = 0;
	switch (from)
	{
		case 0:	//EUR
		{	
			switch (to)
			{
			case 0: newAmount = amount;
				break;
			case 1: newAmount = amount * EurUsd;
				break;
			case 2: newAmount = amount * EurGbp;
				break;
			case 3: newAmount = amount * EurInr;
				break;
			case 4: newAmount = amount * EurJpy;
				break;
			}
			break;
		}
		case 1: //USD
		{
			switch (to)
			{
			case 0: newAmount = amount * UsdEur;
				break;
			case 1: newAmount = amount;
				break;
			case 2: newAmount = amount * UsdGbp;
				break;
			case 3: newAmount = amount * UsdInr;
				break;
			case 4: newAmount = amount * UsdJpy;
				break;
			}
			break;
		}
		case 2:	//GBP
		{
			switch (to)
			{
			case 0: newAmount = amount * GbpEur;
				break;
			case 1: newAmount = amount * GbpUsd;
				break;
			case 2: newAmount = amount;
				break;
			case 3: newAmount = amount * GbpInr;
				break;
			case 4: newAmount = amount * GbpJpy;
				break;
			}
			break;
		}
		case 3: //INR
		{
			switch (to)
			{
			case 0: newAmount = amount * InrEur;
				break;
			case 1: newAmount = amount * InrUsd;
				break;
			case 2: newAmount = amount * InrGbp;
				break;
			case 3: newAmount = amount;
				break;
			case 4: newAmount = amount * InrJpy;
				break;
			}
			break;
		}
		case 4: //JPY
		{
			switch (to)
			{
			case 0: newAmount = amount * JpyEur;
				break;
			case 1: newAmount = amount * JpyUsd;
				break;
			case 2: newAmount = amount * JpyGbp;
				break;
			case 3: newAmount = amount * JpyInr;
				break;
			case 4: newAmount = amount;
				break;
			}
			break;
		}
	}
	return newAmount;
}
