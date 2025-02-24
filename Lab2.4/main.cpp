  #include <iostream>
#include <initializer_list>
#include "function.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    
    Stack stack(3, 3);

    try {
        stack.push(1, 100);
        stack.push(1, 200);
        stack.push(1, 300);
        stack.push(1, 400); // Переплнение стека
    }
    catch(const StackOverflowException& e) {
        cout << "Error: " << e.what() << endl;
    }

    try {
        stack.pop(2); // Попытка удалить из пустого стека
    }
    catch(const StackUnderflowException& e) {
        cout << "Error: " << e.what() << endl;
    }

    try {
        int value = stack[4][0]; // Некоретный индекс элемента
    }
    catch(const ElementIndexOutOfRangeException& e) {
        cout << "Error: " << e.what() << endl;
    }

    try {
        int value = stack[1][5]; // Некоретный индекс элемента
    }
    catch (const ElementIndexOutOfRangeException& e) {
        cout << "Error: " << e.what() << endl;
    }

    try {
        int value = stack[1][2]; // Доступ к неинициализированной памяти
    }
    catch (const UninitializedMemoryAccessException& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
