/**
 * @file person.cpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief 
 * @version 0.1
 * @date 2024-01-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "person.hpp"
#include "validation.hpp"

unsigned int person::amount_created = 0;

/**
 * @brief Construct a new person object using direct user input.
 * 
 */
person::person() : uni_id(++amount_created) {
  std::cin >> *this;
}

/**
 * @brief Construct a new person object using indirect user input.
 * 
 * @param name The person's full name.
 */
person::person(const std::string &name) : name(name), uni_id(++amount_created) {}

/* - Setters - */

void person::setName() {
  this->name = validation::validateNameInput(std::cin, std::cout, std::cerr, "Enter New Name: ");
}

/* - Operator Overloads - */

std::ostream &operator<<(std::ostream &stream, person &person) {
  stream << "| Full Name: " << person.name << std::endl;
  stream << "| University ID: " << person.uni_id << std::endl;
  return stream;
}

std::istream &operator>>(std::istream &stream, person &person) {
  person.name = validation::validateNameInput(stream, std::cout, std::cerr, "Enter Full Name: ");
  return stream;
}















///////////////////////////////* - Student derived class mothod definitions - *///////////////////////////////


















/**
 * @brief Construct a new student object with direct user input.
 * 
 * @param department_code The code of the secretary department. Used in generating the unique formatted id.
 */
student::student(unsigned short department_code) : person(), semester(1),
  formatted_uni_id(std::string(1, this->id_prefix) + "-" + std::string(4 - std::to_string(department_code).length(), '0') 
  + std::to_string(department_code) + "-" + std::string(7 - std::to_string(this->uni_id).length(), '0') + std::to_string(this->uni_id)) {

  std::cin >> *this;
  std::cout << "|-- Created Student named '" + this->getName() + "' with University ID: " + this->formatted_uni_id + " --|" << std::endl;
}

/**
 * @brief Construct a new student object with indirect user input.
 * 
 * @param name The student's full name.
 * @param date_of_birth The date of birth of the student.
 * @param date_of_registration The student's date of registration wit the secretary.
 * @param ects The amount of ECTs the student has amassed.
 * @param mandatory_courses_passed The amount of mandatory courses the student has completed.
 * @param department_code The code of the secretary department. Used in generating the unique formated id.
 */
student::student(const std::string &name, const std::string &date_of_birth, const std::string &date_of_registration, unsigned short ects,
  unsigned short mandatory_courses_passed, unsigned short department_code) : person(name), date_of_birth(date_of_birth),
  date_of_registration(date_of_registration), ects(ects), mandatory_courses_passed(mandatory_courses_passed), semester(1),
  formatted_uni_id(std::string(1, this->id_prefix) + "-" + std::string(4 - std::to_string(department_code).length(), '0') 
  + std::to_string(department_code) + "-" + std::string(7 - std::to_string(this->uni_id).length(), '0') + std::to_string(this->uni_id)) {

  std::cout << "|-- Created Student named '" + this->getName() + "' with University ID: " + this->formatted_uni_id + " --|" << std::endl;
}

/**
 * @brief Destroy the student object.
 * 
 */
student::~student() {
  for (std::vector<struct grade *>::iterator itr = this->grades.begin();
    itr != this->grades.end(); itr++) {

    delete (*itr);
  }
}

/* - Setters - */

void student::setDateOfBirth() {
  this->date_of_birth = validation::validateDateInput(std::cin, std::cout, std::cerr, "Enter New Date of Birth: ");
}

void student::setDateOfRegistration() {
  this->date_of_registration = validation::validateDateInput(std::cin, std::cout, std::cerr, "Enter New Date of Registration: ");
}

void student::setECTs() {
  this->ects = validation::validateNumericalInput(std::cin, std::cout, std::cerr, "Enter New ECT Amount: ", 300);
}

/* - Grade Management - */

bool student::addGrade(const std::string &course_name, unsigned int course_id, const std::string &grader_name, const std::string &grader_id, 
  unsigned short semester, unsigned int grade) {

  for (std::vector<struct grade *>::iterator itr = this->grades.begin();
    itr != this->grades.end(); itr++) {

    if ((*itr)->course_id == course_id) {
      std::cout << "| This Student has already been graded." << std::endl;

      if (validation::validateBoolInput(std::cin, std::cout, std::cerr, "Would you like to modify their grade?")) {
        (*itr)->grader_name = grader_name;
        (*itr)->grader_id = grader_id;
        (*itr)->grade = grade;
        return true;
      } else {
        return false;
      }
    }
  }

  struct grade *new_grade = new struct grade;
  new_grade->course_name = course_name;
  new_grade->course_id = course_id;
  new_grade->grader_name = grader_name;
  new_grade->grader_id = grader_id;
  new_grade->semester = semester;
  new_grade->grade = grade;
  this->grades.insert(this->grades.end(), new_grade);

  return true;
}

