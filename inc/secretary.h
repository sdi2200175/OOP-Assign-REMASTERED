/**
 * @file secretary.h
 * @brief This file contains the definition of the secretary class.
 * @authors Evaggelia Ragkousi, Spyros Strakosia
 * @date 25/01/2024
 */
#ifndef UNIMANAGEMENT_SECRETARY_H
#define UNIMANAGEMENT_SECRETARY_H

#include <iostream>
#include <unordered_map>

#include "person.h"
#include "course.h"

/// Enum representing the semester the department is currently on.
typedef enum {
    FALL = 1, SPRING = 2
} Semester;

class secretary {

private:
    std::string dept_name;
    unsigned int dept_code;
    unsigned short min_attendance, required_ects, mandatory_courses;
    Semester semester;

    std::unordered_map<unsigned int, person *> id_database;
    std::unordered_multimap<std::string, person *> name_database;

    std::unordered_map<unsigned int, course *> course_id_database;
    std::unordered_multimap<std::string, course *> course_name_database;

public:
    secretary();
    secretary(secretary &sec);
    secretary(std::string dept_name, unsigned int dept_code, unsigned short min_attendance,
              unsigned short required_ects, unsigned short mandatory_courses, Semester semester);

    ~secretary();

    // Operator overloads
    friend std::ostream &operator<<(std::ostream &stream, const secretary &secretary);
    friend std::istream &operator>>(std::istream &stream, secretary &secretary);

    // Getters and Setters

    const std::string &getDeptName() const { return dept_name; }
    unsigned int getDeptCode() const { return dept_code; }
    unsigned short getMinAttendance() const { return min_attendance; }
    unsigned short getRequiredEcts() const { return required_ects; }
    unsigned short getMandatoryCourses() const { return mandatory_courses; }
    Semester getSemester() const { return semester; }

    const std::unordered_map<unsigned int, person *> &getIdDatabase() const { return id_database; }
    const std::unordered_multimap<std::string, person *> &getNameDatabase() const { return name_database; }
    const std::unordered_map<unsigned int, course *> &getCourseIdDatabase() const { return course_id_database; }
    const std::unordered_multimap<std::string, course *> &getCourseNameDatabase() const { return course_name_database; }

    // Addition functions
    void add(person *per);
    void add(course *cour);

    //Person retrieval functions
    /**
     * Searches for and returns the person with the given university id or name.
     * @tparam T Class which is being searched for.
     * @param id, name Searches either the name_database or the id_database respectively.
     * @return A pointer to the person that was found.
     * @throw out_of_range if no one was found with the name or id provided.
     */
    template<class T>
    T *retrieve(unsigned int id) {

        auto itr = id_database.find(id);
        if (itr == id_database.end())
            throw std::out_of_range("! ERROR: This ID doesn't belong to any university member.");

        if (itr->second->getFormattedUniId()[0] != T::id_prefix)
            throw std::out_of_range("! ERROR: Invalid ID Format.");

        return (T *) itr->second;
    }

    template<class T>
    T *retrieve(const std::string &name) {

        auto itr = name_database.find(name);
        if (itr == name_database.end())
            throw std::out_of_range("! ERROR: No university member named '" + name + "' found.");

        if (itr->second->getFormattedUniId()[0] != T::id_prefix)
            throw std::out_of_range("! ERROR: Invalid ID Format.");

        return (T *) itr->second;
    }

    // Course retrieval functions
    course *retrieveCourse(unsigned int id);

    course *retrieveCourse(const std::string &name);

    // Removal functions
    void remove(person *per);
    void remove(course *cour);

    // Number of Students calculation function
    unsigned int calculateStudentSize() const;

    // Number of Professors calculation function
    unsigned int calculateProfessorSize() const;

    // Semester incrementation function
    void incrementSemester();

};


#endif //UNIMANAGEMENT_SECRETARY_H
