// BankControl.cpp : Definiert die exportierten Funktionen für die DLL-Anwendung.

#include "stdafx.h"
#include "BankControl.h"
#include <string>
#include "XMLControler.h"
#include "SQLControl.h"
#include "Logging.h"
#include <sys/stat.h> 

using namespace std;
#pragma warning(disable:4996)

BANKCONTROL_API int bankControl_createAcc(int _accType, char *_accName, float _value)
{
	try
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
	catch (...)
	{
		printf("General Error!");
		logging_logError("General Error!", __FILE__);
	}
}

BANKCONTROL_API int bankControl_deleteAcc(int _accNumber)
{
	try
	{
		if (inputCheckNumbers(to_string(_accNumber).c_str()))
		{
			string sql = "DELETE FROM ACCOUNT " \
				"WHERE ACCID = " + to_string(_accNumber) + ";";

			sql_execQuery("Bank", sql.c_str());
			xmlcontroler_closeAccount(_accNumber);
			return 0;
		}
		else
		{
			logging_logError("Illegal character in passing parameters.\n", __FILE__);
			return -1;
		}
	}
	catch (...)
	{
		printf("General Error!");
		logging_logError("General Error!", __FILE__);
	}
}

BANKCONTROL_API int bankControl_renameAcc(int _accNumber, char * _newName)
{
	try
	{
		if (inputCheckNumbers(to_string(_accNumber).c_str()) && inputCheckChars(_newName))
		{
			string sql = "UPDATE ACCOUNT " \
				"SET NAME = '" + string(_newName) + "'" \
				"WHERE ACCID = " + to_string(_accNumber) + ";";

			sql_execQuery("Bank", sql.c_str());
			return 0;
		}
		else
		{
			logging_logError("Illegal character in passing parameters.\n", __FILE__);
			return -1;
		}
		return 0;
	}
	catch (...)
	{
		printf("General Error!");
		logging_logError("General Error!", __FILE__);
	}
}

BANKCONTROL_API int bankControl_addUserToAcc(int _accNumber, int _custNumber)
{
	try
	{
		if(inputCheckNumbers(to_string(_accNumber).c_str())
			&& inputCheckNumbers(to_string(_custNumber).c_str()))
		{
			string sql = "INSERT INTO JOINTABLEACCOUNTS(CUSTID,ACCID) " \
				"VALUES ('" + to_string(_accNumber) + "',"
				+ to_string(_custNumber) + ");";

			sql_execQuery("Bank", sql.c_str());
			xmlcontroler_attachAccount(_accNumber, _custNumber);
			return 0;
		}
	else
	{
		logging_logError("Illegal character in passing parameters.\n", __FILE__);
		return -1;
	}
	return 0;
	}
	catch (...)
	{
		printf("General Error!");
		logging_logError("General Error!", __FILE__);
	}
}

BANKCONTROL_API int bankControl_removeUserFromAcc(int _accNumber, int _custNumber)
{
	try
	{
		if (inputCheckNumbers(to_string(_accNumber).c_str())
			&& inputCheckNumbers(to_string(_custNumber).c_str()))
		{
			string sql = "DELETE FROM JOINTABLEACCOUNTS " \
				"WHERE ACCID = " + to_string(_accNumber) + " " \
				"AND CUSTID = " + to_string(_custNumber) + ";";

			sql_execQuery("Bank", sql.c_str());
			xmlcontroler_dettachAccount(_accNumber, _custNumber);
			return 0;
		}
		else
		{
			logging_logError("Illegal character in passing parameters.\n", __FILE__);
			return -1;
		}
	}
	catch (...)
	{
		printf("General Error!");
		logging_logError("General Error!", __FILE__);
	}
}

