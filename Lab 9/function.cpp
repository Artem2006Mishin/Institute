#include <iostream>
#include "function.h"
using namespace std;

bool empty(Stack* stack, int index)
{
	if (stack->top[index] == -1)
		return 1;
	else
		return 0;
}

bool full(Stack* stack, int index)
{
	if (stack->top[index] == stack->floor[index])
		return 1;
	else
		return 0;
}

void push(Stack* stack, int index, const int value)
{
	index--;
	if (full(stack, index))
		throw std::overflow_error("Stack overflow");

	stack->arr[++stack->top[index] + stack->n * index] = value;
}

int pop(Stack*& stack, int index)
{
	index--;
	if (empty(stack, index))
		throw std::underflow_error("Stack underflow");

	int temp = stack->arr[stack->top[index] + stack->n * index];
	--stack->top[index];
	return temp;
}

void print(Stack*& stack, int index)
{
	index--;
	for (int i = stack->top[index] + stack->n * index;
		i > stack->floor[index] - stack->n; i--)
	{
		cout << stack->arr[i] << " ";
	}
	cout << endl;
}
