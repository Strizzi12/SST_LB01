// LOGGING.h - Contains declaration of Function class
#pragma once

#ifdef CUSTOMER_EXPORTS
#define CUSTOMER_API __declspec(dllexport) 
#else
#define CUSTOMER_API __declspec(dllimport) 
#endif

struct Person {
	int accnumber;
	char name[60];
	char vorname[60];
	char adr[60];
};
typedef struct Person Person;

namespace Customer
{
	const char *buildString = "Customer 1.0 " __DATE__ ", " __TIME__ "\n";
	// This class is exported from the LOGGING.dll
	class Functions
	{

	public:

		// Returns a + b
		static CUSTOMER_API void printVersion();
		static CUSTOMER_API Person createCustomer(char vn[], char nn[], char adr[]);
		static CUSTOMER_API int changeCustomer(int id, char vn[], char nn[], char adr[]);
		static CUSTOMER_API int deleteCustomer(int id);
		static CUSTOMER_API Person getCustomerByName(char vn[], char nn[]);
		static CUSTOMER_API Person getCustomerbyId(int id);
	};


}