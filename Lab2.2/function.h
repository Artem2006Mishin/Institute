#pragma once

class Stack {
public:
    Stack();
    Stack(int n, int m);
    Stack(const Stack& other);
    Stack(std::initializer_list<int> arr, int n, int m);
    ~Stack();
    Stack& operator = (const Stack& other);
    friend std::ostream& operator<<(std::ostream& os, const Stack& stack);
    Stack& operator--();
    Stack& operator--(int value);
    bool empty(int index);
    bool full(int index);
    void push(int index, const int value);
    int pop(int index);
    void print(int index);

    class StackProxy;
    StackProxy operator[](int index);

private:
    class StackProxy {
    public:
        StackProxy(Stack& stack, int stackIndex);
        int& operator[](int elementIndex);
    private:
        Stack& stack; 
        int stackIndex;
    };

    int n, m;
    int* arr;
    int* top;
    int* floor;
};
