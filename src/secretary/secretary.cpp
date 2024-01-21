/**
 * @file secretary.cpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief 
 * @version 0.1
 * @date 2024-01-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "secretary.hpp"
#include "validation.hpp"

/**
 * @brief Construct a new secretary object by requesting input from the user directly
 * 
 */
secretary::secretary() {
  std::cin >> *this;
  std::cout << "|-- Created Secretary For Department of " << this->department_name << " --|" << std::endl;
}

/**
 * @brief Construct a new secretary object without requesting user input directly.
 * 
 * @param department_name The name of the department managed by the secretary object.
 * @param department_code The code of the department managed by the secretary object.
 * @param maximum_attendance The maximum amount of years one can attend the department managed by the secretary object.
 * @param regular_attendance The required amount of years one has to attend the department in order to get their diploma.
 * @param required_ects The ects required by an attendee of the department managed by the secretary object to graduate.
 * @param mandatory_courses The amount of courses in the department managed by the secretary object that are needed for graduation.
 */
secretary::secretary(const std::string &department_name, unsigned short department_code, unsigned short regular_attendance, unsigned short maximum_attendance, 
  unsigned short required_ects, unsigned short mandatory_courses) : department_name(department_name), department_code(department_code),
  maximum_attendance(maximum_attendance), required_ects(required_ects), mandatory_courses(mandatory_courses) {

  std::cout << "|-- Created Secretary For Department of " << this->department_name << " --|" << std::endl;
}

/**
 * @brief Destroy the secretary object
 * 
 */
secretary::~secretary() {

  for (std::map<unsigned int, person*>::iterator itr = this->uni_id_database.begin();
      itr != this->uni_id_database.end(); itr++) {

      if (((professor *)itr->second)->getFormattedUniID()[0] != 'P')
        delete (student *)itr->second;
      else
        delete (professor *)itr->second;  
  }

  for (std::map<unsigned int, course*>::iterator itr = this->uni_id_course_database.begin();
      itr != this->uni_id_course_database.end(); itr++) {

    delete itr->second;  
  }

}


/* - Student Management - */


/**
 * @brief Creates a student using the direct user input constructor and adds it to the university databases.
 * 
 */
void secretary::createStudent() {
  student *new_student = new student(this->department_code);
  this->uni_id_database.insert(std::make_pair(new_student->getUniID(), new_student));
  this->uni_name_database.insert(std::make_pair(new_student->getName(), new_student));
}

void secretary::addStudent(student *student) {
  this->uni_id_database.insert(std::make_pair(student->getUniID(), student));
  this->uni_name_database.insert(std::make_pair(student->getName(), student));
}

student *secretary::retrieveStudent(unsigned int uni_id) {
  std::map<unsigned int, person*>::iterator itr = this->uni_id_database.find(uni_id);
  if (itr != this->uni_id_database.end())
    if (((professor *)itr->second)->getFormattedUniID()[0] != 'P')
      return (student *)itr->second;
  
  return nullptr;
}

student *secretary::retrieveStudent(const std::string &name) {
  std::multimap<std::string, person*>::iterator itr = this->uni_name_database.find(name);
  if (itr != this->uni_name_database.end())
    if (((professor *)itr->second)->getFormattedUniID()[0] != 'P')
      return (student *)itr->second;
    
  return nullptr;
}

/**
 * @brief Searches for and deletes a student.
 * 
 * @return true Returns true if the student was actually deleted.
 * @return false Returns false if the student was not deleted.
 */
bool secretary::deleteStudent() {
  student *(secretary::*id_search)(unsigned int) = &secretary::retrieveStudent;
  student *(secretary::*name_search)(const std::string &) = &secretary::retrieveStudent;
  student *stud = validation::validateSearchCriteria<student>(std::cin, std::cout, std::cerr, 
                                                              "Enter the Name or ID of the Student you want to delete: ", id_search, name_search, *this);
  
  if (stud != nullptr) {
    std::cout << "|" << std::endl << "The Student with the following credentials was found: " << std::endl;
    std::cout << *stud;
    if (validation::validateBoolInput(std::cin, std::cout, std::cerr, "Would you like to delete this student? ")) {
      this->uni_id_database.erase(stud->getUniID());
      this->uni_name_database.erase(stud->getName());
      delete stud;
      return true;
    } else {
      std::cout << "| Student Deletion Aborted." << std::endl;
    }

  } else {
    std::cerr << "! ERROR: The Student you searched for was not found." << std::endl;
  }

  return false;
}

