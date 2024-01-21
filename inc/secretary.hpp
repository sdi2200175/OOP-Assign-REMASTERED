/**
 * @file secretary.hpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief 
 * @version 0.1
 * @date 2024-01-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <iostream>
#include "person.hpp"
#include "course.hpp"

class secretary {

private:
  std::string department_name;
  unsigned short department_code, regular_attendance, maximum_attendance, required_ects, mandatory_courses;
  SEMESTER current_semester;

  std::map<unsigned int, person*> uni_id_database;
  std::multimap<std::string, person*> uni_name_database;

  std::map<unsigned int, course*> uni_id_course_database;
  std::map<std::string, course*> uni_name_course_database;

public:

  /**
   * @brief Construct a new secretary object by requesting input from the user directly
   * 
   */
  secretary();

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
  secretary(const std::string &department_name, unsigned short department_code, unsigned short regular_attendance, 
    unsigned short maximum_attendance, unsigned short required_ects, unsigned short mandatory_courses);

  /**
   * @brief Destroy the secretary object
   * 
   */
  ~secretary();

  /* - Getters - */
  inline const std::string &getDepartmentName() const { return this->department_name; }
  inline unsigned short getDepartmentCode() const { return this->department_code; }
  inline unsigned short getMaximumAttendance() const { return this->maximum_attendance; }
  inline unsigned short getRequiredECTs() const { return this->required_ects; }
  inline unsigned short getMandatoryCourses() const { return this->mandatory_courses; }
  inline SEMESTER getCurrentSemester() const { return this->current_semester; }

  /* - Student Management - */
  void createStudent();                                   // Creates a student object and adds it to the database.
  void addStudent(student *student);                      // Adds a student object to the database.
  student *retrieveStudent(unsigned int uni_id);          // Returns nullptr if the student wasn't found.
  student *retrieveStudent(const std::string &name);      // Returns nullptr if the student wasn't found.
  bool deleteStudent();                                   // Returns true if the student was found and deleted. False otherwise
  void removeStudent(student *student);                   // Removes a student from the database without deleteing the actual object.

  /* - Professor Management - */
  void createProfessor();                                 // Creates a professor object and adds it to the database.
  void addProfessor(professor *professor);                // Adds a professor object to the database.
  professor *retrieveProfessor(unsigned int uni_id);      // Returns nullptr if the professor wasn't found.
  professor *retrieveProfessor(const std::string &name);  // Returns nullptr if the professor wasn't found.
  bool deleteProfessor();                                 // Returns true if the professor was found and deleted. False otherwise
  void removeProfessor(professor *professor);             // Removes a professor from the database without deleteing the actual object.

  /* - Course Management - */
  void createCourse();
  void addCourse(course *course);
  course *retrieveCourse(unsigned int uni_id);
  course *retrieveCourse(const std::string &name);
  bool deleteCourse();
  void removeCourse(course *course);

  /* Increment Semester */
  void incrementSemester();

  /* - Operator overload functions - */
  friend std::ostream &operator<< (std::ostream &stream, secretary &secretary);
  friend std::istream &operator>> (std::istream &stream, secretary &secretary);

};