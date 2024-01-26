/**
 * @file student.cpp
 * @brief This file contains the definition of the interface class functions for
 * the student interfacing parts.
 * @authors Evaggelia Ragkousi, Spyros Strakosia
 * @date 26/01/2024
 */

#include "io.h"
#include "interface.h"

io::SHOULD_EXIT interface::studentManagement() {

    const std::string menu_title = "Student Management Menu";
    const std::string options[] = { "Add a new Student",
                                    "Modify an existing Student",
                                    "Remove a Student",
                                    "Print a Student's Grades",
                                    "Check a Student's Graduation Eligibility",
                                    "Save Passed Courses to File",
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

            // Add a student to the department
            case 1: {
                // We first build the student and then show the object's attributes.
                student *stud = io::output::buildObj<student, unsigned short>("Creating New Student...", sec->getDeptCode());
                io::output::showAttr<student>("Student Information", stud, true);

                // We continuously ask for the user's input until it is correct whether they would like to add
                // the student to the department.
                while (true) {

                    // If the user's input is unexpected we throw catch an exception from io::input::boolean
                    try {
                        // If the user types 'yes' we add the student, else we delete the object and print a relevant message
                        if (io::input::boolean(std::cin, "Would to like to add this Student to the Department?")) {
                            sec->add(stud);
                            std::cout << "Student added successfully!" << std::endl;
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
                io::input::await("Return to Student Management Menu?");
                break;
            }

            case 2: {

                // We store pointers to the relevant retrieval functions.
                student *(secretary::*id_search)(unsigned int) = &secretary::retrieve<student>;
                student *(secretary::*name_search)(const std::string &) = &secretary::retrieve<student>;
                student *stud;

                // We search for the student and catch any exceptions that might be thrown from io::input::search.
                try {
                    stud = io::input::search<student>(std::cin, "Enter the Full Name or the University UD of the Student you would like to modify:", *sec,
                                                      id_search, name_search);
                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                    io::input::await("Return to Student Management Menu?");
                    break;
                } catch (std::out_of_range &e) {
                    std::cout << e.what() << std::endl;
                    io::input::await("Return to Student Management Menu?");
                    break;
                }

                // We show the student information and ask for the user's input whether they want to
                // delete the student or not.
                io::output::showAttr<student>("Found the following Student", stud, true);
                while (true) {

                    // We prepare for and catch any exception that might be thrown from io::input::boolean.
                    try {

                        // If the user types 'yes' we remove the student and delete the heap allocated memory
                        // the object occupies.
                        if (io::input::boolean(std::cin, "Would you like to modify this Student?")) {
                            this->studentModification(stud);
                            std::cout << "Student modified successfully!" << std::endl;
                        } else {
                            std::cout << "Operation Aborted." << std::endl;
                        }

                        break;
                    } catch (std::invalid_argument &e) {
                        std::cout << e.what() << std::endl;
                    }
                }

                // We wait for confirmation before returning to the menu screen.
                io::input::await("Return to Student Management Menu?");
                break;
            }

            // Student removal.
            case 3: {

                // We store pointers to the relevant retrieval functions.
                student *(secretary::*id_search)(unsigned int) = &secretary::retrieve<student>;
                student *(secretary::*name_search)(const std::string &) = &secretary::retrieve<student>;
                student *stud;

                // We search for the student and catch any exceptions that might be thrown from io::input::search.
                try {
                    stud = io::input::search<student>(std::cin, "Enter the Full Name or the University UD of the Student you would like to remove:", *sec,
                                                      id_search, name_search);
                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                    io::input::await("Return to Student Management Menu?");
                    break;
                } catch (std::out_of_range &e) {
                    std::cout << e.what() << std::endl;
                    io::input::await("Return to Student Management Menu?");
                    break;
                }

                // We show the student information and ask for the user's input whether they want to
                // delete the student or not.
                io::output::showAttr<student>("Found the following Student", stud, true);
                while (true) {

                    // We prepare for and catch any exception that might be thrown from io::input::boolean.
                    try {

                        // If the user types 'yes' we remove the student and delete the heap allocated memory
                        // the object occupies.
                        if (io::input::boolean(std::cin, "Would you like to remove this Student?")) {
                            sec->remove(stud);
                            delete stud;
                            std::cout << "Student removed successfully!" << std::endl;
                        } else {
                            std::cout << "Operation Aborted." << std::endl;
                        }

                        break;
                    } catch (std::invalid_argument &e) {
                       std::cout << e.what() << std::endl;
                    }
                }

                // We wait for the user's input and return to the menu.
                io::input::await("Return to Student Management Menu?");
                break;
            }

            // Grade printing.
            case 4: {

                // We store pointers to the relevant retrieval functions.
                student *(secretary::*id_search)(unsigned int) = &secretary::retrieve<student>;
                student *(secretary::*name_search)(const std::string &) = &secretary::retrieve<student>;
                student *stud;

                // We search for the student and catch any exceptions that might be thrown from io::input::search.
                try {
                    stud = io::input::search<student>(std::cin,
                                                      "Enter the Full Name or the University UD of the Student whose grades you'd like to print:",
                                                      *sec, id_search, name_search);
                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                    io::input::await("Return to Student Management Menu?");
                    break;
                } catch (std::out_of_range &e) {
                    std::cout << e.what() << std::endl;
                    io::input::await("Return to Student Management Menu?");
                    break;
                }

                // We show the student information and ask for the user's input whether they want to
                // show the student's grades or not.
                io::output::showAttr<student>("Found the following Student", stud, true);
                while (true) {

                    // We prepare for and catch any exception that might be thrown from io::input::boolean.
                    try {

                        // If the user types 'yes' we print the grades accordingly.
                        if (io::input::boolean(std::cin, "Would you like to print this Student's grades?")) {
                            while (true) {
                                try {
                                    stud->printGrades(io::input::number<unsigned short>(std::cin,
                                                                                        "For which Semester would to like to print this Student's grades? (Type '0' for all semesters)",
                                                                                        stud->getSemester()));
                                    break;
                                } catch (std::invalid_argument &e) {
                                    std::cout << e.what() << std::endl;
                                    break;
                                } catch (std::out_of_range &e) {
                                    std::cout << e.what() << std::endl;
                                    break;
                                }
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
                io::input::await("Return to Student Management Menu?");
                break;
            }

            // Graduation Eligibility
            case 5: {

                // We store pointers to the relevant retrieval functions.
                student *(secretary::*id_search)(unsigned int) = &secretary::retrieve<student>;
                student *(secretary::*name_search)(const std::string &) = &secretary::retrieve<student>;
                student *stud;

                // We search for the student and catch any exceptions that might be thrown from io::input::search.
                try {
                    stud = io::input::search<student>(std::cin,
                                                      "Enter the Full Name or the University UD of the Student whose graduation eligibility you'd like to check:",
                                                      *sec, id_search, name_search);
                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                    io::input::await("Return to Student Management Menu?");
                    break;
                } catch (std::out_of_range &e) {
                    std::cout << e.what() << std::endl;
                    io::input::await("Return to Student Management Menu?");
                    break;
                }

                // We show the student information.
                io::output::showAttr<student>("Found the following Student", stud, true);
                if (stud->getEcts() < sec->getRequiredEcts() ||
                    stud->getMandatoryCoursesPassed() < sec->getMandatoryCourses() ||
                    stud->getSemester() < sec->getMinAttendance() * 2) {

                    std::cout << "This Student cannot graduate yet." << std::endl;
                } else {
                    std::cout << "This Student can graduate." << std::endl;
                }

                io::input::await("Return to Student Management Menu?");
                break;
            }

            default:
                return io::NO_EXIT;
        }
    }
}

io::SHOULD_EXIT interface::studentModification(student *stud) {

    const std::string menu_title = "Student Modification Menu";
    const std::string options[] { "Change Full Name",
                                  "Change Date of Birth",
                                  "Change Date of Registration",
                                  "Return to Student Management Menu" };

    // The inner menu loop.
    while (true) {

        std::stringstream ss;
        ss << "  Modifying Student" << std::endl << io::output::divider << std::endl << *stud << io::output::divider << std::endl;
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

                sec->remove(stud);
                stud->setName(new_name);
                sec->add(stud);
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

                stud->setDateOfBirth(new_date_of_birth);
                std::cout << "Date of Birth Changed Successfully!" << std::endl;
                io::input::await("Return to Student Modification Menu?");
                break;
            }

            // Change date of registration
            case 3: {

                std::string new_date_of_registration;
                while (true) {
                    try {
                        new_date_of_registration = io::input::date(std::cin, "Enter New Date of Registration:");
                        break;
                    } catch (std::invalid_argument &e) {
                        std::cout << e.what() << std::endl;
                    }
                }

                stud->setDateOfRegistration(new_date_of_registration);
                std::cout << "Date of Registration Changed Successfully!" << std::endl;
                io::input::await("Return to Student Modification Menu?");
                break;
            }

            default:
                return io::NO_EXIT;
        }
    }
}
