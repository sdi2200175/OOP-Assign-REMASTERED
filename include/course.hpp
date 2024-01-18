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
        const unsigned int CourseID; 

        const string FormattedCourseID;
    
    public:

        /* - Constructors and Destructors - */
        Course(unsigned short DepartmentCode);
        Course(string Name, bool Mandatory, unsigned short ECTs, unsigned short DepartmentCode);
        ~Course();

        /* - Getters - */
        inline const string &getName() const { return Name; }
        inline const bool &getMandatory() const { return Mandatory; }
        inline const unsigned short &getECTs() const { return ECTs; }
        inline const unsigned int &getCourseID() const { return CourseID; }

        inline const string &getFormattedCourseID() const { return FormattedCourseID; }

        /* - Setters - */
        inline void setName(string Name) { this->Name = Name; }
        inline void setMandatory(bool Mandatory) { this->Mandatory = Mandatory; }
        inline void setECTs(unsigned short ECTs) { this->ECTs = ECTs; }

        /* - Operator Overloads - */
        friend ostream &operator<< (ostream &str, Course &course);
        friend istream &operator>> (istream &str, Course &course);

        /* - Static Universal Counter - */
        static unsigned int CourseAmount;

};