/**
 * @file student.cpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief 
 * @version 
 * @date 2024-01-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "student.hpp"

Student::Student(unsigned short DepartmentCode) : 
    Person(),
    FormattedUniID("S-" + to_string(DepartmentCode) + "-" + string(10 - (to_string(getUniID())).length(), '0') + to_string(getUniID())) {
    
    // cout << "|" << endl << "+----------- Student Details -----------+" << endl;
    cin >> *this;
    // cout << "+--------- Constructed Student ---------+" << endl;

    cout << "+- Constructed Student with University ID: " << getFormattedID() << " -+" << endl;
}

Student::~Student() {}

ostream &operator<< (ostream &str, Student &student) {
    str << "| Full Name: " << student.getName() << endl;
    str << "| ECTs: " << student.ECTs << endl;
    str << "| Date of Birth: " << student.DateOfBirth << endl;
    str << "| Date of Registration: " << student.DateOfRegistration << endl;
    str << "| University ID: " << student.FormattedUniID << endl;
    return str;
}

istream &operator>> (istream &str, Student &student) {
    string Buffer;
    cout << "- Enter ECTs: " << endl;
    getline(str, Buffer);
    student.ECTs = (unsigned int)stoi(Buffer);
    cout << "- Enter Date of Birth: " << endl;
    getline(str, student.DateOfBirth);
    cout << "- Enter Date of Registration: " << endl;
    getline(str, student.DateOfRegistration);
    return str;
}