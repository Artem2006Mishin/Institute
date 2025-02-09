#include <iostream>
#include "function.h"
using namespace std;

/*
	Мишин Артём 24ВП1 | ВАРИАНТ 14
	Реализовать стек стеков:
	1. Проверка на заполненность вложенных стеков
	2. Добавление элементов во вложенные стеки
	3. Удаление элементов из вложенных стеки
	4. Вывод элементов
*/

int main()
{
	setlocale(LC_ALL, "RU");

	Stack* stack = new Stack();

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
