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

        map<unsigned long, Person*> MemberIDDatabase;
        multimap<string, Person*> MemberFullNameDatabase;

        map<unsigned int, Course*> CourseIDDatabase;

    public:

// TODO - Make the methods within the Secretary Class
        /* - Constructors and Destructors - */
        Secretary();
//         Secretary(Secretary &sec);
//         Secretary(string DepartmentName, unsigned short DepartmentCode);
//         ~Secretary();

        /* - Getters - */
        inline string getDepartmentName() const { return DepartmentName; }
        inline unsigned short getDepartmentCode() const { return DepartmentCode; }
        inline unsigned int getMemberAmount() const { return MemberIDDatabase.size(); }
        inline unsigned int getCourseAmount() const { return CourseIDDatabase.size(); }

        /* - Search Functions - */
//         Person* memberSearch(string FullName) const;
//         Person* memberSearch(unsigned long ID) const;

//         Course* courseSearch(unsigned int ID) const;

        /* - Operator Overloads - */
//         Secretary operator=(Secretary &sec);
        friend ostream &operator<<(ostream &str, Secretary &sec);
        friend istream &operator>>(istream &str, Secretary &sec);
};