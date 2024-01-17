/**
 * @file course.hpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief 
 * @version 
 * @date 2024-01-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "course.hpp"

Course::Course() {
	cin >> *this;
}

Course::Course(string Name, bool Mandatory, unsigned short ECTs) : Name(Name), Mandatory(Mandatory), ECTs(ECTs) {
	cout << "|" << endl << "+--------- Constructing Course --------+" << endl;
	cout << "+--------- Constructed Course ---------+" << endl;	
}

Course::~Course() {}

ostream &operator<< (ostream &str, Course &course) {
	str << "|" << endl << "+---------- Course Properties ---------+" << endl;
	str << "| Name: " << course.Name << endl;
	if (course.Mandatory) { str << "| The course is Mandatory: " << endl; }
	else { str << "| The course is not Mandatory: " << endl; }
    str << "| ECTs: " << course.ECTs << endl;
	str << "+-------- End of Course Details -------+" << endl << "|" << endl;
	return str;
}

istream &operator>> (istream &str, Course &course) {
	string Buffer;
	cout << "> Enter Name: ";
	getline(str, course.Name);
    cout << "> Is the course Mandatory? (Y/N)";
    getline(str, Buffer);
    if (Buffer.compare("Y") || Buffer.compare("y")) { course.Mandatory = true; }
    else { course.Mandatory = false; }
	cout << "> Enter ECTs: ";
	getline(str, Buffer);
	course.ECTs = (unsigned short)stoi(Buffer);
	return str;
}