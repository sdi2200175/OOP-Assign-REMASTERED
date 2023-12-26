#include "Members.hpp"

Professor::Professor(unsigned short DepartmentCode) : 
    Person(DepartmentCode),
    FormattedUniversityID("P-" + to_string(DepartmentCode) + "-" + string(10 - (to_string(UniversityID)).length(), '0') + to_string(UniversityID)) {
    
    cout << "--- Created Professor with University ID: " << getFormattedID() << " ---" << endl;
}

Professor::Professor(string Name, string Surname, string FathersName, string DateOfBirth, string DateOfRegistration, unsigned short DepartmentCode) :
    Person(Name, Surname, FathersName, DateOfBirth, DateOfRegistration, DepartmentCode),
    FormattedUniversityID("P-" + to_string(DepartmentCode) + "-" + string(10 - (to_string(UniversityID)).length(), '0') + to_string(UniversityID)) {

    cout << "--- Created Professor with University ID: " << getFormattedID() << " ---" << endl;

}

Professor::~Professor() {}
