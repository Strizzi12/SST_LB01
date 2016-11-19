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

		//create transfer entry when acc is created
		std::stringstream stringStream;
		stringStream << tmpValue;
		tmpAcc->get_transactions()->push_back(stringStream.str());

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
			//delete account from customers
			list<MyCustomer>* tmpCusList = dr->get_bankCustomer();
			list<MyCustomer>::iterator cusit;
			list<MyCustomer>::iterator cusit1;
			list<BankAccount>::iterator accit;
			list<BankAccount>::iterator accit1;
			bool accdataFound = false;
			bool check = true;

			while (check)
			{
				check = false;
				//delete the closed account from every customer
				for (cusit = tmpCusList->begin(); cusit != tmpCusList->end(); cusit++)
				{
					for (accit = cusit->get_bankAccounts()->begin(); accit != cusit->get_bankAccounts()->end(); accit++)
					{
						if (accit->get_accID() == tmpAccID)
						{
							cusit1 = cusit;
							accit1 = accit;
							accdataFound = true;
						}
					}
					//delete the closed account from cus
					if (accdataFound)
					{
						cusit1->removeBankAccount(*accit1);
						check = true;
						accdataFound = false;
					}
				}
			}

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

//modifies account type by its ID
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
			if (tmpType != -1 && (tmpType == 0 || tmpType == 1))
			{
				(*it1).set_type(tmpType);
			}
		}
		else
		{
			logging_logError("No account with specified ID found, or wrong Type for ID chosen!", __FILE__);
			cout << "No account with specified ID: " << tmpAccID << " found, or wrong type for ID chosen!" << endl;
			return false;
		}

		//writing data to file
		std::ofstream ofs("MyXMLFile.xml");
		assert(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		dr->do_serialize(oa, XMLVERSION);

		cout << "Account with Nr: " << tmpAccID << " was succesfully edited." << endl;
		logging_logError("Account succesfully edited!", __FILE__);
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
				//dettach cus from acc
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

				//dettach acc from cus
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

XMLCONTROLER_API bool xmlcontroler_transferMoney(int tmpFromAccID, int tmpToAccID, float tmpValue)
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

		//check if FromAccID is valid
		list<BankAccount>* tmpAccList = dr->get_bankAccount();
		list<BankAccount>::iterator FromIt;
		list<BankAccount>::iterator FromIt1;
		bool fromIDFound = false;

		for (FromIt = tmpAccList->begin(); FromIt != tmpAccList->end(); FromIt++)
		{
			if ((*FromIt).get_accID() == tmpFromAccID)
			{
				//saving iterator/index
				FromIt1 = FromIt;
				fromIDFound = true;
			}
		}

		if (!fromIDFound)
		{
			logging_logError("No account found for tmpFromID!", __FILE__);
			cout << "No account found for tmpFromID: " << tmpFromAccID << " !" << endl;
			return false;
		}

		//check if ToAccID is valid
		list<BankAccount>::iterator ToIt;
		list<BankAccount>::iterator ToIt1;
		bool toIDFound = false;

		for (ToIt = tmpAccList->begin(); ToIt != tmpAccList->end(); ToIt++)
		{
			if ((*ToIt).get_accID() == tmpToAccID)
			{
				//saving iterator/index
				ToIt1 = ToIt;
				toIDFound = true;
			}
		}

		if (!toIDFound)
		{
			logging_logError("No account found for tmpToID!", __FILE__);
			cout << "No account found for tmpToID: " << tmpToAccID << " !" << endl;
			return false;
		}

		//check if FromAcc has enough money to transfer
		if ((*FromIt1).get_value() >= tmpValue)
		{
			float FromNewVal = -1;
			float ToNewVal = -1;
			try
			{
				float FromCurrVal = (*FromIt1).get_value();
				float ToCurrVal = (*ToIt1).get_value();
				FromNewVal = FromCurrVal - tmpValue;
				ToNewVal = ToCurrVal + tmpValue;
			}
			catch (...)
			{
				logging_logError("Calculation failed - Transaction canceled without results!", __FILE__);
				cout << "Calculation failed - Transaction canceled without results!" << endl;
				return false;
			}

			if (FromNewVal != -1 && ToNewVal != -1)
			{
				(*FromIt1).set_value(FromNewVal);
				(*ToIt1).set_value(ToNewVal);

				//create transfer entries for accounts (incoming and outgoing ident. via - sign of value)
				std::stringstream stringStream, stringStream1;
				stringStream << (*FromIt1).get_accID() << ";" << (*ToIt1).get_accID() << "; " << (-1 * tmpValue);
				FromIt1->get_transactions()->push_back(stringStream.str());

				stringStream1 << (*FromIt1).get_accID() << ";" << (*ToIt1).get_accID() << "; " << tmpValue;
				ToIt1->get_transactions()->push_back(stringStream1.str());

				//update accounts linked in users (not nice)
				list<MyCustomer>::iterator cusit;
				list<BankAccount>::iterator accit;

				for (cusit = dr->get_bankCustomer()->begin(); cusit != dr->get_bankCustomer()->end(); cusit++)
				{
					for (accit = (*cusit).get_bankAccounts()->begin(); accit != (*cusit).get_bankAccounts()->end(); accit++)
					{
						if ((*accit).get_accID() == tmpFromAccID)
						{
							(*accit).get_transactions()->push_back(stringStream.str());
							accit->set_value(FromNewVal);
						}
						if ((*accit).get_accID() == tmpToAccID)
						{
							(*accit).get_transactions()->push_back(stringStream1.str());
							accit->set_value(ToNewVal);
						}
					}
				}
			}
			//not quite right (with more time a DB like transaction concept should be implemented for this usecase)
			else
			{
				logging_logError("Transaction failed - Transaction canceled without results!", __FILE__);
				cout << "Transaction failed - Transaction canceled without results!" << endl;
				return false;
			}
		}
		else
		{
			logging_logError("Not enough money left to transfer on tmpFromAccID!", __FILE__);
			cout << "Not enough money left for transfer on tmpFromAccID: " << tmpFromAccID << " !" << endl;
			return false;
		}

		//writing data to file
		std::ofstream ofs("MyXMLFile.xml");
		assert(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		dr->do_serialize(oa, XMLVERSION);

		logging_logError("Transaction completed succesfully!", __FILE__);
		cout << "Transaction from AccID: " << tmpFromAccID << " to AccID: " << tmpToAccID << " over: " << tmpValue << " completed successfully!" << endl;
		return true;
	}
	catch (...)
	{
		logging_logError("XML account dettach error!", __FILE__);
		cout << "Unable to dettach account!" << endl;
		return false;
	}
}

