#pragma once
#include <iostream>
#include <stdexcept>
#include <initializer_list>

template <typename T>
class Stack {
public:
    Stack();
    Stack(int n, int m);
    Stack(const Stack& other);
    Stack(std::initializer_list<T> values, int n, int m);
    ~Stack();
    Stack& operator=(const Stack& other);

    friend std::ostream& operator<<(std::ostream& os, const Stack& stack) {
        for (int i = 0; i < stack.m; i++) {
            os << "Stack " << i + 1 << ": ";
            for (int j = stack.top[i] + stack.n * i; j > stack.floor[i] - stack.n; j--) {
                os << stack.arr[j] << " ";
            }
            os << std::endl;
        }
        return os;
    }

    Stack& operator--();
    Stack operator--(int);
    bool empty(int index);
    bool full(int index);
    void push(int index, const T& value);
    T pop(int index);
    void print(int index);

    class StackProxy;
    StackProxy operator[](int index);

private:
    class StackProxy {
    public:
        StackProxy(Stack& stack, int stackIndex);
        T& operator[](int elementIndex);
    private:
        Stack& stack;
        int stackIndex;
    };

    int n, m;
    T* arr;
    int* top;
    int* floor;
};
