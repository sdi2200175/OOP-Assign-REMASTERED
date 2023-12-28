/*
 * 
 *  Course.hpp
 * +------------------------------------------------------+
 *  This header contains the definition for the Course
 *  class which is used to store information and methods
 *  related to managing the university courses professors
 *  are assigned and students are attending.
 * 
 * 
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
        unsigned short WeeklyHours;

        const unsigned int CourseID;
        const string FormattedCourseID;

    public:

        /* - Constructors and Destructors - */
        Course(unsigned short DepartmentCode);
        Course(string Name, bool Mandatory, unsigned short ECTs, unsigned short WeeklyHours, unsigned short DepartmentCode);
        ~Course();

        /* - Getters - */
        inline string getName() const { return Name; }
        inline bool isMandatory() const { return Mandatory; }
        inline unsigned short getECTs() const { return ECTs; }
        inline unsigned short getWeeklyHours() const { return WeeklyHours; }
        inline unsigned int getCourseID() const { return CourseID; }
        inline string getFormattedID() const { return FormattedCourseID; }

        /* - Setters - */
        inline void setMandatory(bool Mandatory) { this->Mandatory = Mandatory; }
        inline void setECTs(unsigned short ECTs) { this->ECTs = ECTs; }
        inline void setWeeklyHours(unsigned short WeeklyHours) { this->WeeklyHours = WeeklyHours; }

        /* - '<<' and '>>' Operator Overloads - */
        friend ostream &operator<<(ostream &str, Course &cour);
        friend istream &operator>>(istream &str, Course &cour);

        /* - Counter - */
        static unsigned int CreatedCourses;
};