// MathLibrary.cpp : Defines the exported functions for the DLL application.
// Compile by using: cl /EHsc /DMATHLIBRARY_EXPORTS /LD MathLibrary.cpp

#include "stdafx.h"
#include <iostream>
#include "Customer.h"

namespace Customer
{
	void Functions::printVersion()
	{
		printf(buildString);
	}

	CUSTOMER_API Person Functions::createCustomer(char vn[], char nn[], char adr[])
	{


		Person p;
		strcpy_s(p.vorname, vn);
		strcpy_s(p.name, nn);
		strcpy_s(p.adr, adr);


		// id = ctrl.createCustomer(p) // return unique id von db
		// p.accnumber = id;


		return p;
	}


	CUSTOMER_API int Functions::changeCustomer(int id, char vn[], char nn[], char adr[])
	{
		return 0;
	}

	CUSTOMER_API int Functions::deleteCustomer(int id)
	{

		return 0;
	}

	CUSTOMER_API Person Functions::getCustomerByName(char vn[], char nn[])
	{
		Person p;
		strcpy_s(p.vorname, vn);
		strcpy_s(p.name, nn);

		return p;
	}

	CUSTOMER_API Person Functions::getCustomerbyId(int id)
	{
		Person p;
		p.accnumber = 0;
		return p;
	}

	


}