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

#pragma once

#include <iostream>

using namespace std;

class Course {
        
    private:
        string Name;
        bool Mandatory;
        unsigned short ECTs;

        // const string CourseID 
    
    public:

        /* - Constructors and Destructors - */
        Course();
        Course(string Name, bool Mandatory, unsigned short ECTs);
        ~Course();

        /* - Getters - */
        inline const string &getName() const { return Name; }
        inline const bool &getMandatory() const { return Mandatory; }
        inline const unsigned short &getECTs() const { return ECTs; }

        // inline const string &getCourseID() const { return CourseID; }

        /* - Setters - */
        inline void setName(string Name) { this->Name = Name; }
        inline void setMandatory(bool Mandatory) { this->Mandatory = Mandatory; }
        inline void setECTs(unsigned short ECTs) { this->ECTs = ECTs; }

        /* - Operator Overloads - */
        friend ostream &operator<< (ostream &str, Course &course);
        friend istream &operator>> (istream &str, Course &course);

};