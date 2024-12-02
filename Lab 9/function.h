#pragma once

const int N = 3;

struct Stack
{
	int* arr = new int[N];
	int top = -1;
};

void push(const int value, Stack* stack);
void pop(Stack* stack);
bool empty(Stack* stack);
bool full(Stack* stack);
int top(Stack* stack);
void print(Stack* stack);
