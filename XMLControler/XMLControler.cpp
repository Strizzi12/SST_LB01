#include "stdafx.h"
#include "XMLControler.h"
#define XMLVERSION 1

XMLCONTROLER_API void xmlcontroler_printVersion()
{
	printf(xmlcontroler_buildString);
}

XMLCONTROLER_API int xmlcontroler_createCustomer(char* firstName, char* lastname)
{
	try
	{
		DataRoot *dr = DataRoot::getInstance();

		//read data from file if existing
		if (DataRoot::fileExists("MyXMLFile.xml"))
		{
			//reading Data from XML-file if possible
			std::ifstream ifs("MyXMLFile.xml");
			assert(ifs.good());
			boost::archive::xml_iarchive ia(ifs);
			dr->do_deserialize(ia, XMLVERSION);
		}
		else
		{
			return -1;
		}

		MyCustomer *tmpCus = new MyCustomer(firstName, lastname);

		//-----------------------------------------TESTSHIT-----------------------------------------
		list<MyCustomer>* tmpAccs = tmpCus->get_bankAccounts();
		MyCustomer *test = new MyCustomer(firstName, lastname);
		MyCustomer *test1 = new MyCustomer(firstName, lastname);
		MyCustomer *test2 = new MyCustomer(firstName, lastname);
		tmpAccs->push_back(*test);
		tmpAccs->push_back(*test1);
		tmpAccs->push_back(*test2);
		//-----------------------------------------TESTSHIT-----------------------------------------


		dr->addCustomer(tmpCus);

		//writing data to file
		std::ofstream ofs("MyXMLFile.xml");
		assert(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		dr->do_serialize(oa, XMLVERSION);

		return 0;
	}
	catch (...)
	{
		cout << "Unable to create customer!" << endl;
		return -1;
	}
}




