#pragma once

#ifdef BANKCONTROL_EXPORTS
#define BANKCONTROL_API __declspec(dllexport) 
#else
#define BANKCONTROL_API __declspec(dllimport) 
#endif

const char *bankControl_buildString = "BankControl 1.0 " __DATE__ ", " __TIME__ "\n";
bool checkIfStringContainsCharsOnly(const char *str);
bool checkIfStringContainsNumbersOnly(const char *str);
bool inputCheckChars(const char *str);
bool inputCheckNumbers(const char *str);

extern "C" BANKCONTROL_API int bankControl_createAcc(int _accType, char* _accName, float _value);
extern "C" BANKCONTROL_API int bankControl_deleteAcc(int _accNumber);
extern "C" BANKCONTROL_API int bankControl_renameAcc(int _accNumber, char* _newName);
extern "C" BANKCONTROL_API int bankControl_addUserToAcc(int _accNumber, int _custNumber);
extern "C" BANKCONTROL_API int bankControl_removeUserFromAcc(int _accNumber, int _custNumber);
extern "C" BANKCONTROL_API int bankControl_changeAccOwner(int _accNumber, int _custNumberFrom, int _custNumberTo);

extern "C" BANKCONTROL_API int bankControl_createCustomer(char* _firstName, char* _lastName, char* _birthDate, char* _plzLocation, char* _street, char* _houseNr);
extern "C" BANKCONTROL_API int bankControl_deleteCustomer(int _custId);
extern "C" BANKCONTROL_API int bankControl_modifyCustomer(int _custId, char* _firstName, char* _lastName, char* _birthDate, char* _plzLocation, char* _street, char* _houseNr);

extern "C" BANKCONTROL_API int bankControl_transferMoney(int _fromAccID, int _toAccID, float _value);
extern "C" BANKCONTROL_API int bankControl_depositMoney(int _accID, float _value);
extern "C" BANKCONTROL_API int bankControl_withdrawMoney(int _accID, float _value);
extern "C" BANKCONTROL_API int bankControl_getBankStatement(int _accID);
extern "C" BANKCONTROL_API int bankControl_getBalance(int _custID);