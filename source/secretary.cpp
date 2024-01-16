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
  cout << "|" << endl << "+---- Department Secretary Details ----+" << endl;
  cin >> *this;
  cout << "+-- Constructed Department Secretary --+" << endl;
}

void Secretary::addStudent() {
  Student *student = new Student(this->DepartmentCode);
  StudentIDDatabase.insert(make_pair(student->getUniID(), student));
  StudentNameDatabase.insert(make_pair(student->getName(), student));
}

void Secretary::modifyStudent() {
  cout << "| Please enter the Name or University ID of the Student you want to modify below: ";

  string Buffer;
  getline(cin, Buffer);
  
}

void Secretary::deleteStudent() {
  cout << "| Please enter the Name or University ID of the Student you want to delete below: ";
  string Buffer;
  getline(cin, Buffer);
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
