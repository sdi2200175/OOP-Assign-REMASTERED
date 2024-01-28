/**
 * @file student.cpp
 * @brief This file contains the definition of the interface class functions for
 * the student interfacing parts.
 * @authors Spyros Strakosia, Evaggelia Ragkousi
 * @date 27/01/2024
 */

#include "io.h"
#include "interface.h"

io::SHOULD_EXIT interface::studentManagement() {

    const std::string menu_title = "Student Management Menu";
    const std::string options[] = { "Add a new Student", 
                                    "Modify an existing Student", 
                                    "Remove a Student",
                                    "Print a Student's Grades", 
                                    "Register a Student to a Course",
                                    "Check a Student's Graduation Eligibility",
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

            // Add a student to the department.
            case 1: {

                // If the user's input is unexpected we throw catch an exception from io::input::boolean.
                try {

                    // We first build the student and then show the object's attributes.
                    student *stud = io::output::buildObj<student, unsigned short>("Creating New Student...",
                                                                                  sec->getDeptCode());
                    io::output::showAttr<student>("Student Information", stud, true);

                    // If the user types 'yes' we add the Student, else we delete the object and print a relevant message.
                    if (!io::input::boolean(std::cin, "Would to like to add this Student to the Department?")) {
                        delete stud;
                        throw std::invalid_argument("Operation Aborted.");
                    }

                    sec->add(stud);
                    std::cout << "Student added successfully!" << std::endl;

                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                }

                // We wait for confirmation before returning to the menu screen.
                io::input::await("Return to " + menu_title);
                break;
            }

            //  Modify an already existing Student.
            case 2: {

                // We search for the Student and catch any exceptions that might be thrown from io::input::search.
                try {

                    // We store pointers to the relevant retrieval functions.
                    student *(secretary::*id_search)(unsigned int) = &secretary::retrieve<student>;
                    student *(secretary::*name_search)(const std::string &) = &secretary::retrieve<student>;
                    student *stud = io::input::search<student>(std::cin,
                                                               "Enter the Full Name or the University ID of the Student you would like to modify:",
                                                               *sec, id_search, name_search);

                    // We show the Student information and ask for the user's input whether they want to
                    // modify the Student or not.
                    io::output::showAttr<student>("Student Information", stud, true);

                    // If the user types 'no' we abort.
                    if (!io::input::boolean(std::cin, "Would you like to modify this Student?"))
                        throw std::invalid_argument("Operation Aborted.");

                    CHECK_EXIT(this->studentModification(stud));
                    std::cout << "Student modified successfully!" << std::endl;

                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                } catch (std::out_of_range &e) {
                    std::cout << e.what() << std::endl;
                }

                // We wait for confirmation before returning to the menu screen.
                io::input::await("Return to " + menu_title);
                break;
            }

            // Remove a Student from the department.
            case 3: {

                // We search for the Student and catch any exceptions that might be thrown from io::input::search.
                try {

                    // We store pointers to the relevant retrieval functions.
                    student *(secretary::*id_search)(unsigned int) = &secretary::retrieve<student>;
                    student *(secretary::*name_search)(const std::string &) = &secretary::retrieve<student>;
                    student *stud = io::input::search<student>(std::cin,
                                                               "Enter the Full Name or the University ID of the Student you would like to remove:",
                                                               *sec, id_search, name_search);

                    // We show the Student information and ask for the user's input whether they want to
                    // delete the Student or not.
                    io::output::showAttr<student>("Student Information", stud, true);

                    // If the user types 'no' we abort.
                    if (!io::input::boolean(std::cin, "Would you like to remove this Student?"))
                        throw std::invalid_argument("Operation Aborted.");

                    sec->remove(stud);
                    delete stud;
                    std::cout << "Student removed successfully!" << std::endl;

                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                } catch (std::out_of_range &e) {
                    std::cout << e.what() << std::endl;
                }

                // We wait for the user's input and return to the menu.
                io::input::await("Return to " + menu_title);
                break;
            }

            // Print the Grades of a Student.
            case 4: {

                // We search for the student and catch any exceptions that might be thrown from io::input::search.
                try {

                    // We store pointers to the relevant retrieval functions.
                    student *(secretary::*id_search)(unsigned int) = &secretary::retrieve<student>;
                    student *(secretary::*name_search)(const std::string &) = &secretary::retrieve<student>;
                    student *stud = io::input::search<student>(std::cin,
                                                               "Enter the Full Name or the University ID of the Student whose grades you'd like to print:",
                                                               *sec, id_search, name_search);

                    // We show the student information and ask for the user's input whether they want to
                    // show the student's grades or not.
                    io::output::showAttr<student>("Found the following Student", stud, true);

                    // If the user types 'no' we abort.
                    if (!io::input::boolean(std::cin, "Would you like to print this Student's grades?"))
                        throw std::invalid_argument("Operation Aborted.");

                    stud->printGrades(io::input::number<unsigned short>(std::cin,
                                                                        "For which Semester would to like to print this Student's grades? (Type '0' for all semesters)",
                                                                        stud->getSemester()));

                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                    io::input::await("Return to Student Management Menu?");
                    break;
                } catch (std::out_of_range &e) {
                    std::cout << e.what() << std::endl;
                    io::input::await("Return to Student Management Menu?");
                    break;
                }

                // We wait for the user's input and return to the menu.
                io::input::await("Return to " + menu_title);
                break;
            }

            // Register a Student to a Course.
            case 5: {
                courseRegistration();
                io::input::await("Return to " + menu_title);
                break;
            }

            // Graduation Eligibility
            case 6: {

                try {

                    // We store pointers to the relevant retrieval functions.
                    student *(secretary::*id_search)(unsigned int) = &secretary::retrieve<student>;
                    student *(secretary::*name_search)(const std::string &) = &secretary::retrieve<student>;
                    student *stud;

                    // We search for the Student and catch any exceptions that might be thrown from io::input::search.
                    stud = io::input::search<student>(std::cin,
                                                               "Enter the Full Name or the University ID of the Student whose graduation eligibility you'd like to check:",
                                                               *sec, id_search, name_search);

                    // We show the Student information.
                    io::output::showAttr<student>("Student Information", stud, true);

                    if (stud->getEcts() < sec->getRequiredEcts() ||
                        stud->getMandatoryCoursesPassed() < sec->getMandatoryCourses() ||
                        stud->getSemester() < sec->getMinAttendance() * 2) {

                        std::cout << "This Student cannot graduate yet." << std::endl;
                    } else {
                        std::cout << "This Student can graduate." << std::endl;
                    }

                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                } catch (std::out_of_range &e) {
                    std::cout << e.what() << std::endl;
                }

                // We wait for the user's input and return to the menu.
                io::input::await("Return to " + menu_title);
                break;
            }

            default:
                return io::NO_EXIT;
        }
    }
}

