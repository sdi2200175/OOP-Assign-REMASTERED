#include <iomanip>
#include "Members.hpp"

unsigned int Person::RegisteredPersons = 0;

Person::Person(unsigned short DepartmentCode) : 
    UniversityID(++RegisteredPersons) {

    cin >> *this;
}

Person::Person(string Name, string Surname, string FathersName, string DateOfBirth, string DateOfRegistration, unsigned short DepartmentCode) : 
    Name(Name), Surname(Surname), FathersName(FathersName), DateOfBirth(DateOfBirth), DateOfRegistration(DateOfRegistration), UniversityID(++RegisteredPersons) {}

Person::~Person() {}

ostream &operator<<(ostream &str, Person &per) {
    str << "Full Name: " << per.getFullName() << endl;
    str << "Date Of Birth: " << per.getDateOfBirth() << endl;
    str << "Date of Registration: " << per.getDateOfRegistration() << endl;
    str << "University ID: " << per.getFormattedID() << endl;
    str << "--- End of Description ---" << endl;
    return str;
}

istream &operator>>(istream &str, Person &per) {
    cout << "Insert First Name: ";
    getline(str, per.Name);

    cout << "Insert Surname: ";
    getline(str, per.Surname);

    cout << "Insert Father's Name: ";
    getline(str, per.FathersName);

    cout << "Insert Date of Birth: ";
    getline(str, per.DateOfBirth);
    
    cout << "Insert Date of Registration: ";
    getline(str, per.DateOfRegistration);
    return str;
}