#pragma once

class Stack
{
public:
	Stack();
	Stack(int n, int m);
	Stack(const Stack& other);
	Stack(std::initializer_list<int> arr, int n, int m);
	~Stack();
	Stack& operator = (const Stack& other);
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
