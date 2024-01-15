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
	FormattedUniID("S-" + to_string(DepartmentCode) + "-" + string(6 - (to_string(getUniID())).length(), '0') + to_string(getUniID())) {

  cout << "| Constructing a new Student..." << endl;
	cin >> *this;
  cout << "| Constructed a new Student with ID: " << this->FormattedUniID << endl;
}

Student::Student(string Name, unsigned int ECTs, string DateOfBirth, string DateOfRegistration, unsigned short DepartmentCode) : 
	Person(Name), ECTs(ECTs), DateOfBirth(DateOfBirth), DateOfRegistration(DateOfRegistration),
	FormattedUniID("S-" + to_string(DepartmentCode) + "-" + string(6 - (to_string(getUniID())).length(), '0') + to_string(getUniID())) {

	cout << "|" << endl << "+-------- Constructing Student --------+" << endl;
	cout << "+- Constructed Student with ID: " << getFormattedID() << " -+" << endl;
}

Student::~Student() {}

ostream &operator<< (ostream &str, Student &student) {
	str << "|" << endl << "+--------- Student Properties ---------+" << endl;
	str << "| Full Name: " << student.getName() << endl;
	str << "| ECTs: " << student.ECTs << endl;
	str << "| Date of Birth: " << student.DateOfBirth << endl;
	str << "| Date of Registration: " << student.DateOfRegistration << endl;
	str << "| University ID: " << student.FormattedUniID << endl;
	str << "+------- End of Student Details -------+" << endl << "|" << endl;
	return str;
}

istream &operator>> (istream &str, Student &student) {
	string FullName, Buffer;
	cout << "> Enter First Name: ";
	getline(str, FullName);
	cout << "> Enter Father's Name: ";
	getline(str, Buffer);
	FullName = FullName + " " + Buffer;
	cout << "> Enter Last Name: ";
	getline(str, Buffer);
	FullName = FullName + " " + Buffer;
	student.setName(FullName);
	cout << "> Enter ECTs: ";
	getline(str, Buffer);
	student.ECTs = (unsigned int)stoi(Buffer);
	cout << "> Enter Date of Birth: ";
	getline(str, student.DateOfBirth);
	cout << "> Enter Date of Registration: ";
	getline(str, student.DateOfRegistration);
	return str;
}