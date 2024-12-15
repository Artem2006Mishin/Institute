#include <iostream>
#include "function.h"
using namespace std;

/*
Мишин Артем 24ВП1
*/

int main()
{
	setlocale(LC_ALL, "RU");

	Stack* stack = new Stack(3, 3);

	if (empty(stack, 1)) {
		cout << "Стек 1 пустой";
	}
	else {
		cout << "Стек 1 не пустой";
	}
	cout << endl;

	push(stack, 1, 100);
	push(stack, 1, 200);
	push(stack, 1, 300);
	if (full(stack, 1)) {
		cout << "Стек 1 заполнен";
	}
	else {
		cout << "В стеке 1 есть место";
	}
	cout << endl;

	push(stack, 2, 111);
	push(stack, 2, 222);
	int a = pop(stack, 2);
	cout << "a: " << a << endl;
	push(stack, 2, 333);

	cout << "Стек 1: "; print(stack, 1);
	cout << "Стек 2: "; print(stack, 2);
}
