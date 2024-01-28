/**
 * @file person.h
 * @brief This file contains the definition of the person, student and professor
 * classes.
 * @authors Evaggelia Ragkousi, Spyros Strakosia
 * @date 25/01/2024
 */

#ifndef UNIMANAGEMENT_PERSON_H
#define UNIMANAGEMENT_PERSON_H

#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

/// Struct used to statically store the grades in the student classes.
typedef struct grade {
    std::string course_name;
    unsigned int course_id;
    std::string prof_name;
    unsigned short grade_num;
    unsigned short semester;
    unsigned short ects;
    bool mandatory;

    grade(std::string course_name, unsigned int course_id, std::string prof_name,
          unsigned short grade_num,
          unsigned short semester, unsigned short ects, bool mandatory) : course_name(std::move(course_name)),
                                                                          course_id(course_id),
                                                                          prof_name(std::move(prof_name)), grade_num(grade_num),
                                                                          semester(semester), ects(ects),
                                                                          mandatory(mandatory) {}

    friend std::ostream &operator<<(std::ostream &stream, const struct grade &grade) {
        return stream << "| During Semester " << grade.semester << " they were examined in the Course named '"
                      << grade.course_name << " and were graded a " << grade.grade_num << " by " << grade.prof_name
                      << std::endl;
    }

    friend std::ofstream &operator<<(std::ofstream &stream, const struct grade &grade) {
        stream << "{" << grade.course_name << ", " << grade.course_id << ", " << grade.prof_name << ", "
               << grade.grade_num << ", " << grade.semester << ", " << grade.ects << ", " << grade.mandatory << "}"
               << std::endl;

        return stream;
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
    friend std::ostream &operator<<(std::ostream &stream, person &person);

    friend std::istream &operator>>(std::istream &stream, person &person);

    // Getters and Setters

    const std::string &getName() const { return name; }

    void setName(const std::string &new_name) { name = new_name; }

    const std::string &getDateOfBirth() const { return date_of_birth; }

    void setDateOfBirth(const std::string &dateOfBirth) { date_of_birth = dateOfBirth; }

    unsigned int getUniId() const { return uni_id; }

    // Pure virtual functions.
    virtual const std::string &getFormattedUniId() const = 0;

    virtual void incrementSemester() = 0;

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

    // The student's currently attending classes.
    std::vector<unsigned int> attending_courses;

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

    friend std::ofstream &operator<<(std::ofstream &stream, const student &student);

    // Getters and Setters.

    const std::string &getDateOfRegistration() const { return date_of_registration; }

    void setDateOfRegistration(const std::string &dateOfRegistration) { date_of_registration = dateOfRegistration; }

    unsigned short getEcts() const { return ects; }

    void setEcts(unsigned short new_ects) { ects = new_ects; }

    unsigned short getSemester() const { return semester; }

    void setSemester(unsigned short new_semester) { semester = new_semester; }

    unsigned short getMandatoryCoursesPassed() const { return mandatory_courses_passed; }

    void setMandatoryCoursesPassed(
            unsigned short mandatoryCoursesPassed) { mandatory_courses_passed = mandatoryCoursesPassed; }

    unsigned short getTotalCoursesPassed() const { return total_courses_passed; }

    void setTotalCoursesPassed(unsigned short totalCoursesPassed) { total_courses_passed = totalCoursesPassed; }

    const std::string &getFormattedUniId() const override { return formatted_uni_id; }

    const std::vector<Grade> &getGrades() const { return grades; }

    const std::vector<unsigned int> &getAttendingCourses() const { return attending_courses; }

    // Register to a course.
    void registr(unsigned int id);

    // Add a grade.
    void addGrade(Grade grade);

    // Print student's grades.
    void printGrades(unsigned int semester);

    // Check whether the student can progress to the next semester.
    void checkIncrementationEligibility();

    // Progress to the next Semester.
    void incrementSemester() override;

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
    friend std::ostream &operator<<(std::ostream &stream, const professor &professor);

    friend std::istream &operator>>(std::istream &stream, professor &professor);

    // Getters and Setters

    const std::string &getFormattedUniId() const override { return formatted_uni_id; }

    const std::vector<unsigned int> &getAssignedCourses() const { return assigned_courses; }

    // Courses
    void assign(unsigned int id);

    // Progress to the next Semester.
    void incrementSemester() override;

    // Special variable that denotes the prefix of the formatted university id.
    static const char id_prefix = 'P';
};

#endif //UNIMANAGEMENT_PERSON_H
