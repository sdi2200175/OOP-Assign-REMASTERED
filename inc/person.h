/**
 * @file person.h
 * @brief This file contains the definition of the person, student and professor
 * classes.
 * @authors Evaggelia Ragkousi, Spyros Strakosia
 * @date 25/01/2024
 */

#ifndef UNIMANAGEMENT_PERSON_H
#define UNIMANAGEMENT_PERSON_H

#include <iostream>
#include <vector>

/// Struct used to statically store the grades in the student classes.
typedef struct grade {
    std::string course_name;
    std::string course_id;
    std::string prof_name;
    unsigned short grade;
    unsigned short semester;

    friend std::ostream &operator<< (std::ostream &stream, struct grade &grade) {
        return stream << "| During Semester " << grade.semester << " they were examined in the Course named '" << grade.course_name << std::endl
                      << "| with Course ID " << grade.course_id << " and were graded a " << grade.grade << " by " << grade.prof_name << std::endl;
    }

} *Grade;

/// Base class for the Student and Professor objects.
class person {

protected:
    std::string name;                   // Person object's full name.
    std::string date_of_birth;          // Person object's date of birth.
    const unsigned int uni_id;          // Every person will have a unique numerical sequence called their "uni id".

public:
    person();
    person(std::string name, std::string date_of_birth, unsigned int uni_id);
    virtual ~person() = default;

    // Operator overloads.
    friend std::ostream &operator<< (std::ostream &stream, person &person);
    friend std::istream &operator>> (std::istream &stream, person &person);

    // Getters and Setters

    const std::string &getName() const { return name; }
    void setName(const std::string &new_name) { name = new_name; }

    const std::string &getDateOfBirth() const { return date_of_birth; }
    void setDateOfBirth(const std::string &dateOfBirth) { date_of_birth = dateOfBirth; }

    unsigned int getUniId() const { return uni_id; }

    // Pure virtual functions.
    virtual const std::string &getFormattedUniId() const = 0;

    // This variable tracks how many person objects have been created.
    // This number is used to generate the unique "uni id" for every person.
    static unsigned int amount_created;
};

/// Student class as derived from person.
class student : public person {

private:
    std::string date_of_registration;
    unsigned short ects;
    unsigned short semester;
    unsigned short mandatory_courses_passed;
    unsigned short total_courses_passed;

    const std::string formatted_uni_id;

    // This is where the student's grades will be stored.
    std::vector<Grade> grades;

public:

    student(unsigned short dept_code);
    student(const std::string &name, const std::string &date_of_birth, unsigned int uni_id,
            std::string date_of_registration, unsigned short ects, unsigned short semester,
            unsigned short mandatory_courses_passed, unsigned short total_courses_passed, unsigned short dept_code);

    ~student() override;

    // Operator Overloads
    friend std::ostream &operator<<(std::ostream &stream, const student &student);
    friend std::istream &operator>>(std::istream &stream, student &student);

    // Getters and Setters.

    const std::string &getDateOfRegistration() const { return date_of_registration; }
    void setDateOfRegistration(const std::string &dateOfRegistration) { date_of_registration = dateOfRegistration; }

    unsigned short getEcts() const { return ects; }
    void setEcts(unsigned short new_ects) { ects = new_ects; }

    unsigned short getSemester() const { return semester; }
    void setSemester(unsigned short new_semester) { semester = new_semester; }

    unsigned short getMandatoryCoursesPassed() const { return mandatory_courses_passed; }
    void setMandatoryCoursesPassed(unsigned short mandatoryCoursesPassed) { mandatory_courses_passed = mandatoryCoursesPassed; }

    unsigned short getTotalCoursesPassed() const { return total_courses_passed; }
    void setTotalCoursesPassed(unsigned short totalCoursesPassed) { total_courses_passed = totalCoursesPassed; }

    const std::string &getFormattedUniId() const override { return formatted_uni_id; }

    const std::vector<Grade> &getGrades() const { return grades; }

    // Print student's grades.
    void printGrades(unsigned int semester);

    // Special variable that denotes the prefix of the formatted university id.
    static const char id_prefix = 'S';
};

/// Professor class as derived from person.
class professor : public person {

private:
    const std::string formatted_uni_id;

    // This is where the id's of the courses assigned to the professor object will be held.
    std::vector<unsigned int> assigned_courses;

public:
    professor(unsigned short dept_code);
    professor(const std::string &name, const std::string &date_of_birth, unsigned int uni_id, unsigned short dept_code);

    ~professor() override;

    // Operator overloads.
    friend std::ostream &operator<< (std::ostream &stream, const professor &professor);
    friend std::istream &operator>> (std::istream &stream, professor &professor);

    // Getters and Setters

    const std::string &getFormattedUniId() const override { return formatted_uni_id; }

    const std::vector<unsigned int> &getAssignedCourses() const { return assigned_courses; }

    // Courses
    void assign(unsigned int id);

    // Special variable that denotes the prefix of the formatted university id.
    static const char id_prefix = 'P';
};

#endif //UNIMANAGEMENT_PERSON_H
