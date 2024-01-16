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

Interface::Interface() {

  cout << endl << "        Welcome to the University Management System ver. 0.0.1" << endl;
  cout << "+--------------------------------------------------------------------+" << endl;

  // TODO - When there's time
  // cout << "|" << endl << "? Attempting to load Department Information from files..." << endl;
  // cout << "! ERROR: Files Not Found. Please enter the details of your department manually below." << endl;

  cout << "|" << endl << "| Input Department Secretary Attributes below." << endl;

  secretary = new Secretary;

  cout << "|" << endl << "? Attempting to load Department Students, Professors and Courses from files..." << endl;
  cout << "! ERROR: Files Not Found. Secretary will be left empty." << endl;
}

void Interface::main()
{

  while(true) {

    cout << "|" << endl << "+----------- Main User Menu -----------+" << endl;
    cout << "| Choose one of the following Options:" << endl;
    cout << "1. Add/Modify/Delete Student(s)" << endl;
    cout << "2. Add/Modify/Delete Professor(s)" << endl;
    cout << "3. Add/Modify/Delete Course(s)" << endl;
    cout << "4. Print Department Information and/or Statistics" << endl;
    cout << "5. Save to Files and Exit" << endl;
    
    unsigned short Choice = this->ValidateMenuInput(5);
    if (!Choice) continue;
    
    switch(Choice) {
      case 1: {
        this->StudentManagement();
        break;
      }

      case 2:
        break;

      case 3:
        break;

      case 4:
        break; 
      
      case 5:
        break;

    }
  }
}

void Interface::StudentManagement() {

  while(true) {

    cout << "|" << endl << "+------ Student Management Menu -------+" << endl;
    cout << "| Choose one of the following options: " << endl;
    cout << "1. Add a Student to the Secretary" << endl;
    cout << "2. Modify an existing Student of the Secretary" << endl;
    cout << "3. Delete an existing Student from the Secretary" << endl;

    unsigned short Choice = this->ValidateMenuInput(3);
    if (!Choice) continue;

    switch(Choice) {
      case 1: {
        cout << "|" << endl << "+--- Adding New Student to Secretary --+" << endl;
        this->secretary->addStudent();
        cout << "+----- Added Student to Secretary -----+" << endl;
        break;
      }

      case 2: {
        cout << "|" << endl << "> Enter the Full Name or the University ID of the Student you want to modify: ";
        string Buffer;
        getline(cin, Buffer);
        this->secretary->modifyStudent(Buffer);
        cout << "+----- Modified Student of Secretary -----+" << endl;
        break;
      }

      case 3: {
        cout << "|" << endl << "> Enter the Full Name or the University ID of the Student you want to delete: ";
        string Buffer;
        getline(cin, Buffer);
        this->secretary->deleteStudent(Buffer);
        cout << "+----- Deleted Student of Secretary -----+" << endl;
        break;
      }

      default:
        return;
    }
  }
}

unsigned short Interface::ValidateMenuInput(unsigned short NumberOfChoices) {

  cout << "> Enter the Number corresponding to the desired Action: ";
  string Buffer;
  try {
    getline(cin, Buffer);
    for (string::iterator itr = Buffer.begin(); itr != Buffer.end(); itr++)
      if (*itr < '0' || *itr > '9') throw(*itr);

    if (stoi(Buffer) > NumberOfChoices) throw(stoi(Buffer));
    return stoi(Buffer);

  } catch(char InvalidChar) {
    cout << "|" << endl << "! ERROR: Invalid Choice!" <<  endl;
  } catch(int Length) {
    cout << "|" << endl << "! ERROR: Number inserted is outside the selection range!" << endl;
  }

  return 0;
}