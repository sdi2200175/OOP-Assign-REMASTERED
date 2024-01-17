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

  cout << "|" << endl << "| NOTE: To exit the program type '!q' whenever at a menu." << endl;

  // TODO - When there's time
  cout << "|" << endl << "? Attempting to load Department Information from files..." << endl;
  cout << "! ERROR: Files Not Found. Please enter the details of your department manually below." << endl;

  cout << "|" << endl << "+------- Constructing Secretary -------+" << endl;

  string DepartmentName;
  unsigned short DepartmentCode, ECTRequirement, MaximumAttendance;
  while (true) {
    try {
      cout << "> Enter Department Name: ";
      DepartmentName = this->ValidateNameInput();
      break;
    } catch (invalid_argument &e) {
      cout << e.what() << endl;
    }
  }

  while (true) {
    try {
      cout << "> Enter Department Code: ";
      DepartmentCode = this->ValidateMenuInput(9999);
      break;
    } catch (invalid_argument &e) {
      cout << "! ERROR: Not a Number." << endl;
    } catch (out_of_range &e) {
      cout << e.what() << endl;
    }
  }

  while (true) {
    try {
      cout << "> Enter Department's ECT REquirement for Diploma: ";
      ECTRequirement = this->ValidateMenuInput(9999);
      break;
    } catch (invalid_argument &e) {
      cout << "! ERROR: Not a Number." << endl;
    } catch (out_of_range &e) {
      cout << e.what() << endl;
    }
  }

  while (true) {
    try {
      cout << "> Enter Department's Maximum Allowed Years of Attendance: ";
      MaximumAttendance = this->ValidateMenuInput(9999);
      break;
    } catch (invalid_argument &e) {
      cout << "! ERROR: Not a Number." << endl;
    } catch (out_of_range &e) {
      cout << e.what() << endl;
    }
  }

  this->secretary = new Secretary(DepartmentName, DepartmentCode, ECTRequirement, MaximumAttendance);
  
  cout << "+------- Constructed Secretary --------+" << endl;

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
    cout << "> Enter the Number corresponding to the desired Action: ";

    unsigned short Choice;
    try {
      Choice = this->ValidateMenuInput(5);
    } catch (out_of_range &e) {
      cout << e.what() << endl;
      continue;
    } catch (invalid_argument &e) {
      cout << "! ERROR: Not a Number." << endl;
      continue;
    }

    SHOULD_EXIT();
    
    switch(Choice) {
      case 1: {
        this->StudentManagement();
        SHOULD_EXIT();
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

/**
 * @brief Manages the Add, Modify and Delete Operations for the Student Objects in Secretary and handles the Display of them.
 * 
 */
void Interface::StudentManagement() {

  while(true) {

    cout << "|" << endl << "+------ Student Management Menu -------+" << endl;
    cout << "| Choose one of the following options: " << endl;
    cout << "1. Add a Student to the Secretary" << endl;
    cout << "2. Modify an existing Student of the Secretary" << endl;
    cout << "3. Delete an existing Student from the Secretary" << endl;
    cout << "4. Go Back" << endl;
    cout << "> Enter the Number corresponding to the desired Action: ";

    unsigned short Choice;
    try {
      Choice = this->ValidateMenuInput(5);
    } catch (out_of_range &e) {
      cout << "! ERROR: Not a Number." << endl;
      continue;
    } catch (invalid_argument &e) {
      cout << e.what() << endl;
      continue;
    }

    SHOULD_EXIT();

    switch(Choice) {
      case 1: {
        cout << "+-------- Constructing Student --------+" << endl;
        this->secretary->addStudent();
        cout << "+-------- Constructed Student ---------+" << endl;
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
            } catch(out_of_range &e) {
              cout << "! ERROR: Invalid University ID!" << endl;
              continue;
            } catch(invalid_argument &e) {
              cout << "! ERROR: Invalid University ID!" << endl;
              continue;
            }

            try {
              student = this->secretary->retrieveStudent(UniID);
            } catch (invalid_argument &e) {
              cout << e.what() << endl;
            }

            cout << "| Found Student named '" << student->getName() << "'." << endl;

          } else {
            try {
              student = this->secretary->retrieveStudent(Buffer);
            } catch(invalid_argument &e) {
              cout << e.what() << endl;
              continue;
            } 
            
            cout << "| Found Student with University ID: " << student->getFormattedID() << "." << endl;
          }
          break;
        }
        this->StudentModification(student);
        cout << "+---- Modified Student in Secretary ---+" << endl;
        SHOULD_EXIT();
        break;
      }

      case 3: {
        string Buffer;
        Student *student = nullptr;

        cout << "> Enter the Full Name or the University ID of the Student you want to delete: ";
        getline(cin, Buffer);

        if (Buffer[0] == 'S' && Buffer[1] == '-') {

          unsigned int UniID;
          try {
            UniID = stoi(Buffer.substr(7));
            student = this->secretary->retrieveStudent(UniID);
            cout << "| Found Student named '" << student->getName() << "'." << endl;
          } catch(out_of_range &e) {
            cout << "! ERROR: Invalid University ID!" << endl;
            break;
          } catch(invalid_argument &e) {
            cout << "! ERROR: Invalid University ID!" << endl;
            break;
          } catch(unsigned int InvalidID) {
            cout << "! ERROR: Student with University ID " << Buffer << " doesn't exist!" << endl;
            break;
          }

        } else {
          try {
            student = this->secretary->retrieveStudent(Buffer);
            cout << "| Found Student with University ID: " << student->getFormattedID() << "." << endl;
          } catch(const string &Name) {
            cout << "! ERROR: Student named '" << Buffer << "' doesn't exist!" << endl;
            break;
          } 
        }

        this->secretary->deleteStudent(student);
        cout << "+--- Deleted Student from Secretary ---+" << endl;
        return;
      }

      default:
        return;
    }
  }
}

