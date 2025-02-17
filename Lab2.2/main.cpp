include <iostream>
#include <initializer_list>
#include "function.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "RU");

	Stack a(3, 3);
	Stack b(2, 2);

	a.push(1, 100);
	a.push(1, 200);
	a.push(1, 300);
	
	--b;
	

	return 0;
}
