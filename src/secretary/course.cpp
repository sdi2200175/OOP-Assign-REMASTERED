//
// Created by Spyros Strakosia on 26/1/24.
//

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

course::course(std::string name, unsigned short ects, unsigned short semester, bool mandatory,
               const unsigned int uni_id, unsigned short dept_code) : name(std::move(name)), ects(ects), semester(semester),
               mandatory(mandatory), uni_id(uni_id),
               formatted_uni_id(std::string(1, id_prefix) + "-" + std::string(4 - std::to_string(dept_code).length(), '0') +
                                std::to_string(dept_code) +
                                "-" + std::string(7 - std::to_string(uni_id).length(), '0') + std::to_string(uni_id)) {

    if (uni_id > amount_created)
        amount_created = uni_id;
}

std::ostream &operator<<(std::ostream &stream, const course &course) {
    stream << "| Course Name: " << course.name << std::endl
           << "| Course ECT(s): " << course.ects << " ECT(s)" << std::endl
           << "| Course Semester: " << course.semester << std::endl
           << "| This Course is " << (course.mandatory ? "" : "not") << " mandatory." << std::endl
           << "| This Course is attended by " << course.attendees.size() << " Student(s)" << std::endl
           << "| Assigned Professors are: ";

    for (auto itr = course.assigned_professors.begin(); itr != course.assigned_professors.end(); itr++) {
        if (itr + 1 == course.assigned_professors.end())
            stream << (*itr)->getName();
        else
            stream << (*itr)->getName() << ", ";
    }

    return stream << std::endl << "| University ID: " << course.formatted_uni_id << std::endl;
}

std::istream &operator>>(std::istream &stream, course &course) {
    while (true) {
        try {
            course.name = io::input::name(stream, "Enter Course Name:");
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }
    }

    while (true) {
        try {
            course.ects = io::input::number<unsigned short>(stream, "Enter Course ECT(s):", 9);
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        } catch (std::out_of_range &e) {
            std::cout << e.what() << std::endl;
        }
    }

    while (true) {
        try {
            course.semester = io::input::number<unsigned short>(stream, "Enter Course Semester:", 9);
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        } catch (std::out_of_range &e) {
            std::cout << e.what() << std::endl;
        }
    }

    while (true) {
        try {
            course.mandatory = io::input::boolean(stream, "Will this Course be mandatory?");
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }
    }

    return stream;
}

void course::assign(professor *professor) {
    assigned_professors.insert(assigned_professors.end(), professor);
    professor->assign(this->uni_id);
}