BANKCONTROL_API int bankControl_createCustomer(char *_firstName, char *_lastName, char *_birthDate, char *_plzLocation, char *_street, char *_houseNr)
{
	try
	{
		if (inputCheckChars(_firstName) && inputCheckChars(_lastName)
			&& inputCheckNumbersAndChars(_birthDate) && inputCheckChars(_plzLocation)
			&& inputCheckChars(_street) && inputCheckNumbersAndChars(_houseNr))
		{
			string sql = "INSERT INTO CUSTOMER(FIRSTNAME,LASTNAME,BIRTHDATE,PLZLOCATION,STREET,HOUSENR) " \
				"VALUES ('" + string(_firstName) + "','" + string(_lastName) + "','"
				+ string(_birthDate) + "','" + string(_plzLocation) + "','"
				+ string(_street) + "','" + string(_houseNr) + "');";

			sql_execQuery("Bank", sql.c_str());

			if (fileExists("MyXMLFile.xml"))
				int customerNumber = xmlcontroler_createCustomer(_firstName, _lastName, _plzLocation, _street, atoi(_houseNr));
			else
			{
				string sqlGetAllCustomer = "SELECT * FROM CUSTOMER;";
				ResultSet result = sql_execQuery("Bank", sqlGetAllCustomer.c_str());
				for (int i = 0; i < result.rows; i++)
					xmlcontroler_createCustomer(result.data[i][1], result.data[i][2], result.data[i][4], result.data[i][5], 12);
			}
			return 0;
		}
		else
		{
			logging_logError("Illegal character in passing parameters.\n", __FILE__);
			return -1;
		}
	}
	catch (...)
	{
		printf("General Error!");
		logging_logError("General Error!", __FILE__);
	}
}

BANKCONTROL_API int bankControl_deleteCustomer(int custId)
{
	try
	{
		if (inputCheckNumbers(to_string(custId).c_str()))
		{
			string sql = "DELETE FROM CUSTOMER " \
				"WHERE CUSTID = " + to_string(custId) + ";";

			sql_execQuery("Bank", sql.c_str());
			xmlcontroler_deleteCustomerByID(custId);
			return 0;
		}
		else
		{
			logging_logError("Illegal character in passing parameters.\n", __FILE__);
			return -1;
		}
	}
	catch (...)
	{
		printf("General Error!");
		logging_logError("General Error!", __FILE__);
	}
}

BANKCONTROL_API int bankControl_modifyCustomer(int custId, char *_firstName, char *_lastName, char *_birthDate, char *_plzLocation, char *_street, char *_houseNr)
{
	try
	{
		if (inputCheckChars(_firstName) && inputCheckChars(_lastName)
			&& inputCheckNumbersAndChars(_birthDate) && inputCheckChars(_plzLocation)
			&& inputCheckChars(_street) && inputCheckNumbersAndChars(_houseNr))
		{
			string sql = "UPDATE CUSTOMER " \
				"SET FIRSTNAME = '" + string(_firstName) + "', " \
				"LASTNAME = '" + string(_lastName) + "', " \
				"BIRTHDATE = '" + string(_birthDate) + "', " \
				"PLZLOCATION = '" + string(_plzLocation) + "', " \
				"STREET = '" + string(_street) + "', " \
				"HOUSENR = '" + string(_houseNr) + "' " \
				"WHERE CUSTID = " + to_string(custId) + ";";

			sql_execQuery("Bank", sql.c_str());
			int customerNumber = xmlcontroler_updateCustomer(custId, _firstName, _lastName, _plzLocation, _street, atoi(_houseNr));
			printf("Your customer number is: %i", customerNumber);
			return 0;
		}
		else
		{
			logging_logError("Illegal character in passing parameters.\n", __FILE__);
			return -1;
		}
	}
	catch (...)
	{
		printf("General Error!");
		logging_logError("General Error!", __FILE__);
	}
}

