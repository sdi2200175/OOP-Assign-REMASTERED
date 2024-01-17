/**
 * @file professor.hpp
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
#include "person.hpp"

using namespace std;

class Professor : public Person {
    
    private:
        const string FormattedUniID;

    public:

        /* - Constructors and Destructors - */
        Professor(unsigned short DepartmentCode);
        Professor(string Name, unsigned short DepartmentCode);
        ~Professor();

        /* - Pure Virtual Function - */
        inline virtual const string &getFormattedID() const { return FormattedUniID; }

        /* - Operator Overloads - */
        friend ostream &operator<< (ostream &str, Professor &professor);
        friend istream &operator>> (istream &str, Professor &professor);

};