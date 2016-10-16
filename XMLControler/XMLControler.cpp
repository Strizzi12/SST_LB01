#include "stdafx.h"
#include "XMLControler.h"
#include "Logging.h"
#define XMLVERSION 1

XMLCONTROLER_API void xmlcontroler_printVersion()
{
	printf(xmlcontroler_buildString);
}

XMLCONTROLER_API int xmlcontroler_createCustomer(char* firstName, char* lastname, char* plzOrt, char* strasse, int hausNr)
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
			logging_logError("XML file not found -> load error!", __FILE__);
			cout << "XML-File not found or corrupt -> load error!" << endl;
			//return -1;
		}

		int cusID = DataRoot::getFreeCusID();
		MyCustomer *tmpCus = new MyCustomer(cusID, firstName, lastname, plzOrt, strasse, hausNr);
		dr->addCustomer(tmpCus);

		//writing data to file
		std::ofstream ofs("MyXMLFile.xml");
		assert(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		dr->do_serialize(oa, XMLVERSION);

		cout << "Customer with Nr: " << cusID << " was succesfully created. Note this Nr for later use!" << endl;
		logging_logError("Customer succesfully created!", __FILE__);
		return cusID;
	}
	catch (...)
	{
		logging_logError("XML customer creation error!", __FILE__);
		cout << "Unable to create customer!" << endl;
		return -1;
	}
}

XMLCONTROLER_API bool xmlcontroler_deleteCustomerByID(int ID)
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
			logging_logError("XML file not found -> load error!", __FILE__);
			cout << "XML-File not found or corrupt -> load error!" << endl;
			//return -1;
		}

		list<MyCustomer>* tmpCusList = dr->get_bankCustomer();
		list<MyCustomer>::iterator it;
		list<MyCustomer>::iterator it1;
		bool dataFound = false;

		for (it = tmpCusList->begin(); it != tmpCusList->end(); it++)
		{
			if ((*it).get_cusID() == ID)
			{
				//saving iterator/index
				it1 = it;
				dataFound = true;
			}
		}

		if (dataFound)
		{
			//erase object after it was found and iterator is over
			tmpCusList->erase(it1);
		}
		else
		{
			logging_logError("No customer with specified ID found!", __FILE__);
			cout << "No customer with specified ID: " << ID << " found!" << endl;
			return false;
		}

		//writing data to file
		std::ofstream ofs("MyXMLFile.xml");
		assert(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		dr->do_serialize(oa, XMLVERSION);

		logging_logError("Customer succesfully deleted!", __FILE__);
		cout << "Customer with ID " << ID << " succesfully deleted!" << endl;
		return true;
	}
	catch (...)
	{
		logging_logError("XML customer deletion error!", __FILE__);
		cout << "Unable to delete customer!" << endl;
		return false;
	}
	return true;
}

XMLCONTROLER_API bool xmlcontroler_deleteCustomerByUUID(char* cusUUID)
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
			logging_logError("XML file not found -> load error!", __FILE__);
			cout << "XML-File not found or corrupt -> load error!" << endl;
			//return -1;
		}

		list<MyCustomer>* tmpCusList = dr->get_bankCustomer();
		list<MyCustomer>::iterator it;
		list<MyCustomer>::iterator it1;
		bool dataFound = false;

		for (it = tmpCusList->begin(); it != tmpCusList->end(); it++)
		{
			if ((*it).get_cusUUID() == cusUUID)
			{
				//saving iterator/index
				it1 = it;
				dataFound = true;
			}
		}

		if (dataFound)
		{
			//erase object after it was found and iterator is over
			tmpCusList->erase(it1);
		}
		else
		{
			logging_logError("No customer with specified UUID found!", __FILE__);
			cout << "No customer with specified UUID found!" << endl;
			return false;
		}

		//writing data to file
		std::ofstream ofs("MyXMLFile.xml");
		assert(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		dr->do_serialize(oa, XMLVERSION);

		logging_logError("Customer succesfully deleted!", __FILE__);
		cout << "Customer succesfully deleted!" << endl;
		return true;
	}
	catch (...)
	{
		logging_logError("XML customer deletion error!", __FILE__);
		cout << "Unable to delete customer!" << endl;
		return false;
	}
	return true;
}

