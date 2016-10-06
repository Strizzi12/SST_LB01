// MyExecRefsDll.cpp 
// compile with: /EHsc /link MathFuncsDll.lib 


#include "stdafx.h"
#include <iostream>

#include "MathLibrary.h"


using namespace std;

int main()
{
	double a = 7.4;
	int b = 99;

	auto d = MathLibrary::Functions::Add(double(a), double(b));
	cout << d << endl;


	return 0;
}