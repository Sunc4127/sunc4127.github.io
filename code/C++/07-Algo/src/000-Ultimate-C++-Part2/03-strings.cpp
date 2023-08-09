//
// Created by Cheng Sun on 2023/8/6.
//
#include "../../include/library.h"


bool isValid(string customerNumber) {
    if (customerNumber.size() != 6) {
        return false;
    }
    for (int i = 0; i < 2; i++) {
        if (!isalpha(customerNumber[i])) {
            return false;
        }
    }

    for (int i = 2; i < customerNumber.size(); i++) {
        if (!isdigit(customerNumber[i])) {
            return false;
        }
    }
    return true;
}


int main() {
    cout << endl << "02. C string" << endl;
    char name[6] = {'C', 'h', 'e', 'n','g', '\0'};
    // null terminator (\0) is automatically added at the end of the string
    // string literal
    char lastName[50] = "sun "; // the size of the array must be large enough
    // character literal
    lastName[0] = 'S';

    cout << strlen(lastName) << endl;
    strcat(lastName, name);
    cout << lastName << endl;

    strcpy(lastName, "Sun");
    cout << lastName << endl;

    if (strcmp(lastName, name) == 0) {
        cout << "same" << endl;
    } else {
        cout << "different" << endl;
    }

    cout << endl << "03. C++ string" << endl;
    string s = "hello";
    s += " world";
    cout << s << endl;
    cout << s.size() << endl;
    cout << s.length() << endl;
    // copy constructor
    string another = s;

    if (s == another) {
        cout << "same" << endl;
    } else {
        cout << "different" << endl;
    }

    s.starts_with("h");
    s.ends_with("d");
    //s.empty();
    s.front();
    s.back();



    cout << endl << "04. modifying strings" << endl;
    string name4 = "Cheng Sun";
    name4.append(" is a student");
    name4.insert(0, "Mr. ");
    cout << name4 << endl;
    name4.erase(0, 4);
    cout << name4 << endl;
    name4.clear();
    cout << "clear: " << name4 << endl;
    name4.replace(0, 5, "Mr. ");
    cout << name4 << endl;




    cout << endl << "05. searching strings" << endl;
    string name5 = "Cheng Sun";
    cout << name5.find("Sun") << endl;
    cout << name5.find('S') << endl;
    cout << name5.find('n', 4) << endl; // start from index 4
    cout << name5.rfind('n') << endl; // search from the end
    if (name5.find("Sun") != -1) {
        cout << "found" << endl;
    } else {
        cout << "not found" << endl;
    }
    cout << name5.find_first_of(",.;") << endl; // find the first occurrence of any of the characters
    cout << name5.find_last_of(",.;") << endl; // find the last occurrence of any of the characters
    cout << name5.find_first_not_of("Cheng") << endl; // find the first occurrence of any of the characters
    cout << name5.find_last_not_of("Cheng") << endl; // find the last occurrence of any of the characters




    cout << endl << "06. extracting substrings" << endl;
    string name6 = "Cheng Sun";
    string copy6 = name6.substr(0, 5);
    name6 = ""; // clear the string, does not affect copy6
    cout << copy6 << endl;

    name6 = "Cheng Sun";
    auto index6 = name6.rfind(' '); // in case has middle name
    string firstName = name6.substr(0, index6);
    string lastName6 = name6.substr(index6 + 1);
    cout << firstName << " " << lastName << endl;



    cout << endl << "07. working with characters" << endl;
    string name7 = "Cheng Sun";
    cout << islower(name7[0]) << endl;
    cout << isupper(name7[0]) << endl;
    cout << isalpha(name7[0]) << endl;
    cout << isdigit(name7[0]) << endl;

    cout << (char) toupper('a') << endl;
    cout << (char) tolower('A') << endl;

    cout << isValid("AB1234") << endl;




    cout << endl << "08. string numeric conversion functions" << endl;
    string s8 = "19.19"; // 19.19x is ok; 19.x19 is ok, x and decimal are ignored; x19.19 is not ok,error thrown
    double price = stod(s8); // string to double
    cout << price << endl;

    string temp8 = to_string(19.9); // double to string, better use stream
    cout << temp8 << endl;




    cout << endl << "09. escape sequence" << endl;
    char ch = '\''; // single quote



    cout << endl << "10. raw string" << endl;
    R"(string)"; // raw string, no escape sequence
}