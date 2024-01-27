/**
 * @file professor.cpp
 * @brief This file contains the definition of the interface class functions for
 * the professor interfacing parts.
 * @authors Spyros Strakosia, Evaggelia Ragkousi
 * @date 27/01/2024
 */

#include "io.h"
#include "interface.h"

io::SHOULD_EXIT interface::professorManagement() {

    const std::string menu_title = "Professor Management Menu";
    const std::string options[] = { "Add a new Professor", 
                                    "Modify an existing Professor", 
                                    "Remove a Professor",
                                    "Assign a Professor to a Course", 
                                    "Grade a Student",
                                    "View Statistics of Attending Course(s)", 
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

            // Add a Professor to the department.
            case 1: {

                // If the user's input is unexpected we throw catch an exception from io::input::boolean.
                try {

                    // We first build the professor and then show the object's attributes.
                    professor *prof = io::output::buildObj<professor, unsigned short>("Creating New Professor...",
                                                                                      sec->getDeptCode());
                    io::output::showAttr<professor>("Professor Information", prof, true);

                    // If the user types 'yes' we add the Professor, else we delete the object and print a relevant message.
                    if (!io::input::boolean(std::cin, "Would to like to add this Professor to the Department?")) {
                        delete prof;
                        throw std::invalid_argument("Operation Aborted.");
                    }

                    sec->add(prof);
                    std::cout << "Professor added successfully!" << std::endl;

                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                }

                // We wait for confirmation before returning to the menu screen.
                io::input::await("Return to " + menu_title);
                break;
            }

            // Modify an already existing Professor. 
            case 2: {

                // We search for the Professor and catch any exceptions that might be thrown from io::input::search.
                try {

                    // We store pointers to the relevant retrieval functions.
                    professor *(secretary::*id_search)(unsigned int) = &secretary::retrieve<professor>;
                    professor *(secretary::*name_search)(const std::string &) = &secretary::retrieve<professor>;
                    professor *prof = io::input::search<professor>(std::cin,
                                                                   "Enter the Full Name or the University ID of the Professor you would like to modify:",
                                                                   *sec, id_search, name_search);

                    // We show the Professor information and ask for the user's input whether they want to
                    // modify the Professor or not.
                    io::output::showAttr<professor>("Professor Information", prof, true);

                    // If the user types 'no' we abort.
                    if (!io::input::boolean(std::cin, "Would you like to modify this Professor?"))
                        throw std::invalid_argument("Operation Aborted.");

                    CHECK_EXIT(this->professorModification(prof));
                    std::cout << "Professor modified successfully!" << std::endl;

                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                } catch (std::out_of_range &e) {
                    std::cout << e.what() << std::endl;
                }

                // We wait for confirmation before returning to the menu screen.
                io::input::await("Return to " + menu_title);
                break;
            }

            // Remove a Professor from the department.
            case 3: {

                // We search for the Professor and catch any exceptions that might be thrown from io::input::search.
                try {

                    // We store pointers to the relevant retrieval functions.
                    professor *(secretary::*id_search)(unsigned int) = &secretary::retrieve<professor>;
                    professor *(secretary::*name_search)(const std::string &) = &secretary::retrieve<professor>;
                    professor *prof = io::input::search<professor>(std::cin,
                                                                   "Enter the Full Name or the University ID of the Professor you would like to remove:",
                                                                   *sec, id_search, name_search);

                    // We show the Professor information and ask for the user's input whether they want to
                    // delete the Professor or not.
                    io::output::showAttr<professor>("Professor Information", prof, true);

                    // If the user types 'no' we abort.
                    if (!io::input::boolean(std::cin, "Would you like to remove this Professor?"))
                        throw std::invalid_argument("Operation Aborted.");

                    sec->remove(prof);
                    delete prof;
                    std::cout << "Professor removed successfully!" << std::endl;

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
                // We wait for the user's input and return to the menu.
                io::input::await("Return to " + menu_title);
                break;
            }

            // Grade a Student.
            case 5: {

                try {

                    // We store pointers to the relevant retrieval functions.
                    professor *(secretary::*id_search)(unsigned int) = &secretary::retrieve<professor>;
                    professor *(secretary::*name_search)(const std::string &) = &secretary::retrieve<professor>;
                    professor *prof;

                    // We search for the Professor and catch any exceptions that might be thrown from io::input::search.
                    prof = io::input::search<professor>(std::cin,
                                                        "Enter the Full Name or the University ID of the Professor you would like to modify:",
                                                        *sec, id_search, name_search);

                    // We show the Professor information and ask for the user's input whether they want to
                    // submit the grade as this professor.
                    io::output::showAttr<professor>("Professor Information", prof, true);

                    // If the user types 'no' we abort.
                    if (!io::input::boolean(std::cin, "Is this the Professor submitting the Grades?"))
                        throw std::invalid_argument("Operation Aborted.");

                    // We store pointers to the relevant retrieval functions.
                    course *(secretary::*course_id_search)(unsigned int) = &secretary::retrieveCourse;
                    course *(secretary::*course_name_search)(const std::string &) = &secretary::retrieveCourse;
                    course *cour;

                    // We search for the course and catch any exceptions that might be thrown from io::input::search.
                    cour = io::input::search<course>(std::cin,
                                                     "Enter the Full Name or the University ID of the Course you'd like to submit Grades for:",
                                                     *sec, course_id_search, course_name_search);

                    // We show the Course information and ask for the user's input whether they want to
                    // submit the grade for this course.
                    io::output::showAttr<course>("Course Information", cour, false);

                    // If the user types 'no' we abort.
                    if (!io::input::boolean(std::cin, "Is this the Course you'd like to submit Grades for?"))
                        throw std::invalid_argument("Operation Aborted.");

                    // If the professor we have chosen is not assigned to this Course we throw an invalid_argument.
                    if (std::find(prof->getAssignedCourses().begin(), prof->getAssignedCourses().end(),
                                  cour->getUniId()) == prof->getAssignedCourses().end()) {

                        throw std::invalid_argument("! ERROR: This Professor is not assigned to this Course");
                    }

                    // We store pointers to the relevant retrieval functions.
                    student *(secretary::*student_id_search)(unsigned int) = &secretary::retrieve<student>;
                    student *(secretary::*student_name_search)(const std::string &) = &secretary::retrieve<student>;
                    student *stud;

                    // We search for the student and catch any exceptions that might be thrown from io::input::search.
                    stud = io::input::search<student>(std::cin,
                                                      "Enter the Full Name or the University ID of the Student you'd like to grade:",
                                                      *sec, student_id_search, student_name_search);

                    // We show the Student information and ask for the user's input whether they want to
                    // submit the grade for this student.
                    io::output::showAttr<student>("Student Information", stud, false);

                    // If the user types 'no' we abort.
                    if (!io::input::boolean(std::cin, "Is this the Student whose grades you'd like to submit?"))
                        throw std::invalid_argument("Operation Aborted.");

                    // If the student is not registered to the selected course we throw an exception.
                    if (std::find(stud->getAttendingCourses().begin(), stud->getAttendingCourses().end(),
                                  cour->getUniId()) == stud->getAttendingCourses().end()) {

                        throw std::invalid_argument(
                                "! ERROR: This Student is not currently registered to this Course.");
                    }

                    // We iterate over the student's grades and check if the grade already exists in which case we print a relevant prompt.
                    for (auto itr = stud->getGrades().begin(); itr != stud->getGrades().end(); itr++)
                        if ((*itr)->course_id == cour->getUniId()) {

                            // If the user types 'no' we abort.
                            if (!io::input::boolean(std::cin, "This Student has already been graded. Would you like to resubmit their Grade?"))
                                throw std::invalid_argument("Operation Aborted.");

                            break;
                        }

                    // We create the grade and add it to the student.
                    unsigned short grade_num = io::input::number<unsigned short>(std::cin,
                                                                                 "Enter the grade you'd like to give to this Student:",
                                                                                 10);

                    Grade grade = new struct grade(cour->getName(), cour->getUniId(), prof->getName(), grade_num,
                                                   stud->getSemester(), cour->getEcts(), cour->isMandatory());

                    stud->addGrade(grade);
                    std::cout << "Student has been graded successfully." << std::endl;

                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                } catch (std::out_of_range &e) {
                    std::cout << e.what() << std::endl;
                }

                // We wait for the user's input and return to the menu.
                io::input::await("Return to " + menu_title);
                break;
            }

            case 6: {

            }

            default:
                return io::NO_EXIT;
        }
    }
}

io::SHOULD_EXIT interface::professorModification(professor *prof) {

    const std::string menu_title = "Professor Modification Menu";
    const std::string options[] = { "Change Full Name", 
                                    "Change Date of Birth", 
                                    "Return to Professor Management Menu" };

    // The inner menu loop.
    while (true) {

        std::stringstream ss;
        ss << "  Professor Information" << std::endl << io::output::divider << std::endl << *prof << io::output::divider << std::endl;
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
                    sec->remove(prof);
                    prof->setName(new_name);
                    sec->add(prof);
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
                    prof->setDateOfBirth(new_date_of_birth);
                    std::cout << "Date of Birth Changed Successfully!" << std::endl;
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