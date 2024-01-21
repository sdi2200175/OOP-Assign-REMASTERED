/**
 * @file person.hpp
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
#include <vector>
#include <map>

/**
 * @brief This enum represents the 2 possible states of the semester.
 * In other words, we can either be in the fall semester or the spring semester.
 * 
 */
typedef enum {
  FALL = 1, SPRING = 2
} SEMESTER;

class person {

protected:
  std::string name;
  const unsigned int uni_id;

  /**
   * @brief A variable that will store how many person objects have been created and uses the value at each point in time
   * to create a unique uni_id for each one.
   * 
   */
  static unsigned int amount_created;

public:

  /**
   * @brief Construct a new person object using direct user input.
   * 
   */
  person();

  /**
   * @brief Construct a new person object using indirect user input.
   * 
   * @param name The person's full name.
   */
  person(const std::string &name);

  /**
   * @brief Destroy the person object.
   * 
   */
  inline virtual ~person() {}

  /* - Getters - */
  inline const std::string &getName() const { return this->name; }
  inline unsigned int getUniID() const { return this->uni_id; }

  /* - Setters - */
  void setName();
  inline void setName(const std::string &name) { this->name = name; }

  /* - Pure Virtual Function - */
  virtual inline const std::string &getFormattedUniID() const = 0;

  /* - Operator Overloads - */
  friend std::ostream &operator<< (std::ostream &stream, person &person);
  friend std::istream &operator>> (std::istream &stream, person &person);
};

/**
 * @brief Derived class from person to represent students in the secretary.
 * 
 */
class student : public person {

private:
  std::string date_of_birth, date_of_registration;
  unsigned short ects, mandatory_courses_passed, semester;

  const std::string formatted_uni_id;

  struct grade {
    std::string course_name;
    unsigned int course_id;
    std::string grader_name;
    std::string grader_id;
    unsigned short grade;
    unsigned short semester;
  };

  std::vector<struct grade *> grades;

public:

  /**
   * @brief Construct a new student object with direct user input.
   * 
   * @param department_code The code of the secretary department. Used in generating the unique formatted id.
   */
  student(unsigned short department_code);

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
  student(const std::string &name, const std::string &date_of_birth, const std::string &date_of_registration, unsigned short ects,
          unsigned short mandatory_courses_passed, unsigned short department_code);

  /**
   * @brief Destroy the student object.
   * 
   */
  virtual ~student();

  /* - Getters - */
  inline const std::string &getDateOfBirth() const { return this->date_of_birth; }
  inline const std::string &getDateOfRegistration() const { return this->date_of_registration; }
  inline unsigned short getECTs() const { return this->ects; }
  inline unsigned short getMandatoryCoursesPassed() { return this->mandatory_courses_passed; }
  inline const std::string &getFormattedUniID() const { return this->formatted_uni_id; }
  inline unsigned short getSemester() const { return this->semester; }

  /* - Setters - */
  void setDateOfBirth();
  void setDateOfRegistration();
  void setECTs();

  inline void setDateOfBirth(const std::string &date_of_birth) { this->date_of_birth = date_of_birth; }
  inline void setDateOfRegistration(const std::string &date_of_registration) { this->date_of_registration = date_of_registration; }
  inline void setECTs(unsigned short ects) { this->ects = ects; }
  inline void incrementSemester() { this->semester++; }

  /* - Grade Management - */
  bool addGrade(const std::string &course_name, unsigned int course_id, const std::string &grader_name, const std::string &grader_id, 
    unsigned short semester, unsigned int grade);

  void printGrades(unsigned short semester = 0);

  unsigned short getGrade(unsigned int course_id);

  /* - Operator Overloads - */
  friend std::ostream &operator<< (std::ostream &stream, student &student);
  friend std::istream &operator>> (std::istream &stream, student &student);

  // Constant class - wide prefix for the formatted id generation. All student univeristy ids will
  // start with the letter S.
  const static char id_prefix = 'S';
};

/**
 * @brief Derived class from person to represent professors in the secretary.
 * 
 */
class professor : public person {

private:
  std::string date_of_birth;
  const std::string formatted_uni_id;

  std::vector<unsigned int> assigned_courses;

public:

  /**
   * @brief Construct a new Professor object with direct user input.
   * 
   * @param department_code The code of the secretary department. Used in generating the unique formatted id.
   */
  professor(unsigned short department_code);

  /**
   * @brief Construct a new professor object with indirect user input.
   * 
   * @param name The professor's full name.
   * @param date_of_birth The profrssor's date of birth.
   * @param department_code The code of the secretary department. Used in generating the unique formatted id.
   */
  professor(const std::string &name, const std::string &date_of_birth, unsigned int department_code);

  /**
   * @brief Destroy the professor object.
   * 
   */
  virtual ~professor();

  /* - Getters - */
  inline const std::string &getDateOfBirth() const { return this->date_of_birth; }
  inline const std::string &getFormattedUniID() const { return this->formatted_uni_id; }
  inline const std::vector<unsigned int> &getAssignedCourses() const { return this->assigned_courses; }

  /* - Setters */
  void setDateOfBirth();
  inline void setDateOfBirth(const std::string &date_of_birth) { this->date_of_birth = date_of_birth; }
  inline void insertAssignedCourses(const unsigned int uni_id) { this->assigned_courses.insert(this->assigned_courses.end(), uni_id); }

  /* - Operator Overloads - */
  friend std::ostream &operator<< (std::ostream &stream, professor &professor);
  friend std::istream &operator>> (std::istream &stream, professor &professor);

  // Constant class - wide prefix for the formatted id generation. All professor univeristy ids will
  // start with the letter P.
  const static char id_prefix = 'P';
};