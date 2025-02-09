#include <iostream>
#include "function.h"
using namespace std;

Stack::Stack()
{
	this->n = 3;
	this->m = 3;

	arr = new int[n * m];
	top = new int[m];
	floor = new int[m];

	for (int i = 0; i < m; i++)
	{
		top[i] = -1;
		floor[i] = (i + 1) * n - 1;
	}
}

Stack::Stack(int n, int m) : Stack()
{
	this->n = n;
	this->m = m;
}

Stack::~Stack()
{
	delete[] arr; arr = nullptr;
	delete[] top; top = nullptr;
	delete[] floor; floor = nullptr;
}

bool Stack::empty(int index)
{
	index--;
	return (this->top[index] == -1) ? 1 : 0;
}

bool Stack::full(int index)
{
	index--;
	return (this->top[index] == this->floor[index]) ? 1 : 0;
}

void Stack::push(int index, const int value)
{
	if (full(index))
		throw std::overflow_error("Stack overflow");

	index--;
	this->arr[++this->top[index] + this->n * index] = value;
}

int Stack::pop(int index)
{
	if (empty(index))
		throw std::underflow_error("Stack underflow");

	index--;
	int temp = this->arr[this->top[index] + this->n * index];
	--this->top[index];
	return temp;
}

void Stack::print(int index)
{
	index--;
	for (int i = this->top[index] + this->n * index;
		i > this->floor[index] - this->n; i--)
	{
		cout << this->arr[i] << " ";
	}
	cout << endl;
}
