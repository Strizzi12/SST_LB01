#include "stdafx.h"
#include <iostream>
#include "XMLControler.h"
#include <fstream>

using namespace std;




XMLCONTROLER_API void xmlcontroler_printVersion()
{
	
	printf(xmlcontroler_buildString);
}

XMLCONTROLER_API void xmlcontroler_createCustomer(char* firstName, char* lastname)
{
	
	std::ofstream ofs("MyXMLFile.xml");
	MyCustomer tmp = MyCustomer::MyCustomer(firstName, lastname);
	boost::archive::xml_oarchive oa(ofs);
	
	oa << BOOST_SERIALIZATION_NVP(tmp);

	cout << tmp.get_firstname() << " " << tmp.get_lastname() << endl;
}

