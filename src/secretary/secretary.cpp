//
// Created by Spyros Strakosia on 25/1/24.
//

#include "io.h"
#include "secretary.h"

secretary::secretary() {
    std::cin >> *this;
}

secretary::secretary(std::string dept_name, unsigned int dept_code, unsigned short min_attendance,
                     unsigned short required_ects, unsigned short mandatory_courses, Semester semester) : dept_name(std::move(dept_name)),
                                                                                                          dept_code(dept_code),
                                                                                                          min_attendance(min_attendance),
                                                                                                          required_ects(required_ects),
                                                                                                          mandatory_courses(mandatory_courses),
                                                                                                          semester(semester) {}


secretary::~secretary() {
    for (auto itr = id_database.begin(); itr != id_database.end(); itr++) {
        if (itr->second->getFormattedUniId()[0] == 'S')
            delete (student *) (itr->second);
        else
            delete (professor *) (itr->second);
    }

    for (auto itr = course_id_database.begin(); itr != course_id_database.end(); itr++) {
        delete itr->second;
    }
}

std::ostream &operator<<(std::ostream &stream, const secretary &sec) {
    return stream << "| Department's Name: " << sec.dept_name << std::endl
                  << "| Department's Code: " << sec.dept_code << std::endl
                  << "| Department's Minimum Years of Attendance: " << sec.min_attendance << " Year(s)" << std::endl
                  << "| Department's ECT Requirement: " << sec.required_ects << " ECT(s)" << std::endl
                  << "| Department's Mandatory Courses: " << sec.mandatory_courses << " Course(s)" << std::endl
                  << "| Department's Students: " << sec.calculateStudentSize() << " Student(s)" << std::endl
                  << "| Department's Professors: " << sec.calculateProfessorSize() << " Professor(s)" << std::endl
                  << "| Current Semester: " << (sec.semester == FALL ? "Fall Semester" : "Spring Semester") << std::endl;
}

std::istream &operator>>(std::istream &stream, secretary &secretary) {

    while (true) {
        try {
            secretary.dept_name = io::input::name(stream, "Enter Department's Name:");
            break;
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }
    }

    while (true) {
        try {
            secretary.dept_code = io::input::number<unsigned int>(stream, "Enter Department's Code:", 9999);
            break;
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        } catch (std::out_of_range &e) {
            std::cout << e.what() << std::endl;
        }
    }

    while (true) {
        try {
            secretary.min_attendance = io::input::number<unsigned short>(stream, "Enter Department's Minimum Years of Attendance:",
                                                                         9);
            break;
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        } catch (std::out_of_range &e) {
            std::cout << e.what() << std::endl;
        }
    }

    while (true) {
        try {
            secretary.required_ects = io::input::number<unsigned short>(stream, "Enter Department's ECT Requirement:",
                                                                        299);
            break;
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        } catch (std::out_of_range &e) {
            std::cout << e.what() << std::endl;
        }
    }

    while (true) {
        try {
            secretary.mandatory_courses = io::input::number<unsigned short>(stream,
                                                                            "Enter Department's Mandatory Courses:", 99);
            break;
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        } catch (std::out_of_range &e) {
            std::cout << e.what() << std::endl;
        }
    }

    return stream;
}

void secretary::add(person *per) {
    id_database.insert({per->getUniId(), per});
    name_database.insert({per->getName(), per});
}

void secretary::add(course *cour) {
    course_id_database.insert({cour->getUniId(), cour});
    course_name_database.insert({cour->getName(), cour});
}

course *secretary::retrieveCourse(unsigned int id) {
    auto itr = course_id_database.find(id);
    if (itr == course_id_database.end())
        throw std::out_of_range("! ERROR: This ID does not belong to any university Course.");

    return itr->second;
}

course *secretary::retrieveCourse(const std::string &name) {
    auto itr = course_name_database.find(name);
    if (itr == course_name_database.end())
        throw std::out_of_range("! ERROR: No course named '" + name + "' exists.");

    return itr->second;
}

void secretary::remove(person *per) {
    id_database.erase(per->getUniId());
    name_database.erase(per->getName());
}

void secretary::remove(course *cour) {
    course_id_database.erase(cour->getUniId());
    course_name_database.erase(cour->getName());
}

unsigned int secretary::calculateStudentSize() const {
    unsigned int size = 0;
    for (auto itr = id_database.begin(); itr != id_database.end(); itr++) {
        if (itr->second->getFormattedUniId()[0] == 'S')
            size++;
    }
    return size;
}

unsigned int secretary::calculateProfessorSize() const {
    unsigned int size = 0;
    for (auto itr = id_database.begin(); itr != id_database.end(); itr++) {
        if (itr->second->getFormattedUniId()[0] == 'P')
            size++;
    }
    return size;
}

void secretary::incrementSemester() {

    // First we check to see if we CAN increment the semester.
    // All student must have been graded in every course they are currently attending
    // for this semester before the semester can increment.
    for (auto itr = id_database.begin(); itr != id_database.end(); itr++) {

        // If we encountered a professor we skip.
        if (itr->second->getFormattedUniId()[0] == 'P') continue;

        ((student *) (itr->second))->checkIncrementationEligibility();
    }

    // If every student can be incremented we do so, first for all person objects.
    for (auto itr = id_database.begin(); itr != id_database.end(); itr++) {
        itr->second->incrementSemester();
    }

    // And then for every course object.
    for (auto itr = course_id_database.begin(); itr != course_id_database.end(); itr++) {
        itr->second->incrementSemester();
    }

    // We clear databases within course and professors and then change the semester variable in the secretary.
    if (semester == FALL)
        semester = SPRING;
    else
        semester = FALL;
}
