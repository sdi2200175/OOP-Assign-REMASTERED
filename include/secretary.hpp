/**
 * @file secretary.hpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief 
 * @version 
 * @date 2024-01-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <map>
#include <iostream>

#include "student.hpp"
#include "professor.hpp"
#include "course.hpp"

using namespace std;

class Secretary {

  private:
    string DepartmentName;
    unsigned short DepartmentCode, ECTRequirement, MaximumAttendance;

    map<unsigned int, Student*> StudentIDDatabase;
    map<string, Student*> StudentNameDatabase;

    map<unsigned int, Professor*> ProfessorIDDatabase;
    map<string, Professor*> ProfessorNameDatabase;

    map<unsigned int, Course*> CourseIDDatabase;
    map<string, Course*> CourseNameDatabase;

  public:

    /* - Constructors and Destructors - */
    Secretary();
    Secretary(string DepartmentName, unsigned int DepartmentCode, unsigned int ECTRequirement, unsigned short MaximumAttendance);
    ~Secretary();

    /* - Getters - */
    inline const string &getDepartmentName() { return DepartmentName; }
    inline unsigned int getDepartmentCode() { return DepartmentCode; }
    inline unsigned int getECTRequirement() {return ECTRequirement; }  
    inline unsigned int getMaximumAttendance() { return MaximumAttendance; }

    /* - Student Management - */
    void addStudent();
    void addStudentToDatabase(Student *student);
    void deleteStudent(Student *student);
    void removeStudentFromDatabase(Student *student);

    /**
     * @brief Searches for a Student in the Secretary.
     * 
     * @param UniID Search Term.
     * @return A pointer the the Student that was found.
     * @exception Throws an invalid_argument exception if the Student was not found in the secretary.
     */
    Student *retrieveStudent(unsigned int UniID);

    /**
     * @brief Searches for a Student in the Secretary.
     * 
     * @param Name Search Term.
     * @return A pointer to the Student that was found.
     * @exception Throws and invalid_argument exception if the Student was not found in the Secretary.
     */
    Student *retrieveStudent(const string &Name);

    /* - Professor Management - */
    void addProfessor();
    void addProfessorToDatabase(Professor *professor);
    void deleteProfessor(Professor *professor);
    void removeProfessorFromDatabase(Professor *professor);

    /**
     * @brief Searches for a Professor in the Secretary.
     * 
     * @param UniID Search Term.
     * @return A pointer the the Professor that was found.
     * @exception Throws an invalid_argument exception if the Professor was not found in the secretary.
     */
    Professor *retrieveProfessor(unsigned int UniID);

    /**
     * @brief Searches for a Professor in the Secretary.
     * 
     * @param Name Search Term.
     * @return A pointer to the Professor that was found.
     * @exception Throws and invalid_argument exception if the Professor was not found in the Secretary.
     */
    Professor *retrieveProfessor(const string &Name);

    /* - Course Management - */
    void addCourse();
    void addCourseToDatabase(Course *course);
    void deleteCourse(Course *course);
    void removeCourseFromDatabase(Course *course);

    /**
     * @brief Searches for a Course in the Secretary.
     * 
     * @param CourseID Search Term.
     * @return A pointer the the Course that was found.
     * @exception Throws an invalid_argument exception if the Course was not found in the secretary.
     */
    Course *retrieveCourse(unsigned int CourseID);

    /**
     * @brief Searches for a Course in the Secretary.
     * 
     * @param Course Search Term.
     * @return A pointer to the Course that was found.
     * @exception Throws and invalid_argument exception if the Course was not found in the Secretary.
     */
    Course *retrieveCourse(const string &Name);

    /* - Operator Overloads - */
    friend ostream &operator<< (ostream &str, Secretary &sec);
    friend istream &operator>> (istream &str, Secretary &sec);
};