io::SHOULD_EXIT interface::studentModification(student *stud) {

    const std::string menu_title = "Student Modification Menu";
    const std::string options[] = { "Change Full Name", 
                                    "Change Date of Birth", 
                                    "Change Date of Registration",
                                    "Return to Student Management Menu" };

    // The inner menu loop.
    while (true) {

        std::stringstream ss;
        ss << "  Student Information" << std::endl << io::output::divider << std::endl << *stud << io::output::divider << std::endl;
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
                    new_name = io::input::name(std::cin, "Enter New Full Name:");
                    sec->remove(stud);
                    stud->setName(new_name);
                    sec->add(stud);
                    std::cout << "Name Changed Successfully!" << std::endl;
                } catch (std::invalid_argument &e) {
                        std::cout << e.what() << std::endl;
                }

                io::input::await("Return to " + menu_title + "?");
                break;
            }

            // Change date of birth.
            case 2: {

                try {
                    std::string new_date_of_birth;
                    new_date_of_birth = io::input::date(std::cin, "Enter New Date of Birth:");
                    stud->setDateOfBirth(new_date_of_birth);
                    std::cout << "Date of Birth Changed Successfully!" << std::endl;
                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                }

                io::input::await("Return to " + menu_title + "?");
                break;
            }

            // Change date of registration.
            case 3: {

                try {
                    std::string new_date_of_registration;
                    new_date_of_registration = io::input::date(std::cin, "Enter New Date of Registration:");
                    stud->setDateOfRegistration(new_date_of_registration);
                    std::cout << "Date of Registration Changed Successfully!" << std::endl;
                } catch (std::invalid_argument &e) {
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