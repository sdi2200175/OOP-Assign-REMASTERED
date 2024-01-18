/**
 * @file student.hpp
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

class Student : public Person {
    
    private:
        unsigned int ECTs;
        string DateOfBirth, DateOfRegistration;
    
        const string FormattedUniID;

        map<unsigned int, Course*> CompletedCoursesIDDatabase;
        map<string, Course*> CompletedCoursesNameDatabase;

    public:

        /* - Constructors and Destructors - */
        Student(unsigned short DepartmentCode);
        Student(string Name, unsigned int ECTs, string DateOfBirth, string DateOfRegistration, unsigned short DepartmentCode);
        ~Student();

        /* - Getters - */
        inline const unsigned int &getECTs() const { return ECTs; }
        inline const string &getDateOfBirth() const { return DateOfBirth; }
        inline const string &getDateOfRegistration() const { return DateOfRegistration; }

        /* - Setters - */
        inline void setECTs(unsigned int ECTs) { this->ECTs = ECTs; }
        inline void setDateOfBirth(string DateOfBirth) { this->DateOfBirth = DateOfBirth; }
        inline void setDateOfRegistration(string DateofRegistration) { this->DateOfRegistration = DateOfRegistration; }

        /* - Pure Virtual Function - */
        inline virtual const string &getFormattedID() const { return FormattedUniID; }

        /* - Operator Overloads - */
        friend ostream &operator<< (ostream &str, Student &student);
        friend istream &operator>> (istream &str, Student &student);

};