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

ostream &operator<< (ostream &str, Secretary &sec) {
  str << "|" << endl << "+-- Department Secretary Description --+" << endl;
  str << "| Department Name: " << sec.DepartmentName << endl;
  str << "| Department Code: " << sec.DepartmentCode << endl;
  str << "| ECT Diploma Requirement: " << sec.ECTRequirement << " ECTs" << endl;
  str << "| Years of Maximum Attendance: " << sec.MaximumAttendance << endl;
  str << "+--------- End of Description ---------+" << endl << "|" << endl;
  return str;
}

istream &operator>> (istream &str, Secretary &sec) {
  cout << "- Enter Department Name: ";
  getline(str, sec.DepartmentName);

  cout << "- Enter Department Code: ";
  while (true) {
    try {
      string Buffer;
      getline(str, Buffer);
      for (string::iterator itr = Buffer.begin(); itr != Buffer.end(); itr++)
        if (*itr < '0' || *itr > '9') throw(*itr);

      sec.DepartmentCode = stoi(Buffer);
      break;

    } catch(char InvalidChar) {
      cout << "! ERROR: Invalid Character '" << InvalidChar << "' inserted." << endl << "- Please insert a valid Department Code: ";
    }
  }

  cout << "- Enter Amount of ECTs Required for Department Diploma: ";
  while (true) {
    try {
      string Buffer;
      getline(str, Buffer);
      for (string::iterator itr = Buffer.begin(); itr != Buffer.end(); itr++)
        if (*itr < '0' || *itr > '9') throw(*itr);

      sec.ECTRequirement = stoi(Buffer);
      break;

    } catch(char InvalidChar) {
      cout << "! ERROR: Invalid Character '" << InvalidChar << "' inserted." << endl << "- Please insert a valid Amount of ECTs Required: ";
    }
  }

  cout << "- Enter Maximum Years of Attendance: ";
  while (true) {
    try {
      string Buffer;
      getline(str, Buffer);
      for (string::iterator itr = Buffer.begin(); itr != Buffer.end(); itr++)
        if (*itr < '0' || *itr > '9') throw(*itr);

      sec.MaximumAttendance = stoi(Buffer);
      break;
      
    } catch(char InvalidChar) {
      cout << "! ERROR: Invalid Character '" << InvalidChar << "' inserted." << endl << "- Please insert a valid Amount of Years for Maximum Attendance: ";
    }
  }
  
  return str;
}
