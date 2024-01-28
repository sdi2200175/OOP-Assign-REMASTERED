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

    // Parsing the Student Database.
    std::cout << std::endl << "? Attempting to import Student Information from '" << io::stud_db_name << "'..." << std::endl;

    std::ifstream stud_db(io::stud_db_name);
    if (stud_db.is_open()) {
        while (stud_db.good()) {
            std::string buffer;
            getline(stud_db, buffer);

            char name[100], date_of_birth[11], date_of_registration[11];
            unsigned int uni_id, ects, semester, mandatory_courses_passed, total_courses_passed;
            if (std::sscanf(buffer.c_str(), "info: {'%[^']', %u, '%[^']', '%[^']', %u, %u, %u, %u}\n", 
                   name, &uni_id, date_of_birth, date_of_registration, &ects, &semester, &mandatory_courses_passed, &total_courses_passed) != 8) {

                std::cout << "| Completed parsing of file '" << io::stud_db_name << "'." << std::endl;
                break;
            }

            student *stud = new student(name, date_of_birth, uni_id, date_of_registration, 
                                        ects, semester, mandatory_courses_passed, total_courses_passed, sec->getDeptCode());


            getline(stud_db, buffer);
            if (!stud_db.good())
                break;

            getline(stud_db, buffer);
            if (!stud_db.good())
                break;

            auto itr_begin = std::find(buffer.begin(), buffer.end(), '{');
            auto itr_end = buffer.begin() + buffer.rfind('}');
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

            sec->add(stud);
        }

    } else {
        std::cout << "! ERROR: Failed to open '" << io::stud_db_name << "'. Ignore this message if the file doesn't exist." << std::endl;
    }


    // Parsing the Professor Database.
    std::cout << std::endl << "? Attempting to import Professor Information from '" << io::prof_db_name << "'..." << std::endl;

    std::ifstream prof_db(io::prof_db_name);
    if (prof_db.is_open()) {
        while (prof_db.good()) {
            std::string buffer;
            getline(prof_db, buffer);

            char name[100], date_of_birth[11];
            unsigned int uni_id;
            if (std::sscanf(buffer.c_str(), "info: {'%[^']', %u, '%[^']'\n", name, &uni_id, date_of_birth) != 3) {

                std::cout << "| Completed parsing of file '" << io::prof_db_name << "'." << std::endl;
                break;
            }

            professor *prof = new professor(name, date_of_birth, uni_id, sec->getDeptCode());

            getline(prof_db, buffer);
            if (!prof_db.good())
                break;

            getline(prof_db, buffer);
            if (!prof_db.good())
                break;

            sec->add(prof);
        }

    } else {
        std::cout << "! ERROR: Failed to open '" << io::prof_db_name << "'. Ignore this message if the file doesn't exist." << std::endl;
    }


    // Parsing the Course Database.
    std::cout << std::endl << "? Attempting to import Course Information from '" << io::cour_db_name << "'..." << std::endl;

    std::ifstream cour_db(io::cour_db_name);
    if (cour_db.is_open()) {
        while (cour_db.good()) {
            std::string buffer;
            getline(cour_db, buffer);

            char name[100];
            unsigned int uni_id, ects, semester, mandatory;
            if (std::sscanf(buffer.c_str(), "info: {'%[^']', %u, %u, %u, %u}\n", 
                   name, &uni_id, &ects, &semester, &mandatory) != 5) {

                std::cout << "| Completed parsing of file '" << io::cour_db_name << "'." << std::endl;
                break;
            }

            course *cour = new course(name, uni_id, ects, semester, mandatory, sec->getDeptCode());

            getline(cour_db, buffer);
            if (!cour_db.good())
                break;

            std::string temp;
            auto itr_begin1 = std::find(buffer.begin(), buffer.end(), '{');
            auto itr_end1 = std::find(buffer.begin(), buffer.end(), '}');
            for (auto itr = itr_begin1 + 1; itr != itr_end1; itr++) {
                if (*itr == ',') {
                    professor *prof = sec->retrieve<professor>((stoi(temp)));
                    cour->assign(prof);
                    temp.clear();
                    itr++;
                    continue;
                } 

                temp.insert(temp.end(), *itr);
            }

            if (!temp.empty()) {
                professor *prof = sec->retrieve<professor>((stoi(temp)));
                cour->assign(prof);
            }

            getline(cour_db, buffer);
            if (!cour_db.good())
                break;

            temp.clear();
            auto itr_begin2 = std::find(buffer.begin(), buffer.end(), '{');
            auto itr_end2 = std::find(buffer.begin(), buffer.end(), '}');
            for (auto itr = itr_begin2 + 1; itr != itr_end2; itr++) {
                if (*itr == ',') {
                    student *stud = sec->retrieve<student>((stoi(temp)));
                    cour->registr(stud);
                    temp.clear();
                    itr++;
                    continue;
                } 

                temp.insert(temp.end(), *itr);
            }

            if (!temp.empty()) {
                student *stud = sec->retrieve<student>((stoi(temp)));
                cour->registr(stud);
            }

            getline(cour_db, buffer);
            if (!cour_db.good())
                break;

            sec->add(cour);

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
        if (itr->second->getFormattedUniId()[0] == 'S'){
            stud_db << *((student *)(itr->second));
        } else
            prof_db << *((professor *)(itr->second));

    stud_db.close();
    prof_db.close();

    std::ofstream cour_db("data/course_db");
    for (auto itr = sec->getCourseIdDatabase().begin(); itr != sec->getCourseIdDatabase().end(); itr++)
        cour_db << *((course *)(itr->second));

    cour_db.close();

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

            case 4: {

                std::vector<student *> graduates;
                for (auto itr = sec->getIdDatabase().begin(); itr != sec->getIdDatabase().end(); itr++) {
                    if (((student *)(itr->second))->getMandatoryCoursesPassed() >= sec->getMandatoryCourses() 
                        && ((student *)(itr->second))->getEcts() >= sec->getRequiredEcts()
                        && ((student *)(itr->second))->getSemester() >= sec->getMinAttendance() * 2) {

                        graduates.insert(graduates.end(), (student *)itr->second);
                    }
                }

                io::output::items<student *>(std::cout, "Students Eligible for Graduation", graduates, true);
                io::input::await("Return to Main Menu?");
                break;
            }

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
