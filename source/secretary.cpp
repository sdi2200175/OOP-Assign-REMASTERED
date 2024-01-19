/**
 * @file secretary.cpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief 
 * @version 
 * @date 2024-01-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "secretary.hpp"

Secretary::Secretary() : Semester(Fall) {
  cin >> *this;
}

Secretary::Secretary(string DepartmentName, unsigned int DepartmentCode, unsigned int ECTRequirement, unsigned short MaximumAttendance) : 
  DepartmentName(DepartmentName), DepartmentCode(DepartmentCode), ECTRequirement(ECTRequirement), MaximumAttendance(MaximumAttendance), Semester(Fall) {}

Secretary::~Secretary() {

  for (map<unsigned int, Student*>::iterator itr = this->StudentIDDatabase.begin(); 
      itr != this->StudentIDDatabase.end(); itr++) {

      delete itr->second;
  }
}

/* - Student Management - */

void Secretary::addStudent() {
  Student *student = new Student(this->DepartmentCode);
  this->addStudentToDatabase(student);
}

void Secretary::addStudentToDatabase(Student *student) {
  this->StudentIDDatabase.insert(make_pair(student->getUniID(), student));
  this->StudentNameDatabase.insert(make_pair(student->getName(), student));
}

void Secretary::deleteStudent(Student *student) {
  this->removeStudentFromDatabase(student);
  delete student;
}

void Secretary::removeStudentFromDatabase(Student *student) {
  this->StudentIDDatabase.erase(student->getUniID());
  this->StudentNameDatabase.erase(student->getName());
}

/**
 * @brief Searches for a Student in the Secretary.
 * 
 * @param UniID Search Term.
 * @return A pointer to the Student that was found.
 * @exception Throws an invalid_argument exception if the Student was not found in the secretary.
 */
Student *Secretary::retrieveStudent(unsigned int UniID) {
  map<unsigned int, Student*>::iterator student = this->StudentIDDatabase.find(UniID);
  if (student == this->StudentIDDatabase.end())
    throw invalid_argument("! ERROR: Student with University ID: S-" + to_string(this->DepartmentCode) + "-" + 
                            string(6 - (to_string(UniID)).length(), '0') + to_string(UniID) + " wasn't found.");
  else
    return student->second;
}

/**
 * @brief Searches for a Student in the Secretary.
 * 
 * @param Name Search Term.
 * @return A pointer to the Student that was found.
 * @exception Throws and invalid_argument exception if the Student was not found in the Secretary.
 */
Student *Secretary::retrieveStudent(const string &Name) {
  map<string, Student*>::iterator student = this->StudentNameDatabase.find(Name);
  if (student == this->StudentNameDatabase.end())
    throw invalid_argument("! ERROR: Student named '" + Name + " wasn't found.");
  else
    return student->second;
}

/* - Professor Management - */

void Secretary::addProfessor() {
  Professor *professor = new Professor(this->DepartmentCode);
  this->addProfessorToDatabase(professor);
}

void Secretary::addProfessorToDatabase(Professor *professor) {
  this->ProfessorIDDatabase.insert(make_pair(professor->getUniID(), professor));
  this->ProfessorNameDatabase.insert(make_pair(professor->getName(), professor));
}

void Secretary::deleteProfessor(Professor *professor) {
  this->removeProfessorFromDatabase(professor);
  delete professor;
}

void Secretary::removeProfessorFromDatabase(Professor *professor) {
  this->ProfessorIDDatabase.erase(professor->getUniID());
  this->ProfessorNameDatabase.erase(professor->getName());
}

/**
 * @brief Searches for a Professor in the Secretary.
 * 
 * @param UniID Search Term.
 * @return A pointer to the Professor that was found.
 * @exception Throws an invalid_argument exception if the Professor was not found in the secretary.
 */
Professor *Secretary::retrieveProfessor(unsigned int UniID) {
  map<unsigned int, Professor*>::iterator professor = this->ProfessorIDDatabase.find(UniID);
  if (professor == this->ProfessorIDDatabase.end())
    throw invalid_argument("! ERROR: Professor with University ID: P-" + to_string(this->DepartmentCode) + "-" + 
                            string(6 - (to_string(UniID)).length(), '0') + to_string(UniID) + " wasn't found.");
  else
    return professor->second;
}

/**
 * @brief Searches for a Professor in the Secretary.
 * 
 * @param Name Search Term.
 * @return A pointer to the Professor that was found.
 * @exception Throws and invalid_argument exception if the Professor was not found in the Secretary.
 */
