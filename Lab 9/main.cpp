#include <iostream>
#include "function.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "RU");
	Stack* mass = new Stack[3];
	
	push(1, &mass[0]);
	push(2, &mass[0]);
	print(&mass[0]);
	pop(&mass[0]);
	print(&mass[0]);

	push(100, &mass[1]);
	push(200, &mass[1]);
	push(300, &mass[1]);
	if (full(&mass[1])) {
		cout << "Массив заполнен" << endl;
	}
	else {
		cout << "В массиве есть место" << endl;
	}

	if (empty(&mass[2])) {
		cout << "Массив пустой" << endl;
	}
	else {
		cout << "Массив не пустой" << endl;
	}
	push(123, &mass[2]);
	push(456, &mass[2]);
	top(&mass[2]);


}
