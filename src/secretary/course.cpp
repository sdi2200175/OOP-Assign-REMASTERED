/**
 * @file course.cpp
 * @brief This file contains the definition of the interface class functions for
 * the course interfacing parts.
 * @authors Spyros Strakosia, Evaggelia Ragkousi
 * @date 27/01/2024
 */

#include "io.h"
#include "course.h"

unsigned int course::amount_created = 0;

course::course(unsigned short dept_code) :
        uni_id(++amount_created),
        formatted_uni_id(std::string(1, id_prefix) + "-" + std::string(4 - std::to_string(dept_code).length(), '0') +
                         std::to_string(dept_code) +
                         "-" + std::string(7 - std::to_string(uni_id).length(), '0') + std::to_string(uni_id)) {

    std::cin >> *this;
}

course::course(course &cour) : 
    name(cour.name), ects(cour.ects), semester(cour.semester), mandatory(cour.mandatory), uni_id(++course::amount_created),
    formatted_uni_id(std::string(1, id_prefix) + "-" + cour.formatted_uni_id.substr(2, 4) 
    + "-" + std::string(7 - std::to_string(uni_id).length(),'0') + std::to_string(uni_id)) {

    for (auto itr = cour.attendees.begin(); itr != cour.attendees.end(); itr++)
        attendees.insert(attendees.end(), new student(*(student *)(*itr)));

    for (auto itr = cour.assigned_professors.begin(); itr != cour.assigned_professors.end(); itr++)
        assigned_professors.insert(assigned_professors.end(), new professor(*(professor *)(*itr)));

}

course::course(std::string name, unsigned short ects, unsigned short semester, bool mandatory,
               const unsigned int uni_id, unsigned short dept_code) : name(std::move(name)), ects(ects),
               semester(semester), mandatory(mandatory), uni_id(uni_id),
               formatted_uni_id(std::string(1, id_prefix) + "-" + std::string(4 - std::to_string(dept_code).length(), '0') +
               std::to_string(dept_code) + "-" + std::string(7 - std::to_string(uni_id).length(),'0') + std::to_string(uni_id)) {

    if (this->uni_id > course::amount_created)
        amount_created = this->uni_id;
}

// Overload of the output stream operator.
std::ostream &operator<<(std::ostream &stream, const course &course) {
    stream << "| Course Name: " << course.name << std::endl
           << "| Course ECT(s): " << course.ects << " ECT(s)" << std::endl
           << "| Course Semester: " << course.semester << std::endl
           << "| This Course is " << (course.mandatory ? "" : "not ") << "mandatory." << std::endl
           << "| This Course is attended by " << course.attendees.size() << " Student(s)" << std::endl
           << "| Assigned Professors are: ";

    if (course.assigned_professors.empty())
        stream << "None";
    else
        for (auto itr = course.assigned_professors.begin(); itr != course.assigned_professors.end(); itr++) {
            if (itr + 1 == course.assigned_professors.end())
                stream << (*itr)->getName();
            else
                stream << (*itr)->getName() << ", ";
        }

    return stream << std::endl << "| University ID: " << course.formatted_uni_id << std::endl;
}

// Overload of the input stream operator.
std::istream &operator>>(std::istream &stream, course &course) {

    while (true) {
        try {
            course.name = io::input::name(stream, "Enter Course Name:");
            break;
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }
    }

    while (true) {
        try {
            course.ects = io::input::number<unsigned short>(stream, "Enter Course ECT(s):", 9);
            break;
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        } catch (std::out_of_range &e) {
            std::cout << e.what() << std::endl;
        }
    }

    while (true) {
        try {
            course.semester = io::input::number<unsigned short>(stream, "Enter Course Semester:", 9);
            break;
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        } catch (std::out_of_range &e) {
            std::cout << e.what() << std::endl;
        }
    }

    while (true) {
        try {
            course.mandatory = io::input::boolean(stream, "Will this Course be mandatory?");
            break;
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }
    }

    return stream;
}

std::ofstream &operator<<(std::ofstream &stream, const course &course) {

    stream << "info: {'" << course.name << "', " << course.ects << ", " << course.semester << ", " 
           << course.mandatory << ", " << course.uni_id << "}\n";

    stream << "assigned_professors: {";
    for (auto itr = course.assigned_professors.begin(); itr != course.assigned_professors.end(); itr++)
        stream << std::to_string((*itr)->getUniId()) << (itr + 1 == course.assigned_professors.end() ? "" : ", ");

    stream << "}\n";

    stream << "registered_students: {";
    for (auto itr = course.attendees.begin(); itr != course.attendees.end(); itr++)
        stream << std::to_string((*itr)->getUniId()) << (itr + 1 == course.attendees.end() ? "" : ", ");

    stream << "}\n" << std::endl;
    return stream;
}

void course::assign(professor *professor) {
    if (std::find(assigned_professors.begin(), assigned_professors.end(), professor) != assigned_professors.end())
        throw std::invalid_argument("! ERROR: Professor is already assigned to this Course.");

    assigned_professors.insert(assigned_professors.end(), professor);
    professor->assign(this->uni_id);
}

void course::registr(student *student) {
    if (std::find(attendees.begin(), attendees.end(), student) != attendees.end())
        throw std::invalid_argument("! ERROR: Student is already registered to this Course.");

    attendees.insert(attendees.end(), student);
    student->registr(this->uni_id);
}

void course::incrementSemester() {
    attendees.clear();
    assigned_professors.clear();
}
