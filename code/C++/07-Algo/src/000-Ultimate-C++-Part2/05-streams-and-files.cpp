//
// Created by Cheng Sun on 2023/8/20.
//
#include "../../include/library.h"

int getNumber(string prompt) {
    int number;
    while (true) {
        cout << prompt;
        cin >> number;
        // handling read errors
        if (cin.fail()) {
            cout << "Error reading number" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    return number;
}

struct Movie {
    int id;
    string title;
    int year;
};

int main() {
    // writing to a stream
    cout << "hello world" << endl;

    // reading from a stream
    int first = getNumber("Enter the first number: ");
    int second = getNumber("Enter the second number: ");
    cout << "The first number is: " << first << endl;
    cout << "The second number is: " << second << endl;

    // write to a text file; ofstream: output file stream
    ofstream outFile;
    outFile.open("file.txt", ios::trunc); // if the file does not exist, it will be created, overwrite the file
    if (outFile.is_open()) {
        // CSV: comma separated values
        outFile << "id,title,year\n" // \n is preferred over endl because it will not flush the buffer, which is more efficient
                << "1,The Matrix,1999\n"
                << "2,The Matrix Reloaded,2003\n";
        outFile.close(); // always close the file after writing, otherwise the file may be corrupted
        // or not accessible to other programs
    } else {
        cout << "Could not create file: file.txt" << endl;
    }

    // reading from a text file; ifstream: input file stream; fstream: file stream, both input and output
    ifstream inFile;
    inFile.open("file.txt"); // if the file does not exist, it will be created
    if (inFile.is_open()) {
        string str;
        getline(inFile, str); // read the first line
        cout << str << endl;
        while (!inFile.eof()) { // eof: end of file
            getline(inFile, str, ',');
            if (str.empty()) {
                continue;
            }
            Movie movie;
            movie.id = stoi(str); // stoi: string to integer
            getline(inFile, str, ',');
            movie.title = str;
            getline(inFile, str);
            movie.year = stoi(str);
            cout << movie.id << " " << movie.title << " " << movie.year << endl;
        }
        inFile.close();
    }

    // writing to a binary file
    int numbers[3] = {1, 2, 3};
    ofstream outFile2;
    outFile2.open("file.bin", ios::trunc | ios::binary);
    if (outFile2.is_open()) {
        outFile2.write(reinterpret_cast<char *>(&numbers), sizeof(numbers));
        outFile2.close();
    } else {
        cout << "Could not create file: file.bin" << endl;
    }

    // reading from a binary file
    ifstream inFile2;
    inFile2.open("file.bin", ios::binary);
    if (inFile2.is_open()) {
        int number;
        while (inFile2.read(reinterpret_cast<char *>(&number), sizeof(number))) {
            cout << number << endl;
        }
        inFile2.close();
    }
};