XMLCONTROLER_API bool xmlcontroler_depositMoney(int tmpAccID, float tmpValue)
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

		//check if FromAccID is valid
		list<BankAccount>* tmpAccList = dr->get_bankAccount();
		list<BankAccount>::iterator It;
		list<BankAccount>::iterator It1;
		bool fromIDFound = false;

		for (It = tmpAccList->begin(); It != tmpAccList->end(); It++)
		{
			if ((*It).get_accID() == tmpAccID)
			{
				//saving iterator/index
				It1 = It;
				fromIDFound = true;
			}
		}

		if (!fromIDFound)
		{
			logging_logError("No account found for tmpAccID!", __FILE__);
			cout << "No account found for tmpAccID: " << tmpAccID << " !" << endl;
			return false;
		}

		//check for valid amout to deposit
		if (tmpValue > 0)
		{
			try
			{
				//2 step value calculation
				float newValue = It1->get_value() + tmpValue;
				It1->set_value(newValue);

				//create transfer entries for accounts (incoming and outgoing ident. via - sign of value)
				std::stringstream stringStream;
				stringStream << (*It1).get_accID() << "; " << tmpValue;
				It1->get_transactions()->push_back(stringStream.str());

				//update accounts linked in users (not nice)
				list<MyCustomer>::iterator cusit;
				list<BankAccount>::iterator accit;
				for (cusit = dr->get_bankCustomer()->begin(); cusit != dr->get_bankCustomer()->end(); cusit++)
				{
					for (accit = (*cusit).get_bankAccounts()->begin(); accit != (*cusit).get_bankAccounts()->end(); accit++)
					{
						if ((*accit).get_accID() == tmpAccID)
						{
							(*accit).get_transactions()->push_back(stringStream.str());
							accit->set_value(newValue);
						}
					}
				}
			}
			catch (...)
			{
				logging_logError("TOO MUCH MONEY!", __FILE__);
				cout << "TOO MUCH MONEY!" << endl;
				return false;
			}
		}
		else
		{
			logging_logError("Invalid amount of money for deposit!", __FILE__);
			cout << "Invalid amount of money for deposit. Amout has to be greater than 0.0!" << endl;
			return false;
		}

		//writing data to file
		std::ofstream ofs("MyXMLFile.xml");
		assert(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		dr->do_serialize(oa, XMLVERSION);

		logging_logError("Deposit completed succesfully!", __FILE__);
		cout << "Deposit into account with AccID: " << tmpAccID << " over " << tmpValue << " completed successfully!" << endl;
		return true;
	}
	catch (...)
	{
		logging_logError("XML deposit money error!", __FILE__);
		cout << "Unable to deposit money into the account!" << endl;
		return false;
	}
}