void secretary::removeStudent(student *student) {
  this->uni_id_database.erase(student->getUniID());
  this->uni_name_database.erase(student->getName());
}


/* - Professor Management - */


void secretary::createProfessor() {
  professor *new_professor = new professor(this->department_code);
  this->uni_id_database.insert(std::make_pair(new_professor->getUniID(), new_professor));
  this->uni_name_database.insert(std::make_pair(new_professor->getName(), new_professor));
}

void secretary::addProfessor(professor *professor) {
  this->uni_id_database.insert(std::make_pair(professor->getUniID(), professor));
  this->uni_name_database.insert(std::make_pair(professor->getName(), professor));
}

professor *secretary::retrieveProfessor(unsigned int uni_id) {
  std::map<unsigned int, person*>::iterator itr = this->uni_id_database.find(uni_id);
  if (itr != this->uni_id_database.end())
    if (((professor *)itr->second)->getFormattedUniID()[0] == 'P')
      return (professor *)itr->second;

  return nullptr;
}

professor *secretary::retrieveProfessor(const std::string &name) {
  std::multimap<std::string, person*>::iterator itr = this->uni_name_database.find(name);
  if (itr != this->uni_name_database.end())
    if (((professor *)itr->second)->getFormattedUniID()[0] == 'P')
      return (professor *)itr->second;
  
  return nullptr;
}

/**
 * @brief Searches for and deletes a professor.
 * 
 * @return true Returns true if the professor was actually deleted.
 * @return false Returns false if the professor was not deleted.
 */
bool secretary::deleteProfessor() {
  professor *(secretary::*id_search)(unsigned int) = &secretary::retrieveProfessor;
  professor *(secretary::*name_search)(const std::string &) = &secretary::retrieveProfessor;
  professor *prof = validation::validateSearchCriteria<professor>(std::cin, std::cout, std::cerr, 
                      "Enter the Name or ID of the Professor you want to delete: ", id_search, name_search, *this);
  
  if (prof != nullptr) {
    std::cout << "|" << std::endl << "The Professor with the following credentials was found: " << std::endl;
    std::cout << *prof;
    if (validation::validateBoolInput(std::cin, std::cout, std::cerr, "Would you like to delete this Professor? ")) {
      this->uni_id_database.erase(prof->getUniID());
      this->uni_name_database.erase(prof->getName());
      delete prof;
      return true;
    } else {
      std::cout << "| Professor Deletion Aborted." << std::endl;
    }

  } else {
    std::cerr << "! ERROR: The Professor you searched for was not found." << std::endl;
  }

  return false;
}

void secretary::removeProfessor(professor *professor) {
  this->uni_id_database.erase(professor->getUniID());
  this->uni_name_database.erase(professor->getName());
}


/* - Course Management - */


void secretary::createCourse() {
  course *new_course = new course(this->department_code);
  this->uni_id_course_database.insert(std::make_pair(new_course->getUniID(), new_course));
  this->uni_name_course_database.insert(std::make_pair(new_course->getName(), new_course));
}

void secretary::addCourse(course *course) {
  this->uni_id_course_database.insert(std::make_pair(course->getUniID(), course));
  this->uni_name_course_database.insert(std::make_pair(course->getName(), course));
}

course *secretary::retrieveCourse(unsigned int uni_id) {
  std::map<unsigned int, course*>::iterator itr = this->uni_id_course_database.find(uni_id);
  if (itr != this->uni_id_course_database.end())
    return (course *)itr->second;

  return nullptr;
}

