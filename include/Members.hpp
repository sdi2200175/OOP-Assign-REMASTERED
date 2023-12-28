/*
 *  
 *  Members.hpp 
 * +------------------------------------------------------+
 *  This header defines the Person, Student and Professor
 *  classes stored within Secretary.
 * 
 * 
 * 
 * 
 */

#pragma once
#include <iostream>
using namespace std;

class Person {

    protected:
        string Name, Surname, FathersName, DateOfBirth, DateOfRegistration;
        const unsigned long UniversityID;

    public:

        /* - Constructors and Destructors - */
        Person(unsigned short DepartmentCode);
        Person(string Name, string Surname, string FathersName, string DateOfBirth, string DateOfRegistration, unsigned short DepartmentCode);
        virtual ~Person();

        /* - Getters - */
        inline string getName() const { return Name; }
        inline string getSurname() const { return Surname; }
        inline string getFathersName() const { return FathersName; }
        inline string getFullName() const { return Name + FathersName + Surname; }
        inline string getDateOfBirth() const { return DateOfBirth; }
        inline string getDateOfRegistration() const { return DateOfRegistration; }
        inline unsigned long getID() const { return UniversityID; }
        inline virtual string getFormattedID() const = 0;

        /* - Setters - */
        inline void setName(string Name) { this->Name = Name; }
        inline void setSurname(string Surname) { this->Surname = Surname; }
        inline void setFathersName(string FathersName) { this->FathersName = FathersName; }

        /* - '<<' and '>>' Operator Overloads - */
        friend ostream &operator<<(ostream &str, Person &per);
        friend istream &operator>>(istream &str, Person &per);
        
        /* - Counter - */
        static unsigned int RegisteredPersons;
};

/* - Student Subclass (of the Person class) - */

class Student : public Person {

    private:
        const string FormattedUniversityID;

    public:

        /* - Constructors and Destructors - */
        Student(unsigned short DepartmentCode);
        Student(string Name, string Surname, string FathersName, string DateOfBirth, string DateOfRegistration, unsigned short DepartmentCode);
        virtual ~Student();

        /* - Getters - */
        inline virtual string getFormattedID() const { return FormattedUniversityID; }

};

/* - Professor Subclass (of the Person class) - */

class Professor : public Person {

    private:
        const string FormattedUniversityID;

    public:

        /* - Constructors and Destructors - */
        Professor(unsigned short DepartmentCode);
        Professor(string Name, string Surname, string FathersName, string DateOfBirth, string DateOfRegistration, unsigned short DepartmentCode);
        virtual ~Professor();

        /* - Getters - */
        inline virtual string getFormattedID() const { return FormattedUniversityID; }
};  