//string parameters which should not get updated should be entered as ""; int parameters as -1
XMLCONTROLER_API int xmlcontroler_updateCustomer(int cusID, char* firstName, char* lastname, char* plzOrt, char* strasse, int hausNr)
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
			logging_logError("XML file not found -> load error!", __FILE__);
			cout << "XML-File not found or corrupt -> load error!" << endl;
			//return -1;
		}

		//retrieve customer which should get updated
		list<MyCustomer>* tmpCusList = dr->get_bankCustomer();
		list<MyCustomer>::iterator it;
		bool dataFound = false;

		for (it = tmpCusList->begin(); it != tmpCusList->end(); it++)
		{
			if ((*it).get_cusID() == cusID)
			{
				//setting values if they should be updated (real intputcheck in central data control unit)
				if (!((firstName != NULL) && (firstName[0] == '\0')))
				{
					(*it).set_firstname(firstName);
				}
				if (!((lastname != NULL) && (lastname[0] == '\0')))
				{
					(*it).set_lastname(lastname);
				}
				if (!((plzOrt != NULL) && (plzOrt[0] == '\0')))
				{
					(*it).set_plzOrt(plzOrt);
				}
				if (!((strasse != NULL) && (strasse[0] == '\0')))
				{
					(*it).set_Straﬂe(strasse);
				}
				if (hausNr != -1)
				{
					(*it).set_hausNr(hausNr);
				}
				dataFound = true;
			}
		}

		if (!dataFound)
		{
			logging_logError("No customer with specified ID found!", __FILE__);
			cout << "No customer with specified ID: " << cusID << " found to update!" << endl;
			return -1;
		}

		//writing data to file
		std::ofstream ofs("MyXMLFile.xml");
		assert(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		dr->do_serialize(oa, XMLVERSION);

		cout << "Customer with Nr: " << cusID << " was succesfully updated!" << endl;
		logging_logError("Customer succesfully updated!", __FILE__);
		return cusID;
	}
	catch (...)
	{
		logging_logError("XML customer update error!", __FILE__);
		cout << "Unable to update customer!" << endl;
		return -1;
	}
}

//string parameters left empty will not get updated
XMLCONTROLER_API int xmlcontroler_renameCustomer(int cusID, char* firstName, char* lastname)
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
			logging_logError("XML file not found -> load error!", __FILE__);
			cout << "XML-File not found or corrupt -> load error!" << endl;
			//return -1;
		}

		//retrieve customer which should get updated
		list<MyCustomer>* tmpCusList = dr->get_bankCustomer();
		list<MyCustomer>::iterator it;
		bool dataFound = false;

		for (it = tmpCusList->begin(); it != tmpCusList->end(); it++)
		{
			if ((*it).get_cusID() == cusID)
			{
				//setting values if they should be updated (real intputcheck in central data control unit)
				if (!((firstName != NULL) && (firstName[0] == '\0')))
				{
					(*it).set_firstname(firstName);
				}
				if (!((lastname != NULL) && (lastname[0] == '\0')))
				{
					(*it).set_lastname(lastname);
				}
				dataFound = true;
			}
		}

		if (!dataFound)
		{
			logging_logError("No customer with specified ID found!", __FILE__);
			cout << "No customer with specified ID: " << cusID << " found to rename!" << endl;
			return -1;
		}

		//writing data to file
		std::ofstream ofs("MyXMLFile.xml");
		assert(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		dr->do_serialize(oa, XMLVERSION);

		cout << "Customer with Nr: " << cusID << " was succesfully renamed!" << endl;
		logging_logError("Customer succesfully renamed!", __FILE__);
		return cusID;
	}
	catch (...)
	{
		logging_logError("XML customer update error!", __FILE__);
		cout << "Error! Unable to rename customer!" << endl;
		return -1;
	}
}

XMLCONTROLER_API int xmlcontroler_createAccount(int tmpType, float tmpValue)
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
			logging_logError("XML file not found -> load error!", __FILE__);
			cout << "XML-File not found or corrupt -> load error!" << endl;
			//return -1;
		}

		int accID = DataRoot::getFreeAccID();
		BankAccount *tmpAcc = new BankAccount(accID, tmpType, tmpValue);
		dr->addBankAcc(tmpAcc);

		//writing data to file
		std::ofstream ofs("MyXMLFile.xml");
		assert(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		dr->do_serialize(oa, XMLVERSION);

		cout << "Account with Nr: " << accID << " was succesfully created. Note this Nr for later use!" << endl;
		logging_logError("Account succesfully created!", __FILE__);
		return accID;
	}
	catch (...)
	{
		logging_logError("XML account creation error!", __FILE__);
		cout << "Unable to create account!" << endl;
		return -1;
	}
}

