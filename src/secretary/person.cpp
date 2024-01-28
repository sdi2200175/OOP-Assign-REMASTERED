/**
 * @file person.cpp
 * @brief This file contains the definition of the interface class functions for
 * the person interfacing parts.
 * @authors Spyros Strakosia, Evaggelia Ragkousi
 * @date 27/01/2024
 */

#include <utility>

#include "io.h"
#include "person.h"

unsigned int person::amount_created = 0;

person::person() : uni_id(++person::amount_created) {
    std::cin >> *this;
}

person::person(std::string name, std::string date_of_birth, unsigned int uni_id) :
        name(std::move(name)), date_of_birth(std::move(date_of_birth)), uni_id(uni_id) {

    if (this->uni_id > person::amount_created)
        amount_created = this->uni_id;
}

// Overload of the output stream operator.
std::ostream &operator<<(std::ostream &stream, person &person) {
    return stream << "| Full Name: " << person.name << std::endl
                  << "| Date of Birth: " << person.date_of_birth << std::endl;
}

// Overload of the input stream operator.
std::istream &operator>>(std::istream &stream, person &person) {

    while (true) {
        try {
            person.name = io::input::name(stream, "Enter Full Name:");
            break;
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }
    }

    while (true) {
        try {
            person.date_of_birth = io::input::date(stream, "Enter Date of Birth:");
            break;
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        } catch (std::out_of_range &e) {
            std::cout << e.what() << std::endl;
        }
    }

    return stream;
}





///////////////////////////////////////////////// Student Functions /////////////////////////////////////////////////






student::student(unsigned short dept_code) :
        person(), ects(0), semester(1), mandatory_courses_passed(0), total_courses_passed(0),
        formatted_uni_id(std::string(1, id_prefix) + "-" + std::string(4 - std::to_string(dept_code).length(), '0') +
                         std::to_string(dept_code) +
                         "-" + std::string(7 - std::to_string(uni_id).length(), '0') + std::to_string(uni_id)) {

    std::cin >> *this;
}

student::student(const std::string &name, const std::string &date_of_birth, unsigned int uni_id,
                 std::string date_of_registration, unsigned short ects, unsigned short semester,
                 unsigned short mandatory_courses_passed, unsigned short total_courses_passed, unsigned short dept_code)
        :
        person(name, date_of_birth, uni_id), date_of_registration(std::move(date_of_registration)),
        ects(ects), semester(semester), mandatory_courses_passed(mandatory_courses_passed),
        total_courses_passed(total_courses_passed),
        formatted_uni_id(std::string(1, id_prefix) + "-" + std::string(4 - std::to_string(dept_code).length(), '0') +
                         std::to_string(dept_code) +
                         "-" + std::string(7 - std::to_string(uni_id).length(), '0') + std::to_string(uni_id)) {}

student::~student() {
    for (auto itr = grades.begin(); itr != grades.end(); itr++)
        delete (*itr);
}


std::ostream &operator<<(std::ostream &stream, const student &student) {
    return stream << *(person *) &student
                  << "| Date of Registration: " << student.date_of_registration << std::endl
                  << "| Amount of ECT(s): " << student.ects << std::endl
                  << "| Semester: " << student.semester << std::endl
                  << "| Amount of Mandatory Course(s) Passed: " << student.mandatory_courses_passed << " Course(s)" << std::endl
                  << "| Amount of Total Course(s) Passed: " << student.total_courses_passed << " Course(s)" << std::endl
                  << "| University ID: " << student.formatted_uni_id << std::endl;
}

std::istream &operator>>(std::istream &stream, student &student) {
    while (true) {
        try {
            student.date_of_registration = io::input::date(stream, "Enter Date of Registration:");
            break;
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        } catch (std::out_of_range &e) {
            std::cout << e.what() << std::endl;
        }
    }

    return stream;
}

std::ofstream &operator<<(std::ofstream &stream, const student &student) {

    stream << "info: {'" << student.name << "', " << student.uni_id << ", '" << student.date_of_birth << "', '" 
           << student.date_of_registration << "', " << student.ects << ", " << student.semester << ", " 
           << student.mandatory_courses_passed << ", " << student.total_courses_passed << "}\n";

    stream << "attending_courses: {";
    for (auto itr = student.getAttendingCourses().begin(); itr != student.getAttendingCourses().end(); itr++)
        stream << std::to_string(*itr) << (itr + 1 == student.getAttendingCourses().end() ? "" : ", ");

    stream << "}\n";

    stream << "grades: {";
    for (auto itr = student.getGrades().begin(); itr != student.getGrades().end(); itr++)
        stream << *(*itr) << (itr + 1 == student.grades.end() ? "" : ", ");

    stream << "}\n" << std::endl;
    return stream;
}

