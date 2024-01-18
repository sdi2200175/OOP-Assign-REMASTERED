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
#include "course.hpp"

/* - Constructors and Destructors - */

Student::Student(unsigned short DepartmentCode) : 
	Person(),
	FormattedUniID("S-" + string(4 - (to_string(DepartmentCode)).length(), '0') + to_string(DepartmentCode) + "-" + string(6 - (to_string(getUniID())).length(), '0') + to_string(getUniID())) {

	cin >> *this;
  cout << "| Student ID: " << this->FormattedUniID << endl;
}

Student::Student(string Name, unsigned int ECTs, string DateOfBirth, string DateOfRegistration, unsigned short DepartmentCode) : 
	Person(Name), ECTs(ECTs), DateOfBirth(DateOfBirth), DateOfRegistration(DateOfRegistration),
	FormattedUniID("S-" + string(4 - (to_string(DepartmentCode)).length(), '0') + to_string(DepartmentCode) + "-" + string(6 - (to_string(getUniID())).length(), '0') + to_string(getUniID())) {

  cout << "| Student ID: " << this->FormattedUniID << endl;
}

Student::~Student() {}

/* Course Registration */

void Student::addCourseToRegisteredCoursesDatabase(Course *course) {
	this->RegisteredCoursesIDDatabase.insert(make_pair(course->getCourseID(), course));
	this->RegisteredCoursesNameDatabase.insert(make_pair(course->getName(), course));
}

void Student::removeCourseFromRegisteredCoursesDatabase(Course *course) {
	this->RegisteredCoursesIDDatabase.erase(course->getCourseID());
	this->RegisteredCoursesNameDatabase.erase(course->getName());
}

/* - Mandatory Course Completion - */

void Student::addCourseToMandatoryDatabase(Course *course) {
	this->CompletedMandatoryCoursesIDDatabase.insert(make_pair(course->getCourseID(), course));
  	this->CompletedMandatoryCoursesNameDatabase.insert(make_pair(course->getName(), course));
}

void Student::removeCourseFromMandatoryDatabase(Course *course) {
	this->CompletedMandatoryCoursesIDDatabase.erase(course->getCourseID());
	this->CompletedMandatoryCoursesNameDatabase.erase(course->getName());
}

/* - Non Mandatory Course Completion - */

void Student::addCourseToNonMandatoryDatabase(Course *course) {
	this->CompletedNonMandatoryCoursesIDDatabase.insert(make_pair(course->getCourseID(), course));
  	this->CompletedNonMandatoryCoursesNameDatabase.insert(make_pair(course->getName(), course));
}

void Student::removeCourseFromNonMandatoryDatabase(Course *course) {
	this->CompletedNonMandatoryCoursesIDDatabase.erase(course->getCourseID());
	this->CompletedNonMandatoryCoursesNameDatabase.erase(course->getName());
}

/* - Operator Overloads - */

ostream &operator<< (ostream &str, Student &student) {
	str << "|" << endl << "+-------- Student Description ---------+" << endl;
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