XMLCONTROLER_API int xmlcontroler_closeAccount(int tmpAccID)
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
			logging_logError("XML file not found -> load error!", __FILE__);
			cout << "XML-File not found or corrupt -> load error!" << endl;
			//return -1;
		}

		list<BankAccount>* tmpAccList = dr->get_bankAccount();
		list<BankAccount>::iterator it;
		list<BankAccount>::iterator it1;
		bool dataFound = false;

		for (it = tmpAccList->begin(); it != tmpAccList->end(); it++)
		{
			if ((*it).get_accID() == tmpAccID)
			{
				//saving iterator/index
				it1 = it;
				dataFound = true;
			}
		}

		if (dataFound)
		{
			//erase object after it was found and iterator is over
			tmpAccList->erase(it1);
		}
		else
		{
			logging_logError("No account with specified ID found!", __FILE__);
			cout << "No account with specified ID: " << tmpAccID << " found!" << endl;
			return false;
		}

		//writing data to file
		std::ofstream ofs("MyXMLFile.xml");
		assert(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		dr->do_serialize(oa, XMLVERSION);

		cout << "Account with Nr: " << tmpAccID << " was succesfully closed." << endl;
		logging_logError("Account succesfully closed!", __FILE__);
		return tmpAccID;
	}
	catch (...)
	{
		logging_logError("XML account deletion error!", __FILE__);
		cout << "Unable to delete account!" << endl;
		return -1;
	}
}

//modifies account type by its ID;
XMLCONTROLER_API int xmlcontroler_manageAccount(int tmpAccID, int tmpType)
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
			logging_logError("XML file not found -> load error!", __FILE__);
			cout << "XML-File not found or corrupt -> load error!" << endl;
			//return -1;
		}

		list<BankAccount>* tmpAccList = dr->get_bankAccount();
		list<BankAccount>::iterator it;
		list<BankAccount>::iterator it1;
		bool dataFound = false;

		for (it = tmpAccList->begin(); it != tmpAccList->end(); it++)
		{
			if ((*it).get_accID() == tmpAccID)
			{
				//saving iterator/index
				it1 = it;
				dataFound = true;
			}
		}

		if (dataFound)
		{
			if (tmpType != -1)
			{
				(*it1).set_type(tmpType);
			}
		}
		else
		{
			logging_logError("No account with specified ID found!", __FILE__);
			cout << "No account with specified ID: " << tmpAccID << " found!" << endl;
			return false;
		}

		//writing data to file
		std::ofstream ofs("MyXMLFile.xml");
		assert(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		dr->do_serialize(oa, XMLVERSION);

		cout << "Account with Nr: " << tmpAccID << " was succesfully closed." << endl;
		logging_logError("Account succesfully closed!", __FILE__);
		return tmpAccID;
	}
	catch (...)
	{
		logging_logError("XML account deletion error!", __FILE__);
		cout << "Unable to delete account!" << endl;
		return -1;
	}
}

