/**
 * @file interface.cpp
 * @brief This file contains the definition of the interface class functions.
 * @authors Evaggelia Ragkousi, Spyros Strakosia
 * @date 26/01/2024
 */

#include <string.h>

#include "io.h"
#include "interface.h"

interface::interface() {

    // Create the secretary manually and show its properties.
    this->sec = io::output::buildObj<secretary>("Building Department Secretary...");
    io::output::showAttr<secretary>("Department Information", this->sec, true);

    std::cout << "? Attempting to import Student Information from '" << io::stud_db_name << "'..." << std::endl;

    std::ifstream stud_db(io::stud_db_name);
    if (stud_db.is_open()) {
        while (stud_db.good()) {
            std::string buffer;
            getline(stud_db, buffer);
            if (!stud_db.good())
                break;

            char name[100], date_of_birth[11], date_of_registration[11];
            unsigned int uni_id, ects, semester, mandatory_courses_passed, total_courses_passed;
            if (std::sscanf(buffer.c_str(), "info: {'%[^']', %u, '%[^']', '%[^']', %u, %u, %u, %u}\n", 
                   name, &uni_id, date_of_birth, date_of_registration, &ects, &semester, &mandatory_courses_passed, &total_courses_passed) != 8) {

                std::cout << "Completed parsing of file '" << io::stud_db_name << "'." << std::endl;
                break;
            }

            student *stud = new student(name, date_of_birth, uni_id, date_of_registration, 
                                        ects, semester, mandatory_courses_passed, total_courses_passed, sec->getDeptCode());

            getline(stud_db, buffer);
            if (!stud_db.good())
                break;

            std::string temp;
            auto itr_begin = std::find(buffer.begin(), buffer.end(), '{');
            auto itr_end = std::find(buffer.begin(), buffer.end(), '}');
            for (auto itr = itr_begin + 1; itr != itr_end; itr++) {
                if (*itr == ',') {
                    stud->registr(stoi(temp));
                    temp.clear();
                    itr++;
                    continue;
                } 

                temp.insert(temp.end(), *itr);
            }

            stud->registr(stoi(temp));

            getline(stud_db, buffer);
            if (!stud_db.good())
                break;

            itr_begin = std::find(buffer.begin(), buffer.end(), '{');
            itr_end = buffer.begin() + buffer.rfind('}');
            for (auto itr = itr_begin + 1; itr != itr_end; itr++) {

                auto inner_itr_begin = std::find(itr, itr_end, '{');
                auto inner_itr_end = std::find(itr, itr_end, '}');
                std::string new_grade(inner_itr_begin, inner_itr_end + 1);
                itr = inner_itr_end;
                
                char course_name[100], prof_name[100];
                unsigned int course_id, grade_num, semester, ects, mandatory;
                std::sscanf(new_grade.c_str(), "{'%[^']', %u, '%[^']', %u, %u, %u, %u}\n", 
                   course_name, &course_id, prof_name, &grade_num, &semester, &ects, &mandatory);

                Grade grade = new struct grade(course_name, course_id, prof_name, grade_num, semester, ects, mandatory);
                stud->addGradeWithoutCheck(grade);
            }

            getline(stud_db, buffer);
            if (!stud_db.good())
                break;

            std::cout << *stud;

            sec->add(stud);
        }

    } else {
        std::cout << "! ERROR: Failed to open '" << io::stud_db_name << "'. Ignore this message if the file doesn't exist." << std::endl;
    }

    // Wait for user confirmation.
    io::input::await("Proceed to the Main Menu?");
}

interface::~interface() {

    std::ofstream stud_db("data/student_db");
    std::ofstream prof_db("data/professor_db");
    for (auto itr = sec->getIdDatabase().begin(); itr != sec->getIdDatabase().end(); itr++)
        if (itr->second->getFormattedUniId()[0] == 'S')
            stud_db << *((student *)(itr->second));
        else
            prof_db << *((professor *)(itr->second));

    stud_db.close();
    prof_db.close();

    std::ofstream course_db("data/course_db");
    for (auto itr = sec->getCourseIdDatabase().begin(); itr != sec->getCourseIdDatabase().end(); itr++)
        course_db << *((course *)(itr->second));

    delete sec;
}

io::SHOULD_EXIT interface::main_menu() {

    const std::string menu_title = "Main Menu";
    const std::string options[] = { "Manage Student(s)", 
                                    "Manage Professor(s)", 
                                    "Manage Course(s)",
                                    "Show Potential Graduates", 
                                    "Move to the next Semester",
                                    "Save to Local Files and Exit" };

    while (true) {

        std::stringstream ss;
        ss << "  Department Information" << std::endl << io::output::divider << std::endl << *sec << io::output::divider
           << std::endl;
        io::output::menu(ss.str(), menu_title, sizeof(options) / sizeof(options[0]), options);

        unsigned char option;
        while (true) {
            try {
                option = io::input::number<unsigned char>(std::cin, "Choose one of the options above:",
                                                          sizeof(options) / sizeof(options[0]));
                break;
            } catch (std::invalid_argument &e) {
                std::cout << e.what() << std::endl;
            }
        }

        CHECK_EXIT(option);

        switch (option) {

            case 1:
                CHECK_EXIT(studentManagement());
                break;

            case 2:
                CHECK_EXIT(professorManagement());
                break;

            case 3:
                CHECK_EXIT(courseManagement());
                break;

            case 5:
                try {
                    sec->incrementSemester();
                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                }

                io::input::await("Return to Main Menu?");
                break;

            default:
                return io::NO_EXIT;
        }
    }
}
