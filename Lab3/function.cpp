#include <iostream>
#include <stdexcept>
#include "function.h"

// Конструктор по умолчанию
template <typename T>
Stack<T>::Stack() : Stack(3, 3) {}

// Конструктор с параметрами
template <typename T>
Stack<T>::Stack(int n, int m) : n(n), m(m) {
    arr = new T[n * m];
    top = new int[m];
    floor = new int[m];

    for (int i = 0; i < m; i++) {
        top[i] = -1;
        floor[i] = (i + 1) * n - 1;
    }
}

// Конструктор копирования
template <typename T>
Stack<T>::Stack(const Stack& other) : n(other.n), m(other.m) {
    arr = new T[n * m];
    top = new int[m];
    floor = new int[m];

    for (int i = 0; i < m; i++) {
        top[i] = other.top[i];
        floor[i] = other.floor[i];
    }

    for (int i = 0; i < n * m; i++) {
        arr[i] = other.arr[i];
    }
}

// Конструктор с initializer_list
template <typename T>
Stack<T>::Stack(std::initializer_list<T> values, int n, int m) : n(n), m(m) {
    arr = new T[n * m];
    top = new int[m];
    floor = new int[m];

    for (int i = 0; i < m; i++) {
        top[i] = -1;
        floor[i] = (i + 1) * n - 1;
    }

    int i = 0, j = 0;
    for (const auto& elem : values) {
        if (i >= n * m) {
            throw std::overflow_error("Too many elements in initializer list");
        }

        if (j >= m) {
            throw std::overflow_error("Too many stacks");
        }

        arr[i++] = elem;
        top[j]++;

        if (floor[j] == top[j]) {
            j++;
        }
    }
}

// Деструктор
template <typename T>
Stack<T>::~Stack() {
    delete[] arr;
    delete[] top;
    delete[] floor;
}

// Оператор присваивания
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
    if (this == &other) {
        return *this;
    }

    delete[] arr;
    delete[] top;
    delete[] floor;

    n = other.n;
    m = other.m;

    arr = new T[n * m];
    top = new int[m];
    floor = new int[m];

    for (int i = 0; i < m; i++) {
        top[i] = other.top[i];
        floor[i] = other.floor[i];
    }

    for (int i = 0; i < n * m; i++) {
        arr[i] = other.arr[i];
    }

    return *this;
}

// Оператор постфиксного декремента
template <typename T>
Stack<T> Stack<T>::operator--(int) {
    Stack temp(*this);
    --(*this);
    return temp;
}

// Оператор префиксного декремента
template <typename T>
Stack<T>& Stack<T>::operator--() {
    for (int i = 0; i < n * m; i++) {
        arr[i]--;
    }
    return *this;
}

// Проверка на пустоту стека
template <typename T>
bool Stack<T>::empty(int index) {
    index--;
    return top[index] == -1;
}

// Проверка на заполненность стека
template <typename T>
bool Stack<T>::full(int index) {
    index--;
    return top[index] == floor[index];
}

// Добавление элемента в стек
template <typename T>
void Stack<T>::push(int index, const T& value) {
    if (full(index)) {
        throw std::overflow_error("Stack overflow");
    }

    index--;
    arr[++top[index] + n * index] = value;
}

// Извлечение элемента из стека
template <typename T>
T Stack<T>::pop(int index) {
    if (empty(index)) {
        throw std::underflow_error("Stack underflow");
    }

    index--;
    T temp = arr[top[index] + n * index];
    top[index]--;
    return temp;
}

// Вывод содержимого стека
template <typename T>
void Stack<T>::print(int index) {
    index--;
    for (int i = top[index] + n * index; i > floor[index] - n; i--) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// Реализация StackProxy
template <typename T>
Stack<T>::StackProxy::StackProxy(Stack& stack, int stackIndex)
    : stack(stack), stackIndex(stackIndex) {
    if (stackIndex < 0 || stackIndex >= stack.m) {
        throw std::out_of_range("Stack index out of range");
    }
}

template <typename T>
Stack<T>::StackProxy Stack<T>::operator[](int index) {
    return StackProxy(*this, index);
}

template <typename T>
T& Stack<T>::StackProxy::operator[](int elementIndex) {
    if (elementIndex < 0 || elementIndex >= stack.n) {
        throw std::out_of_range("Element index out of range");
    }

    int actualIndex = stack.n * stackIndex + elementIndex;
    if (elementIndex > stack.top[stackIndex]) {
        throw std::out_of_range("Access to uninitialized memory");
    }

    return stack.arr[actualIndex];
}
