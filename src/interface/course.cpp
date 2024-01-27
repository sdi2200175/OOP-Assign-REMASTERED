/**
 * @file course.cpp
 * @brief This file contains the definition of the interface class functions for
 * the course interfacing parts.
 * @authors Spyros Strakosia, Evaggelia Ragkousi
 * @date 27/01/2024
 */

#include "io.h"
#include "interface.h"

io::SHOULD_EXIT interface::courseManagement() {

    const std::string menu_title = "Course Management Menu";
    const std::string options[] = { "Add a new Course",
                                    "Modify an existing Course",
                                    "Remove a Course",
                                    "Assign a Professor to a Course",
                                    "Register a Student to a Course",
                                    "Return to Main Menu" };

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

            // Add a Course to the department.
            case 1: {

                // If the user's input is unexpected we throw catch an exception from io::input::boolean.
                try {

                    // We first build the course and then show the object's attributes.
                    course *cour = io::output::buildObj<course, unsigned short>("Creating New Course...",
                                                                                sec->getDeptCode());
                    io::output::showAttr<course>("Course Information", cour, true);

                    // If the user types 'yes' we add the course, else we delete the object and print a relevant message.
                    if (!io::input::boolean(std::cin, "Would to like to add this Course to the Department?")) {
                        delete cour;
                        throw std::invalid_argument("Operation Aborted.");
                    }

                    sec->add(cour);
                    std::cout << "Course added successfully!" << std::endl;

                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                }

                // We wait for confirmation before returning to the menu screen.
                io::input::await("Return to " + menu_title);
                break;
            }

            // Modify an already existing Course. 
            case 2: {

                // We search for the Course and catch any exceptions that might be thrown from io::input::search.
                try {

                    // We store pointers to the relevant retrieval functions.
                    course *(secretary::*id_search)(unsigned int) = &secretary::retrieve<course>;
                    course *(secretary::*name_search)(const std::string &) = &secretary::retrieve<course>;
                    course *cour = io::input::search<course>(std::cin,
                                                             "Enter the Full Name or the University ID of the Course you would like to modify:",
                                                             *sec, id_search, name_search);

                    // We show the Course information and ask for the user's input whether they want to
                    // modify the course or not.
                    io::output::showAttr<course>("Course Information", cour, true);

                    // If the user types 'no' we abort.
                    if (!io::input::boolean(std::cin, "Would you like to modify this Course?"))
                        throw std::invalid_argument("Operation Aborted.");

                    if (cour->getAttendees().empty()) {
                        CHECK_EXIT(this->courseModification(cour));
                        std::cout << "Course modified successfully!" << std::endl;
                    }
                    else
                        throw std::invalid_argument("! ERROR: This Course cannot be modified because there are Students attending it.");

                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                } catch (std::out_of_range &e) {
                    std::cout << e.what() << std::endl;
                }

                // We wait for confirmation before returning to the menu screen.
                io::input::await("Return to " + menu_title);
                break;
            }

            // Remove a Course from the department.
            case 3: {

                // We search for the Course and catch any exceptions that might be thrown from io::input::search.
                try {

                    // We store pointers to the relevant retrieval functions.
                    course *(secretary::*id_search)(unsigned int) = &secretary::retrieve<course>;
                    course *(secretary::*name_search)(const std::string &) = &secretary::retrieve<course>;
                    course *cour = io::input::search<course>(std::cin,
                                                     "Enter the Full Name or the University ID of the Course you would like to remove:",
                                                     *sec, id_search, name_search);

                    // We show the Course information and ask for the user's input whether they want to
                    // delete the Course or not.
                    io::output::showAttr<course>("Course Information", cour, true);

                    // If the user types 'no' we abort.
                    if (!io::input::boolean(std::cin, "Would you like to remove this Course?"))
                        throw std::invalid_argument("Operation Aborted.");

                    if (cour->getAttendees().empty() && cour->getAssignedProfessors().empty()) {
                        sec->remove(cour);
                        delete cour;
                        std::cout << "Course removed successfully!" << std::endl;
                    } else
                        throw std::invalid_argument("! ERROR: Cannot remove Course while Student are attending it and/or Professors are assigned to it.");

                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                } catch (std::out_of_range &e) {
                    std::cout << e.what() << std::endl;
                }

                // We wait for the user's input and return to the menu.
                io::input::await("Return to " + menu_title);
                break;
            }

            // Assign a Professor to a Course.
            case 4: {
                courseAssignment();
                io::input::await("Return to " + menu_title);
                break;
            }

            // Register a Student to a Course.
            case 5: {
                courseRegistration();
                // We wait for the user's input and return to the menu.
                io::input::await("Return to " + menu_title);
                break;
            }

            default:
                return io::NO_EXIT;
        }
    }
}