XMLCONTROLER_API bool xmlcontroler_attachAccount(int tmpAccID, int tmpCusID)
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
			logging_logError("XML file not found -> load error!", __FILE__);
			cout << "XML-File not found or corrupt -> load error!" << endl;
			//return false;
		}

		list<BankAccount>* tmpAccList = dr->get_bankAccount();
		list<BankAccount>::iterator it;
		list<BankAccount>::iterator it1;
		bool dataFound = false;

		for (it = tmpAccList->begin(); it != tmpAccList->end(); it++)
		{
			if ((*it).get_accID() == tmpAccID)
			{
				//saving iterator/index
				it1 = it;
				dataFound = true;
			}
		}
		//accID was valid
		if (dataFound)
		{
			list<MyCustomer>* tmpCusList = dr->get_bankCustomer();
			list<MyCustomer>::iterator cusit;
			list<MyCustomer>::iterator cusit1;
			bool cusdataFound = false;

			for (cusit = tmpCusList->begin(); cusit != tmpCusList->end(); cusit++)
			{
				if ((*cusit).get_cusID() == tmpCusID)
				{
					//saving iterator/index
					cusit1 = cusit;
					cusdataFound = true;
				}
			}
			//accID && cusID valid -> connect them
			if (cusdataFound)
			{
				bool alreadyattached = false;
				for (list<MyCustomer>::iterator Myit = tmpCusList->begin(); Myit != tmpCusList->end(); Myit++)
				{
					if ((*Myit).get_cusID() == tmpCusID)
					{
						for (list<BankAccount>::iterator Myit1 = (*Myit).get_bankAccounts()->begin(); Myit1 != (*Myit).get_bankAccounts()->end(); Myit1++)
						{
							if ((*Myit1).get_accID() == tmpAccID)
							{
								cout << "Error account with ID " << tmpAccID << " already attached!" << endl;
								logging_logError("Error account already attached!", __FILE__);
								return false;
							}
						}
					}
				}



				//assign cus to acc
				(*it1).add_ownerID((*cusit1).get_cusID());

				//not good (update other objects as well) should be done via pointer/reference but no time
				for (cusit = tmpCusList->begin(); cusit != tmpCusList->end(); cusit++)
				{
					for (list<BankAccount>::iterator j = (*cusit).get_bankAccounts()->begin(); j != (*cusit).get_bankAccounts()->end(); j++)
					{
						if ((*j).get_accID() == (*it1).get_accID())
						{
							*j = *it1;
						}
					}
				}

				//assign acc to cus
				(*cusit1).addBankAccount(*it1);
			}
			else
			{
				logging_logError("No customer with specified ID found!", __FILE__);
				cout << "No customer with specified ID: " << tmpCusID << " found!" << endl;
				return false;
			}
		}
		else
		{
			logging_logError("No account with specified ID found!", __FILE__);
			cout << "No account with specified ID: " << tmpAccID << " found!" << endl;
			return false;
		}

		//writing data to file
		std::ofstream ofs("MyXMLFile.xml");
		assert(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		dr->do_serialize(oa, XMLVERSION);

		cout << "Account with Nr: " << tmpAccID << " was succesfully attached to customer with ID: " << tmpCusID << endl;
		logging_logError("Account succesfully attached!", __FILE__);
		return true;
	}
	catch (...)
	{
		logging_logError("XML account attach error!", __FILE__);
		cout << "Unable to attach account!" << endl;
		return false;
	}
}

XMLCONTROLER_API bool xmlcontroler_dettachAccount(int tmpAccID, int tmpCusID)
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
			logging_logError("XML file not found -> load error!", __FILE__);
			cout << "XML-File not found or corrupt -> load error!" << endl;
			//return false;
		}

		list<BankAccount>* tmpAccList = dr->get_bankAccount();
		list<BankAccount>::iterator it;
		list<BankAccount>::iterator it1;
		bool dataFound = false;

		for (it = tmpAccList->begin(); it != tmpAccList->end(); it++)
		{
			if ((*it).get_accID() == tmpAccID)
			{
				//saving iterator/index
				it1 = it;
				dataFound = true;
			}
		}
		//accID was valid
		if (dataFound)
		{
			list<MyCustomer>* tmpCusList = dr->get_bankCustomer();
			list<MyCustomer>::iterator cusit;
			list<MyCustomer>::iterator cusit1;
			bool cusdataFound = false;

			for (cusit = tmpCusList->begin(); cusit != tmpCusList->end(); cusit++)
			{
				if ((*cusit).get_cusID() == tmpCusID)
				{
					//saving iterator/index
					cusit1 = cusit;
					cusdataFound = true;
				}
			}
			//accID && cusID valid -> connect them
			if (cusdataFound)
			{
				//assign cus to acc
				(*it1).remove_ownerID((*cusit1).get_cusID());

				list<BankAccount>::iterator j;
				//not good (update other objects as well) should be done via pointer/reference but no time
				for (cusit = tmpCusList->begin(); cusit != tmpCusList->end(); cusit++)
				{
					for (j = (*cusit).get_bankAccounts()->begin(); j != (*cusit).get_bankAccounts()->end(); j++)
					{
						if ((*j).get_accID() == (*it1).get_accID())
						{
							*j = *it1;
						}
					}
				}

				//assign acc to cus
				(*cusit1).removeBankAccount(*it1);
			}
			else
			{
				logging_logError("No customer with specified ID found!", __FILE__);
				cout << "No customer with specified ID: " << tmpCusID << " found!" << endl;
				return false;
			}
		}
		else
		{
			logging_logError("No account with specified ID found!", __FILE__);
			cout << "No account with specified ID: " << tmpAccID << " found!" << endl;
			return false;
		}

		//writing data to file
		std::ofstream ofs("MyXMLFile.xml");
		assert(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		dr->do_serialize(oa, XMLVERSION);

		cout << "Account with Nr: " << tmpAccID << " was succesfully dettached from customer with ID: " << tmpCusID << endl;
		logging_logError("Account succesfully dettached!", __FILE__);
		return true;
	}
	catch (...)
	{
		logging_logError("XML account dettach error!", __FILE__);
		cout << "Unable to dettach account!" << endl;
		return false;
	}
}