XMLCONTROLER_API bool xmlcontroler_withdrawMoney(int tmpAccID, float tmpValue)
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

		//check if AccID is valid
		list<BankAccount>* tmpAccList = dr->get_bankAccount();
		list<BankAccount>::iterator It;
		list<BankAccount>::iterator It1;
		bool IDFound = false;

		for (It = tmpAccList->begin(); It != tmpAccList->end(); It++)
		{
			if ((*It).get_accID() == tmpAccID)
			{
				//saving iterator/index
				It1 = It;
				IDFound = true;
			}
		}

		if (!IDFound)
		{
			logging_logError("No account found for tmpAccID!", __FILE__);
			cout << "No account found for tmpAccID: " << tmpAccID << " !" << endl;
			return false;
		}

		//check for valid amout to withdraw
		if (tmpValue > 0)
		{
			try
			{
				//checking if the customer has enough money
				if (It1->get_value() < tmpValue)
				{
					logging_logError("Too little money.", __FILE__);
					cout << "Too little money - current balance: " << It1->get_value() << " !" << endl;
					return false;
				}

				//2 step value calculation
				float newValue = It1->get_value() - tmpValue;
				It1->set_value(newValue);

				//create transfer entries for accounts (incoming and outgoing ident. via - sign of value)
				std::stringstream stringStream;
				stringStream << (*It1).get_accID() << "; " << (-1 * tmpValue);
				It1->get_transactions()->push_back(stringStream.str());

				//update accounts linked in users (not nice)
				list<MyCustomer>::iterator cusit;
				list<BankAccount>::iterator accit;
				for (cusit = dr->get_bankCustomer()->begin(); cusit != dr->get_bankCustomer()->end(); cusit++)
				{
					for (accit = (*cusit).get_bankAccounts()->begin(); accit != (*cusit).get_bankAccounts()->end(); accit++)
					{
						if ((*accit).get_accID() == tmpAccID)
						{
							(*accit).get_transactions()->push_back(stringStream.str());
							accit->set_value(newValue);
						}
					}
				}
			}
			catch (...)
			{
				logging_logError("TOO MUCH MONEY!", __FILE__);
				cout << "TOO MUCH MONEY!" << endl;
				return false;
			}
		}
		else
		{
			logging_logError("Invalid amount of money for deposit!", __FILE__);
			cout << "Invalid amount of money for deposit. Amout has to be greater than 0.0!" << endl;
			return false;
		}

		//writing data to file
		std::ofstream ofs("MyXMLFile.xml");
		assert(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		dr->do_serialize(oa, XMLVERSION);

		logging_logError("Deposit completed succesfully!", __FILE__);
		cout << "Deposit into account with AccID: " << tmpAccID << " over " << tmpValue << " completed successfully!" << endl;
		return true;
	}
	catch (...)
	{
		logging_logError("XML deposit money error!", __FILE__);
		cout << "Unable to deposit money into the account!" << endl;
		return false;
	}
}

