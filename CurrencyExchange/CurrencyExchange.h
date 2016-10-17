#pragma once

#ifdef CURRENCYEXCHANGE_EXPORTS
#define CURRENCYEXCHANGE_API __declspec(dllexport) 
#else
#define CURRENCYEXCHANGE_API __declspec(dllimport) 
#endif

using namespace std;

static double EurUsd = 1.0994;
static double EurGbp = 0.9039;
static double EurInr = 73.4858;
static double EurJpy = 114.439;

static double UsdEur = 0.90974;
static double UsdGbp = 0.82211;
static double UsdInr = 66.8391;
static double UsdJpy = 104.113;

static double GbpEur = 1.10738;
static double GbpUsd = 1.21701;
static double GbpInr = 81.3616;
static double GbpJpy = 126.708;

static double InrEur = 0.01361;
static double InrUsd = 0.01496;
static double InrGbp = 0.01229;
static double InrJpy = 1.55739;

static double JpyEur = 0.00874;
static double JpyUsd = 0.00961;
static double JpyGbp = 0.00789;
static double JpyInr = 0.64203;

const char *currency_buildString = "CurrencyExchange 1.0 " __DATE__ ", " __TIME__ "\n";

extern "C" CURRENCYEXCHANGE_API void currencyExchange_printVersion();
extern "C" CURRENCYEXCHANGE_API void currencyExchange_info();
extern "C" CURRENCYEXCHANGE_API double currencyExchange_exchange(double amount, int from, int to);

