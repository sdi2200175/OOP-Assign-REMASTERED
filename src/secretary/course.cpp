/**
 * @file course.cpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief 
 * @version 0.1
 * @date 2024-01-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <algorithm>

#include "course.hpp"
#include "validation.hpp"

unsigned int course::amount_created = 0;

/**
 * @brief Construct a new course object with direct user input.
 * 
 * @param department_code The code of the Secretary Department that this course belongs to.
 */
course::course(unsigned short department_code) : uni_id(++amount_created), 
  formatted_uni_id(std::string(1, this->id_prefix) + "-" + std::string(4 - std::to_string(department_code).length(), '0') 
  + std::to_string(department_code) + "-" + std::string(7 - std::to_string(this->uni_id).length(), '0') + std::to_string(this->uni_id)) {

  std::cin >> *this;
  std::cout << "|-- Created Course named '" + this->getName() + "' with University ID: " + this->formatted_uni_id + " --|" << std::endl;
}

/**
 * @brief Construct a new course object without direct user input.
 * 
 * @param name The course name.
 * @param ects The course ECTs that a student is awarded when they complete it,.
 * @param is_mandatory If the course is mandatory.
 * @param semester Wheter its in the spring or the fall semester.
 * @param department_code The code of the Secretary Department that this course belongs to.
 */
course::course(const std::string &name, unsigned short ects, bool is_mandatory, unsigned short semester, unsigned short department_code) :
  name(name), ects(ects), semester(semester), is_mandatory(is_mandatory), uni_id(++amount_created),
  formatted_uni_id(std::string(1, this->id_prefix) + "-" + std::string(4 - std::to_string(department_code).length(), '0') 
  + std::to_string(department_code) + "-" + std::string(7 - std::to_string(this->uni_id).length(), '0') + std::to_string(this->uni_id)) {

  std::cout << "|-- Created Course named '" + this->getName() + "' with University ID: " + this->formatted_uni_id + " --|" << std::endl;
}

/**
 * @brief Destroy the course object
 * 
 */
course::~course() {

  for (std::vector<person *>::iterator itr = this->attendees.begin();
    itr != this->attendees.end(); itr++) {

    delete (*itr);
  }
    
  for (std::vector<person *>::iterator itr = this->assigned_professors.begin();
    itr != this->assigned_professors.end(); itr++) {

    delete (*itr);
  }

};

/* - Setters - */

void course::setName() {
  this->name = validation::validateNameInput(std::cin, std::cout, std::cerr, "Enter New Name: ");
}

void course::setSemester() {
  this->semester = validation::validateNumericalInput<unsigned short>(std::cin, std::cout, std::cerr, "Enter New Course Semester: ", 10);
}

void course::setECTs() {
  this->ects = validation::validateNumericalInput<unsigned short>(std::cin, std::cout, std::cerr, "Enter New Amount of ECTs: ", 10);
}

void course::setIsMandatory() {
  this->is_mandatory = validation::validateBoolInput(std::cin, std::cout, std::cerr, "Will this Course be mandatory for graduation? ");
}

/* - Professor Management - */

/**
 * @brief Assigns a professor to a course.
 * 
 * @param professor The professor that will be assigned to the course.
 * @return true If the professor was assigned successfully.
 * @return false If the professor was already assigned to the course and was not rerassigned.
 */
bool course::assignProfessor(professor *professor) {
  if (this->isAssigned(professor))
    return false;

  this->assigned_professors.insert(this->assigned_professors.end(), professor);
  professor->insertAssignedCourses(this->uni_id);
  return true;
}

/**
 * @brief Finds if a given professor is assigned to a course.
 * 
 * @param professor The professor we're looking for.
 * @return true If the professor is assigned to the course.
 * @return false If the professor is not assigned to the course.
 */
bool course::isAssigned(professor *professor) {
  if (std::find(this->assigned_professors.begin(), this->assigned_professors.end(), professor) != this->assigned_professors.end())
    return true;

  return false;
}

/* - Student Management - */

/**
 * @brief Registers a student to the course.
 * 
 * @param student The student that will be registered.
 * @return true If the student was registered successfully.
 * @return false If the student was already registered to the course.
 */
bool course::registerStudent(student *student) {
  if (this->isRegistered(student))
    return false;

  this->attendees.insert(this->attendees.end(), student);
  return true;
}

/**
 * @brief Finds if a given student is registered to a course.
 * 
 * @param student The student we're looking for.
 * @return true If the student is registered to the course.
 * @return false If the student is not registered to the course.
 */
bool course::isRegistered(student *student) {
  for (std::vector<person*>::iterator itr = this->attendees.begin(); 
    itr != this->attendees.end(); itr++) {
    if ((*itr)->getFormattedUniID().compare(student->getFormattedUniID()))
      return true;
  }

  return false;
}

/* New Semester */

void course::newSemester(){
  this->assigned_professors.clear();
  this->attendees.clear();
}

/* - Operator Overloads - */

std::ostream &operator<< (std::ostream &stream, course &course) {
  stream << "| Course Name: " << course.name << std::endl;
  stream << "| Course ECTs: " << course.ects << " ECT(s)" << std::endl;
  stream << "| Course is available during semester " << course.semester << "." << std::endl;
  stream << "| Course is" << (course.is_mandatory ? "" : " not") << " mandatory for graduation." << std::endl;
  stream << "| This course is being attended by " << course.attendees.size() << " Student(s)." << std::endl;
  stream << "| Assigned professors are: "; 
  for (std::vector<person*>::iterator itr = course.assigned_professors.begin(); itr != course.assigned_professors.end(); itr++)
    stream << (*itr)->getName() << ", " << std::endl;

  return stream;
}

std::istream &operator>> (std::istream &stream, course &course) {
  course.name = validation::validateNameInput(stream, std::cout, std::cerr, "Enter Name: ");
  course.ects = validation::validateNumericalInput(stream, std::cout, std::cerr, "Enter Amount of ECTs: ", 10);
  course.semester = validation::validateNumericalInput(stream, std::cout, std::cerr, "Enter Course Semester: ", 2);
  course.is_mandatory = validation::validateBoolInput(stream, std::cout, std::cerr, "Will this Course be mandatory for graduation? ");
  return stream;
}