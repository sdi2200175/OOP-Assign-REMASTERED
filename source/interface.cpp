#include "interface.hpp"

void Interface::begin() {

  cout << endl << "        Welcome to the University Management System ver. 0.0.1" << endl;
  cout << "+--------------------------------------------------------------------+" << endl;

  cout << "| Attempting to load Department Information from files..." << endl;
  cout << "! Error: Files Not Found. Please enter the details of your department manually: " << endl;

  cin.get();

}