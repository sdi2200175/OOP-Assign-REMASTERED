/**
 * @file interface.hpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief 
 * @version 
 * @date 2024-01-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <iostream>
#include <limits>
#include "secretary.hpp"

using namespace std;

/**
 * @brief Special MACRO that checks whether the Interface has detected the exit command "!q" and returns the current function if it has.
 * 
 */
#define SHOULD_EXIT() if(ShouldExit) return;

class Interface {

  private:
    Secretary *secretary;
    
    /**
     * @brief Validates the input when the user is asked to choose among a number of operations. If the function detects an input of "!q" it changes the Should exit
     * value and returns 1.
     * 
     * @param NumberOfChoices The number of operations available to the user at the given time.
     * @return Either the choice the user made as a numerical value or 0 if the user's input was invalid;
     */
    unsigned short ValidateMenuInput(unsigned short NumberOfChoices);

    /**
     * @brief Validates the input when the user is asked for a date. Example of valid date input: DD/MM/YYYY. If it detects the wrong user input it throws an
     * invalid argument exception.
     * 
     * @return The date as read from the user.
     */
    string ValidateDateInput();

    /**
     * @brief Validates the input when the user is asked for a name. If it detects an unacceptable user input it throws an invalid_argument exception.
     * 
     * @return The string with the new name.
     * @exception Throws an invalid_argument exception when an invalid name has been inserted.
     */
    string ValidateNameInput();

    /**
     * @brief Manages the Add, Modify and Delete Operations for the Student Objects in Secretary and handles the Display of them.
     * 
     */
    void StudentManagement();

    /**
     * @brief Handles the Display and Modification of a Student Object. Is Called by StudentManagement().
     * 
     * @param student Takes a Student Pointer as a parameter and performs all modifications on that Object.
     */
    void StudentModification(Student *student);

    /**
     * @brief Manages the Add, Modify and Delete Operations for the Professor Objects in Secretary and handles the Display of them.
     * 
     */
    void ProfessorManagement();

    /**
     * @brief Handles the Display and Modification of a Professor Object. Is Called by ProfessorManagement().
     * 
     * @param professor Takes a Professor Pointer as a parameter and performs all modifications on that Object.
     */
    void ProfessorModification(Professor *professor);

  public:

    Interface();
    ~Interface();

    void main();

    static bool ShouldExit;

};