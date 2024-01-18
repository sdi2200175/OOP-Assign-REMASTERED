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
#include <map>
#include "professor.hpp"
#include "student.hpp"

using namespace std;

class Course {
        
    private:
        string Name;
        bool Mandatory;
        unsigned short ECTs;
        const unsigned int CourseID; 

        const string FormattedCourseID;

        map<unsigned int, Professor*> AssignedProfessorsIDDatabase;
        map<string, Professor*> AssignedProfessorsNameDatabase;
    
        map<unsigned int, Student*> AttendingStudentsIDDatabase;
        map<string, Student*> AttendingStudentsNameDatabase;

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

        /* - Professor Assignment - */
        void addProfessorToAssignedProfessorsDatabase(Professor *professor);
        void removeProfessorFromAssignedProfessorsDatabase(Professor *professor);

        /* - Operator Overloads - */
        friend ostream &operator<< (ostream &str, Course &course);
        friend istream &operator>> (istream &str, Course &course);

        /* - Static Universal Counter - */
        static unsigned int CourseAmount;

};