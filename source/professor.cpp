/**
 * @file professor.cpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief 
 * @version 
 * @date 2024-01-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "professor.hpp"

Professor::Professor(unsigned short DepartmentCode) : 
	Person(),
	FormattedUniID("P-" + string(4 - (to_string(DepartmentCode)).length(), '0') + to_string(DepartmentCode) + "-" + string(6 - (to_string(getUniID())).length(), '0') + to_string(getUniID())) {

	cin >> *this;
  cout << "| Professor ID: " << this->FormattedUniID << endl;
}

Professor::Professor(string Name, unsigned short DepartmentCode) : 
	Person(Name), 
	FormattedUniID("P-" + string(4 - (to_string(DepartmentCode)).length(), '0') + to_string(DepartmentCode) + "-" + string(6 - (to_string(getUniID())).length(), '0') + to_string(getUniID())) {

  cout << "| Professor ID: " << this->FormattedUniID << endl;
}

Professor::~Professor() {}

ostream &operator<< (ostream &str, Professor &professor) {
	str << "|" << endl << "+-------- Professor Properties --------+" << endl;
	str << "| Full Name: " << professor.getName() << endl;
	str << "| University ID: " << professor.FormattedUniID << endl;
	str << "+------ End of Professor Details ------+" << endl << "|" << endl;
	return str;
}

istream &operator>> (istream &str, Professor &professor) {
	string FullName, Buffer;
	cout << "> Enter First Name: ";
	getline(str, FullName);
	cout << "> Enter Father's Name: ";
	getline(str, Buffer);
	FullName = FullName + " " + Buffer;
	cout << "> Enter Last Name: ";
	getline(str, Buffer);
	FullName = FullName + " " + Buffer;
	professor.setName(FullName);
	return str;
}