//writes out the listed transfers of a bank account into a file called BankStatements
XMLCONTROLER_API bool xmlcontroler_getBankStatement(int tmpAccID)
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

		//check if AccID is valid
		list<BankAccount>* tmpAccList = dr->get_bankAccount();
		list<BankAccount>::iterator It;
		list<BankAccount>::iterator It1;
		bool IDFound = false;

		for (It = tmpAccList->begin(); It != tmpAccList->end(); It++)
		{
			if ((*It).get_accID() == tmpAccID)
			{
				//saving iterator/index
				It1 = It;
				IDFound = true;
			}
		}

		if (!IDFound)
		{
			logging_logError("No account found for tmpAccID!", __FILE__);
			cout << "No account found for tmpAccID: " << tmpAccID << " !" << endl;
			return false;
		}

		ofstream bankstatementFile;
		bankstatementFile.exceptions(ofstream::failbit | ofstream::badbit);
		string onlyFileName;
		string ID = to_string(It1->get_accID());
		string tmp = "BankStatements";
		string strPath(tmp);

		int x = 1;
		list<string>* tmpTrans = It1->get_transactions();
		std::list<string>::iterator strIt;

		//generating time as string
		//from http://stackoverflow.com/questions/14386923/localtime-vs-localtime-s-and-appropriate-input-arguments
		time_t rawtime;
		struct tm timeinfo;
		char buffer[80];

		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		//formating time string
		strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
		std::string str(buffer);

		try
		{
			bankstatementFile.open("BankStatement AccountNR " + It1->get_accID(), fstream::app);
			bankstatementFile << "Bankstatement for account with ID: " << It1->get_accID() << " printed at: " << str << endl;
			bankstatementFile.close();
		}
		//general ex handling -> not nice but works, use carefully
		catch (...)
		{
			logging_logError("Exception opening/writing bank statement!", __FILE__);
			cout << "Exception opening/writing bank statement!" << endl;
			return false;
		}

		for (strIt = tmpTrans->begin(); strIt != tmpTrans->end(); strIt++)
		{
			//determine case: 1 -> creation statement; 2 deposit/withdraw depending on -/+ value; 3 transfer received/sent depending on +/- value
			//string split by http://stackoverflow.com/questions/236129/split-a-string-in-c
			stringstream myStringStream;
			vector<string> elems;
			myStringStream.str(*strIt);
			string item;
			while (getline(myStringStream, item, ';')) {
				elems.push_back(item);
			}
			int eleCnt = elems.size();

			switch (eleCnt)
			{
			case 1:
				try
				{
					bankstatementFile.open("BankStatement AccountNR " + It1->get_accID(), fstream::app);
					bankstatementFile << x << ". " << "Initial account (accID: " << It1->get_accID() << ") balance of " << elems[0] << endl;
					bankstatementFile.close();
				}
				//general ex handling -> not nice but works, use carefully
				catch (...)
				{
					logging_logError("Exception opening/writing bank statement!", __FILE__);
					cout << "Exception opening/writing bank statement!" << endl;
					return false;
				}
				break;
			case 2:
				if (elems[1].find("-") != string::npos)
				{
					try
					{
						bankstatementFile.open("BankStatement AccountNR " + It1->get_accID(), fstream::app);
						bankstatementFile << x << ". " << "Money withdrawn: " << elems[1] << endl;
						bankstatementFile.close();
					}
					//general ex handling -> not nice but works, use carefully
					catch (...)
					{
						logging_logError("Exception opening/writing bank statement!", __FILE__);
						cout << "Exception opening/writing bank statement!" << endl;
						return false;
					}
				}
				else
				{
					try
					{
						bankstatementFile.open("BankStatement AccountNR " + It1->get_accID(), fstream::app);
						bankstatementFile << x << ". " << "Money deposited: " << elems[1] << endl;
						bankstatementFile.close();
					}
					//general ex handling -> not nice but works, use carefully
					catch (...)
					{
						logging_logError("Exception opening/writing bank statement!", __FILE__);
						cout << "Exception opening/writing bank statement!" << endl;
						return false;
					}
				}
				break;
			case 3:
				if (elems[2].find("-") != string::npos)
				{
					try
					{
						bankstatementFile.open("BankStatement AccountNR " + It1->get_accID(), fstream::app);
						bankstatementFile << x << ". " << "Money transfered to accountID " << elems[1] << " with amount: " << elems[2] << endl;
						bankstatementFile.close();
					}
					//general ex handling -> not nice but works, use carefully
					catch (...)
					{
						logging_logError("Exception opening/writing bank statement!", __FILE__);
						cout << "Exception opening/writing bank statement!" << endl;
						return false;
					}
				}
				else
				{
					try
					{
						bankstatementFile.open("BankStatement AccountNR " + It1->get_accID(), fstream::app);
						bankstatementFile << x << ". " << "Money received from accountID " << elems[0] << " with amount: " << elems[2] << endl;
						bankstatementFile.close();
					}
					//general ex handling -> not nice but works, use carefully
					catch (...)
					{
						logging_logError("Exception opening/writing bank statement!", __FILE__);
						cout << "Exception opening/writing bank statement!" << endl;
						return false;
					}
				}
				break;
			default:
				logging_logError("No account found for tmpAccID!", __FILE__);
				cout << "No account found for tmpAccID: " << tmpAccID << " !" << endl;
				return false;
			}
			//line counter
			x++;
		}

		//stating current account balance as well
		try
		{
			bankstatementFile.open("BankStatement AccountNR " + It1->get_accID(), fstream::app);
			bankstatementFile << x << ". " << "Current account balance: " << It1->get_value() << endl;
			bankstatementFile.close();
		}
		//general ex handling -> not nice but works, use carefully
		catch (...)
		{
			logging_logError("Exception opening/writing bank statement!", __FILE__);
			cout << "Exception opening/writing bank statement!" << endl;
			return false;
		}

		//no write of data necessary - only reading required


		logging_logError("Bank statement was generated succesfully!", __FILE__);
		cout << "Bank statement for account with accID: " << tmpAccID << " was generated successfully!" << endl;
		return true;
	}
	catch (...)
	{
		logging_logError("XML bank statement error!", __FILE__);
		cout << "Unable to generate bank statement for account!" << endl;
		return false;
	}
}

