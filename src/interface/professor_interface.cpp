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
    
    /* - menu print - */
    this->output << "|" << std::endl << "|--------------- Professor Management Menu ---------------|" << std::endl;
    this->output << "| Choose one of the following options: " << std::endl;
    this->output << "1. Add a new Professor to the Secretary Department" << std::endl;
    this->output << "2. Modify an existing Professor of the Secretary Department" << std::endl;
    this->output << "3. Remove an exisitng Professor from the Secretary Department" << std::endl;
    this->output << "4. Return to the Main Menu" << std::endl;

    /* - obtain and validate user option/input - */
    unsigned char option;

    VALIDATE_EXIT(option = validation::validateNumericalInput<unsigned char>(this->input, this->output, this->error, 
                              "Enter the number corresponding to what you want to do: ", 4));

    /* - cases for each option - */
    switch (option) {
      
      case 1:
        this->output << "|---- Adding New Professor to the Secretary Department ---|" << std::endl;
        this->sec->createProfessor();
        this->output << "|-------- Added Professor to Secretary Department --------|" << std::endl;
        break;

      case 2: {
        professor *(secretary::*id_search)(unsigned int) = &secretary::retrieveProfessor;
        professor *(secretary::*name_search)(const std::string &) = &secretary::retrieveProfessor;
        professor *prof = validation::validateSearchCriteria<professor>(this->input, this->output, this->error,
                            "Enter the Name or ID of the Professor you want to modify: ", id_search, name_search, *this->sec);

        // if the professor was not found we print an error and break, else we print the professor's credenitials
        // and verify the professor's modification.
        if (prof != nullptr) {
          this->output << "|" << std::endl << "| The Professor with the following credentials was found: " << std::endl;
          this->output << *prof;
          if (validation::validateBoolInput(input, this->output, error, "Would you like to modify this Professor? ")) {
            VALIDATE_EXIT(professorModification(*this, prof));
          }
        } else {
          error << "! ERROR: The Professor you searched for was not found." << std::endl;
        }

        break;
      }

      case 3:
        if (this->sec->deleteProfessor()) {
          this->output << "| Professor has been successfully deleted." << std::endl;
        }
        break;

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
interface::SHOULD_EXIT professorModification(interface &interface, professor *professor) {


  while (true) {
    
    /* - menu print - */
    interface.output << "|" << std::endl << "|------- Modifying Professor with ID: " << professor->getFormattedUniID() << " -------|" << std::endl;
    interface.output << "| Choose one of the following options: " << std::endl;
    interface.output << "1. Change Professor's Name" << std::endl;
    interface.output << "2. Change Professor's Date of Birth" << std::endl;
    interface.output << "3. Submit Semester Grades" << std::endl;
    interface.output << "4. Print Professor Parameters" << std::endl;
    interface.output << "5. Return to Professor Management Menu" << std::endl;

    /* - obtain and validate user option/input - */
    unsigned char option;

    VALIDATE_EXIT(option = validation::validateNumericalInput<unsigned char>(interface.input, interface.output, interface.error, 
                              "Enter the number corresponding to what you want to do: ", 5));

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

        student *(secretary::*id_search)(unsigned int) = &secretary::retrieveStudent;
        student *(secretary::*name_search)(const std::string &) = &secretary::retrieveStudent;
        student *stud = validation::validateSearchCriteria(interface.input, interface.output, interface.error, 
                          "Enter the Name or University ID of the Student you want to grade: ", id_search, name_search, *interface.sec);

        if (stud != nullptr) {
          interface.output << "| The Student with the following credentials was found: " << std::endl;
          interface.output << *stud;

          bool found = false;
          for (std::vector<unsigned int>::const_iterator itr = professor->getAssignedCourses().begin(); 
            itr != professor->getAssignedCourses().end(); itr++) {

            course *cour = interface.sec->retrieveCourse(*itr);
            if ((found = cour->isRegistered(stud))) {

              interface.output << "| Student is registered in '" << cour->getName() << "' with University ID: " << cour->getFormattedUniID() << "." << std::endl;
              bool modify = validation::validateBoolInput(interface.input, interface.output, interface.error, 
                              "Is this the Course you'd like to grade this Student on? ");

              if (modify) {
                unsigned short grade = validation::validateNumericalInput<unsigned short>(interface.input, interface.output, interface.error,
                                          "Enter the grade you'd like to give to this Student: ", 10);

                stud->addGrade(cour->getName(), cour->getUniID(), professor->getName(), professor->getFormattedUniID(), stud->getSemester(), grade);
                interface.output << "|--------- Student has been graded successfully ----------|" << std::endl;
              }
            }
          }

          if (!found) {
            interface.error << "! ERROR: The Student you searched for is not registered to any of your courses." << std::endl;
          } else {
            interface.output << "| Student grades have not been modified." << std::endl;
          }

        } else {
          interface.error << "! ERROR: The Student you searched for was not found." << std::endl;
        }

        break;
      }

      case 4:
        interface.output << *professor;
        break;

      default:
        return interface::NO_EXIT;

    }
  }
} 