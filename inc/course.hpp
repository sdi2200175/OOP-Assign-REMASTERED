/**
 * @file course.hpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief
 * @version 0.1
 * @date 2024-01-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include "person.hpp"
#include <iostream>
#include <vector>

class course {

private:
    std::string name;
    unsigned short ects, semester;
    bool is_mandatory;

    const unsigned int uni_id;
    const std::string formatted_uni_id;

    std::vector<person*> attendees;
    std::vector<person*> assigned_professors;

    static unsigned int amount_created;

public:
    /**
     * @brief Construct a new course object with direct user input.
     *
     * @param department_code The code of the Secretary Department that this course belongs to.
     */
    course(unsigned short department_code);

    /**
     * @brief Construct a new course object without direct user input.
     *
     * @param name The course name.
     * @param ects The course ECTs that a student is awarded when they complete it,.
     * @param is_mandatory If the course is mandatory.
     * @param semester Wheter its in the spring or the fall semester.
     * @param department_code The code of the Secretary Department that this course belongs to.
     */
    course(const std::string& name, unsigned short ects, bool is_mandatory, unsigned short semester, unsigned short department_code);

    /**
     * @brief Destroy the course object.
     *
     */
    ~course();

    /* - Getters - */
    inline const std::string& getName() const { return this->name; }
    inline unsigned short getECTs() const { return this->ects; }
    inline bool getIsMandatory() const { return this->is_mandatory; }
    inline unsigned short getSemester() const { return this->semester; }
    inline unsigned int getUniID() const { return this->uni_id; }
    inline const std::string& getFormattedUniID() { return this->formatted_uni_id; }
    inline const std::vector<person*>& getAttendees() const { return this->attendees; }

    /* - Setters - */
    void setName();
    void setECTs();
    void setIsMandatory();
    void setSemester();

    inline void setName(const std::string& name) { this->name = name; }
    inline void setECTs(unsigned short ects) { this->ects = ects; }
    inline void setSemester(unsigned short semester) { this->semester = semester; }
    inline void setIsMandatory(bool is_mandatory) { this->is_mandatory = is_mandatory; }

    /* - Professor Assignment - */

    /**
     * @brief Assigns a professor to a course.
     *
     * @param professor The professor that will be assigned to the course.
     * @return true If the professor was assigned successfully.
     * @return false If the professor was already assigned to the course and was not rerassigned.
     */
    bool assignProfessor(professor* professor);
    bool isAssigned(professor* professor);
    inline void unassignProfessors() { this->assigned_professors.clear(); }

    /* - Student Registration - */

    /**
     * @brief Registers a student to the course.
     *
     * @param student The student that will be registered.
     * @return true If the student was registered successfully.
     * @return false If the student was already registered to the course.
     */
    bool registerStudent(student* student);
    bool isRegistered(student* student);
    inline void deregisterStudents() { this->attendees.clear(); }

    /* New Semester */
    void newSemester();

    /* - Operator Overloads - */
    friend std::ostream& operator<<(std::ostream& stream, course& course);
    friend std::istream& operator>>(std::istream& stream, course& course);

    // Constant class - wide prefix for the formatted id generation. All course univeristy ids will
    // start with the letter C.
    const static char id_prefix = 'C';
};