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

#include "interface.hpp"
#include "validation.hpp"

/**
 * @brief Construct a new interface object
 * 
 * @param input An input stream from which the interface will accept user input.
 * @param output An output stream the interface will use to display standard usage messages.
 * @param error An output stream the interface will use to display any errors and warnings.
 */
interface::interface(std::istream &input, std::ostream &output, std::ostream &error):
  input(input), output(output), error(error) {

  /* - Start Message - */

  this->output << "        Welcome to the University Management System" << std::endl;
  this->output << "+---------------------------------------------------------+" << std::endl;
  this->output << "| Made by: Evaggelia Ragkousi and Spyros Strakosia" << std::endl << "|" << std::endl;

  /* - File Loader - */
  this->output << "? Attempting to load Department Secretary properties from files..." << std::endl;
  this->error << "! ERROR: File loading failed. Proceeding with manual input." << std::endl << "|" << std::endl;

  /* - Fallback if secretary files aren't found - */
  this->sec = new secretary;

  /* - Student Professor and Course File Loaders - */
  this->output << "|" << std::endl << "? Attempting to load Department Students, Professors and Courses from files..." << std::endl;
  this->error << "! ERROR: Files Not Found. Secretary will be left empty." << std::endl << "|" << std::endl;
}

/**
 * @brief Destroy the interface object
 * 
 */
interface::~interface() {
  delete this->sec;
}

/**
 * @brief Display the main menu and handle the rest of the gui and display of the program.
 * 
 * @return SHOULD_EXIT If this value is equal to EXIT the function above this one should always also return EXIT until the
 * program exits.
 */
interface::SHOULD_EXIT interface::mainMenu() {

  /* - Main menu loop - */
  while (true) {

    /* - menu print - */
    this->output << "|" << std::endl << "|-------------------- Main User Menu ---------------------|" << std::endl;
    this->output << "| Choose one of the following options: " << std::endl;
    this->output << "1. Add/Modify/Delete Student(s)" << std::endl;
    this->output << "2. Add/Modify/Delete Professor(s)" << std::endl;
    this->output << "3. Add/Modify/Delete Course(s)" << std::endl;
    this->output << "4. Department Statistics" << std::endl;
    this->output << "5. Next Semester" << std::endl;
    this->output << "6. Save Data to Files and Exit Program" << std::endl;
    
    /* - obtain and validate user option/input - */
    unsigned char option = validation::validateNumericalInput<unsigned char>(this->input, this->output, this->error,
                                                                            "Enter the number corresponding to what you want to do: ", 6);

    /* - cases for each option - */
    switch (option) {

      case 1:
        VALIDATE_EXIT(this->studentManagement());
        break;

      case 2:
        VALIDATE_EXIT(this->professorManagement());
        break;

      case 3:
        VALIDATE_EXIT(this->courseManagement());
        break;

      default:
        return EXIT;
    }
  }
}