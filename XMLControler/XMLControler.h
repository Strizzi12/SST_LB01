// XMLControler.h - Contains declaration of Function class
#pragma

#ifdef XMLCONTROLER_EXPORTS
#define XMLCONTROLER_API __declspec(dllexport) 
#else
#define XMLCONTROLER_API __declspec(dllimport) 
#endif

#define CUSCNTMAX 20000
#define ACCCNTMAX 20000

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/list.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <list>
#include <fstream>
#include <iostream>

const char *xmlcontroler_buildString = "XMLControler 1.0 " __DATE__ ", " __TIME__ "\n";
const int MAXACCNR = 10;

extern "C" XMLCONTROLER_API void xmlcontroler_printVersion();
extern "C" XMLCONTROLER_API int xmlcontroler_createCustomer(char* firstName, char* lastname, char* tmpplzOrt, char* tmpstrasse, int tmphausNr);
extern "C" XMLCONTROLER_API bool xmlcontroler_deleteCustomerByID(int ID);
extern "C" XMLCONTROLER_API bool xmlcontroler_deleteCustomerByUUID(char* cusUUID);
extern "C" XMLCONTROLER_API int xmlcontroler_updateCustomer(int cusID, char* firstName, char* lastname, char* tmpplzOrt, char* tmpstrasse, int tmphausNr);
extern "C" XMLCONTROLER_API int xmlcontroler_renameCustomer(int cusID, char* firstName, char* lastname);
extern "C" XMLCONTROLER_API int xmlcontroler_createAccount(int tmpType, float tmpValue);
extern "C" XMLCONTROLER_API int xmlcontroler_closeAccount(int tmpAccID);
extern "C" XMLCONTROLER_API int xmlcontroler_manageAccount(int tmpType);
extern "C" XMLCONTROLER_API bool xmlcontroler_attachAccount(int tmpAccID, int tmpCusID);
extern "C" XMLCONTROLER_API bool xmlcontroler_dettachAccount(int tmpAccID, int tmpCusID);

using namespace std;

#pragma region ACCOUNT
class BankAccount
{
public:
	BankAccount(int tmpID, int tmpType, float tmpValue);
	BankAccount();
	~BankAccount();

#pragma region GETTER
	int get_accID()
	{
		return accID;
	}

#pragma endregion

#pragma region SETTER
	void set_accID(int tmpBankID)
	{
		accID = tmpBankID;
	}

	void set_type(int tmpType)
	{
		type = tmpType;
	}

	void add_ownerID(int tmpOwnerID)
	{
		ownerIDs.push_back(tmpOwnerID);
	}

	void remove_ownerID(int tmpOwnerID)
	{
		ownerIDs.remove(tmpOwnerID);
	}

#pragma endregion

private:

	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(accID);
		ar & BOOST_SERIALIZATION_NVP(value);
		ar & BOOST_SERIALIZATION_NVP(ownerIDs);
		ar & BOOST_SERIALIZATION_NVP(transaction);
	}

	int accID;
	// 0 = Spar; 1 = Kredit
	int type;
	float value;
	list<int> ownerIDs;
	list<string> transaction;
};

BankAccount::BankAccount(int tmpID, int tmpType, float tmpValue)
{
	accID = tmpID;
	value = tmpValue;
	type = tmpType;
}

BankAccount::BankAccount()
{
}

BankAccount::~BankAccount()
{
}
#pragma endregion 

#pragma region CUSTOMER
class MyCustomer
{
public:
	MyCustomer();
	~MyCustomer();

	MyCustomer(int tmpCusID, char* tmpFirstName, char* tmpLastName, char* tmpplzOrt, char* tmpstrasse, int tmphausNr);
	template<class Archive>
	void do_serialize(Archive & ar, const unsigned int version);

	bool IndexGreaterThanTen(const MyCustomer& o, int delID)
	{
		return o.cusID == delID;
	}

#pragma region GETTER
	int get_cusID()
	{
		return cusID;
	}

	string get_firstname()
	{
		return firstname;
	}

	string get_lastname()
	{
		return lastname;
	}

	list<BankAccount>* get_bankAccounts()
	{
		return &bankAccounts;
	}

	void addBankAccount(BankAccount tmpAcc)
	{
		bankAccounts.push_back(tmpAcc);
	}

	void removeBankAccount(BankAccount it1)
	{
		list<BankAccount>::iterator it;
		list<BankAccount>::iterator it2;
		bool dataFound = false;

		for (it = bankAccounts.begin(); it != bankAccounts.end(); it++)
		{
			if ((*it).get_accID() == it1.get_accID())
			{
				//saving iterator/index
				it2 = it;
				dataFound = true;
			}
		}

		if (dataFound)
		{
			//erase object after it was found and iterator is over
			bankAccounts.erase(it2);
		}
	}

	string get_plzOrt()
	{
		return plzOrt;
	}
	
	string get_Straﬂe()
	{
		return strasse;
	}

	int get_hausNr()
	{
		return hausNr;
	}

	string get_cusUUID()
	{
		return cusUUID;
	}
#pragma endregion

#pragma region SETTER
	void set_cusID(int tmpCusID)
	{
		cusID = tmpCusID;
	}

	void set_firstname(char* tmpFirstname)
	{
		firstname = tmpFirstname;
	}

	void set_lastname(char* tmpLastname)
	{
		lastname = tmpLastname;
	}

	void set_bankAccounts(list<BankAccount>* tmpBankAccounts)
	{
		bankAccounts = *tmpBankAccounts;
	}

	void set_plzOrt(char* tmpPlzOrt)
	{
		plzOrt = tmpPlzOrt;
	}

