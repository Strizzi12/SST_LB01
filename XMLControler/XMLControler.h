// XMLControler.h - Contains declaration of Function class
#pragma

#ifdef XMLCONTROLER_EXPORTS
#define XMLCONTROLER_API __declspec(dllexport) 
#else
#define XMLCONTROLER_API __declspec(dllimport) 
#endif

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
extern "C" XMLCONTROLER_API int xmlcontroler_createCustomer(char* firstName, char* lastname);

using namespace std;

#pragma region CUSTOMER
class MyCustomer
{
public:
	MyCustomer();
	~MyCustomer();

	MyCustomer(char* tmpFirstName, char* tmpLastName);
	template<class Archive>
	void do_serialize(Archive & ar, const unsigned int version);

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

	list<MyCustomer>* get_bankAccounts()
	{
		return &bankAccounts;
	}

	//list<int> get_bankAccounts()
	//{
	//	return bankAccounts;
	//}
#pragma endregion GETTER

private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(cusID);
		ar & BOOST_SERIALIZATION_NVP(cusUUID);
		ar & BOOST_SERIALIZATION_NVP(firstname);
		ar & BOOST_SERIALIZATION_NVP(lastname);
		ar & BOOST_SERIALIZATION_NVP(bankAccounts);
	}

	int cusID;
	string firstname;
	string lastname;
	string cusUUID;
	list<MyCustomer> bankAccounts;
};

MyCustomer::MyCustomer(char* tmpFirstName, char* tmpLastName)
{
	//generate uuid; notice fancy ()() 
	boost::uuids::uuid uuid = boost::uuids::random_generator()();

	cusID = 1;
	cusUUID = boost::uuids::to_string(uuid);
	firstname = tmpFirstName;
	lastname = tmpLastName;
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
#pragma endregion CUSTOMER

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

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(bankCustomers);
	}

	template<class Archive>
	void deserialize(Archive & ar, const unsigned int version)
	{
		ar & ar & BOOST_SERIALIZATION_NVP(bankCustomers);
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

	template<class Archive>
	void do_serialize(Archive & ar, const unsigned int version);

	template<class Archive>
	void do_deserialize(Archive & ar, const unsigned int version);

	void addCustomer(MyCustomer *tmpCus)
	{
		bankCustomers.push_back(*tmpCus);
	}

	list<MyCustomer> get_bankCustomer()
	{
		return bankCustomers;
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
#pragma endregion DATAROOT

class MyClass
{
public:
	MyClass();
	~MyClass();
	string testpro = "test";
private:

};

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}





