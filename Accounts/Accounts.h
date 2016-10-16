// LOGGING.h - Contains declaration of Function class
#pragma once

#ifdef ACCOUNTS_EXPORTS
#define ACCOUNTS_API __declspec(dllexport) 
#else
#define ACCOUNTS_API __declspec(dllimport) 
#endif


const char *accounts_buildString = "Accounts 1.0 " __DATE__ ", " __TIME__ "\n";

struct BankAccount
{
	char accName[100];
	int accNumber;
	int accType;
	int ownerCustNumber;
	int otherUsers[1];
	int *userNumbers;
	//userNumbers = otherUsers;
};
//typedef struct Account Acc;

extern "C" ACCOUNTS_API void accounts_printVersion();
extern "C" ACCOUNTS_API int accounts_createAcc(int _custNumber, int _accType, char* _accName);
extern "C" ACCOUNTS_API int accounts_deleteAcc(int _accNumber);
extern "C" ACCOUNTS_API int accounts_(int _accNumber, char* _newName);
extern "C" ACCOUNTS_API int accounts_addUserToAcc(int _accNumber, int _custNumber);
extern "C" ACCOUNTS_API int accounts_removeUserFromAcc(int _accNumber, int _custNumber);
extern "C" ACCOUNTS_API int accounts_changeAccOwner(int _accNumber, int _custNumberFrom, int _custNumberTo);