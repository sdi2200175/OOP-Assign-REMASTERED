/**
 * @file professor.cpp
 * @brief This file contains the definition of the interface class functions for
 * the professor interfacing parts.
 * @authors Evaggelia Ragkousi, Spyros Strakosia
 * @date 26/01/2024
 */

#include "io.h"
#include "interface.h"

io::SHOULD_EXIT interface::professorManagement() {

    const std::string menu_title = "Professor Management Menu";
    const std::string options[] = { "Add a new Professor",
                                    "Modify an existing Professor",
                                    "Remove a Professor",
                                    "Assign Professor to Course",
                                    "Grade a Student",
                                    "View Statistics of Attending Course(s)",
                                    "Return to Main Menu"};

    // The inner menu loop.
    while (true) {

        io::output::menu(std::string(), menu_title, options);

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

            // Add a professor to the department
            case 1: {
                // We first build the professor and then show the object's attributes.
                professor *prof = io::output::buildObj<professor, unsigned short>("Creating New Professor...", sec->getDeptCode());
                io::output::showAttr<professor>("Professor Information", prof, true);

                // We continuously ask for the user's input until it is correct whether they would like to add
                // the student to the department.
                while (true) {

                    // If the user's input is unexpected we throw catch an exception from io::input::boolean
                    try {
                        // If the user types 'yes' we add the student, else we delete the object and print a relevant message
                        if (io::input::boolean(std::cin, "Would to like to add this Professor to the Department?")) {
                            sec->add(prof);
                            std::cout << "Professor added successfully!" << std::endl;
                        } else {
                            delete prof;
                            std::cout << "Operation Aborted." << std::endl;
                        }

                        break;
                    } catch (std::invalid_argument &e) {
                        std::cout << e.what() << std::endl;
                    }
                }

                // We wait for confirmation before returning to the menu screen.
                io::input::await("Return to Professor Management Menu?");
                break;
            }

            case 2: {

                // We store pointers to the relevant retrieval functions.
                professor *(secretary::*id_search)(unsigned int) = &secretary::retrieve<professor>;
                professor *(secretary::*name_search)(const std::string &) = &secretary::retrieve<professor>;
                professor *prof;

                // We search for the student and catch any exceptions that might be thrown from io::input::search.
                try {
                    prof = io::input::search<professor>(std::cin, "Enter the Full Name or the University UD of the Professor you would like to modify:", *sec,
                                                        id_search, name_search);
                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                    io::input::await("Return to Professor Management Menu?");
                    break;
                } catch (std::out_of_range &e) {
                    std::cout << e.what() << std::endl;
                    io::input::await("Return to Professor Management Menu?");
                    break;
                }

                // We show the Professor information and ask for the user's input whether they want to
                // delete the student or not.
                io::output::showAttr<professor>("Found the following Professor", prof, true);
                while (true) {

                    // We prepare for and catch any exception that might be thrown from io::input::boolean.
                    try {

                        // If the user types 'yes' we remove the student and delete the heap allocated memory
                        // the object occupies.
                        if (io::input::boolean(std::cin, "Would you like to modify this Student?")) {
                            this->professorModification(prof);
                            std::cout << "Professor modified successfully!" << std::endl;
                        } else {
                            std::cout << "Operation Aborted." << std::endl;
                        }

                        break;
                    } catch (std::invalid_argument &e) {
                        std::cout << e.what() << std::endl;
                    }
                }

                // We wait for confirmation before returning to the menu screen.
                io::input::await("Return to Professor Management Menu?");
                break;
            }

            // Professor removal.
            case 3: {

                // We store pointers to the relevant retrieval functions.
                professor *(secretary::*id_search)(unsigned int) = &secretary::retrieve<professor>;
                professor *(secretary::*name_search)(const std::string &) = &secretary::retrieve<professor>;
                professor *prof;

                // We search for the student and catch any exceptions that might be thrown from io::input::search.
                try {
                    prof = io::input::search<professor>(std::cin, "Enter the Full Name or the University UD of the Professor you would like to remove:", *sec,
                                                        id_search, name_search);
                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                    io::input::await("Return to Professor Management Menu?");
                    break;
                } catch (std::out_of_range &e) {
                    std::cout << e.what() << std::endl;
                    io::input::await("Return to Professor Management Menu?");
                    break;
                }

                // We show the Professor information and ask for the user's input whether they want to
                // delete the student or not.
                io::output::showAttr<professor>("Found the following Professor", prof, true);
                while (true) {

                    // We prepare for and catch any exception that might be thrown from io::input::boolean.
                    try {

                        // If the user types 'yes' we remove the student and delete the heap allocated memory
                        // the object occupies.
                        if (io::input::boolean(std::cin, "Would you like to remove this Professor?")) {
                            sec->remove(prof);
                            delete prof;
                            std::cout << "Professor removed successfully!" << std::endl;
                        } else {
                            std::cout << "Operation Aborted." << std::endl;
                        }

                        break;
                    } catch (std::invalid_argument &e) {
                        std::cout << e.what() << std::endl;
                    }
                }

                // We wait for the user's input and return to the menu.
                io::input::await("Return to Professor Management Menu?");
                break;
            }

            case 4: {

                // We store pointers to the relevant retrieval functions.
                professor *(secretary::*id_search)(unsigned int) = &secretary::retrieve<professor>;
                professor *(secretary::*name_search)(const std::string &) = &secretary::retrieve<professor>;
                professor *prof;

                // We search for the student and catch any exceptions that might be thrown from io::input::search.
                try {
                    prof = io::input::search<professor>(std::cin,
                                                        "Enter the Full Name or the University UD of the Professor you would like to assign:",
                                                        *sec,
                                                        id_search, name_search);
                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                    io::input::await("Return to Professor Management Menu?");
                    break;
                } catch (std::out_of_range &e) {
                    std::cout << e.what() << std::endl;
                    io::input::await("Return to Professor Management Menu?");
                    break;
                }

                // We show the Professor information and ask for the user's input.
                io::output::showAttr<professor>("Found the following Professor", prof, true);
                while (true) {

                    // We prepare for and catch any exception that might be thrown from io::input::boolean.
                    try {

                        // If the user types 'yes' we search for a course to assign the professor to.
                        if (io::input::boolean(std::cin, "Would you like to assign this Professor?")) {

                            // We store pointers to the relevant retrieval functions.
                            course *(secretary::*course_id_search)(unsigned int) = &secretary::retrieveCourse;
                            course *(secretary::*course_name_search)(const std::string &) = &secretary::retrieveCourse;
                            course *cour;

                            while (true) {
                                // We search for the course and catch any exceptions that might be thrown from io::input::search.
                                try {
                                    cour = io::input::search<course>(std::cin,
                                                                     "Enter the Full Name or the University UD of the Course you would like assigned:",
                                                                     *sec,
                                                                     course_id_search, course_name_search);

                                    if (std::find(cour->getAssignedProfessors().begin(),
                                                  cour->getAssignedProfessors().end(), prof) != cour->getAssignedProfessors().end()) {

                                        throw std::invalid_argument("! ERROR: This Professor is already assigned to this Course.");
                                    }

                                    while (true) {

                                        // If the user types 'yes' we search for a course to assign the professor to.
                                        if (io::input::boolean(std::cin, "Would you like to assign this Professor?")) {
                                            cour->assign(prof);
                                            std::cout << "Professor assigned successfully!" << std::endl;
                                        }

                                        break;
                                    }

                                } catch (std::invalid_argument &e) {
                                    std::cout << e.what() << std::endl;
                                    io::input::await("Return to Professor Management Menu?");
                                    break;
                                } catch (std::out_of_range &e) {
                                    std::cout << e.what() << std::endl;
                                    io::input::await("Return to Professor Management Menu?");
                                    break;
                                }

                                break;
                            }

                        } else {
                            std::cout << "Operation Aborted." << std::endl;
                        }

                        break;
                    } catch (std::invalid_argument &e) {
                        std::cout << e.what() << std::endl;
                    }
                }

                // We wait for the user's input and return to the menu.
                io::input::await("Return to Professor Management Menu?");
                break;
            }

            default:
                return io::NO_EXIT;
        }
    }
}

