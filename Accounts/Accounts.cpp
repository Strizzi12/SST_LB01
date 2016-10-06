// MathLibrary.cpp : Defines the exported functions for the DLL application.
// Compile by using: cl /EHsc /DMATHLIBRARY_EXPORTS /LD MathLibrary.cpp

#include "stdafx.h"
#include <iostream>
#include "Accounts.h"
#include <list>

namespace Accounts
{
	ACCOUNTS_API void Functions::printVersion()
	{
		printf(buildString);
	}
	ACCOUNTS_API int Functions::createAcc(int _custNumber, int _accType, char* _accName)
	{
		if (*_accName == NULL || sizeof(_accName) == 0)
			return -1;
		struct Account acc;
		strcpy_s(acc.accName, _accName);
		acc.accType = _accType;
		acc.ownerCustNumber = _custNumber;
		//accNumber is set from the database
		//createNewAccount(acc);
		return 0;
	}
	ACCOUNTS_API int Functions::deleteAcc(int _accNumber)
	{
		if (_accNumber <= 0)
			return -1;
		//deleteAcc
		return 0;
	}
	ACCOUNTS_API int Functions::editAccName(int _accNumber, char* _newName)
	{
		if (*_newName == NULL || sizeof(_newName) == 0 || _accNumber <= 0)
			return -1;
		return 0;
	}
	ACCOUNTS_API int Functions::addUserToAcc(int _accNumber, int _custNumber)
	{
		return 0;
	}
	ACCOUNTS_API int Functions::removeUserFromAcc(int _accNumber, int _custNumber)
	{
		return 0;
	}
	ACCOUNTS_API int Functions::changeAccOwner(int _accNumber, int _custNumberFrom, int _custNumberTo)
	{
		return 0;
	}
}