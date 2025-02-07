#include <iostream>
#include "function.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "RU");

	Stack* stack = new Stack(3, 3);

	if (stack->empty(1)) {
		cout << "Стек 1 пустой";
	}
	else {
		cout << "Стек 1 не пустой";
	}
	cout << endl;

	stack->push(1, 100);
	stack->push(1, 200);
	stack->push(1, 300);
	if (stack->full(1)) {
		cout << "Стек 1 заполнен";
	}
	else {
		cout << "В стеке 1 есть место";
	}
	cout << endl;

	stack->push(2, 111);
	stack->push(2, 222);
	int a = stack->pop(2);
	cout << "a: " << a << endl;
	stack->push(2, 333);

	cout << "Стек 1: "; stack->print(1);
	cout << "Стек 2: "; stack->print(2);


	return 0;
}
