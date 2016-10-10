// LOGGING.h - Contains declaration of Function class
#pragma once

#ifdef ACCOUNTS_EXPORTS
#define ACCOUNTS_API __declspec(dllexport) 
#else
#define ACCOUNTS_API __declspec(dllimport) 
#endif


	const char *buildString = "Accounts 1.0 " __DATE__ ", " __TIME__ "\n";

	struct Account
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

	extern "C" ACCOUNTS_API void printVersion();
	extern "C" ACCOUNTS_API int createAcc(int _custNumber, int _accType, char* _accName);
	extern "C" ACCOUNTS_API int deleteAcc(int _accNumber);
	extern "C" ACCOUNTS_API int editAccName(int _accNumber, char* _newName);
	extern "C" ACCOUNTS_API int addUserToAcc(int _accNumber, int _custNumber);
	extern "C" ACCOUNTS_API int removeUserFromAcc(int _accNumber, int _custNumber);
	extern "C" ACCOUNTS_API int changeAccOwner(int _accNumber, int _custNumberFrom, int _custNumberTo);