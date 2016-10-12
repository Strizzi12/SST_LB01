// XMLControler.h - Contains declaration of Function class
#pragma once

#ifdef XMLCONTROLER_EXPORTS
#define XMLCONTROLER_API __declspec(dllexport) 
#else
#define XMLCONTROLER_API __declspec(dllimport) 
#endif

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

const char *xmlcontroler_buildString = "XMLControler 1.0 " __DATE__ ", " __TIME__ "\n";

extern "C" XMLCONTROLER_API void xmlcontroler_printVersion();
extern "C" XMLCONTROLER_API void xmlcontroler_createCustomer(char* firstName, char* lastname);

class MyCustomer
{
public:
	MyCustomer();
	~MyCustomer();

	MyCustomer(char* tmpFirstName, char* tmpLastName);
	template<class Archive>
	void do_serialize(Archive & ar, const unsigned int version);
	
	int get_firstname()
	{
		return firstname;
	}

	int get_lastname()
	{
		return lastname;
	}

private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(firstname);
		ar & BOOST_SERIALIZATION_NVP(lastname);
	}

	int firstname;
	int lastname;
};

template<class Archive>
void MyCustomer::do_serialize(Archive & ar, const unsigned int version)
{
	serialize(ar, version);
}

MyCustomer::MyCustomer(char* tmpFirstName, char* tmpLastName)
{
	firstname = 13;
	lastname = 14;
}

MyCustomer::MyCustomer()
{
}

MyCustomer::~MyCustomer()
{
}