io::SHOULD_EXIT interface::courseModification(course *cour) {

    const std::string menu_title = "Course Modification Menu";
    const std::string options[] = { "Change Course Name",
                                    "Change ECT(s)",
                                    "Change Mandatory Status",
                                    "Change Semester" 
                                    "Return to Course Management Menu "};

    // The inner menu loop.
    while (true) {

        std::stringstream ss;
        ss << "  Course Information" << std::endl << io::output::divider << std::endl << *cour << io::output::divider << std::endl;
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

            // Change name.
            case 1: {

                try {
                    std::string new_name;
                    new_name = io::input::name(std::cin, "Enter New Course Name:");
                    sec->remove(cour);
                    cour->setName(new_name);
                    sec->add(cour);
                    std::cout << "Name Changed Successfully!" << std::endl;
                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                }

                io::input::await("Return to " + menu_title + "?");
                break;
            }

            // Change ECT(s).
            case 2: {

                try {
                    unsigned short ects;
                    ects = io::input::number<unsigned short>(std::cin, "Enter new ECT(s):", 9);
                    cour->setEcts(ects);
                    std::cout << "ECT(s) Changed Successfully!" << std::endl;
                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                } catch (std::out_of_range &e) {
                    std::cout << e.what() << std::endl;
                }

                io::input::await("Return to " + menu_title + "?");
                break;
            }

            // Change mandatory status.
            case 3: {

                try {
                    bool mandatory;
                    mandatory = io::input::boolean(std::cin, "Will this Course be mandatory?");
                    cour->setMandatory(mandatory);
                    std::cout << "Course successfully set to " << (mandatory ? "" : "non-") << "mandatory." << std::endl;
                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                }

                io::input::await("Return to " + menu_title + "?");
                break;
            }

            // Change semester.
            case 4: {

                try {
                    unsigned short semester;
                    semester = io::input::number<unsigned short>(std::cin, "Enter new Semester:", sec->getMinAttendance() * 2);
                    cour->setSemester(semester);
                    std::cout << "Semester Changed Successfully!" << std::endl;
                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                } catch (std::out_of_range &e) {
                    std::cout << e.what() << std::endl;
                }

                io::input::await("Return to " + menu_title + "?");
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
        io::output::showAttr<student>("Student Information", stud, true);

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
                                         *sec, course_id_search, course_name_search);
        
        // We show the Course information and ask for the user's input on whether they want to
        // register the Student to this course or not.
        io::output::showAttr<course>("Course Information", cour, false);

        // We check to make sure the student is eligible to register to this course.
        if (stud->getSemester() < cour->getSemester())
            throw std::invalid_argument("! ERROR: The Student cannot register to this Course due to Semester ineligibility.");

        // We check to make sure this course has not yet been completed by the student.
        for (auto itr = stud->getGrades().begin(); itr != stud->getGrades().end(); itr++)
            if ((*itr)->course_id == cour->getUniId())
                throw std::invalid_argument("! ERROR: The Student has already completed this Course.");

        // If the user types 'no' we abort.
        if (!io::input::boolean(std::cin, "Would you like to register the Student to this Course?"))
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
                                            *sec, id_search, name_search);

        // We show the Professor information and ask for the user's input.
        io::output::showAttr<professor>("Professor Information", prof, true);

        // If the user types 'no' we abort.
        if (!io::input::boolean(std::cin, "Would you like to assign this Professor?"))
            throw std::invalid_argument("Operation Aborted.");

        // We store pointers to the relevant retrieval functions.
        course *(secretary::*course_id_search)(unsigned int) = &secretary::retrieveCourse;
        course *(secretary::*course_name_search)(const std::string &) = &secretary::retrieveCourse;
        course *cour;

        // We search for the course and catch any exceptions that might be thrown from io::input::search.
        cour = io::input::search<course>(std::cin,
                                         "Enter the Full Name or the University ID of the Course you would like to assign to the Professor:",
                                         *sec, course_id_search, course_name_search);

        // We show the Course information and ask for the user's input on whether they want to
        // submit the grade for this Course or not.
        io::output::showAttr<course>("Course Information", cour, false);

        // If the user types 'no' we abort.
        if (!io::input::boolean(std::cin, "Would you like to assign the Professor to this Course?"))
            throw std::invalid_argument("Operation Aborted.");

        cour->assign(prof);
        std::cout << "Professor has been assigned successfully." << std::endl;

    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
    } catch (std::out_of_range &e) {
        std::cout << e.what() << std::endl;
    }
}