/**
 * @brief Handles the Display and Modification of a Student Object. Is Called by StudentManagement().
 * 
 * @param student Takes a Student Pointer as a parameter and performs all modifications on that Object.
 */
void Interface::StudentModification(Student *student) {

  while (true) {
    cout << "|" << endl << "+- Modifying Student with ID " << student->getFormattedID() << " -+" << endl;
    cout << "| Choose one of the following options: " << endl;
    cout << "1. Change Student's Name" << endl;
    cout << "2. Change Student's ECTs" << endl;
    cout << "3. Change Student's Date of Birth" << endl;
    cout << "4. Change Student's Date of Registration" << endl;
    cout << "5. Go Back" << endl;
    cout << "> Enter the Number corresponding to the desired Action: ";

    unsigned short Choice;
    try {
      Choice = this->ValidateMenuInput(5);

    // stoi() exception handling
    } catch (out_of_range &e) {
      cout << "! ERROR: Not a Number." << endl;
      continue;

    // handles the case of the user inserting a number that's above the possible options of the menu.
    } catch (invalid_argument &e) {
      cout << e.what() << endl;
      continue;
    }

    // checks whether the user has input '!q' and returns the function if that's the case.
    SHOULD_EXIT();

    string Buffer;
    switch (Choice) {
    case 1: {
      try {
        cout << "> Enter Student's new Full Name: ";
        Buffer = this->ValidateNameInput();

      // handles the case where the user has input an invalid name.
      } catch (invalid_argument &e) {
        cout << e.what() << endl;
      }

      this->secretary->removeStudentFromDatabase(student);
      student->setName(Buffer);
      this->secretary->addStudentToDatabase(student);
      break;
    }

    case 2: {
      unsigned short NewECTs;
      cout << "> Enter the Student's new ECT Amount: ";
      try {
        NewECTs = this->ValidateMenuInput(9999);

      // stoi() exception handling
      } catch (invalid_argument &e) { 
        cout << "! ERROR: Not a Number." << endl;
        break;

      // handle the case when the given value is above the limit of the possible ECT Values.
      } catch (out_of_range &e) {
        cout << e.what() << endl;
        break;;
      }

      student->setECTs(NewECTs);
      break;
    }

    case 3: {
      cout << "> Enter Student's new Date Of Birth: ";
      try {
        Buffer = this->ValidateDateInput();
      } catch (invalid_argument &e) {
        cout << e.what() << endl;
        break;
      }

      student->setDateOfBirth(Buffer);
      break;
    }

    case 4: {
      cout << "> Enter Student's new Date Of Registration: ";
      try {
        Buffer = this->ValidateDateInput();
      } catch (invalid_argument &e) {
        cout << e.what() << endl;
        break;
      }

      student->setDateOfRegistration(Buffer);
      break;
    }

    default:
      return;
    }
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
  
  string Buffer;
  getline(cin, Buffer);
  if (!Buffer.compare("!q")) {
    ShouldExit = true;
    return 0;
  }

  if (stoi(Buffer) > NumberOfChoices) 
    throw out_of_range("! ERROR: Number '" + Buffer + "' is outside the allowed range of options.");
  else  
    return stoi(Buffer);
}

/**
  * @brief Validates the input when the user is asked for a date. Example of valid date input: DD/MM/YYYY. If it detecs the wrong user input it throws an
  * invalid argument exception.
  */
string Interface::ValidateDateInput() {

  string Buffer;
  getline(cin, Buffer);
  if (Buffer.length() != 10)
    throw invalid_argument("! ERROR: Invalid Date Format.");

  string::iterator itr = Buffer.begin();
  for (int i = 0; i < 2; i++)
    if (*itr >= '0' && *itr <= '9') itr++;
    else throw invalid_argument("! ERROR: Invalid Character '" + to_string(*itr) + "' inserted.");

  if (*itr == '/' || *itr == '-') itr++;
    else throw invalid_argument("! ERROR: Invalid Date Format.");

  for (int i = 0; i < 2; i++)
    if (*itr >= '0' && *itr <= '9') itr++;
    else throw invalid_argument("! ERROR: Invalid Character '" + to_string(*itr) + "' inserted.");

  if (*itr == '/' || *itr == '-') itr++;
  else throw invalid_argument("! ERROR: Invalid Date Format.");

  for (int i = 0; i < 4; i++)
    if (*itr >= '0' && *itr <= '9') itr++;
    else throw invalid_argument("! ERROR: Invalid Character '" + to_string(*itr) + "' inserted.");

  return Buffer;
}

/**
 * @brief Validates the input when the user is asked for a name. If it detects an unacceptable user input it throws an invalid_argument exception.
 * 
 * @return The string with the new name.
 * @exception Throws an invalid_argument exception when an invalid name has been inserted.
 */
string Interface::ValidateNameInput() {
  
  string Buffer;
  getline(cin, Buffer);

  for (string::iterator itr = Buffer.begin(); itr != Buffer.end(); itr++)
    if ((*itr >= 'a' && *itr <= 'z') || (*itr >= 'A' && *itr <= 'Z') || *itr == ' ') continue;
    else throw invalid_argument("! ERROR: Invalid Character '" + string(1, *itr) + "' inserted.");

  return Buffer;
}