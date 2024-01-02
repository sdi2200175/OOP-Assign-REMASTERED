#include <fstream>
#include <algorithm>
#include "Secretary.hpp"

Secretary::Secretary() {
    cout << "+- Constructing new University Secretary... -+" << endl;
    cin >> *this;
    cout << "+- Created Secretary for Department of " << DepartmentName << " with Department Code: " << DepartmentCode << " -+" << endl;
}

Secretary::~Secretary() {

    for (map<unsigned long, Student*>::iterator itr = StudentIDDatabase.begin(); itr != StudentIDDatabase.end(); itr++)
        delete itr->second;

    for (map<unsigned long, Professor*>::iterator itr = ProfessorIDDatabase.begin(); itr != ProfessorIDDatabase.end(); itr++) 
        delete itr->second;

    for (map<unsigned int, Course*>::iterator itr = CourseIDDatabase.begin(); itr != CourseIDDatabase.end(); itr++)
        delete itr->second;
}

Student *Secretary::studentSearch(string FullName) const {

    multimap<string, Student*>::const_iterator per = StudentFullNameDatabase.find(FullName);
    if (per != StudentFullNameDatabase.end())
        return per->second;

    return nullptr;
}

Student *Secretary::studentSearch(unsigned long ID) const {

    map<unsigned long, Student*>::const_iterator per = StudentIDDatabase.find(ID);
    if (per != StudentIDDatabase.end())
        return per->second;

    return nullptr;
}

Course *Secretary::courseSearch(unsigned int ID) const
{
    return nullptr;
}

void Secretary::parseStudents(const string FileName)
{

    string Buffer;
    ifstream File(FileName);

    string Name, Surname, FathersName, DateOfBirth, DateOfRegistration;

    while(getline(File, Buffer)) {
        
        if (Buffer[0] == '{') continue;
        if (Buffer[0] == '}') {
            Student *student = new Student(Name, Surname, FathersName, DateOfBirth, DateOfRegistration, DepartmentCode);
            StudentIDDatabase.insert(make_pair(student->getID(), student));
            StudentFullNameDatabase.insert(make_pair(student->getFullName(), student));
            Name.clear();
            Surname.clear();
            FathersName.clear();
            DateOfBirth.clear();
            DateOfRegistration.clear();
            continue;
        }

        Buffer.erase(remove(Buffer.begin(), Buffer.end(), ' '), Buffer.end());  // We erase all spaces.

        string VariableNameBuffer;
        string::iterator itr;
        for (itr = Buffer.begin(); *itr != ':'; itr++)
            VariableNameBuffer.insert(VariableNameBuffer.end(), *itr);

        if (!VariableNameBuffer.compare("Name")) {
            for (itr += 2; *itr != '"'; itr++)
                Name.insert(Name.end(), *itr);

        } else if(!VariableNameBuffer.compare("Surname")){
            for (itr += 2; *itr != '"'; itr++)
                Surname.insert(Surname.end(), *itr);

        } else if(!VariableNameBuffer.compare("FathersName")){
            for (itr += 2; *itr != '"'; itr++)
                FathersName.insert(FathersName.end(), *itr);

        } else if(!VariableNameBuffer.compare("DateOfBirth")){
            for (itr += 2; *itr != '"'; itr++)
                DateOfBirth.insert(DateOfBirth.end(), *itr);

        } else if(!VariableNameBuffer.compare("DateOfRegistration")){
            for (itr += 2; *itr != '"'; itr++)
                DateOfRegistration.insert(DateOfRegistration.end(), *itr);
        }
    }

    File.close();
}

