// LOGGING.h - Contains declaration of Function class
#pragma once

#ifdef ACCOUNTS_EXPORTS
#define ACCOUNTS_API __declspec(dllexport) 
#else
#define ACCOUNTS_API __declspec(dllimport) 
#endif

namespace Accounts
{
	const char *buildString = "Accounts 1.0 " __DATE__ ", " __TIME__ "\n";

	struct Account
	{
		char accName[100];
		int accNumber;
		int accType;
		int ownerCustNumber;
		int otherUsers[1];
		int *userNumbers;
		userNumbers = otherUsers;
	};
	//typedef struct Account Acc;

	class Functions
	{
	public:
		static ACCOUNTS_API void printVersion();
		static ACCOUNTS_API int createAcc(int _custNumber, int _accType, char* _accName);
		static ACCOUNTS_API int deleteAcc(int _accNumber);
		static ACCOUNTS_API int editAccName(int _accNumber, char* _newName);
		static ACCOUNTS_API int addUserToAcc(int _accNumber, int _custNumber);
		static ACCOUNTS_API int removeUserFromAcc(int _accNumber, int _custNumber);
		static ACCOUNTS_API int changeAccOwner(int _accNumber, int _custNumberFrom, int _custNumberTo);
	};
}