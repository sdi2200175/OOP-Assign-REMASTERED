/**
 * @file secretary.cpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief 
 * @version 
 * @date 2024-01-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "secretary.hpp"

Secretary::Secretary() {
  cin >> *this;
}

Secretary::Secretary(string DepartmentName, unsigned int DepartmentCode, unsigned int ECTRequirement, unsigned short MaximumAttendance) : 
  DepartmentName(DepartmentName), DepartmentCode(DepartmentCode), ECTRequirement(ECTRequirement), MaximumAttendance(MaximumAttendance) {}

Secretary::~Secretary() {

  for (map<unsigned int, Student*>::iterator itr = this->StudentIDDatabase.begin(); 
      itr != this->StudentIDDatabase.end(); itr++) {

      delete itr->second;
  }
}

void Secretary::addStudent() {
  Student *student = new Student(this->DepartmentCode);
  this->addStudentToDatabase(student);
}

void Secretary::addStudentToDatabase(Student *student) {
  this->StudentIDDatabase.insert(make_pair(student->getUniID(), student));
  this->StudentNameDatabase.insert(make_pair(student->getName(), student));
}

void Secretary::deleteStudent(Student *student) {
  this->removeStudentFromDatabase(student);
  delete student;
}

void Secretary::removeStudentFromDatabase(Student *student) {
  this->StudentIDDatabase.erase(student->getUniID());
  this->StudentNameDatabase.erase(student->getName());
}

/**
 * @brief Searches for a Student in the Secretary.
 * 
 * @param UniID Search Term.
 * @return A pointer the the Student that was found.
 * @exception Throws an invalid_argument exception if the Student was not found in the secretary.
 */
Student *Secretary::retrieveStudent(unsigned int UniID) {
  map<unsigned int, Student*>::iterator student = this->StudentIDDatabase.find(UniID);
  if (student == this->StudentIDDatabase.end())
    throw invalid_argument("! ERROR: Student with University ID: S-" + to_string(this->DepartmentCode) + "-" + 
                            string(6 - (to_string(UniID)).length(), '0') + to_string(UniID) + " wasn't found.");
  else
    return student->second;
}

/**
 * @brief Searches for a Student in the Secretary.
 * 
 * @param Name Search Term.
 * @return A pointer to the Student that was found.
 * @exception Throws and invalid_argument exception if the Student was not found in the Secretary.
 */
Student *Secretary::retrieveStudent(const string &Name) {
  map<string, Student*>::iterator student = this->StudentNameDatabase.find(Name);
  if (student == this->StudentNameDatabase.end())
    throw invalid_argument("! ERROR: Student named '" + Name + " wasn't found.");
  else
    return student->second;
}

ostream &operator<< (ostream &str, Secretary &sec) {
  str << "|" << endl << "+-- Department Secretary Description --+" << endl;
  str << "| Department Name: " << sec.DepartmentName << endl;
  str << "| Department Code: " << sec.DepartmentCode << endl;
  str << "| ECT Diploma Requirement: " << sec.ECTRequirement << " ECTs" << endl;
  str << "| Years of Maximum Attendance: " << sec.MaximumAttendance << endl;
  str << "| Attending Students: " << sec.StudentIDDatabase.size() << endl;
  str << "+--------- End of Description ---------+" << endl;
  return str;
}

istream &operator>> (istream &str, Secretary &sec) {
  cout << "> Enter Department Name: ";
  getline(str, sec.DepartmentName);

  while (true) {
    cout << "> Enter Department Code: ";
    try {
      string Buffer;
      getline(str, Buffer);
      for (string::iterator itr = Buffer.begin(); itr != Buffer.end(); itr++)
        if (*itr < '0' || *itr > '9') throw(*itr);

      sec.DepartmentCode = stoi(Buffer);
      break;

    } catch(char InvalidChar) {
      cout << "! ERROR: Invalid Character '" << InvalidChar << "' inserted." << endl;
      continue;
    }
  }

  while (true) {
    cout << "> Enter Amount of ECTs Required for Department Diploma: ";
    try {
      string Buffer;
      getline(str, Buffer);
      for (string::iterator itr = Buffer.begin(); itr != Buffer.end(); itr++)
        if (*itr < '0' || *itr > '9') throw(*itr);

      sec.ECTRequirement = stoi(Buffer);
      break;

    } catch(char InvalidChar) {
      cout << "! ERROR: Invalid Character '" << InvalidChar << "' inserted." << endl;
      continue;
    }
  }

  while (true) {
    cout << "> Enter Maximum Years of Attendance: ";
    try {
      string Buffer;
      getline(str, Buffer);
      for (string::iterator itr = Buffer.begin(); itr != Buffer.end(); itr++)
        if (*itr < '0' || *itr > '9') throw(*itr);

      sec.MaximumAttendance = stoi(Buffer);
      break;
      
    } catch(char InvalidChar) {
      cout << "! ERROR: Invalid Character '" << InvalidChar << "' inserted." << endl;
      continue;
    }
  }
  
  return str;
}