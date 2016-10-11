// XMLControler.h - Contains declaration of Function class
#pragma once

#ifdef XMLCONTROLER_EXPORTS
#define XMLCONTROLER_API __declspec(dllexport) 
#else
#define XMLCONTROLER_API __declspec(dllimport) 
#endif


const char *xmlcontroler_buildString = "XMLControler 1.0 " __DATE__ ", " __TIME__ "\n";

extern "C" XMLCONTROLER_API void xmlcontroler_printVersion();