//calculates a sum for all accs of a given customer and printing it to file TotalBalances
XMLCONTROLER_API bool xmlcontroler_getBalance(int tmpCusID)
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

		//check if cusID is valid
		list<MyCustomer>* tmpCusList = dr->get_bankCustomer();
		list<MyCustomer>::iterator It;
		list<MyCustomer>::iterator It1;
		bool IDFound = false;

		for (It = tmpCusList->begin(); It != tmpCusList->end(); It++)
		{
			if ((*It).get_cusID() == tmpCusID)
			{
				//saving iterator/index
				It1 = It;
				IDFound = true;
			}
		}

		if (!IDFound)
		{
			logging_logError("No customer found for tmpCusID!", __FILE__);
			cout << "No customer found for tmpCusID: " << tmpCusID << " !" << endl;
			return false;
		}

		list<BankAccount>* tmpAccLst = It1->get_bankAccounts();
		float fValue = 0;

		ofstream bankstatementFile;
		bankstatementFile.exceptions(ofstream::failbit | ofstream::badbit);
		string onlyFileName;
		string strPath("TotalBalances");

		//generating time as string
		//from http://stackoverflow.com/questions/14386923/localtime-vs-localtime-s-and-appropriate-input-arguments
		time_t rawtime;
		struct tm timeinfo;
		char buffer[80];

		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		//formating time string
		strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
		std::string str(buffer);

		try
		{
			bankstatementFile.open("TotalBalances", fstream::app);
			bankstatementFile << "Total balance calculated for account with ID: " << It1->get_cusID() << " printed at: " << str << endl;
			bankstatementFile.close();
		}
		//general ex handling -> not nice but works, use carefully
		catch (...)
		{
			logging_logError("Exception opening/writing bank statement!", __FILE__);
			cout << "Exception opening/writing bank statement!" << endl;
			return false;
		}

		//calculating the value over all acc of a customer
		for (list<BankAccount>::iterator MyIt = tmpAccLst->begin(); MyIt != tmpAccLst->end(); MyIt++)
		{
			fValue += MyIt->get_value();

			try
			{
				bankstatementFile.open("TotalBalances", fstream::app);
				bankstatementFile << "Balance of account with ID: " << MyIt->get_accID() << ": " << MyIt->get_value() << endl;
				bankstatementFile.close();
			}
			//general ex handling -> not nice but works, use carefully
			catch (...)
			{
				logging_logError("Exception opening/writing bank statement!", __FILE__);
				cout << "Exception opening/writing bank statement!" << endl;
				return false;
			}
		}

		try
		{
			bankstatementFile.open("TotalBalances", fstream::app);
			bankstatementFile << "_________________________________________" << endl;
			bankstatementFile.close();
		}
		//general ex handling -> not nice but works, use carefully
		catch (...)
		{
			logging_logError("Exception opening/writing bank statement!", __FILE__);
			cout << "Exception opening/writing bank statement!" << endl;
			return false;
		}

		try
		{
			bankstatementFile.open("TotalBalances", fstream::app);
			bankstatementFile << "Final balance over all accounts: " << fValue << endl;
			bankstatementFile.close();
		}
		//general ex handling -> not nice but works, use carefully
		catch (...)
		{
			logging_logError("Exception opening/writing bank statement!", __FILE__);
			cout << "Exception opening/writing bank statement!" << endl;
			return false;
		}

		//no write of data necessary - only reading required

		logging_logError("Balance for customer was calculated succesfully!", __FILE__);
		cout << "Balance for customer with cusID: " << tmpCusID << " was calculated successfully!" << endl;
		return true;
	}
	catch (...)
	{
		logging_logError("XML balance calculation error!", __FILE__);
		cout << "Unable to calculate the balance for given customer ID!" << endl;
		return false;
	}
}