BANKCONTROL_API int bankControl_transferMoney(int _fromAccID, int _toAccID, float _value)
{
	try
	{
		if (inputCheckNumbers(to_string(_fromAccID).c_str()) &&
			inputCheckNumbers(to_string(_toAccID).c_str()) &&
			inputCheckNumbers(to_string(_value).c_str()))
		{
			string sqlFrom = "SELECT VALUE " \
				"FROM ACCOUNT " \
				"WHERE ACCID = " + to_string(_fromAccID) + ";";

			string sqlTo = "SELECT VALUE " \
				"FROM ACCOUNT " \
				"WHERE ACCID = " + to_string(_toAccID) + ";";

			ResultSet resultFrom = sql_execQuery("Bank", sqlFrom.c_str());
			ResultSet resultTo = sql_execQuery("Bank", sqlTo.c_str());

			if (resultFrom.rows != 0 && resultTo.rows != 0)
			{
				float from = atof(resultFrom.data[0][0]);
				float to = atof(resultTo.data[0][0]);
				if (from < _value)
				{
					logging_logError("Too less money.\n", __FILE__);
				}
				else
				{
					string sqlUpdateFrom = "UPDATE ACCOUNT " \
						"SET VALUE = '" + to_string(from - _value) + "'" \
						"WHERE ACCID = " + to_string(_fromAccID) + ";";
					string sqlUpdateTo = "UPDATE ACCOUNT " \
						"SET VALUE = '" + to_string(to + _value) + "'" \
						"WHERE ACCID = " + to_string(_toAccID) + ";";
					sql_execQuery("Bank", sqlUpdateFrom.c_str());
					sql_execQuery("Bank", sqlUpdateTo.c_str());
					string sqlTransaction = "INSERT INTO TRANSACTIONS(FROMACC,TOACC,VALUE) " \
						"VALUES (" + to_string(_fromAccID) + "," +
						to_string(_toAccID) + "," + to_string(_value) + ");";
					sql_execQuery("Bank", sqlTransaction.c_str());
				}
			}
			else
				logging_logError("Wrong Account Number.\n", __FILE__);

			xmlcontroler_transferMoney(_fromAccID, _toAccID, _value);
			return 0;
		}
		else
		{
			logging_logError("Illegal character in passing parameters.\n", __FILE__);
			return -1;
		}
	}
	catch (...)
	{
		printf("General Error!");
		logging_logError("General Error!", __FILE__);
	}
}

BANKCONTROL_API int bankControl_depositMoney(int _accID, float _value)
{
	try
	{
		if (inputCheckNumbers(to_string(_accID).c_str()) &&
			inputCheckNumbers(to_string(_value).c_str()))
		{
			string sql = "SELECT VALUE " \
				"FROM ACCOUNT " \
				"WHERE ACCID = " + to_string(_accID) + ";";

			ResultSet resultFrom = sql_execQuery("Bank", sql.c_str());
			if (resultFrom.rows != 0)
			{
				float myValue = atof(resultFrom.data[0][0]);
				string sqlUpdate = "UPDATE ACCOUNT " \
					"SET VALUE = '" + to_string(myValue + _value) + "' " \
					"WHERE ACCID = " + to_string(_accID) + ";";

				sql_execQuery("Bank", sqlUpdate.c_str());
				string sqlTransaction = "INSERT INTO TRANSACTIONS(FROMACC,TOACC,VALUE) " \
					"VALUES (" + to_string(_accID) + "," +
					to_string(_accID) + "," + to_string(_value) + ");";
				sql_execQuery("Bank", sqlTransaction.c_str());
			}
			else
				logging_logError("Wrong Account Number.\n", __FILE__);

			xmlcontroler_depositMoney(_accID, _value);
			return 0;
		}
		else
		{
			logging_logError("Illegal character in passing parameters.\n", __FILE__);
			return -1;
		}
	}
	catch (...)
	{
		printf("General Error!");
		logging_logError("General Error!", __FILE__);
	}
}

