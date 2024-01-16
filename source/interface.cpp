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

bool Interface::ShouldExit = false;

Interface::Interface() {

  cout << endl << "        Welcome to the University Management System ver. 0.0.1" << endl;
  cout << "+--------------------------------------------------------------------+" << endl;

  // TODO - When there's time
  // cout << "|" << endl << "? Attempting to load Department Information from files..." << endl;
  // cout << "! ERROR: Files Not Found. Please enter the details of your department manually below." << endl;

  cout << "|" << endl << "| Input Department Secretary Attributes below." << endl;

  this->secretary = new Secretary;

  cout << "|" << endl << "? Attempting to load Department Students, Professors and Courses from files..." << endl;
  cout << "! ERROR: Files Not Found. Secretary will be left empty." << endl;
}

Interface::~Interface() {
  delete this->secretary;
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
    
    unsigned short Choice = this->ValidateMenuInput(5);
    if (!Choice) continue;
    SHOULD_EXIT();
    
    switch(Choice) {
      case 1: {
        this->StudentManagement();
        if (ShouldExit) return;
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
    SHOULD_EXIT();
    cout << "|" << endl;

    switch (Choice) {
    case 1: {
      cout << "+--- Adding New Student to Secretary --+" << endl;
      this->secretary->addStudent();
      cout << "+----- Added Student to Secretary -----+" << endl;
      break;
    }
    case 2: {
      string Buffer;
      Student *student = nullptr;
      while(true) {
        cout << "> Enter the Full Name or the University ID of the Student you want to modify: ";
        getline(cin, Buffer);
        if (Buffer[0] == 'S' && Buffer[1] == '-') {
          unsigned int UniID;
          try {
            UniID = stoi(Buffer.substr(7));
            student = this->secretary->retrieveStudent(UniID);
            cout << "| Found Student named '" << student->getName() << "'." << endl;
          } catch(out_of_range &e) {
            cout << "! ERROR: Invalid University ID!" << endl;
            continue;
          } catch(invalid_argument &e) {
            cout << "! ERROR: Invalid University ID!" << endl;
            continue;
          } catch(unsigned int InvalidID) {
            cout << "! ERROR: Student with University ID " << Buffer << " doesn't exist!" << endl;
            continue;
          }
        } else {
          try {
            student = this->secretary->retrieveStudent(Buffer);
            cout << "| Found Student with University ID: " << student->getFormattedID() << "." << endl;
          } catch(const string &Name) {
            cout << "! ERROR: Student named '" << Buffer << "' doesn't exist!" << endl;
            continue;
          } 
        }
        break;
      }
      this->StudentModification(student);
      SHOULD_EXIT();
      break;
    }
    default:
      break;
  }
  }
}

void Interface::StudentModification(Student *student) {

  while (true) {
    cout << "|" << endl << "+- Modifying Student with ID " << student->getFormattedID() << " -+" << endl;
    cout << "| Choose one of the following options: " << endl;
    cout << "1. Change Student's Name" << endl;
    cout << "2. Change Student's ECTs" << endl;
    cout << "3. Change Student's Date of Birth" << endl;
    cout << "4. Change Student's Date of Registration" << endl;

    unsigned short Choice = this->ValidateMenuInput(4);
    if (!Choice) continue;
    SHOULD_EXIT();

    string Buffer;

    switch (Choice) {
    case 1: {
      string NewName;
      while (true) {
        cout << "> Enter the Student's new First Name: ";
        getline(cin, NewName);
        cout << "> Enter the Student's new Father's Name / Middle Name: ";
        getline(cin, Buffer);
        NewName = NewName + " " + Buffer;
        cout << "> Enter the Student's new Last Name: ";
        getline(cin, Buffer);
        NewName = NewName + " " + Buffer;
        try {
          for (string::iterator itr = NewName.begin(); itr != NewName.end(); itr++)
            if ((*itr >= 'a' && *itr <= 'z') || (*itr >= 'A' && *itr <= 'Z') || *itr == ' ') continue;
            else throw *itr;
        } catch (char InvalidChar) {
          cout << "! ERROR: Invalid Character " << InvalidChar << " inserted." << endl;
          continue;
        }

        break;
      }

      this->secretary->removeStudentFromDatabase(student);
      student->setName(NewName);
      this->secretary->addStudentToDatabase(student);
      break;
    }

    case 2: {
      unsigned short NewECTs;
      while (true) {
        cout << "> Enter the Student's new ECT Amount: ";
        getline(cin, Buffer);
        try {
          int Temp = stoi(Buffer);
          if (Temp > numeric_limits<unsigned short>::max() || Temp < 0) 
            throw out_of_range("! ERROR: Number inserted is outside the allowed range.");

          NewECTs = Temp;
        } catch (invalid_argument &e) {
          cout << "! ERROR: Not a Number." << endl;
          continue;
        } catch (out_of_range &e) {
          cout << e.what() << endl;
          continue;
        }

        break;
      }

      student->setECTs(NewECTs);
      break;
    }

    case 3: {
      while(true) {
        cout << "> Enter Student's new Date Of Birth: ";
        getline(cin, Buffer);
        try {
          if (Buffer.length() != 10)
            throw invalid_argument("! ERROR: Invalid Date.");

          string::iterator itr = Buffer.begin();
          for (int i = 0; i < 2; i++)
            if (*itr >= '0' && *itr <= '9') itr++;
            else throw invalid_argument("! ERROR: Invalid Date.");
          
          if (*itr == '/' || *itr == '-') itr++;
          else throw invalid_argument("! ERROR: Invalid Date.");

          for (int i = 0; i < 2; i++)
            if (*itr >= '0' && *itr <= '9') itr++;
            else throw invalid_argument("! ERROR: Invalid Date.");

          if (*itr == '/' || *itr == '-') itr++;
          else throw invalid_argument("! ERROR: Invalid Date.");

          for (int i = 0; i < 4; i++)
            if (*itr >= '0' && *itr <= '9') itr++;
            else throw invalid_argument("! ERROR: Invalid Date.");
        } catch (invalid_argument &e) {
          cout << e.what() << endl;
          continue;
        }

        break;
      }
      
      student->setDateOfBirth(Buffer);
      break;
    }

    default:
      break;
    }

    break;
  }
}

/**
 * @brief Validates the input when the user is asked to choose among a number of operations. If the function detects an input of "!q" it changes the Should exit
 * value and returns 1.
 * 
 * @param NumberOfChoices The number of operations available to the user at the given time.
 * @return Either the choice the user made as a numerical value or 0 if the user's input was invalid;
 */
unsigned short Interface::ValidateMenuInput(unsigned short NumberOfChoices) {

  cout << "> Enter the Number corresponding to the desired Action: ";
  string Buffer;
  try {
    getline(cin, Buffer);
    if (!Buffer.compare("!q")) {
      ShouldExit = true;
      return 1;
    }

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