//returns accIDs which are attached to a customer in the outparam
XMLCONTROLER_API bool xmlcontroler_getAccsByCusID(int tmpCusID, int* outParam)
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

	//check if cusID is valid
	list<MyCustomer>* tmpCusList = dr->get_bankCustomer();
	list<MyCustomer>::iterator It;
	list<MyCustomer>::iterator It1;
	bool IDFound = false;

	for (It = tmpCusList->begin(); It != tmpCusList->end(); It++)
	{
		if ((*It).get_cusID() == tmpCusID)
		{
			//saving iterator/index
			It1 = It;
			IDFound = true;
		}
	}

	if (!IDFound)
	{
		logging_logError("No customer found for tmpCusID!", __FILE__);
		cout << "No customer found for tmpCusID: " << tmpCusID << " !" << endl;
		return false;
	}

	list<BankAccount>* tmpAccLst = It1->get_bankAccounts();
	int accCnt = tmpAccLst->size();
	int x = 0;
	int* tmp = new int[accCnt];
	for (list<BankAccount>::iterator MyIt = tmpAccLst->begin(); MyIt != tmpAccLst->end(); MyIt++)
	{
		tmp[x] = MyIt->get_accID();
		x++;
	}

	memcpy(outParam, tmp, sizeof(tmp));

	logging_logError("xmlcontroler_getAccsByCusID terminated successfully!", __FILE__);
	cout << "xmlcontroler_getAccsByCusID terminated successfully!" << endl;
	return true;
}

