/**
 * @file secretary.hpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief 
 * @version 
 * @date 2024-01-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <map>
#include <iostream>

#include "student.hpp"

using namespace std;

class Secretary {

  private:
    string DepartmentName;
    unsigned int DepartmentCode, ECTRequirement;
    unsigned short MaximumAttendance;

    map<unsigned int, Student*> StudentIDDatabase;
    map<string, Student*> StudentNameDatabase;

  public:

    /* - Constructors and Destructors - */
    Secretary();
    // Secretary(string DepartmentName, unsigned int DepartmentCode, unsigned int ECTRequirement, unsigned short MaximumAttendance);

    /* - Getters - */
    inline const string &getDepartmentName() { return DepartmentName; }
    inline unsigned int getDepartmentCode() { return DepartmentCode; }
    inline unsigned int getECTRequirement() {return ECTRequirement; }  
    inline unsigned short getMaximumAttendance() { return MaximumAttendance; }

    /* - Student Management - */
    void addStudent();
    void addStudentToDatabase(Student *student);
    void deleteStudent(Student *student);
    void removeStudentFromDatabase(Student *student);
  
    Student *retrieveStudent(unsigned int UniID);
    Student *retrieveStudent(const string &Name);

    /* - Operator Overloads - */
    friend ostream &operator<< (ostream &str, Secretary &sec);
    friend istream &operator>> (istream &str, Secretary &sec);
};