void student::printGrades(unsigned short semester) {

  if (!semester) {
    for (std::vector<struct grade *>::iterator itr = this->grades.begin(); 
      itr != this->grades.end(); itr++) {    
    std::cout << "| " << (*itr)->course_name << ", graded " << (*itr)->grade << " by Professor named '" << (*itr)->grader_name << "'." << std::endl;
  }

  } else {
    for (std::vector<struct grade *>::iterator itr = this->grades.begin(); 
      itr != this->grades.end(); itr++) {

      if((*itr)->semester != semester) continue;
      std::cout << "| " << (*itr)->course_name << ", graded " << (*itr)->grade << " by Professor named '" << (*itr)->grader_name << "'." << std::endl;
    }
  }

}

unsigned short student::getGrade(unsigned int course_id) {
  
  for (std::vector<struct grade *>::iterator itr = this->grades.begin(); 
    itr != this->grades.end(); itr++) {
  
    if (course_id == (*itr)->course_id)
      return (*itr)->grade;
  }

  return 0;
}

/* - Operator Overloads - */

std::ostream &operator<<(std::ostream &stream, student &student) {
  stream << "| Student's Full Name: " << student.name << std::endl;
  stream << "| Student's Date of Birth: " << student.date_of_birth << std::endl;
  stream << "| Student's Date of Registration: " << student.date_of_registration << std::endl;
  stream << "| Student's Total ECT Amount: " << student.ects << " ECT(s)" << std::endl;
  stream << "| Student's Amount of Mandatory Courses Passed: " << student.mandatory_courses_passed << " Course(s)" << std::endl;
  stream << "| Student's University ID: " << student.formatted_uni_id << std::endl;
  return stream;
}

std::istream &operator>>(std::istream &stream, student &student) {
  student.date_of_birth = validation::validateDateInput(stream, std::cout, std::cerr, "Enter Date of Birth: ");
  student.date_of_registration = validation::validateDateInput(stream, std::cout, std::cerr, "Enter Date of Registration: ");
  student.ects = validation::validateNumericalInput(std::cin, std::cout, std::cerr, "Enter ECT Amount: ", 300);
  return stream;
}















///////////////////////////////* - Professor derived class method definitions - *///////////////////////////////

















/**
 * @brief Construct a new Professor object with direct user input.
 * 
 * @param department_code The code of the secretary department. Used in generating the unique formatted id.
 */
professor::professor(unsigned short department_code) : person(), 
  formatted_uni_id(std::string(1, this->id_prefix) + "-" + std::string(4 - std::to_string(department_code).length(), '0') 
  + std::to_string(department_code) + "-" + std::string(7 - std::to_string(this->uni_id).length(), '0') + std::to_string(this->uni_id)) {

  std::cin >> *this;
  std::cout << "|-- Created Professor named '" + this->getName() + "' with University ID: " + this->formatted_uni_id + " --|" << std::endl;
}

/**
 * @brief Construct a new professor object with indirect user input.
 * 
 * @param name The professor's full name.
 * @param date_of_birth The profrssor's date of birth.
 * @param department_code The code of the secretary department. Used in generating the unique formatted id.
 */
professor::professor(const std::string &name, const std::string &date_of_birth, unsigned int department_code) : 
  person(name), date_of_birth(date_of_birth),
  formatted_uni_id(std::string(1, this->id_prefix) + "-" + std::string(4 - std::to_string(department_code).length(), '0') 
  + std::to_string(department_code) + "-" + std::string(7 - std::to_string(this->uni_id).length(), '0') + std::to_string(this->uni_id)) {

  std::cout << "|-- Created Professor named '" + this->getName() + "' with University ID: " + this->formatted_uni_id + " --|" << std::endl;
}

/**
 * @brief Destroy the professor object.
 * 
 */
professor::~professor() {}

/* - Setters - */

void professor::setDateOfBirth() {
  this->date_of_birth = validation::validateDateInput(std::cin, std::cout, std::cerr, "Enter New Date of Birth: ");
}

/* - Operator Overloads - */

std::ostream &operator<< (std::ostream &stream, professor &professor) {
  stream << "| Professor's Full Name: " << professor.name << std::endl;
  stream << "| Professor's Date of Birth: " << professor.date_of_birth << std::endl;
  stream << "| Professor's University ID: " << professor.formatted_uni_id << std::endl;
  return stream;
}

std::istream &operator>> (std::istream &stream, professor &professor) {
  professor.date_of_birth = validation::validateDateInput(stream, std::cout, std::cerr, "Enter Date of Birth: ");
  return stream;
}