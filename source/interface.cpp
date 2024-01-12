#include "interface.hpp"
#include "secretary.hpp"

void Interface::begin() {

  cout << endl << "        Welcome to the University Management System ver. 0.0.1" << endl;
  cout << "+--------------------------------------------------------------------+" << endl;

  cout << "|" << endl << "? Attempting to load Department Information from files..." << endl;
  cout << "! ERROR: Files Not Found. Please enter the details of your department manually below." << endl;

  Secretary sec;

  cout << "|" << endl << "? Attempting to load Department Students, Professors and Courses from files..." << endl;
  cout << "! ERROR: Files Not Found. Secretary will be left empty." << endl;
}

void Interface::main() {

  cout << "|" << endl << "+----------- Main User Menu -----------+" << endl;
  cout << "1. Modify Student(s)" << endl;
  cout << "2. Modify Proffessor(s)" << endl;
  cout << "3. Modify Course(s)" << endl;
  cout << "4. Print Department Information and/or Statistics" << endl;
  cout << "| Enter the Number corresponding to the desired Action." << endl << "> ";

  cin.get();
}