course *secretary::retrieveCourse(const std::string &name) {
  std::map<std::string, course*>::iterator itr = this->uni_name_course_database.find(name);
  if (itr != this->uni_name_course_database.end())
    return (course *)itr->second;
  
  return nullptr;
}

bool secretary::deleteCourse() {
  course *(secretary::*id_search)(unsigned int) = &secretary::retrieveCourse;
  course *(secretary::*name_search)(const std::string &) = &secretary::retrieveCourse;
  course *cour = validation::validateSearchCriteria<course>(std::cin, std::cout, std::cerr, 
                                                              "Enter the Name or ID of the Course you want to delete: ", id_search, name_search, *this);
  
  if (cour != nullptr) {
    std::cout << "|" << std::endl << "The Course with the following credentials was found: " << std::endl;
    std::cout << *cour;
    if (validation::validateBoolInput(std::cin, std::cout, std::cerr, "Would you like to delete this Course? ")) {
      this->uni_id_course_database.erase(cour->getUniID());
      this->uni_name_course_database.erase(cour->getName());
      delete cour;
      return true;
    } else {
      std::cout << "| Course Deletion Aborted." << std::endl;
    }

  } else {
    std::cerr << "! ERROR: The Course you searched for was not found." << std::endl;
  }

  return false;
}

void secretary::removeCourse(course *course) {
  this->uni_id_course_database.erase(course->getUniID());
  this->uni_name_course_database.erase(course->getName());
}

/* New Semester */

void secretary::incrementSemester(){
  SEMESTER semester = this->getCurrentSemester();
  
  if (semester == FALL)
    this->current_semester = SPRING;
  else    
    this->current_semester = FALL;
  
  for (std::map<unsigned int, person*>::iterator itr = uni_id_database.begin(); 
    itr != this->uni_id_database.end(); itr++) {
    if (((professor *)itr->second)->getFormattedUniID()[0] == 'P'){
      professor *prof = (professor *)itr->second;
      prof->newSemester();
    }
    else {
      student *stud = (student *)itr->second;
      stud->newSemester();
    }
       
  }

  for (std::map<unsigned int, course*>::iterator itr = uni_id_course_database.begin(); 
    itr != this->uni_id_course_database.end(); itr++) {
    course *cour = itr->second; 
    cour->newSemester();
  }

}

/* - Operator Overloads - */

std::ostream &operator<< (std::ostream &stream, secretary &secretary) {
  stream << "| Secretary Department Name: " << secretary.department_name << std::endl;
  stream << "| Secreatry Department Code: " << secretary.department_code << std::endl;
  stream << "| Secretary Department Required Attendance: " << secretary.regular_attendance << " years(s)" << std::endl;
  stream << "| Secretary Department Maximum Attendance: " << secretary.maximum_attendance << " year(s)" << std::endl;
  stream << "| Secretary Department Graduation ECT Requirement: " << secretary.required_ects << " ECT(s)" << std::endl;
  stream << "| Secretary Department Mandatory Courses: " << secretary.mandatory_courses << " course(s)" << std::endl;
  return stream;
}

std::istream &operator>> (std::istream &stream, secretary &secretary) {
  secretary.department_name = validation::validateNameInput(stream, std::cout, std::cerr, "Enter Secretary Department Name: ");
  secretary.department_code = validation::validateNumericalInput<unsigned short>(stream, std::cout, std::cerr, "Enter Secretary Department Code: ", 9999);
  secretary.regular_attendance = validation::validateNumericalInput<unsigned short>(stream, std::cout, std::cerr, "Enter Secretary Department Required Years of Attendance: ", 10);
  secretary.maximum_attendance = validation::validateNumericalInput<unsigned short>(stream, std::cout, std::cerr, "Enter secretary Department Maximum Years of Attendance: ", 10);
  secretary.required_ects = validation::validateNumericalInput<unsigned short>(stream, std::cout, std::cerr, "Enter Secretary Department Graduation ECT Requirement: ", 300);
  secretary.mandatory_courses = validation::validateNumericalInput<unsigned short>(stream, std::cout, std::cerr, "Enter Secretary Department Mandatory Courses: ", 100);
  return stream;
}
