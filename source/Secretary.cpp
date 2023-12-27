#include "Secretary.hpp"

Secretary::Secretary() {
    cin >> *this;
    cout << "+- Created Secretary for Department of " << DepartmentName << " with Department Code: " << DepartmentCode << " -+" << endl;
}

ostream &operator<<(ostream &str, Secretary &sec) {
    str << "| Secretary Department Name: " << sec.DepartmentName << endl;
    str << "| Secretary Department Code: " << sec.DepartmentCode << endl;
    str << "| This Secretary contains " << sec.getMemberAmount() << " Members and " << sec.getCourseAmount() << " available Courses." << endl;
    str << "+- End of Description -+" << endl;
    return str;
}

istream &operator>>(istream &str, Secretary &sec) {
    cout << "| Insert Secretary Department Name: ";
    getline(str, sec.DepartmentName);

    cout << "| Insert Secretary Department Code: ";
    string buffer;
    getline(str, buffer);
    sec.DepartmentCode = (unsigned short)stoi(buffer);

    return str;
}
