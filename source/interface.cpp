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
#include "secretary.hpp"

void Interface::begin() {

  cout << endl << "        Welcome to the University Management System ver. 0.0.1" << endl;
  cout << "+--------------------------------------------------------------------+" << endl;

  // TODO - When there's time
  // cout << "|" << endl << "? Attempting to load Department Information from files..." << endl;
  // cout << "! ERROR: Files Not Found. Please enter the details of your department manually below." << endl;

  cout << "|" << endl << "| Input Department Secretary Attributes below." << endl;

  Secretary sec;

  cout << "|" << endl << "? Attempting to load Department Students, Professors and Courses from files..." << endl;
  cout << "! ERROR: Files Not Found. Secretary will be left empty." << endl;
}

void Interface::main() {

  cout << "|" << endl << "+----------- Main User Menu -----------+" << endl;
  cout << "| Choose one of the following Options:" << endl;
  cout << "1. Add/Modify/Delete Student(s)" << endl;
  cout << "2. Add/Modify/Delete Professor(s)" << endl;
  cout << "3. Add/Modify/Delete Course(s)" << endl;
  cout << "4. Print Department Information and/or Statistics" << endl;
  cout << "5. Save to Files and Exit" << endl;
  cout << "| Enter the Number corresponding to the desired Action." << endl << "> ";

  cin.get();
}
