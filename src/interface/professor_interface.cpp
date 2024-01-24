/**
 * @file professor_interface.cpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief
 * @version 0.1
 * @date 2024-01-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <thread>
#include <chrono>

#include "interface.hpp"
#include "validation.hpp"

/**
 * @brief Manages all professor-centric options in the program.
 *
 * @return SHOULD_EXIT Returns EXIT if the program should quit.
 */
interface::SHOULD_EXIT interface::professorManagement() {

  /* - Professor Menu Loop - */
  while (true) {

    system("clear");
    this->displayTitle();

    /* - menu print - */
    this->output << "  Professor Management Menu" << std::endl
                 << this->divider << std::endl
                 << "| Choose one of the following options: " << std::endl
                 << "| 1. Add a new Professor to the Department" << std::endl
                 << "| 2. Modify an existing Professor of the Deaprtment" << std::endl
                 << "| 3. Remove an existing Professor from the Deaprtment" << std::endl
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
      this->output << "  Building Professor: " << std::endl
                   << this->divider << std::endl
                   << "| Enter Professor's Credentials Below: " << std::endl;

      professor *prof = this->sec->createProfessor();
      this->output << "| Created Professor named '" << prof->getName() << "'"
                   << std::endl
                   << "| with University ID: " << prof->getFormattedUniID()
                   << std::endl
                   << interface::divider << std::endl;

      validation::validateConfirmation(
          this->input, this->output, this->error,
          "Return to the Professor Management Menu? ");
      break;
    }

    case 2: {
      system("clear");
      this->displayTitle();

      this->output << "  Modifying Professor" << std::endl
                   << this->divider << std::endl;

      professor *(secretary::*id_search)(unsigned int) = &secretary::retrieveProfessor;
      professor *(secretary::*name_search)(const std::string &) = &secretary::retrieveProfessor;
      professor *prof = validation::validateSearchCriteria<professor>(
          this->input, this->output, this->error,
          "Enter the Name or ID of the Professor you want to modify: ", id_search,
          name_search, *this->sec);

      if (prof != nullptr) {
        system("clear");
        this->displayTitle();

        this->output << "  Modifying Professor" << std::endl
                     << this->divider << std::endl;

        this->output << "| Found Professor with the following credentials: " << std::endl
                     << *prof
                     << this->divider << std::endl;

        if (validation::validateBoolInput(
                input, this->output, error,
                "Would you like to modify this Professor? ")) {
          VALIDATE_EXIT(professorModification(*this, prof));
        }
      } else {
        error << "! ERROR: The Professor you searched for was not found."
              << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      }

      break;
    }

