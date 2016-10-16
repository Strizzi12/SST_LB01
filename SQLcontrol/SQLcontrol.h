#pragma once
#include "sqlite3.h"
#include <list>
#include <string>

#ifdef SQLCONTROL_EXPORTS
#define SQLCONTROL_API __declspec(dllexport) 
#else
#define SQLCONTROL_API __declspec(dllimport) 
#endif

using namespace std;

struct ResultSet
{
	int rows;
	char **columns;
	char **data;
	int errorCode;
};
typedef ResultSet Resultset;

const char *buildString = "SQLontrol 1.0 " __DATE__ ", " __TIME__ "\n";

static int callback(void *data, int argc, char **argv, char **azColName);

class Result
{
	typedef list<string> myList;
	public:
		int rows;
		int errorCode;
		Result::Result()
		{

		}

		Result::~Result()
		{

		}

		void addColumns(string toAdd);

		void addData(string toAdd);

	private:
		myList dataList;
		myList nameOfColumnsList;
};


extern "C" SQLCONTROL_API void SQLcontrol_printVersion();
extern "C" SQLCONTROL_API int sql_createDatabase(char *dbName);
extern "C" SQLCONTROL_API Result sql_execQuery(char *dbName, char *sqlStatement);