	void set_Straﬂe(char* tmpStrasse)
	{
		strasse = tmpStrasse;
	}

	void set_hausNr(int tmpHausNr)
	{
		hausNr = tmpHausNr;
	}

	void set_cusUUID(char* tmpCusUUID)
	{
		cusUUID = tmpCusUUID;
	}
#pragma endregion

private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(cusID);
		ar & BOOST_SERIALIZATION_NVP(cusUUID);
		ar & BOOST_SERIALIZATION_NVP(firstname);
		ar & BOOST_SERIALIZATION_NVP(lastname);
		ar & BOOST_SERIALIZATION_NVP(plzOrt);
		ar & BOOST_SERIALIZATION_NVP(strasse);
		ar & BOOST_SERIALIZATION_NVP(hausNr);
		ar & BOOST_SERIALIZATION_NVP(bankAccounts);
	}

	int cusID;
	string firstname;
	string lastname;
	string cusUUID;
	string plzOrt;
	string strasse;
	int hausNr;
	list<BankAccount> bankAccounts;
};

MyCustomer::MyCustomer(int tmpCusID, char* tmpFirstName, char* tmpLastName, char* tmpplzOrt, char* tmpstrasse, int tmphausNr)
{
	//generate uuid; notice fancy ()() 
	boost::uuids::uuid uuid = boost::uuids::random_generator()();

	cusID = tmpCusID;
	//property should be used for real implementation of ID of object - too long for manual usage in dev environment
	cusUUID = boost::uuids::to_string(uuid);
	firstname = tmpFirstName;
	lastname = tmpLastName;
	plzOrt = tmpplzOrt;
	strasse = tmpstrasse;
	hausNr = tmphausNr;
}

MyCustomer::MyCustomer()
{
}

MyCustomer::~MyCustomer()
{
}

template<class Archive>
void MyCustomer::do_serialize(Archive & ar, const unsigned int version)
{
	serialize(ar, version);
}
#pragma endregion 

#pragma region DATAROOT
class DataRoot
{
private:
	static bool instanceFlag;
	static DataRoot *singDataRoot;
	DataRoot()
	{
		//private constructor
	}

	list<MyCustomer> bankCustomers;
	list<BankAccount> bankAccounts;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(bankCustomers);
		ar & BOOST_SERIALIZATION_NVP(bankAccounts);
	}

	template<class Archive>
	void deserialize(Archive & ar, const unsigned int version)
	{
		ar & ar & BOOST_SERIALIZATION_NVP(bankCustomers);
		ar & ar & BOOST_SERIALIZATION_NVP(bankAccounts);
	}

public:
	static DataRoot* getInstance();
	~DataRoot()
	{
		instanceFlag = false;
	}

	static bool fileExists(const string& name) {
		ifstream f(name.c_str());
		return f.good();
	}

	//generates not existing customer ID returns -1 if error (sets Max count of customers to 20k)
	static int getFreeCusID()
	{
		DataRoot *dr = DataRoot::getInstance();
		list<MyCustomer>* tmpCusList = dr->get_bankCustomer();
		list<MyCustomer>::iterator it;
		bool check = false;
		int i = 0;

		while (!check)
		{
			check = true;
			for (it = tmpCusList->begin(); it != tmpCusList->end(); it++)
			{
				if ((*it).get_cusID() == i)
				{
					check = false;
				}
			}

			if (check)
				return i;


			if (i >= CUSCNTMAX)
			{
				cout << "Data storage full! Please delete a customer before creating a new one." << endl;
				return -1;
			}
			i++;
		}
		return -1;
	}

	//generates not existing customer ID returns -1 if error (sets Max count of customers to 20k)
	static int getFreeAccID()
	{
		DataRoot *dr = DataRoot::getInstance();
		list<BankAccount>* tmpAccList = dr->get_bankAccount();
		list<BankAccount>::iterator it;
		bool check = false;
		int i = 0;

		while (!check)
		{
			check = true;
			for (it = tmpAccList->begin(); it != tmpAccList->end(); it++)
			{
				if ((*it).get_accID() == i)
				{
					check = false;
				}
			}

			if (check)
			{
				return i;
			}

			if (i >= ACCCNTMAX)
			{
				cout << "Data storage full! Please delete an account before creating a new one." << endl;
				return -1;
			}
			i++;
		}
		return -1;
	}

	template<class Archive>
	void do_serialize(Archive & ar, const unsigned int version);

	template<class Archive>
	void do_deserialize(Archive & ar, const unsigned int version);

	void addBankAcc(BankAccount *tmpAcc)
	{
		bankAccounts.push_back(*tmpAcc);
	}

	void addCustomer(MyCustomer *tmpCus)
	{
		bankCustomers.push_back(*tmpCus);
	}

	list<MyCustomer>* get_bankCustomer()
	{
		return &bankCustomers;
	}

	list<BankAccount>* get_bankAccount()
	{
		return &bankAccounts;
	}
};

template<class Archive>
void DataRoot::do_serialize(Archive & ar, const unsigned int version)
{
	//saving data
	serialize(ar, version);
}

template<class Archive>
void DataRoot::do_deserialize(Archive & ar, const unsigned int version)
{
	//saving data
	serialize(ar, version);
}

bool DataRoot::instanceFlag = false;
DataRoot* DataRoot::singDataRoot = NULL;
DataRoot* DataRoot::getInstance()
{
	if (!instanceFlag)
	{
		singDataRoot = new DataRoot();
		instanceFlag = true;
		
		return singDataRoot;
	}
	else
	{
		return singDataRoot;
	}
}
#pragma endregion 






