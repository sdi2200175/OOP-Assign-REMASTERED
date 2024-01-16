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
    void StudentManagement();
    void StudentModification(Student *student);

  public:

    Interface();

    void main();

    static bool ShouldExit;

};