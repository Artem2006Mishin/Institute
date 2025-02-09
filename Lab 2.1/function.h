#pragma once

class Stack
{
public:
	Stack();
	Stack(int n, int m);
	Stack(const Stack&);
	~Stack();
	bool empty(int index);
	bool full(int index);
	void push(int index, const int value);
	int pop(int index);
	void print(int index);
private:
	int n, m;
	int* arr;
	int* top;
	int* floor;
};