Professor *Secretary::retrieveProfessor(const string &Name) {
  map<string, Professor*>::iterator professor = this->ProfessorNameDatabase.find(Name);
  if (professor == this->ProfessorNameDatabase.end())
    throw invalid_argument("! ERROR: Professor named '" + Name + " wasn't found.");
  else
    return professor->second;
}

/* - Course Management - */

void Secretary::addCourse() {
  Course *course = new Course(this->DepartmentCode);
  this->addCourseToDatabase(course);
}

void Secretary::addCourseToDatabase(Course *course) {
  this->CourseIDDatabase.insert(make_pair(course->getCourseID(), course));
  this->CourseNameDatabase.insert(make_pair(course->getName(), course));
}

void Secretary::deleteCourse(Course *course) {
  this->removeCourseFromDatabase(course);
  delete course;
}

void Secretary::removeCourseFromDatabase(Course *course) {
  this->CourseIDDatabase.erase(course->getCourseID());
  this->CourseNameDatabase.erase(course->getName());
}

/**
 * @brief Searches for a Course in the Secretary.
 * 
 * @param CourseID Search Term.
 * @return A pointer to the Course that was found.
 * @exception Throws an invalid_argument exception if the Course was not found in the secretary.
 */
Course *Secretary::retrieveCourse(unsigned int CourseID) {
  map<unsigned int, Course*>::iterator course = this->CourseIDDatabase.find(CourseID);
  if (course == this->CourseIDDatabase.end())
    throw invalid_argument("! ERROR: Course with University ID: C-" + to_string(this->DepartmentCode) + "-" + 
                            string(6 - (to_string(CourseID)).length(), '0') + to_string(CourseID) + " wasn't found.");
  else
    return course->second;
}

/**
 * @brief Searches for a Course in the Secretary.
 * 
 * @param Name Search Term.
 * @return A pointer to the Course that was found.
 * @exception Throws and invalid_argument exception if the Course was not found in the Secretary.
 */
Course *Secretary::retrieveCourse(const string &Name) {
  map<string, Course*>::iterator course = this->CourseNameDatabase.find(Name);
  if (course == this->CourseNameDatabase.end())
    throw invalid_argument("! ERROR: Course named '" + Name + " wasn't found.");
  else
    return course->second;
}

ostream &operator<< (ostream &str, Secretary &sec) {
  str << "|" << endl << "+-- Department Secretary Description --+" << endl;
  str << "| Department Name: " << sec.DepartmentName << endl;
  str << "| Department Code: " << sec.DepartmentCode << endl;
  str << "| ECT Diploma Requirement: " << sec.ECTRequirement << " ECTs" << endl;
  str << "| Years of Maximum Attendance: " << sec.MaximumAttendance << endl;
  str << "| Attending Students: " << sec.StudentIDDatabase.size() << endl;
  str << "| Attending Professors: " << sec.ProfessorIDDatabase.size() << endl;
  str << "+--------- End of Description ---------+" << endl;
  return str;
}

istream &operator>> (istream &str, Secretary &sec) {
  cout << "> Enter Department Name: ";
  getline(str, sec.DepartmentName);

  while (true) {
    cout << "> Enter Department Code: ";
    try {
      string Buffer;
      getline(str, Buffer);
      for (string::iterator itr = Buffer.begin(); itr != Buffer.end(); itr++)
        if (*itr < '0' || *itr > '9') throw(*itr);

      sec.DepartmentCode = stoi(Buffer);
      break;

    } catch(char InvalidChar) {
      cout << "! ERROR: Invalid Character '" << InvalidChar << "' inserted." << endl;
      continue;
    }
  }

  while (true) {
    cout << "> Enter Amount of ECTs Required for Department Diploma: ";
    try {
      string Buffer;
      getline(str, Buffer);
      for (string::iterator itr = Buffer.begin(); itr != Buffer.end(); itr++)
        if (*itr < '0' || *itr > '9') throw(*itr);

      sec.ECTRequirement = stoi(Buffer);
      break;

    } catch(char InvalidChar) {
      cout << "! ERROR: Invalid Character '" << InvalidChar << "' inserted." << endl;
      continue;
    }
  }

  while (true) {
    cout << "> Enter Maximum Years of Attendance: ";
    try {
      string Buffer;
      getline(str, Buffer);
      for (string::iterator itr = Buffer.begin(); itr != Buffer.end(); itr++)
        if (*itr < '0' || *itr > '9') throw(*itr);

      sec.MaximumAttendance = stoi(Buffer);
      break;
      
    } catch(char InvalidChar) {
      cout << "! ERROR: Invalid Character '" << InvalidChar << "' inserted." << endl;
      continue;
    }
  }
  
  return str;
}