void student::printGrades(unsigned int semester) {
    if (!semester) {
        io::output::items<Grade>(std::cout, "Showing all grades:", grades, true);
    }

    std::vector<Grade> new_grades;
    for (auto itr = grades.begin(); itr != grades.end(); itr++)
        if (semester == (*itr)->semester)
            new_grades.insert(new_grades.end(), (*itr));

    io::output::items(std::cout, "Showing grades from Semester " + std::to_string(semester), new_grades, true);
}

void student::registr(unsigned int id) {
    attending_courses.insert(attending_courses.end(), id);
}

void student::addGrade(Grade grade) {

    int prev_grade = -1;

    // We check to see if this grade is already in the grades vector.
    for (auto itr = grades.begin(); itr != grades.end(); itr++)
        if ((*itr)->course_id == grade->course_id) {
            prev_grade = (*itr)->grade_num;
            delete *itr;
            grades.erase(itr);
            break;
        }

    grades.insert(grades.end(), grade);

    // If the student has passed the course e give them the ects
    // and mandatory pass if it was mandatory.
    if (grade->grade_num > 5 && prev_grade <= 5) {
        ects += grade->ects;
        mandatory_courses_passed += grade->mandatory;
        total_courses_passed += 1;
    } else if (grade->grade_num <= 5 && prev_grade > 5) {
        ects -= grade->ects;
        mandatory_courses_passed -= grade->mandatory;
        total_courses_passed -= 1;
    }
}

void student::checkIncrementationEligibility() {

    // We keep a variable that counts how many of the attending courses of the student
    // are graded.
    unsigned int courses_graded = 0;
    for (auto itr = grades.begin(); itr != grades.end(); itr++) {

        // If this grade was added in a previous semester we skip, else we count.
        if ((*itr)->semester != semester) continue;
        courses_graded++;
    }

    // If they can't progress we throw an invalid_argument.
    if (courses_graded != attending_courses.size())
        throw std::invalid_argument("! ERROR: Student with University ID: " + formatted_uni_id +
                                    " cannot progress to the next semester as they haven't been graded on all attending courses.");
}

void student::incrementSemester() {
    semester++;
    attending_courses.clear();
}






///////////////////////////////////////////////// Professor Functions /////////////////////////////////////////////////







professor::professor(unsigned short dept_code) :
        person(),
        formatted_uni_id(std::string(1, id_prefix) + "-" + std::string(4 - std::to_string(dept_code).length(), '0') +
                         std::to_string(dept_code) +
                         "-" + std::string(7 - std::to_string(uni_id).length(), '0') + std::to_string(uni_id)) {

    std::cin >> *this;
}

professor::professor(const std::string &name, const std::string &date_of_birth, unsigned int uni_id,
                     unsigned short dept_code) :
        person(name, date_of_birth, uni_id),
        formatted_uni_id(std::string(1, id_prefix) + "-" + std::string(4 - std::to_string(dept_code).length(), '0') +
                         std::to_string(dept_code) +
                         "-" + std::string(7 - std::to_string(uni_id).length(), '0') + std::to_string(uni_id)) {}

professor::~professor() {}

std::ostream &operator<<(std::ostream &stream, const professor &professor) {
    return stream << *(person *) &professor
                  << "| University ID: " << professor.getFormattedUniId() << std::endl;
}

std::istream &operator>>(std::istream &stream, professor &professor) {
    return stream;
}

std::ofstream &operator<<(std::ofstream &stream, const professor &professor) {

    stream << "info: {'" << professor.name << "', " << professor.uni_id << ", '" << professor.date_of_birth << "'}\n";

    stream << "assigned_courses: {";
    for (auto itr = professor.assigned_courses.begin(); itr != professor.assigned_courses.end(); itr++)
        stream << std::to_string(*itr) << (itr + 1 == professor.assigned_courses.end() ? "" : ", ");

    stream << "}\n" << std::endl;
    return stream;
}

void professor::assign(unsigned int id) {
    assigned_courses.insert(assigned_courses.end(), id);
}

void professor::incrementSemester() {
    assigned_courses.clear();
}