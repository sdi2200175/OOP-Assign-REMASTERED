/**
 * @file interface.cpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief 
 * @version 
 * @date 2024-01-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "interface.hpp"

// This static interface variable controls the program's exit point.
// If it is ever changed to true the program will gracefully exit.
bool Interface::ShouldExit = false;

Interface::Interface() {

  cout << endl << "        Welcome to the University Management System ver. 0.0.1" << endl;
  cout << "+--------------------------------------------------------------------+" << endl;

  cout << "|" << endl << "| NOTE: To exit the program type '!q' whenever at a menu." << endl;

  // TODO - When there's time
  cout << "|" << endl << "? Attempting to load Department Information from files..." << endl;
  cerr << "! ERROR: Files Not Found. Please enter the details of your department manually below." << endl;

  cout << "|" << endl << "+------- Constructing Secretary -------+" << endl;

  string DepartmentName;
  unsigned short DepartmentCode, ECTRequirement, MaximumAttendance;
  while (true) {
    try {
      cout << "> Enter Department Name: ";
      DepartmentName = this->ValidateNameInput();
      break;
    } catch (invalid_argument &e) {
      cerr << e.what() << endl;
    }
  }

  while (true) {
    try {
      cout << "> Enter Department Code: ";
      DepartmentCode = this->ValidateMenuInput(9999);
      break;
    } catch (invalid_argument &e) {
      cerr << e.what() << endl;
    } catch (out_of_range &e) {
      cerr << e.what() << endl;
    }
  }

  while (true) {
    try {
      cout << "> Enter Department's ECT REquirement for Diploma: ";
      ECTRequirement = this->ValidateMenuInput(9999);
      break;
    } catch (invalid_argument &e) {
      cerr << e.what() << endl;
    } catch (out_of_range &e) {
      cerr << e.what() << endl;
    }
  }

  while (true) {
    try {
      cout << "> Enter Department's Maximum Allowed Years of Attendance: ";
      MaximumAttendance = this->ValidateMenuInput(9999);
      break;
    } catch (invalid_argument &e) {
      cerr << e.what() << endl;
    } catch (out_of_range &e) {
      cerr << e.what() << endl;
    }
  }

  this->secretary = new Secretary(DepartmentName, DepartmentCode, ECTRequirement, MaximumAttendance);
  
  cout << "+------- Constructed Secretary --------+" << endl;

  cout << "|" << endl << "? Attempting to load Department Students, Professors and Courses from files..." << endl;
  cerr << "! ERROR: Files Not Found. Secretary will be left empty." << endl;
}

void Interface::main() {

  while(true) {

    cout << "|" << endl << "+----------- Main User Menu -----------+" << endl;
    cout << "| Choose one of the following Options:" << endl;
    cout << "1. Add/Modify/Delete Student(s)" << endl;
    cout << "2. Add/Modify/Delete Professor(s)" << endl;
    cout << "3. Add/Modify/Delete Course(s)" << endl;
    cout << "4. Print Department Information and/or Statistics" << endl;
    cout << "5. Save to Files and Exit" << endl;
    cout << "> Enter the Number corresponding to the desired Action: ";

    unsigned short Choice;
    try {
      Choice = this->ValidateMenuInput(5);

    // stoi() exception handling
    } catch (invalid_argument &e) {
      cerr << e.what() << endl;
      continue;

    // handles the case when the user inserts a number that's outside the range of options.
    } catch (out_of_range &e) {
      cerr << e.what() << endl;
      continue;
    }

    // checks whether the user has input "!q" and if they have it returns the function.
    SHOULD_EXIT();
    
    switch(Choice) {
      case 1: {
        this->StudentManagement();
        SHOULD_EXIT();
        break;
      }

      case 2: {
        this->ProfessorManagement();
        SHOULD_EXIT();
        break;
      }

      case 3: {
        this->CourseManagement();
        SHOULD_EXIT();        
        break;
      }

      case 4:
        break; 
      
      default:
    }
  }
}