BANKCONTROL_API int bankControl_withdrawMoney(int _accID, float _value)
{
	try
	{
		if (inputCheckNumbers(to_string(_accID).c_str()) &&
			inputCheckNumbers(to_string(_value).c_str()))
		{
			string sql = "SELECT VALUE " \
				"FROM ACCOUNT " \
				"WHERE ACCID = " + to_string(_accID) + ";";

			ResultSet resultFrom = sql_execQuery("Bank", sql.c_str());

			if (resultFrom.rows != 0)
			{
				float myValue = atof(resultFrom.data[0][0]);
				if (myValue < _value)
				{
					logging_logError("Too less money.\n", __FILE__);
				}
				else
				{
					string sqlUpdate = "UPDATE ACCOUNT " \
						"SET VALUE = '" + to_string(myValue - _value) + "' " \
						"WHERE ACCID = " + to_string(_accID) + ";";

					sql_execQuery("Bank", sqlUpdate.c_str());
					string sqlTransaction = "INSERT INTO TRANSACTIONS(FROMACC,TOACC,VALUE) " \
						"VALUES (" + to_string(_accID) + "," +
						to_string(_accID) + "," + to_string(-_value) + ");";
					sql_execQuery("Bank", sqlTransaction.c_str());
				}
			}
			else
				logging_logError("Wrong Account Number.\n", __FILE__);

			xmlcontroler_withdrawMoney(_accID, _value);
			return 0;
		}
		else
		{
			logging_logError("Illegal character in passing parameters.\n", __FILE__);
			return -1;
		}
	}
	catch (...)
	{
		printf("General Error!");
		logging_logError("General Error!", __FILE__);
	}
}

BANKCONTROL_API int bankControl_getBankStatement(int _accID)
{
	//What?
	//Olle Transaktionen von am Account ausgeben
	try
	{
		if (inputCheckNumbers(to_string(_accID).c_str()))
		{
			string sql = "SELECT * " \
				"FROM TRANSACTIONS " \
				"WHERE FROMACC = " + to_string(_accID) + " " +
				"OR TOACC = " + to_string(_accID) + ";";

			ResultSet result = sql_execQuery("Bank", sql.c_str());
			if (result.rows != 0)
				for (int i = 0; i < result.rows; i++)
					printf("From Acc: %s to Acc: %s with value = %s \n", \
						result.data[i][1], result.data[i][2], result.data[i][3]);
			else
				logging_logError("Wrong Account Number.\n", __FILE__);

			xmlcontroler_getBankStatement(_accID);
			return 0;
		}
		else
		{
			logging_logError("Illegal character in passing parameters.\n", __FILE__);
			return -1;
		}
		return 0;
	}
	catch (...)
	{
		printf("General Error!");
		logging_logError("General Error!", __FILE__);
	}
}

BANKCONTROL_API int bankControl_getBalance(int custID)
{
	//Fettes SQL Statement
	return 0;
}

// Test if the given string has anything not in A-Za-z0-9 .-
bool checkIfStringContainsCharsAndNumbersOnly(const char *str)
{
	return str[strspn(str, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzß-.0123456789 ")] != 0;
}

// Test if the given string has anything not in A-Za-z-.
bool checkIfStringContainsCharsOnly(const char *str)
{
	return str[strspn(str, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzß-. ")] != 0;
}

// Test if the given string has anything not in 0-9. Dot is for floating point variables
bool checkIfStringContainsNumbersOnly(const char *str)
{
	return str[strspn(str, "0123456789-.")] != 0;
}

//Input check for the chars
bool inputCheckChars(const char *str)
{
	if (str != NULL && strlen(str) >= 0 && checkIfStringContainsCharsOnly(str))
		return false;
	else
		return true;
}

//Input check for numbers
bool inputCheckNumbers(const char *str)
{
	if (str != NULL && strlen(str) >= 0 && checkIfStringContainsNumbersOnly(str))
		return false;
	else
		return true;
}

//Input check for numbers and chars
bool inputCheckNumbersAndChars(const char *str)
{
	if (str != NULL && strlen(str) >= 0 && checkIfStringContainsCharsAndNumbersOnly(str))
		return false;
	else
		return true;
}

inline bool fileExists(const char* name) 
{
	struct stat buffer;
	return (stat(name, &buffer) == 0);
}