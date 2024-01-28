/**
 * @file person.h
 * @brief This file contains the definition of the course class.
 * @authors Evaggelia Ragkousi, Spyros Strakosia
 * @date 26/01/2024
 */

#ifndef UNIMANAGEMENT_COURSE_H
#define UNIMANAGEMENT_COURSE_H

#include <iostream>
#include <vector>

#include "person.h"

class course {

private:
    std::string name;
    unsigned short ects;
    unsigned short semester;
    bool mandatory;

    const unsigned int uni_id;
    const std::string formatted_uni_id;

    std::vector<person *> attendees;
    std::vector<person *> assigned_professors;

public:

    course(unsigned short dept_code);
    course(std::string name, unsigned short ects, unsigned short semester, bool mandatory,
           unsigned int uni_id, unsigned short dept_code);

    // Operator overloads.
    friend std::ostream &operator<<(std::ostream &stream, const course &course);
    friend std::istream &operator>>(std::istream &stream, course &course);
    
    friend std::ofstream &operator<<(std::ofstream &stream, const course &course);

    // Getters and Setters

    const std::string &getName() const { return name; }
    void setName(const std::string &new_name) { name = new_name; }

    unsigned short getEcts() const { return ects; }
    void setEcts(unsigned short new_ects) { ects = new_ects; }

    unsigned short getSemester() const { return semester; }
    void setSemester(unsigned short new_semester) { semester = new_semester; }

    bool isMandatory() const { return mandatory; }
    void setMandatory(bool new_mandatory) { mandatory = new_mandatory; }

    unsigned int getUniId() const { return uni_id; }
    const std::string &getFormattedUniId() const { return formatted_uni_id; }

    const std::vector<person *> &getAttendees() const { return attendees; }
    const std::vector<person *> &getAssignedProfessors() const { return assigned_professors; }

    // Attendee and Professor management.
    void registr(student *student);
    void assign(professor *professor);

    // Move to next semester
    void incrementSemester();

    // Special variable that denotes the prefix of the formatted university id.
    static const char id_prefix = 'C';

    // This variable tracks how many course objects have been created.
    // This number is used to generate the unique "uni id" for every course.
    static unsigned int amount_created;
};


#endif //UNIMANAGEMENT_COURSE_H
