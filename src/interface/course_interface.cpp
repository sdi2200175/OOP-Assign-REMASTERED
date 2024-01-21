/**
 * @file course_interface.cpp
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
 * @brief Manages all course-centric options in the program.
 * 
 * @return SHOULD_EXIT Returns EXIT if the program should quit.
 */
interface::SHOULD_EXIT interface::courseManagement() {

  /* - Course Menu Loop - */
  while (true) {

    /* - menu print - */
    this->output << "|" << std::endl << "|---------------- Course Management Menu -----------------|" << std::endl;
    this->output << "| Choose one of the following options: " << std::endl;
    this->output << "1. Add a new Course to the Secretary Department" << std::endl;
    this->output << "2. Modify an existing Course of the Secretary Department" << std::endl;
    this->output << "3. Remove an existing Course from the Secretary Department" << std::endl;
    this->output << "4. Return to the Main Menu" << std::endl;

    /* - obtain and validate user option/input - */
    unsigned char option;

    VALIDATE_EXIT(option = validation::validateNumericalInput<unsigned char>(this->input, this->output, this->error, 
                                                                          "Enter the number corresponding to what you want to do: ", 4));

    /* - cases for each option - */
    switch (option) {
    
      case 1:
        this->output << "|----- Adding New Course to the Secretary Department -----|" << std::endl;
        this->sec->createCourse();
        this->output << "|----- Added New Course to the Secretary Department ------|" << std::endl;
        break;

      case 2: {
        course *(secretary::*id_search)(unsigned int) = &secretary::retrieveCourse;
        course *(secretary::*name_search)(const std::string &) = &secretary::retrieveCourse;
        course *cour = validation::validateSearchCriteria<course>(this->input, this->output, this->error,
                          "Enter the Name or ID of the Course you want to modify: ", id_search, name_search, *this->sec);

        if (cour != nullptr) {
          this->output << "|" << std::endl << "| The Course with the following credentials was found: " << std::endl;
          this->output << *cour;
          if (validation::validateBoolInput(input, this->output, error, "Would you like to modify this Course? ")) {
            VALIDATE_EXIT(courseModification(*this, cour));
          }
        } else {
          this->error << "! ERROR: The Course you searched for was not found." << std::endl;
        }

        break;
      }

      case 3:
        if (this->sec->deleteCourse()) {
          this->output << "|---------------- Course has been deleted ----------------|" << std::endl;
        }

        break;

      default:
        return NO_EXIT;
    }
  }
}

/**
 * @brief This function handles modifying a given course object.
 * 
 * @param interface Takes the interface since its not a member function.
 * @param professor Takes the course which it is modifying.
 * @return SHOULD_EXIT Returns EXIT if it needs to exit.
 */
interface::SHOULD_EXIT courseModification(interface &interface, course *course) {

  while (true) {

    /* - menu print - */
    interface.output << "|" << std::endl << "|------- Modifying Course with ID: " << course->getFormattedUniID() << " -------|" << std::endl;
    interface.output << "| Choose one of the following options: " << std::endl;
    interface.output << "1. Change Course Name" << std::endl;
    interface.output << "2. Change Course ECTs" << std::endl;
    interface.output << "3. Change Whether the Course is Mandatory or Not" << std::endl;
    interface.output << "4. Change Course Semester" << std::endl;
    interface.output << "5. Assign a Professor to this Course" << std::endl;
    interface.output << "6. Register a Student to this Course" << std::endl;
    interface.output << "7. Print and Save to File every Student that Passed this Course" << std::endl;
    interface.output << "8. Print Course Parameters" << std::endl;
    interface.output << "9. Return to Course Management Menu" << std::endl;

        /* - obtain and validate user option/input - */
    unsigned char option;

    VALIDATE_EXIT(option = validation::validateNumericalInput<unsigned char>(interface.input, interface.output, interface.error, 
                              "Enter the number corresponding to what you want to do: ", 9));

    /* - cases for each option - */
    switch (option) {

      case 1:
        interface.sec->removeCourse(course);
        course->setName();
        interface.sec->addCourse(course);
        break;

      case 2:
        course->setECTs();
        break;

      case 3:
        course->setIsMandatory();
        break;

      case 4:
        course->setSemester();
        break;

      case 5: {

        professor *(secretary::*id_search)(unsigned int) = &secretary::retrieveProfessor;
        professor *(secretary::*name_search)(const std::string &) = &secretary::retrieveProfessor;
        professor *prof = validation::validateSearchCriteria<professor>(interface.input, interface.output, interface.error, 
                            "Enter the Name or University ID of the Professor you want to assign to this Course: ", id_search, name_search, *interface.sec);

        if (prof != nullptr) {
          interface.output << "|" << "| Professor with the following credentials was found: " << std::endl;
          interface.output << *prof;
          
          if (validation::validateBoolInput(interface.input, interface.output, interface.error, "Would to like to assign this Professor? ")) {
            if (course->assignProfessor(prof))
              interface.output << "|-------------- Professor has been assigned --------------|" << std::endl;
            else 
              interface.error << "! ERROR: This Professor is already assigned to this Course." << std::endl;

          } else {
            interface.output << "| Assignment has been aborted." << std::endl;
          }
        } else {
          interface.error << "! ERROR: The Professor you searched for was not found." << std::endl;
        }

        break;
      }

      case 6: {

        student *(secretary::*id_search)(unsigned int) = &secretary::retrieveStudent;
        student *(secretary::*name_search)(const std::string &) = &secretary::retrieveStudent;
        student *stud = validation::validateSearchCriteria<student>(interface.input, interface.output, interface.error, 
                          "Enter the Name or University ID of the Student you want to register to this Course: ", id_search, name_search, *interface.sec);

        if (stud != nullptr) {
          interface.output << "|" << "| Student with the following credentials was found: " << std::endl;
          interface.output << *stud;

          if (stud->getSemester() < course->getSemester()) {
            interface.error << "! ERROR: Based on Semester qualifiers, this Student is not eligible to register to this Course." << std::endl;
            break;

          } else if (validation::validateBoolInput(interface.input, interface.output, interface.error, "Would to like to register this Student? ")) {
            if (course->registerStudent(stud))
              interface.output << "|-------------- Student has been registered --------------|" << std::endl;
            else 
              interface.error << "! ERROR: This Student is already assigned to this Course." << std::endl;

          } else {
            interface.output << "| Registration has been aborted." << std::endl;
          }

        } else {
          interface.error << "! ERROR: The Student you searched for was not found." << std::endl;
        }

        break;
      }

      case 7: {
      }

      case 8:
        interface.output << *course;
        break;

      default:
        return interface::NO_EXIT;
    }
  }
}