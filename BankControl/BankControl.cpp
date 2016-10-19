// BankControl.cpp : Definiert die exportierten Funktionen für die DLL-Anwendung.

#include "stdafx.h"
#include "BankControl.h"
#include <string>
#include "XMLControler.h"
#include "SQLControl.h"
#include "Logging.h"

using namespace std;
#pragma warning(disable:4996)

BANKCONTROL_API int bankControl_createAcc(int _accType, char *_accName, float _value)
{
	if (inputCheckNumbers(to_string(_accType).c_str()) && inputCheckChars(_accName))
	{
		string sql = "INSERT INTO ACCOUNT(NAME,TYPE,VALUE) " \
			"VALUES ('" + string(_accName) + "'," 
			+ to_string(_accType) + "," 
			+ to_string(_value) + ");";

		sql_execQuery("Bank", sql.c_str());
		int accNumber = xmlcontroler_createAccount(_accType, _value);
		printf("Your account number is: %i", accNumber);
		return 0;
	}
	else
	{
		logging_logError("Illegal character in passing parameters.\n", __FILE__);
		return -1;
	}
}

BANKCONTROL_API int bankControl_deleteAcc(int _accNumber)
{
	if (inputCheckNumbers(to_string(_accNumber).c_str()))
	{
		string sql = "DELETE FROM ACCOUNT " \
			"WHERE ACCID = " + to_string(_accNumber) + ";";

		sql_execQuery("Bank", sql.c_str());
		xmlcontroler_deleteCustomerByID(_accNumber);
		return 0;
	}
	else
	{
		logging_logError("Illegal character in passing parameters.\n", __FILE__);
		return -1;
	}
}

BANKCONTROL_API int bankControl_renameAcc(int _accNumber, char * _newName)
{
	return 0;
}

BANKCONTROL_API int bankControl_addUserToAcc(int _accNumber, int _custNumber)
{
	return 0;
}

BANKCONTROL_API int bankControl_removeUserFromAcc(int _accNumber, int _custNumber)
{
	return 0;
}

BANKCONTROL_API int bankControl_changeAccOwner(int _accNumber, int _custNumberFrom, int _custNumberTo)
{
	return 0;
}

BANKCONTROL_API int bankControl_createCustomer(char * firstName, char * lastName, char * birthDate, char * plzLocation, char * street, char * houseNr)
{
	return 0;
}

BANKCONTROL_API int bankControl_deleteCustomer(int custId)
{
	return 0;
}

BANKCONTROL_API int bankControl_modifyCustomer(int custId, char * firstName, char * lastName, char * birthDate, char * plzLocation, char * street, char * houseNr)
{
	return 0;
}

BANKCONTROL_API int bankControl_transferMoney(int fromAccID, int toAccID, float value)
{
	return 0;
}

BANKCONTROL_API int bankControl_depositMoney(int accID, float value)
{
	return 0;
}

BANKCONTROL_API int bankControl_withdrawMoney(int accID, float value)
{
	return 0;
}

BANKCONTROL_API int bankControl_getBankStatement(int accID)
{
	return 0;
}

BANKCONTROL_API int bankControl_getBalance(int custID)
{
	return 0;
}

// Test if the given string has anything not in A-Za-z-.
bool checkIfStringContainsCharsOnly(const char *str)
{
	return str[strspn(str, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-.")] != 0;
}

// Test if the given string has anything not in 0-9. Dot is for floating point variables
bool checkIfStringContainsNumbersOnly(const char *str)
{
	return str[strspn(str, "0123456789.")] != 0;
}

//Input check for the chars
bool inputCheckChars(const char *str)
{
	if (str != NULL && strlen(str) >= 0 && checkIfStringContainsCharsOnly(str))
		return true;
	else
		return false;
}

//Input check for numbers
bool inputCheckNumbers(const char *str)
{
	if (str != NULL && strlen(str) >= 0 && checkIfStringContainsNumbersOnly(str))
		return false;
	else
		return true;
}