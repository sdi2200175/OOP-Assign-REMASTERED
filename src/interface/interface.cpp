/**
 * @file interface.cpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief
 * @version 0.1
 * @date 2024-01-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <chrono>
#include <thread>

#include "interface.hpp"
#include "validation.hpp"

const std::string interface::divider =
    "+==========================================================+";

/**
 * @brief Construct a new interface object
 *
 * @param input An input stream from which the interface will accept user input.
 * @param output An output stream the interface will use to display standard
 * usage messages.
 * @param error An output stream the interface will use to display any errors
 * and warnings.
 */
interface::interface(std::istream &input, std::ostream &output,
                     std::ostream &error)
    : input(input), output(output), error(error) {

  system("clear");

  this->displayTitle();

  /* - File Loader - */
  this->output << "? Attempting to load Department Secretary properties from files..."
               << std::endl;
  this->error << "! ERROR: File loading failed. Proceeding with manual input."
              << std::endl
              << std::endl;

  // Wait a bit before prompting the user to insert secretary data.
  std::this_thread::sleep_for(std::chrono::milliseconds(750));

  /* - Fallback if secretary files aren't found - */
  this->output << "  Building Secretary: " << std::endl
               << interface::divider << std::endl
               << "| Enter Secretary Credentials Below: " << std::endl;

  this->sec = new secretary;

  this->output << "| Created Secretary for the Deaprtment of "
               << this->sec->getDepartmentName() << std::endl
               << interface::divider << std::endl
               << std::endl;

  /* - Student Professor and Course File Loaders - */
  this->output << "? Attempting to load Department Students, Professors and "
                  "Courses from files..."
               << std::endl;
  this->error << "! ERROR: Files Not Found. Secretary will be left empty."
              << std::endl
              << std::endl;

  this->output << "| Proceeding to Main User Menu..." << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

/**
 * @brief Destroy the interface object
 *
 */
interface::~interface() { delete this->sec; }

/**
 * @brief Display the main menu and handle the rest of the gui and display of
 * the program.
 *
 * @return SHOULD_EXIT If this value is equal to EXIT the function above this
 * one should always also return EXIT until the program exits.
 */
interface::SHOULD_EXIT interface::mainMenu() {

  /* - Main menu loop - */
  while (true) {

    // Clear Terminal Screen
    system("clear");

    this->displayTitle();

    /* - menu print - */
    this->output << "  Main User Menu" << std::endl
                 << this->divider << std::endl
                 << "| Choose one of the following options: " << std::endl
                 << "| 1. Proceed to Student Management Menu" << std::endl
                 << "| 2. Proceed to Professor Management Menu" << std::endl
                 << "| 3. Proceed to Course Management Menu" << std::endl
                 << "| 4. Print every Student who is able to Graduate"
                 << std::endl
                 << "| 5. Move on to the Next Semester" << std::endl
                 << "| 6. Print Department Parameters" << std::endl
                 << "| 7. Save Data to Files and Exit Program" << std::endl
                 << this->divider << std::endl;

    /* - obtain and validate user option/input - */
    unsigned char option = validation::validateNumericalInput<unsigned char>(
        this->input, this->output, this->error,
        "Enter the number corresponding to what you want to do: ", 7);

    /* - cases for each option - */
    switch (option) {

      while (true) {

      case 1:
        VALIDATE_EXIT(this->studentManagement());
        break;

      case 2:
        VALIDATE_EXIT(this->professorManagement());
        break;

      case 3:
        VALIDATE_EXIT(this->courseManagement());
        break;

      case 4:
        this->sec->printGraduates();

      case 5:
        this->sec->incrementSemester();
        break;

      case 6:
        system("clear");
        this->displayTitle();
        this->output << "  Secretary Department Information" << std::endl
                     << interface::divider << std::endl;

        this->output << *(this->sec);

        this->output << interface::divider << std::endl;
        validation::validateConfirmation(this->input, this->output, this->error,
                                         "Return to the Main User Menu? ");

        break;

      default:
        return EXIT;
      }
    }
  }
}

void interface::displayTitle() {
  /* - Start Message - */
  this->output << this->divider << std::endl
               << "|                                                          |"
               << std::endl
               << "|               University Mnagement System                |"
               << std::endl
               << "|                                                          |"
               << std::endl
               << this->divider << std::endl
               << std::endl;
}
