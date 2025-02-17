#include <iostream>
#include <initializer_list>
#include "function.h"
using namespace std;

Stack::Stack() : Stack(3, 3) {}

Stack::Stack(int n, int m) 
{
	this->n = n;
	this->m = m;

	arr = new int[n * m];
	top = new int[m];
	floor = new int[m];

	for (int i = 0; i < m; i++)
	{
		top[i] = -1;
		floor[i] = (i + 1) * n - 1;
	}
}

Stack::Stack(const Stack& other)
{
	this->m = other.m;
	this->n = other.n;

	this->arr = new int[this->n * this->m];
	this->top = new int[this->m];
	this->floor = new int[this->m];

	for (int i = 0; i < this->m; i++)
	{
		this->top[i] = other.top[i];
		this->floor[i] = other.floor[i];
	}

	for (int i = 0; i < this->m * this->n; i++)
	{
		this->arr[i] = other.arr[i];
	}
}

Stack::Stack(std::initializer_list<int> values, int n, int m)
{
	this->m = m;
	this->n = n;

	this->arr = new int[n * m];
	this->top = new int[m];
	this->floor = new int[m];

	// Инициализация top и floor
	for (int i = 0; i < this->m; i++)
	{
		this->top[i] = -1;
		this->floor[i] = (i + 1) * this->n - 1;
	}

	int i = 0, j = 0;
	for (auto elem : values)
	{
		// Проверка на переполнение arr
		if (i >= n * m)
		{
			throw std::overflow_error("Too many elements in initializer list");
		}

		// Проверка на переполнение текущего стека
		if (j >= m)
		{
			throw std::overflow_error("Too many stacks");
		}

		this->arr[i++] = elem;
		this->top[j]++;

		// Если текущий стек заполнен, переходим к следующему
		if (this->floor[j] == this->top[j])
		{
			j++;
		}
	}
}

Stack::~Stack()
{
	delete[] arr;
	delete[] top;
	delete[] floor;
}

Stack& Stack::operator=(const Stack& other)
{
	this->m = other.m;
	this->n = other.n;

	if (this->arr != nullptr)
	{
		delete[] this->arr;
		delete[] this->top;
		delete[] this->floor;
	}

	this->arr = new int[this->n * this->m];
	this->top = new int[this->m];
	this->floor = new int[this->m];

	for (int i = 0; i < this->m; i++)
	{
		this->top[i] = other.top[i];
		this->floor[i] = other.floor[i];
	}

	for (int i = 0; i < this->m * this->n; i++)
	{
		this->arr[i] = other.arr[i];
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Stack& stack)
{
	for (int i = 0; i < stack.m; i++)
	{
		os << "Stack " << i + 1 << ": ";
		for (int j = stack.top[i] + stack.n * i; j > stack.floor[i] - stack.n; j--)
		{
			os << stack.arr[j] << " ";
		}
		os << endl;
	}
	return os;
}

Stack& Stack::operator--()
{
	if (this->top[0] != -1)
	{
		for (int i = 0; i < this->n * this->m; i++)
		{
			this->arr[i]--;
		}		
	}
	return *this;	
}

Stack& Stack::operator--(int value)
{
	Stack temp(*this);
	if (this->top[0] != -1)
	{
		for (int i = 0; i < this->n * this->m; i++)
		{
			this->arr[i]--;
		}
	}
	return temp;
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

Stack::StackProxy Stack::operator[](int index)
{
	return StackProxy(*this, index);
}

Stack::StackProxy::StackProxy(Stack& stack, int stackIndex) :
	stack(stack), stackIndex(stackIndex)
{
	if (stackIndex < 0 || stackIndex >= stack.m)
		throw std::out_of_range("Stack index out of range");
}

int& Stack::StackProxy::operator[](int elementIndex)
{
	if (elementIndex < 0 || elementIndex >= stack.n)
		throw std::out_of_range("Element index out of range");

	int actualIndex = stack.n * stackIndex + elementIndex;
	if (elementIndex > stack.top[stackIndex])
		throw std::out_of_range("Access to uninitialized memory");

	return stack.arr[actualIndex];
}
