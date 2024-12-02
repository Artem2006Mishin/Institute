#include <iostream>
#include "function.h"
using namespace std;

void push(const int value, Stack* stack)
{
	if (stack->top == N - 1) {
		throw std::overflow_error("Stack overflow");
	}
	stack->arr[++stack->top] = value;
}

void pop(Stack* stack)
{
	if (stack->top == -1) {
		throw std::underflow_error("Stack underflow");
	}
	--stack->top;
}

bool empty(Stack* stack)
{
	if (stack->top == -1)
		return 1;
	else
		return 0;
}

bool full(Stack* stack)
{
	if (stack->top == N - 1)
		return 1;
	else
		return 0;
}

int top(Stack* stack)
{
	return stack->top;
}

void print(Stack* stack)
{
	for (int i = stack->top; i >= 0; i--)
		cout << stack->arr[i] << " ";
	cout << endl;
}
