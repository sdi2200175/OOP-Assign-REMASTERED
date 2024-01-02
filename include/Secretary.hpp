/*
 * 
 *  Secretary.hpp
 * +------------------------------------------------------+
 *  This file defines a Secretary class that manages all 
 *  Person and Course type objects.
 * 
 * 
 */

#pragma once
#include <map>
#include <iostream>

#include "Course.hpp"
#include "Members.hpp"

using namespace std;

class Secretary {

    private:
        string DepartmentName;
        unsigned short DepartmentCode;

        map<unsigned long, Student*> StudentIDDatabase;
        multimap<string, Student*> StudentFullNameDatabase;

        map<unsigned long, Professor*> ProfessorIDDatabase;
        multimap<string, Professor*> ProfessorFullNameDatabase;

        map<unsigned int, Course*> CourseIDDatabase;
        map<string, Course*> CourseNameDatabase;

    public:

// TODO - Make the methods within the Secretary Class
        /* - Constructors and Destructors - */
        Secretary();
//         Secretary(Secretary &sec);
//         Secretary(string DepartmentName, unsigned short DepartmentCode);
        ~Secretary();

        /* - Getters - */
        inline string getDepartmentName() const { return DepartmentName; }
        inline unsigned short getDepartmentCode() const { return DepartmentCode; }
        inline unsigned int getStudentAmount() const { return StudentIDDatabase.size(); }
        inline unsigned int getProfessorAmount() const { return ProfessorIDDatabase.size(); }
        inline unsigned int getCourseAmount() const { return CourseIDDatabase.size(); }

        /* - Search Functions - */
        Student* studentSearch(string FullName) const;
        Student* studentSearch(unsigned long ID) const;

        Professor* professorSearch(string FullName) const;
        Professor* professorSearch(unsigned long ID) const;

        Course* courseSearch(string CourseName) const;
        Course* courseSearch(unsigned int ID) const;
    

        void parseStudents(const string FileName);
        void parseProfessors(const string FileName);
        void parseCourses(const string FileName);

        /* - Operator Overloads - */
//         Secretary operator=(Secretary &sec);
        friend ostream &operator<<(ostream &str, Secretary &sec);
        friend istream &operator>>(istream &str, Secretary &sec);
};