    case 3: {
      system("clear");
      this->displayTitle();

      this->output << "  Deleting Professor" << std::endl
                   << this->divider << std::endl;

      professor *(secretary::*id_search)(unsigned int) = &secretary::retrieveProfessor;
      professor *(secretary::*name_search)(const std::string &) = &secretary::retrieveProfessor;
      professor *prof = validation::validateSearchCriteria<professor>(
          this->input, this->output, this->error,
          "Enter the Name or ID of the Professor you want to delete: ", id_search,
          name_search, *this->sec);

      if (prof != nullptr) {
        system("clear");
        this->displayTitle();

        this->output << "  Deleting Professor" << std::endl
                     << this->divider << std::endl;

        this->output << "| Found Professor with the following credentials: " << std::endl
                     << *prof
                     << this->divider << std::endl;

        if (validation::validateBoolInput(
                input, this->output, error,
                "Would you like to delete this Professor? ")) {
          this->sec->removeProfessor(prof);
          delete prof;
        }
      } else {
        error << "! ERROR: The Professor you searched for was not found."
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
 * @brief This function handles modifying a given professor object.
 *
 * @param interface Takes the interface since its not a member function.
 * @param professor Takes the professor which it is modifying.
 * @return SHOULD_EXIT Returns EXIT if it needs to exit.
 */
interface::SHOULD_EXIT professorModification(interface &interface,
                                             professor *professor) {

  while (true) {

    system("clear");
    interface.displayTitle();

    /* - menu print - */
    interface.output << "  Modifying Professor" << std::endl
                     << interface.divider << std::endl
                     << "| Modifying Professor with the following credentials: " << std::endl
                     << *professor
                     << interface.divider << std::endl
                     << std::endl
                     << "  Professor Modification" << std::endl
                     << interface.divider << std::endl
                     << "| Choose one of the following options: " << std::endl
                     << "| 1. Change Proferssor's Name" << std::endl
                     << "| 2. Change Proferssor's Date of Birth" << std::endl
                     << "| 3. Submit Semester Grades" << std::endl
                     << "| 4. Print Professor's Statistics" << std::endl
                     << "| 6. Print Proferssor's Parameters" << std::endl
                     << "| 7. Return to Proferssor Management Menu" << std::endl
                     << interface.divider << std::endl;

    /* - obtain and validate user option/input - */
    unsigned char option;

    VALIDATE_EXIT(
        option = validation::validateNumericalInput<unsigned char>(
            interface.input, interface.output, interface.error,
            "Enter the number corresponding to what you want to do: ", 6));

    /* - cases for each option - */
    switch (option) {

    case 1:
      interface.sec->removeProfessor(professor);
      professor->setName();
      interface.sec->addProfessor(professor);
      break;

    case 2:
      professor->setDateOfBirth();
      break;

    case 3: {

      student *(secretary::*id_search)(unsigned int) =
          &secretary::retrieveStudent;
      student *(secretary::*name_search)(const std::string &) =
          &secretary::retrieveStudent;
      student *stud = validation::validateSearchCriteria(
          interface.input, interface.output, interface.error,
          "Enter the Name or University ID of the Student you want to grade: ",
          id_search, name_search, *interface.sec);

      if (stud != nullptr) {
        interface.output
            << "| The Student with the following credentials was found: "
            << std::endl;
        interface.output << *stud;

        bool found = false;
        for (std::vector<unsigned int>::const_iterator itr =
                 professor->getAssignedCourses().begin();
             itr != professor->getAssignedCourses().end(); itr++) {

          course *cour = interface.sec->retrieveCourse(*itr);
          if ((found = cour->registerStudent(stud))) {

            interface.output
                << "| Student is registered in '" << cour->getName()
                << "' with University ID: " << cour->getFormattedUniID() << "."
                << std::endl;
            bool modify = validation::validateBoolInput(
                interface.input, interface.output, interface.error,
                "Is this the Course you'd like to grade this Student on? ");

            if (modify) {
              unsigned short grade =
                  validation::validateNumericalInput<unsigned short>(
                      interface.input, interface.output, interface.error,
                      "Enter the grade you'd like to give to this Student: ",
                      10);

              stud->addGrade(
                  cour->getName(), cour->getUniID(), professor->getName(),
                  professor->getFormattedUniID(), stud->getSemester(), grade);
              interface.output << "|--------- Student has been graded "
                                  "successfully ----------|"
                               << std::endl;
            }
          }
        }

        if (!found)
          interface.error << "! ERROR: The Student you searched for is not "
                             "registered to any of your courses."
                          << std::endl;

      } else {
        interface.error
            << "! ERROR: The Student you searched for was not found."
            << std::endl;
      }

      break;
    }

    case 4: {

      for (std::vector<unsigned int>::const_iterator itr =
               professor->getAssignedCourses().begin();
           itr != professor->getAssignedCourses().end(); itr++) {

        course *cour = interface.sec->retrieveCourse(*itr);
        interface.output << "| Professor is assigned to Course '"
                         << cour->getName() << "' with University ID: "
                         << cour->getFormattedUniID() << "." << std::endl;
        bool modify = validation::validateBoolInput(
            interface.input, interface.output, interface.error,
            "Is this a Course for which the Statistics you'd like to print? ");

        if (!modify)
          continue;

        for (std::vector<person *>::const_iterator itr2 =
                 cour->getAttendees().begin();
             itr2 != cour->getAttendees().end(); itr2++) {
          student *stud = interface.sec->retrieveStudent((*itr2)->getUniID());
          interface.output << "| Student named '" << stud->getName()
                           << "' graded " << stud->getGrade(cour->getUniID())
                           << std::endl;
        }
      }

      break;
    }

    case 5:
      interface.output << *professor;
      break;

    default:
      return interface::NO_EXIT;
    }
  }
}
