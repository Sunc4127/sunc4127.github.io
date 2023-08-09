//
// Created by Cheng Sun on 2023/8/6.
//

#include "../../include/library.h"

void increasePrice(double &price) {
    price *= 1.1;
}

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main () {
    int a = 1;
    int *p = &a;
    cout << *p << endl << endl;
    cout << p << endl;
    cout << &a << endl << endl;
    cout << &p << endl << endl;

    // &(*p) == p
    cout << &(*p) << endl;
    // &(*&a) == &a
    cout << &(*&a) << endl << endl;

    // *&a == a
    cout << *&a << endl;
    // *&p == p
    cout << *&p << endl;
    // **&p == *p == a
    cout << **&p << endl;

    // pointers:
    // 1. efficiently passing large objects to functions
    // 2. dynamically allocating memory
    // 3. enabling polymorphism
    // 4. building data structures such as linked lists, trees, and graphs

    cout << "====================" << endl;

    cout << "03. declaring and using pointers" << endl;
    int number = 10;
    cout << "the value of the number is:" << number << endl;
    // this pointer can only point to the address of integer
    // do not forget to initialize the pointer
    int *ptr = nullptr;
    ptr = &number;
    cout << "the address of the number is:" << ptr << endl;
    // indirection (de-referencing) operator
    *ptr = 20;
    cout << "the value of the number is now:" << number << endl << endl;

    int x = 10;
    int y = 20;
    int *p1 = &x;
    *p1 *= 5;
    p1 = &y;
    *p1 *= 5;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;



    cout << endl << "04. constant pointers" << endl;
    // three scenarios:
    // 1. data is constant
    // 2. pointer is constant
    // 3. data and pointer are both constant
    int scenario = random() % 2 == 0;
    if (scenario == 1) {
        // pointer has to be constant to point to a constant data
        // we cannot change the value of the data through the pointer
        // but the pointer itself can point to another data
        const int value = 5;
        const int *p2 = &value;
        int value2 = 10;
        p2 = &value2; // legal
    }
    else if (scenario == 2) {
        int value3 = 10;
        // we should always initialize the pointer,
        // otherwise it will point to a random address, and we cannot change the value of the data
        int *const p3 = &value3;
    }
    else if (scenario == 3) {
        const int value4 = 5;
        const int *const p4 = &value4;
    }



    cout << endl << "05. passing pointers to functions" << endl;
    double price = 10;
    increasePrice(price);
    cout << "the price is now: "<< price << endl;

    int a5 = 10;
    int b5 = 15;
    swap(a5, b5);
    cout << "a5 = " << a5 << endl;
    cout << "b5 = " << b5 << endl;



    cout << endl << "06. the relationship between arrays and pointers" << endl;
    int numbers6[] = {1, 2, 3, 4, 5};
    cout << numbers6 << endl;
    cout << *numbers6 << endl;
    int *ptr6 = numbers6;
    cout << ptr6 << endl;
    cout << *ptr6 << endl;



    cout << endl << "07. pointer arithmetic" << endl;
    int numbers7[] = {1, 2, 3, 4, 5};
    int *ptr7 = numbers7;
    ptr7++; // move to the next element, move 4 bytes, because int is 4 bytes (sizeof(int))
    cout << *ptr7 << endl;
    cout << *ptr7 + 1 << endl;



    cout << endl << "08. comparing pointers" << endl;
    int x8 = 10;
    int y8 = 20;
    int *ptrX8 = &x8;
    int *ptrY8 = &y8;

    // avoid nullptr when comparing pointers
    if (ptrX8 == ptrY8) {
        cout << "ptrX8 and ptrY8 point to the same address" << endl;
    }
    else {
        cout << "ptrX8 and ptrY8 do not point to the same address" << endl;
    }

    if (*ptrX8 == *ptrY8) {
        cout << "ptrX8 and ptrY8 point to the same value" << endl;
    }
    else {
        cout << "ptrX8 and ptrY8 do not point to the same value" << endl;
    }

    // reverse print the array
    int *ptr8 = &numbers7[size(numbers7) - 1];
    while (ptr8 >= numbers7) {
        cout << *ptr8 << " ";
        ptr8--;
    }



    cout << endl << "09. dynamic memory allocation" << endl;
    // stack memory: fast, limited, automatically allocated and deallocated
    int numberStack[1000];

    // heap memory: slower, larger, manually allocated and deallocated
    // risk: memory leak if we forget to deallocate the memory
    int *numbersHeap = new int[1000];
    delete[] numbersHeap;
    int *numberHeap = new int;
    delete numberHeap;
    numberHeap = nullptr; // good practice
    numbersHeap = nullptr;



    cout << endl << "10. dynamic resizing an array" << endl;
    int capacity = 5;
    int *numbers10 = new int[capacity];
    int entries = 0;
    while (true) {
        numbers10[entries] = entries;
        entries++;
        if (entries == capacity) {
            capacity *= 2;
            int *newNumbers = new int[capacity];
            for (int i = 0; i < entries; i++) {
                newNumbers[i] = numbers10[i];
            }
            delete[] numbers10; // don't forget to deallocate the memory
            numbers10 = newNumbers;
        }
        cout << entries << " ";
        if (entries == 10) {
            break;
        }
    }
    delete[] numbers10; // very important
    numbers10 = nullptr;



    cout << endl << "11. smart pointers" << endl;
    // two types of smart pointers:
    // 1. unique_ptr: only one pointer can point to the data
    // 2. shared_ptr: multiple pointers can point to the data
    // smart pointers are automatically deallocated when they go out of scope
    // smart pointers are not compatible with regular pointers
    // smart pointers are not compatible with arrays

    // cannot do arithmetic with smart pointers
    unique_ptr<int> number11(new int);
    cout << *number11 << endl;

    // recommended way to create a smart unique pointer
    auto x11 = make_unique<int>(10);
    auto y11 = make_unique<int>(10);
    auto numbers11 = make_unique<int[]>(10);

    // shared pointers
    auto xShared = make_shared<int>();
    shared_ptr<int> yShared(xShared);
    *yShared = 20;
    if (xShared == yShared) {
        cout << "xShared and yShared point to the same address" << endl;
    }
    else {
        cout << "xShared and yShared do not point to the same address" << endl;
    }
}