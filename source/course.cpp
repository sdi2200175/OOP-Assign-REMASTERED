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
#include "professor.hpp"
#include "student.hpp"

unsigned int Course::CourseAmount = 0;

/* - Constructors and Destructors - */

Course::Course(unsigned short DepartmentCode) : CourseID(++CourseAmount),
	FormattedCourseID("C-" + string(4 - (to_string(DepartmentCode)).length(), '0') + to_string(DepartmentCode) + "-" + string(6 - (to_string(getCourseID())).length(), '0') + to_string(getCourseID())) {
	
  cin >> *this;
  cout << "| Course ID: " << this->FormattedCourseID << endl;
}

Course::Course(string Name, bool Mandatory, unsigned short ECTs, unsigned short Semester, unsigned short DepartmentCode) : 
  	Name(Name), Mandatory(Mandatory), ECTs(ECTs), Semester(Semester), CourseID(++CourseAmount),
	FormattedCourseID("C-" + string(4 - (to_string(DepartmentCode)).length(), '0') + to_string(DepartmentCode) + "-" + string(6 - (to_string(getCourseID())).length(), '0') + to_string(getCourseID())) {

  cout << "| Course ID: " << this->FormattedCourseID << endl;
}

Course::~Course() {}

/* - Professor Assignment - */

void Course::assignProfessor(Professor *professor) {
  this->AssignedProfessorsIDDatabase.insert(make_pair(professor->getUniID(), professor));
  this->AssignedProfessorsNameDatabase.insert(make_pair(professor->getName(), professor));
}

/* - Student Registration - */

void Course::registerStudent(Student *student) {
  this->RegisteredStudentsIDDatabase.insert(make_pair(student->getUniID(), student));
  this->RegisteredStudentsNameDatabase.insert(make_pair(student->getName(), student));
}

/* - Operator Overloads - */

ostream &operator<< (ostream &str, Course &course) {
	str << "|" << endl << "+---------- Course Properties ---------+" << endl;
	str << "| Name: " << course.Name << endl;
	str << "| Mandatory: ";
	if (course.Mandatory) { str << "| Yes" << endl; }
	else { str << "| No" << endl; }
    str << "| ECTs: " << course.ECTs << endl;
	str << "| Semester: " << course.Semester << endl;
	str << "+-------- End of Course Details -------+" << endl << "|" << endl;
	return str;
}

istream &operator>> (istream &str, Course &course) {
	string Buffer;
	cout << "> Enter Name: ";
	getline(str, course.Name);
    cout << "> Is the course Mandatory? (Y/N) ";
    getline(str, Buffer);
    if (Buffer.compare("Y") || Buffer.compare("y")) { course.Mandatory = true; }
    else { course.Mandatory = false; }
	cout << "> Enter ECTs: ";
	getline(str, Buffer);
	course.ECTs = (unsigned short)stoi(Buffer);
	cout << "> Enter Semester: ";
	getline(str, Buffer);
	course.Semester = (unsigned short)stoi(Buffer);
	return str;
}