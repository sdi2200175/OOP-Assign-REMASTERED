/**
 * @file student_interface.cpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief
 * @version 0.1
 * @date 2024-01-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "interface.hpp"
#include "validation.hpp"

/**
 * @brief Manages all student-centric options in the program.
 *
 * @return SHOULD_EXIT Returns EXIT if the program should quit.
 */
interface::SHOULD_EXIT interface::studentManagement() {

    /* - Student Menu Loop - */
    while (true) {

        /* - menu print - */
        this->output << "|" << std::endl
                     << "|---------------- Student Management Menu ----------------|" << std::endl;
        this->output << "| Choose one of the following options: " << std::endl;
        this->output << "1. Add a new Student to the Secretary Department" << std::endl;
        this->output << "2. Modify an existing Student of the Secretary Department" << std::endl;
        this->output << "3. Remove an existing Student from the Secretary Department" << std::endl;
        this->output << "4. Return to the Main Menu" << std::endl;

        /* - obtain and validate user option/input - */
        unsigned char option;

        VALIDATE_EXIT(option = validation::validateNumericalInput<unsigned char>(this->input, this->output, this->error,
                          "Enter the number corresponding to what you want to do: ", 4));

        /* - cases for each option - */
        switch (option) {

        case 1:
            this->output << "|---- Adding New Student to the Secretary Department -----|" << std::endl;
            this->sec->createStudent();
            this->output << "|--------- Added Student to Secretary Department ---------|" << std::endl;
            break;

        case 2: {
            student* (secretary::*id_search)(unsigned int) = &secretary::retrieveStudent;
            student* (secretary::*name_search)(const std::string&) = &secretary::retrieveStudent;
            student* stud = validation::validateSearchCriteria<student>(this->input, this->output, this->error,
                "Enter the Name or ID of the Student you want to modify: ", id_search, name_search, *this->sec);

            if (stud != nullptr) {
                this->output << "| The Student with the following credentials was found: " << std::endl;
                this->output << *stud;
                if (validation::validateBoolInput(input, this->output, error, "Would you like to modify this student? ")) {
                    VALIDATE_EXIT(studentModification(*this, stud));
                }
            } else {
                error << "! ERROR: The Student you searched for was not found." << std::endl;
            }

            break;
        }

        case 3:
            if (this->sec->deleteStudent()) {
                this->output << "|--------------- Student has been deleted ----------------|" << std::endl;
            }

            break;

        default:
            return NO_EXIT;
        }
    }
}

/**
 * @brief This function handles modifying a given student object.
 *
 * @param interface Takes the interface since its not a member function.
 * @param student Takes the student which it is modifying.
 * @return SHOULD_EXIT Returns EXIT if it needs to exit.
 */
interface::SHOULD_EXIT studentModification(interface& interface, student* student) {

    while (true) {

        /* - menu print - */
        interface.output << "|" << std::endl
                         << "|------- Modifying Student with ID: " << student->getFormattedUniID() << " -------|" << std::endl;
        interface.output << "| Choose one of the following options: " << std::endl;
        interface.output << "1. Change Student's Name" << std::endl;
        interface.output << "2. Change Student's Date of Birth" << std::endl;
        interface.output << "3. Change Student's Date of Registration" << std::endl;
        interface.output << "4. Change Student's ECTs" << std::endl;
        interface.output << "5. Print Student's Grades" << std::endl;
        interface.output << "6. Print Student's Parameters" << std::endl;
        interface.output << "7. Return to Student Management Menu" << std::endl;

        /* - obtain and validate user option/input - */
        unsigned char option;

        VALIDATE_EXIT(option = validation::validateNumericalInput<unsigned char>(interface.input, interface.output, interface.error,
                          "Enter the number corresponding to what you want to do: ", 7));

        /* - cases for each option - */
        switch (option) {

        case 1:
            interface.sec->removeStudent(student);
            student->setName();
            interface.sec->addStudent(student);
            break;

        case 2:
            student->setDateOfBirth();
            break;

        case 3:
            student->setDateOfRegistration();
            break;

        case 4:
            student->setECTs();
            break;

        case 5:
            student->printGrades(validation::validateNumericalInput<unsigned short>(interface.input, interface.output, interface.error,
                "Enter the semester for which you'd like to print the Student's grades: (Type '0' to print every semester) ", student->getSemester()));
            break;

        case 6:
            interface.output << *student;
            break;

        default:
            return interface::NO_EXIT;
        }
    }
}