io::SHOULD_EXIT interface::professorModification(professor *prof) {

    const std::string menu_title = "Professor Modification Menu";
    const std::string options[]{"Change Full Name",
                                "Change Date of Birth",
                                "Return to Professor Management Menu"};

    // The inner menu loop.
    while (true) {

        std::stringstream ss;
        ss << "  Modifying Professor" << std::endl << io::output::divider << std::endl << *prof << io::output::divider
           << std::endl;
        io::output::menu(ss.str(), menu_title, options);

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

            // Change name
            case 1: {

                std::string new_name;
                while (true) {
                    try {
                        new_name = io::input::name(std::cin, "Enter New Full Name:");
                        break;
                    } catch (std::invalid_argument &e) {
                        std::cout << e.what() << std::endl;
                    }
                }

                sec->remove(prof);
                prof->setName(new_name);
                sec->add(prof);
                std::cout << "Name Changed Successfully!" << std::endl;
                io::input::await("Return to Student Modification Menu?");
                break;
            }

            // Change date of birth
            case 2: {

                std::string new_date_of_birth;
                while (true) {
                    try {
                        new_date_of_birth = io::input::date(std::cin, "Enter New Date of Birth:");
                        break;
                    } catch (std::invalid_argument &e) {
                        std::cout << e.what() << std::endl;
                    }
                }

                prof->setDateOfBirth(new_date_of_birth);
                std::cout << "Date of Birth Changed Successfully!" << std::endl;
                io::input::await("Return to Student Modification Menu?");
                break;
            }

            default:
                return io::NO_EXIT;

        }
    }
}