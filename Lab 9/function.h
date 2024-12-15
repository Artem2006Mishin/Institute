#pragma once

struct Stack
{
	// n - вместимость 1-го массива 
	// m - кол-во массивов 
	int n, m;
	int* arr = new int[n * m];
	int* top = new int[m]; // | -1 -1 -1 |
	int* floor = new int[m]; // | 2 5 8 |

	Stack(int _n, int _m) : n(_n), m(_m) {
		for (int i = 0; i < m; i++) {
			top[i] = -1; 
			floor[i] = (i + 1) * n - 1; 
		}
	}
};

bool empty(Stack* stack, int index);
bool full(Stack* stack, int index);
void push(Stack* stack, int index, const int value);
int pop(Stack*& stack, int index);
void print(Stack*& stack, int index);
