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

/**
 * @brief Special MACRO that checks whether the Interface has detected the exit command "!q" and returns the current function if it has.
 * 
 */
#define SHOULD_EXIT_2() if(ShouldExit) return modified;

class Interface {

  private:

    Secretary *secretary;

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
    bool StudentModification(Student *student);

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
    bool ProfessorModification(Professor *professor);

    /**
     * @brief Manages the Add, Modify and Delete Operations for the Course Objects in Secretary and handles the Display of them.
     * 
     */
    void CourseManagement();

    /**
     * @brief Handles the Display and Modification of a Course Object. Is Called by CourseManagement().
     * 
     * @param course Takes a Course Pointer as a parameter and performs all modifications on that Object.
     */
    bool CourseModification(Course *course);

    /**
     * @brief Searches for a Course Object.
     * 
     */
    void ProfessorAssignment();

    /**
     * @brief Assigns Professor Objects to a Course Object in Secretary. Is Called by ProfessorAssignment().
     * 
     * @param course Takes a Course Pointer as a parameter and performs all modifications on that Object.
     */
    bool ProfessorAssigner(Course *course);

    /**
     * @brief Validates the input when the user is asked to choose among a number of operations. If the function detects an input of "!q" it changes the Should exit
     * value and returns 1.
     * 
     * @param NumberOfChoices The number of operations available to the user at the given time.
     * @return Either the choice the user made as a numerical value or 0 if the user's input was invalid;
     */
    unsigned short ValidateMenuInput(unsigned short NumberOfChoices);

    /**
     * @brief Validates the input when the user is asked for a date. Example of valid date input: DD/MM/YYYY. If it detecs the wrong user input it throws an
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
     * @brief Validates the user input as either a University ID number or a Name as a string and returns the pointer to the object retrieved from the secretary.
     * 
     * @param IDSearchFunc The function within secretary that retrieves an object using an unsigned int ID.
     * @param NameSearchFunc The function within the secretary that retrieves an object using a string Name.
     * @return void* Pointer to the object retrieved.
     */
    template <typename T>
    T* ValidateSearchCriteria(T* (Secretary::*IDSearchFunc)(unsigned int), T* (Secretary::*NameSearchFunc)(const string &));

  public:

    Interface();
    inline ~Interface() { delete this->secretary; }

    void main();

    static bool ShouldExit;

};

/**
 * @brief Validates the user input as either a University ID number or a Name as a string and returns the pointer to the object retrieved from the secretary.
 * 
 * @param IDSearchFunc The function within secretary that retrieves an object using an unsigned int ID.
 * @param NameSearchFunc The function within the secretary that retrieves an object using a string Name.
 * @return void* Pointer to the object retrieved.
 */
template <typename T>
T *Interface::ValidateSearchCriteria(T *(Secretary::*IDSearchFunc)(unsigned int), T *(Secretary::*NameSearchFunc)(const string &)) {

  string Buffer;
  getline(cin, Buffer);

  if ((Buffer[0] == 'S' && Buffer[1] == '-') 
      || (Buffer[0] == 'P' && Buffer[1] == '-') 
      || (Buffer[0] == 'C' && Buffer[1] == '-')) {
    
    unsigned int UniID;
    try {
      UniID = stoi(Buffer.substr(7));

    // handle out_of_range cases from both substr() and stoi().
    } catch (out_of_range &e) {
      if (!string(e.what()).compare("substr")) 
        throw out_of_range("! ERROR: University ID is too short.");
      else if (!string(e.what()).compare("stoi")) 
        throw out_of_range("! ERROR: University ID is too long.");

    // handle the case where the substring isn't a number
    } catch (invalid_argument &e) {
      throw invalid_argument("! ERROR: Invalid University ID Format.");
    }

    // if the id is valid we return the result of the search function.
    return (this->secretary->*IDSearchFunc)(UniID);

  } else {

    // check whether the name REALLY is a name and contains only allowed characters. else we throw an invalid_argument
    for (string::iterator itr = Buffer.begin(); itr != Buffer.end(); itr++)
      if ((*itr >= 'a' && *itr <= 'z') || (*itr >= 'A' && *itr <= 'Z') || *itr == ' ') continue;
      else throw invalid_argument("! ERROR: Invalid Character '" + string(1, *itr) + "' inserted. Expected a Name.");

    // if the name is valid we return the result of the search function.
    return (this->secretary->*NameSearchFunc)(Buffer);
  }
}