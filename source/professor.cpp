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
    FormattedUniID("P-" + to_string(DepartmentCode) + "-" + string(10 - (to_string(getUniID())).length(), '0') + to_string(getUniID())) {
    
    cout << "+- Constructed Professor with University ID: " << getFormattedID() << " -+" << endl;
}

Professor::~Professor() {}

ostream &operator<< (ostream &str, Professor &professor) {
    str << "| Full Name: " << professor.getName() << endl;
    str << "| University ID: " << professor.FormattedUniID << endl;
    return str;
}