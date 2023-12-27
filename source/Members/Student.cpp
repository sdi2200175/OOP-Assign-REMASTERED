#include "Members.hpp"

Student::Student(unsigned short DepartmentCode) : 
    Person(DepartmentCode),
    FormattedUniversityID("S-" + to_string(DepartmentCode) + "-" + string(10 - (to_string(UniversityID)).length(), '0') + to_string(UniversityID)) {
    
    cout << "+- Created Student with University ID: " << getFormattedID() << " -+" << endl;
}

Student::Student(string Name, string Surname, string FathersName, string DateOfBirth, string DateOfRegistration, unsigned short DepartmentCode) :
    Person(Name, Surname, FathersName, DateOfBirth, DateOfRegistration, DepartmentCode),
    FormattedUniversityID("S-" + to_string(DepartmentCode) + "-" + string(10 - (to_string(UniversityID)).length(), '0') + to_string(UniversityID)) {

    cout << "+- Created Student with University ID: " << getFormattedID() << " -+" << endl;

}

Student::~Student() {}