void Secretary::parseProfessors(const string FileName) {

    string Buffer;
    ifstream File(FileName);

    string Name, Surname, FathersName, DateOfBirth, DateOfRegistration;

    while(getline(File, Buffer)) {
        
        if (Buffer[0] == '{') continue;
        if (Buffer[0] == '}') {
            Professor *professor = new Professor(Name, Surname, FathersName, DateOfBirth, DateOfRegistration, DepartmentCode);
            ProfessorIDDatabase.insert(make_pair(professor->getID(), professor));
            ProfessorFullNameDatabase.insert(make_pair(professor->getFullName(), professor));
            Name.clear();
            Surname.clear();
            FathersName.clear();
            DateOfBirth.clear();
            DateOfRegistration.clear();
            continue;
        }

        Buffer.erase(remove(Buffer.begin(), Buffer.end(), ' '), Buffer.end());  // We erase all spaces.

        string VariableNameBuffer;
        string::iterator itr;
        for (itr = Buffer.begin(); *itr != ':'; itr++)
            VariableNameBuffer.insert(VariableNameBuffer.end(), *itr);

        if (!VariableNameBuffer.compare("Name")) {
            for (itr += 2; *itr != '"'; itr++)
                Name.insert(Name.end(), *itr);

        } else if(!VariableNameBuffer.compare("Surname")){
            for (itr += 2; *itr != '"'; itr++)
                Surname.insert(Surname.end(), *itr);

        } else if(!VariableNameBuffer.compare("FathersName")){
            for (itr += 2; *itr != '"'; itr++)
                FathersName.insert(FathersName.end(), *itr);

        } else if(!VariableNameBuffer.compare("DateOfBirth")){
            for (itr += 2; *itr != '"'; itr++)
                DateOfBirth.insert(DateOfBirth.end(), *itr);

        } else if(!VariableNameBuffer.compare("DateOfRegistration")){
            for (itr += 2; *itr != '"'; itr++)
                DateOfRegistration.insert(DateOfRegistration.end(), *itr);
        }
    }

    File.close();
}

void Secretary::parseCourses(const string FileName) {

    string Buffer;
    ifstream File(FileName);

    string Name, MandatoryString, ECTsString, WeeklyHoursString, SemesterString;
    bool Mandatory;
    unsigned short ECTs, WeeklyHours, Semester;

    while(getline(File, Buffer)) {
        
        if (Buffer[0] == '{') continue;
        if (Buffer[0] == '}') {
            Course *course = new Course(Name, Mandatory, ECTs, WeeklyHours, Semester, DepartmentCode);
            CourseIDDatabase.insert(make_pair(course->getCourseID(), course));
            CourseNameDatabase.insert(make_pair(course->getName(), course));
            Name.clear();
            MandatoryString.clear();
            ECTsString.clear();
            WeeklyHoursString.clear();
            SemesterString.clear();
            continue;
        }

        Buffer.erase(remove(Buffer.begin(), Buffer.end(), ' '), Buffer.end());  // We erase all spaces.

        string VariableNameBuffer;
        string::iterator itr;
        for (itr = Buffer.begin(); *itr != ':'; itr++)
            VariableNameBuffer.insert(VariableNameBuffer.end(), *itr);

        if (!VariableNameBuffer.compare("Name")) {
            for (itr += 2; *itr != '"'; itr++)
                Name.insert(Name.end(), *itr);

        } else if(!VariableNameBuffer.compare("Mandatory")){
            for (itr += 2; *itr != '"'; itr++)
                MandatoryString.insert(MandatoryString.end(), *itr);

            if (!MandatoryString.compare("Yes"))
                Mandatory = true;
            else if (!MandatoryString.compare("No"))
                Mandatory = false;

        } else if (!VariableNameBuffer.compare("ECTs")) {
            for (itr++; *itr != EOF; itr++)
                ECTsString.insert(ECTsString.end(), *itr);
            ECTs = (unsigned short)stoi(ECTsString);

        } else if (!VariableNameBuffer.compare("WeeklyHours")) {
            for (itr++; *itr != EOF; itr++)
                WeeklyHoursString.insert(WeeklyHoursString.end(), *itr);
            WeeklyHours = (unsigned short)stoi(WeeklyHoursString);
        
        } else if (!VariableNameBuffer.compare("Semester")) {
            for (itr++; *itr != EOF; itr++)
                SemesterString.insert(SemesterString.end(), *itr);
            Semester = (unsigned short)stoi(SemesterString);
        }
    }

    File.close();
}

ostream &operator<<(ostream &str, Secretary &sec) {
    str << "+- Start of Secretary Description -+" << endl;
    str << "| Secretary Department Name: " << sec.DepartmentName << endl;
    str << "| Secretary Department Code: " << sec.DepartmentCode << endl;
    str << "| This Secretary manages " << sec.getStudentAmount() << " Students, " << sec.getProfessorAmount() << " Professors and " << sec.getCourseAmount() << " Courses." << endl;
    str << "+- End of Secretary Description -+" << endl;
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
