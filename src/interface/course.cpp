/**
 * @file interface.cpp
 * @brief This file contains the definition of the interface class functions for
 * the course interfacing parts.
 * @authors Evaggelia Ragkousi, Spyros Strakosia
 * @date 26/01/2024
 */

#include "io.h"
#include "interface.h"

io::SHOULD_EXIT interface::courseManagement() {

    const std::string menu_title = "Course Management Menu";
    const std::string options[] = {"Add a new Course",
                                   "Modify an existing Course",
                                   "Remove a Course",
                                   "Assign Professor to Course",
                                   "Register Student to Course",
                                   "Return to Main Menu"};

    // The inner menu loop.
    while (true) {

        io::output::menu(std::string(), menu_title, sizeof(options) / sizeof(options[0]), options);

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

            // Add a course to the department
            case 1: {
                // We first build the course and then show the object's attributes.
                course *stud = io::output::buildObj<course, unsigned short>("Creating New Course...",
                                                                            sec->getDeptCode());
                io::output::showAttr<course>("Course Information", stud, true);

                // We continuously ask for the user's input until it is correct whether they would like to add
                // the course to the department.
                while (true) {

                    // If the user's input is unexpected we throw catch an exception from io::input::boolean
                    try {
                        // If the user types 'yes' we add the course, else we delete the object and print a relevant message
                        if (io::input::boolean(std::cin, "Would to like to add this Course to the Department?")) {
                            sec->add(stud);
                            std::cout << "Course added successfully!" << std::endl;
                        } else {
                            delete stud;
                            std::cout << "Operation Aborted." << std::endl;
                        }

                        break;
                    } catch (std::invalid_argument &e) {
                        std::cout << e.what() << std::endl;
                    }
                }

                // We wait for confirmation before returning to the menu screen.
                io::input::await("Return to " + menu_title);
                break;
            }

                // Course removal.
            case 3: {

                // We store pointers to the relevant retrieval functions.
                course *(secretary::*id_search)(unsigned int) = &secretary::retrieve<course>;
                course *(secretary::*name_search)(const std::string &) = &secretary::retrieve<course>;
                course *cour;

                // We search for the Course and catch any exceptions that might be thrown from io::input::search.
                try {
                    cour = io::input::search<course>(std::cin,
                                                     "Enter the Full Name or the University UD of the Course you would like to remove:",
                                                     *sec,
                                                     id_search, name_search);
                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                    io::input::await("Return to Course Management Menu?");
                    break;
                } catch (std::out_of_range &e) {
                    std::cout << e.what() << std::endl;
                    io::input::await("Return to Course Management Menu?");
                    break;
                }

                // We show the Course information and ask for the user's input whether they want to
                // delete the student or not.
                io::output::showAttr<course>("Found the following Course", cour, true);
                while (true) {

                    // We prepare for and catch any exception that might be thrown from io::input::boolean.
                    try {

                        // If the user types 'yes' we remove the Course and delete the heap allocated memory
                        // the object occupies.
                        if (io::input::boolean(std::cin, "Would you like to remove this Course?")) {
                            sec->remove(cour);
                            delete cour;
                            std::cout << "Course removed successfully!" << std::endl;
                        } else {
                            std::cout << "Operation Aborted." << std::endl;
                        }

                        break;
                    } catch (std::invalid_argument &e) {
                        std::cout << e.what() << std::endl;
                    }
                }

                // We wait for the user's input and return to the menu.
                io::input::await("Return to " + menu_title);
                break;
            }

                // Course Assignment.
            case 4: {
                courseAssignment();
                io::input::await("Return to " + menu_title);
                break;
            }

                // Register Student to Course.
            case 5: {
                courseRegistration();
                io::input::await("Return to " + menu_title);
                break;
            }

            default:
                return io::NO_EXIT;
        }
    }
}







/////////////////////////////////////////////// Helper Functions ///////////////////////////////////////////////






void interface::courseRegistration() {

    // We search for the student and catch any exceptions that might be thrown from io::input::search.
    try {

        // We store pointers to the relevant retrieval functions and search for the student.
        student *(secretary::*id_search)(unsigned int) = &secretary::retrieve<student>;
        student *(secretary::*name_search)(const std::string &) = &secretary::retrieve<student>;
        student *stud = io::input::search<student>(std::cin,
                                                   "Enter the Full Name or the University ID of the Student who you'd like to register to a Course:",
                                                   *sec, id_search, name_search);

        // We show the student information.
        io::output::showAttr<student>("Found the following Student", stud, true);

        // If the user types 'no' we abort.
        if (!io::input::boolean(std::cin, "Would you like to register this Student?"))
            throw std::invalid_argument("Operation Aborted.");

        // We store pointers to the relevant retrieval functions.
        course *(secretary::*course_id_search)(unsigned int) = &secretary::retrieveCourse;
        course *(secretary::*course_name_search)(const std::string &) = &secretary::retrieveCourse;
        course *cour;

        // We search for the course and catch any exceptions that might be thrown from io::input::search.
        cour = io::input::search<course>(std::cin,
                                         "Enter the Full Name or the University ID of the Course you would like to register the Student to:",
                                         *sec,
                                         course_id_search, course_name_search);

        // If the user types 'no' we abort.
        if (!io::input::boolean(std::cin, "Would you like to register this Student to this Course?"))
            throw std::invalid_argument("Operation Aborted.");

        cour->registr(stud);
        std::cout << "Student registered successfully!" << std::endl;

    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
    } catch (std::out_of_range &e) {
        std::cout << e.what() << std::endl;
    }
}

void interface::courseAssignment() {

    // We search for the student and catch any exceptions that might be thrown from io::input::search.
    try {

        // We store pointers to the relevant retrieval functions.
        professor *(secretary::*id_search)(unsigned int) = &secretary::retrieve<professor>;
        professor *(secretary::*name_search)(const std::string &) = &secretary::retrieve<professor>;
        professor *prof;

        // Search for the professor.
        prof = io::input::search<professor>(std::cin,
                                            "Enter the Full Name or the University ID of the Professor you would like to assign:",
                                            *sec,
                                            id_search, name_search);

        // We show the Professor information and ask for the user's input.
        io::output::showAttr<professor>("Professor Information", prof, true);

        // If the user types 'no' we abort.
        if (!io::input::boolean(std::cin, "Would you like to assign this Professor?"))
            throw std::invalid_argument("Operation Aborted.");

        // We store pointers to the relevant retrieval functions.
        course *(secretary::*course_id_search)(unsigned int) = &secretary::retrieveCourse;
        course *(secretary::*course_name_search)(const std::string &) = &secretary::retrieveCourse;
        course *cour;

        // Search for the course.
        cour = io::input::search<course>(std::cin,
                                         "Enter the Full Name or the University ID of the Course you would like assigned:",
                                         *sec,
                                         course_id_search, course_name_search);

        // We show the Course information and ask for the user's input whether they want to
        // submit the grade for this course.
        io::output::showAttr<course>("Course Information", cour, true);

        // If the user types 'no' we abort.
        if (!io::input::boolean(std::cin, "Would you like to assign this Professor to this Course?"))
            throw std::invalid_argument("Operation Aborted.");

        cour->assign(prof);
        std::cout << "Professor has been assigned successfully." << std::endl;

    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
    } catch (std::out_of_range &e) {
        std::cout << e.what() << std::endl;
    }
}