//used for transactions from another bank (subject of SST_LB03)
XMLCONTROLER_API bool xmlcontroler_remoteTransaction(int tmpFromAccID, int tmpToAccID, int tmpFromBIC, int tmpToBic, float tmpValue, char* tmpPurpose)
{
	try
	{
		DataRoot *dr = DataRoot::getInstance();

		//check if the remoteTransaction is from/to the own bank
		bool localOrRemote = false; // true if local ; false if extern
		//if from and to Bic are equal then the transaction is made within the localhost¥s bank
		if (tmpFromBIC == tmpToBic)
		{
			localOrRemote = true;
		}

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

		//check if FromAccID is valid
		list<BankAccount>* tmpAccList = dr->get_bankAccount();
		list<BankAccount>::iterator FromIt;
		list<BankAccount>::iterator FromIt1;
		bool fromIDFound = false;

		for (FromIt = tmpAccList->begin(); FromIt != tmpAccList->end(); FromIt++)
		{
			if ((*FromIt).get_accID() == tmpFromAccID)
			{
				//saving iterator/index
				FromIt1 = FromIt;
				fromIDFound = true;
			}
		}

		if (!fromIDFound)
		{
			logging_logError("No account found for tmpFromID!", __FILE__);
			cout << "No account found for tmpFromID: " << tmpFromAccID << " !" << endl;
			return false;
		}

		//check if ToAccID is valid
		list<BankAccount>::iterator ToIt;
		list<BankAccount>::iterator ToIt1;
		bool toIDFound = false;
		//only has to be done if remoteTransaction is internal
		if (localOrRemote)
		{
			for (ToIt = tmpAccList->begin(); ToIt != tmpAccList->end(); ToIt++)
			{
				if ((*ToIt).get_accID() == tmpToAccID)
				{
					//saving iterator/index
					ToIt1 = ToIt;
					toIDFound = true;
				}
			}

			if (!toIDFound)
			{
				logging_logError("No account found for tmpToID!", __FILE__);
				cout << "No account found for tmpToID: " << tmpToAccID << " !" << endl;
				return false;
			}
		}

		//check if FromAcc has enough money to transfer
		if ((*FromIt1).get_value() >= tmpValue)
		{
			float FromNewVal = -1;
			float ToNewVal = -1;
			try
			{
				float FromCurrVal = (*FromIt1).get_value();
				FromNewVal = FromCurrVal - tmpValue;

				float ToCurrVal = 0;
				if (localOrRemote)
				{
					ToCurrVal = (*ToIt1).get_value();
					ToNewVal = ToCurrVal + tmpValue;
				}
				else
				{
					ToNewVal = 0;
				}
			}
			catch (...)
			{
				logging_logError("Calculation failed - Transaction canceled without results!", __FILE__);
				cout << "Calculation failed - Transaction canceled without results!" << endl;
				return false;
			}

			if (FromNewVal != -1 && ToNewVal != -1)
			{
				(*FromIt1).set_value(FromNewVal);
				if (localOrRemote)
				{
					(*ToIt1).set_value(ToNewVal);
				}

				//create transfer entries for accounts (incoming and outgoing ident. via - sign of value)
				std::stringstream stringStream, stringStream1;
				if (localOrRemote)
				{
					stringStream << tmpFromAccID << ";" << tmpToAccID << " local bank account" << "; " << (-1 * tmpValue);
					FromIt1->get_transactions()->push_back(stringStream.str());
				}
				else
				{
					stringStream << tmpFromAccID << ";" << tmpToAccID << " remote bank account" << "; " << (-1 * tmpValue);
					FromIt1->get_transactions()->push_back(stringStream.str());
				}


				if (localOrRemote)
				{
					stringStream1 << tmpFromAccID << ";" << tmpToAccID << "; " << tmpValue;
					ToIt1->get_transactions()->push_back(stringStream1.str());
				}
				
				//update accounts linked in users (not nice)
				list<MyCustomer>::iterator cusit;
				list<BankAccount>::iterator accit;

				for (cusit = dr->get_bankCustomer()->begin(); cusit != dr->get_bankCustomer()->end(); cusit++)
				{
					for (accit = (*cusit).get_bankAccounts()->begin(); accit != (*cusit).get_bankAccounts()->end(); accit++)
					{
						if ((*accit).get_accID() == tmpFromAccID)
						{
							(*accit).get_transactions()->push_back(stringStream.str());
							accit->set_value(FromNewVal);
						}
						if (localOrRemote)
						{
							if ((*accit).get_accID() == tmpToAccID)
							{
								(*accit).get_transactions()->push_back(stringStream1.str());
								accit->set_value(ToNewVal);
							}
						}
					}
				}
			}
			//not quite right (with more time a DB like transaction concept should be implemented for this usecase)
			else
			{
				logging_logError("Transaction failed - Transaction canceled without results!", __FILE__);
				cout << "Transaction failed - Transaction canceled without results!" << endl;
				return false;
			}
		}
		else
		{
			logging_logError("Not enough money left to transfer on tmpFromAccID!", __FILE__);
			cout << "Not enough money left for transfer on tmpFromAccID: " << tmpFromAccID << " !" << endl;
			return false;
		}

		//writing data to file
		std::ofstream ofs("MyXMLFile.xml");
		assert(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		dr->do_serialize(oa, XMLVERSION);

		logging_logError(tmpPurpose, __FILE__);
		cout << tmpPurpose << endl;
		return true;
	}
	catch (...)
	{
		logging_logError("XML account dettach error!", __FILE__);
		cout << "Unable to dettach account!" << endl;
		return false;
	}
}