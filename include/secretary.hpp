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

#include <iostream>

using namespace std;

class Secretary {

  private:
    string DepartmentName;
    unsigned int DepartmentCode;
    unsigned int ECTRequirement;
    unsigned short MaximumAttendance;

  public:

    /* - Constructors and Destructors - */
    Secretary();
    // Secretary(string DepartmentName, unsigned int DepartmentCode, unsigned int ECTRequirements, unsigned short MaximumAttendance);

    /* - Operator Overloads - */
    friend ostream &operator<< (ostream &str, Secretary &sec);
    friend istream &operator>> (istream &str, Secretary &sec);

};