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

#include <thread>
#include <chrono>

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

    system("clear");
    this->displayTitle();

    /* - menu print - */
    this->output << "  Student Management Menu" << std::endl
                 << this->divider << std::endl
                 << "| Choose one of the following options: " << std::endl
                 << "| 1. Add a new Student to the Department" << std::endl
                 << "| 2. Modify an existing Student of the Deaprtment" << std::endl
                 << "| 3. Remove an existing Student from the Deaprtment" << std::endl
                 << "| 4. Return to the Main Menu" << std::endl
                 << this->divider << std::endl;

    /* - obtain and validate user option/input - */
    unsigned char option;

    VALIDATE_EXIT(
        option = validation::validateNumericalInput<unsigned char>(
            this->input, this->output, this->error,
            "Enter the number corresponding to what you want to do: ", 4));

    /* - cases for each option - */
    switch (option) {

    case 1: {
      system("clear");
      this->displayTitle();
      this->output << "  Building Student: " << std::endl 
                   << this->divider << std::endl
                   << "| Enter Student's Credentials Below: " << std::endl;

      student *stud = this->sec->createStudent();
      this->output << "| Created Student named '" << stud->getName() << "'" << std::endl 
                   << "| with University ID: " << stud->getFormattedUniID() << std::endl
                   << interface::divider << std::endl;

      validation::validateConfirmation(this->input, this->output, this->error, "Return to the Student Management Menu? ");
      break;
    }

    case 2: {
      system("clear");
      this->displayTitle();

      this->output << "  Modifying Student" << std::endl
                   << this->divider << std::endl;

      student *(secretary::*id_search)(unsigned int) = &secretary::retrieveStudent;
      student *(secretary::*name_search)(const std::string &) = &secretary::retrieveStudent;
      student *stud = validation::validateSearchCriteria<student>(
          this->input, this->output, this->error,
          "Enter the Name or ID of the Student you want to modify: ", id_search,
          name_search, *this->sec);

      if (stud != nullptr) {
        system("clear");
        this->displayTitle();

        this->output << "  Modifying Student" << std::endl
                     << this->divider << std::endl;

        this->output << "| Found Student with the following credentials: " << std::endl
                     << *stud
                     << this->divider << std::endl;

        if (validation::validateBoolInput(
                input, this->output, error,
                "Would you like to modify this student? ")) {
          VALIDATE_EXIT(studentModification(*this, stud));
        }
      } else {
        error << "! ERROR: The Student you searched for was not found."
              << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      }

      break;
    }

    case 3: {
      system("clear");
      this->displayTitle();

      this->output << "  Deleting Student" << std::endl
                   << this->divider << std::endl;

      student *(secretary::*id_search)(unsigned int) = &secretary::retrieveStudent;
      student *(secretary::*name_search)(const std::string &) = &secretary::retrieveStudent;
      student *stud = validation::validateSearchCriteria<student>(
          this->input, this->output, this->error,
          "Enter the Name or ID of the Student you want to delete: ", id_search,
          name_search, *this->sec);

      if (stud != nullptr) {
        system("clear");
        this->displayTitle();

        this->output << "  Deleting Student" << std::endl
                     << this->divider << std::endl;

        this->output << "| Found Student with the following credentials: " << std::endl
                     << *stud
                     << this->divider << std::endl;

        if (validation::validateBoolInput(
                input, this->output, error,
                "Would you like to delete this student? ")) {
          this->sec->removeStudent(stud);
          delete stud;
        }
      } else {
        error << "! ERROR: The Student you searched for was not found."
              << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      }

      break;
    }

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
interface::SHOULD_EXIT studentModification(interface &interface,
                                           student *student) {

  while (true) {

    system("clear");
    interface.displayTitle();

    /* - menu print - */
    interface.output << "  Modifying Student" << std::endl
                     << interface.divider << std::endl
                     << "| Modifying Student with the following credentials: " << std::endl
                     << *student
                     << interface.divider << std::endl
                     << std::endl
                     << "  Student Modification" << std::endl
                     << interface.divider << std::endl
                     << "| Choose one of the following options: " << std::endl
                     << "| 1. Change Student's Name" << std::endl
                     << "| 2. Change Student's Date of Birth" << std::endl
                     << "| 3. Change Student's Date of Registration" << std::endl
                     << "| 4. Change Student's ECTs" << std::endl
                     << "| 5. Print Student's Grades" << std::endl
                     << "| 6. Print Student's Parameters" << std::endl
                     << "| 7. Return to Student Management Menu" << std::endl
                     << interface.divider << std::endl;

    /* - obtain and validate user option/input - */
    unsigned char option;

    VALIDATE_EXIT(
        option = validation::validateNumericalInput<unsigned char>(
            interface.input, interface.output, interface.error,
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
      student->printGrades(validation::validateNumericalInput<unsigned short>(
          interface.input, interface.output, interface.error,
          "Enter the semester for which you'd like to print this Student's "
          "grades: (Type '0' to print every semester) ",
          student->getSemester()));
      break;

    case 6:
      interface.output << *student;
      break;

    default:
      return interface::NO_EXIT;
    }
  }
}
