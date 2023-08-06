//
// Created by Cheng Sun on 2023/8/6.
//

#include "../../include/library.h"

// we can use a pointer to represent an array
// the length of the array is necessary, because size() will not work on a pointer (int*)
void printNumbers(int numbers[], int length) {
    for (int i = 0; i < length; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
}

// find the index of the target in the array
int find(int numbers[], int length, int target) {
    for (int i = 0; i < length; i++) {
        if (numbers[i] == target) {
            return i;
        }
    }
    return -1;
}

// remove the target from the array
int remove(int numbers[], int length, int target) {
    int index = find(numbers, length, target);
    if (index == -1) {
        return length;
    }
    for (int i = index; i < length - 1; i++) {
        numbers[i] = numbers[i + 1];
    }
    return length - 1;
}

void swap(int numbers[], int i, int j) {
    int temp = numbers[i];
    numbers[i] = numbers[j];
    numbers[j] = temp;
}

// sort the array
void bubbleSort(int numbers[], int length) {
    for (int pass = 0; pass < length; pass++) {
        for (int i = 1; i < length; i++) {
            if (numbers[i] < numbers[i - 1]) {
                swap(numbers, i, i - 1);
            }
        }
    }
}

const int rows = 2;
const int columns = 3;
void printMatrix(int matrix[rows][columns]) {
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column ++) {
            cout << matrix[row][column] << " ";
        }
        cout << endl;
    }
}

int main() {
    int numbers[5];
    numbers[0] = 10;
    numbers[4] = 20;
    cout << numbers[0] << endl;
    int numbers2[5] = {10, 20, 30, 40, 50};
    cout << numbers2[4] << endl;

    // a pointer to the first element of the array
    cout << endl << "03. determine the size of arrays" << endl;
    if(numbers[0] > 5) {
        for (auto number : numbers) {
            cout << number << " ";
        }
        cout << endl << "print array with index" << endl;
        // sizeof(numbers2) / sizeof(int) is the length of the array
        // we can also use size(numbers2) to get the length of the array
        for (int i = 0; i < sizeof(numbers) / sizeof(int); i++) {
            cout << numbers2[i] << " ";
        }
        cout << endl;
    }

    // copy array
    cout << endl << "04. copy array" << endl;
    cout << "copy array" << endl;
    int first[5] = {1, 2, 3, 4, 5};
    int second[size(first)];
    for (int i = 0; i < size(first); i++) {
        second[i] = first[i];
    }
    // compare two arrays
    cout << endl << "05. compare two arrays" << endl;
    for (int i = 0; i < size(first); i++) {
        if (first[i] != second[i]) {
            cout << "copy array failed" << endl;
            break;
        }
    }
    cout << "copy array success" << endl;

    printNumbers(second, size(second));

    cout << endl << "07. understanding size_t" << endl;
    cout << sizeof(int) << " " << sizeof(size_t) << endl;
    // size_t = unsigned int; it is a data type to represent the sizes
    // it is large enough to hold the size of the largest object the system can handle
    cout << numeric_limits<int>::min() << " " << numeric_limits<int>::max() << endl;
    cout << numeric_limits<size_t>::min() << " " << numeric_limits<size_t>::max() << endl;

    // c++: structured binding; JavaScript: destructuring assignment; Python: unpacking
    cout << endl << "08. unpacking arrays" << endl;
    int values[3] = {1, 2, 3};
    auto [x, y, z] = values;
    cout << x << " " << y << " " << z << endl;

    // 09. searching arrays
    cout << endl << "09. searching arrays" << endl;
    cout << "find the index of the target in the array: "<< find(values, size(values), 2) << endl;

    // 10. sorting arrays
    cout << endl << "10. sort the array" << endl;
    int numbers3[] = {5, 3, 4, 1, 2};
    bubbleSort(numbers3, size(numbers3));
    printNumbers(numbers3, size(numbers3));

    // 11. multidimensional arrays
    cout << endl << "11. multidimensional arrays" << endl;
    int matrix[rows][columns] = {{1, 2, 3}, {4, 5, 6}};
    printMatrix(matrix);

}
