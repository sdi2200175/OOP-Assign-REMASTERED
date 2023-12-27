#include "Course.hpp"

unsigned int Course::CreatedCourses = 0;

Course::Course(unsigned short DepartmentCode) : 
    CourseID(++CreatedCourses),
    FormattedCourseID("C-" + to_string(DepartmentCode) + "-" + string(5 - (to_string(CourseID)).length(), '0') + to_string(CourseID)) {

    cin >> *this;
    cout << "+- Created Course with Course ID: " << getFormattedID() << " -+" << endl;
}

Course::Course(string Name, bool Mandatory, unsigned short ECTs, unsigned short WeeklyHours, unsigned short DepartmentCode) :
    Name(Name), Mandatory(Mandatory), ECTs(ECTs), WeeklyHours(WeeklyHours), CourseID(++CreatedCourses),
    FormattedCourseID("C-" + to_string(DepartmentCode) + "-" + string(5 - (to_string(CourseID)).length(), '0') + to_string(CourseID)) {

    cout << "+- Created Course with Course ID: " << getFormattedID() << " -+" << endl;
}

Course::~Course() {}

ostream &operator<<(ostream &str, Course &cour) {
    str << "| Course Name: " << cour.Name << endl;
    str << "| This Course is " << (cour.Mandatory ? "mandatory." : "not mandatory.") << endl;
    str << "| Course ECTs: " << cour.ECTs << endl;
    str << "| Course Weekly Hours: " << cour.WeeklyHours << endl;
    str << "+- End of Description -+" << endl;
    return str;
}

istream &operator>>(istream &str, Course &cour) {
    cout << "| Insert Course Name: ";
    getline(str, cour.Name);
    
    cout << "| Is this Course going to be Mandatory? (Yes / No) ";
    string buffer;
    getline(str, buffer);
    if (!buffer.compare("Yes") || !buffer.compare("yes") || !buffer.compare("Y") || !buffer.compare("y")) {
        cour.Mandatory = true;
    } else {
        cour.Mandatory = false;
    }
    
    cout << "| Insert ECTs: ";
    getline(str, buffer);
    cour.ECTs = (unsigned short)stoi(buffer);
    
    cout << "| Insert Weekly Hours: ";
    getline(str, buffer);
    cour.WeeklyHours = (unsigned short)stoi(buffer);

    return str;
}
