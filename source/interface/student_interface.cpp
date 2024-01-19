/**
 * @file student_interface.cpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief 
 * @version 0.1
 * @date 2024-01-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "interface.hpp"

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
      Choice = this->ValidateMenuInput(4);

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

      // Add a Student to the Secretary
      case 1: {
        this->secretary->addStudent();
        cout << "| Added Student to Secretary." << endl;
        break;
      }

      // Modify a Student in the Secretary
      case 2: {
        string Buffer;
        Student *student = nullptr;

          cout << "> Enter the Full Name or the University ID of the Student you want to modify: ";
          try {
            Student* (Secretary::*retrieveByID)(unsigned int) = &Secretary::retrieveStudent;
            Student* (Secretary::*retrieveByName)(const string &) = &Secretary::retrieveStudent;
            student = ValidateSearchCriteria<Student>(retrieveByID, retrieveByName);
          
          // handle the case where the id inserted is outside the allowed range of number lengths.
          } catch (out_of_range &e) {
            cerr << e.what() << endl;
            break;
          
          // handle the case where the id and/or name is invalid or uses invalid characters.
          } catch (invalid_argument &e) {
            cerr << e.what() << endl;
          break;
        }

        cout << "| Found Student named " << student->getName() << " with University ID: " << student->getFormattedID() << "." << endl;
        this->StudentModification(student);
        SHOULD_EXIT();
        break;
      }

      // Delete a Student from the Secretary
      case 3: {
        string Buffer;
        Student *student = nullptr;

          cout << "> Enter the Full Name or the University ID of the Student you want to delete: ";
          try {
            Student* (Secretary::*retrieveByID)(unsigned int) = &Secretary::retrieveStudent;
            Student* (Secretary::*retrieveByName)(const string &) = &Secretary::retrieveStudent;
            student = ValidateSearchCriteria<Student>(retrieveByID, retrieveByName);

          // handle the case where the id inserted is outside the allowed range of number lengths.
          } catch (out_of_range &e) {
            cerr << e.what() << endl;
            break;

          // handle the case where the id and/or name is invalid or uses invalid characters.
          } catch (invalid_argument &e) {
            cerr << e.what() << endl;
          break;
        }

        cout << "| Found Student named " << student->getName() << " with University ID: " << student->getFormattedID() << "." << endl;
        this->secretary->deleteStudent(student);
        cout << "| Deleted Student from Secretary." << endl;
        break;
      }

      default:
        return;
    }
  }
}

/**
 * @brief Handles the Display and Modification of a Student Object. Is called by StudentManagement().
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

    string Buffer;
    switch (Choice) {
    case 1: {
      while (true) {
        cout << "> Enter Student's new Full Name: ";
        try {
          Buffer = this->ValidateNameInput();

        // handles the case where the user has input an invalid name.
        } catch (invalid_argument &e) {
          cerr << e.what() << endl;
          continue;
        }

        break;
      }

      this->secretary->removeStudentFromDatabase(student);
      student->setName(Buffer);
      this->secretary->addStudentToDatabase(student);
      cout << "| Modified Student's Name." << endl;
      break;
    }

    case 2: {
      unsigned short NewECTs;
      while (true) {
        cout << "> Enter the Student's new ECT Amount: ";
        try {
          NewECTs = this->ValidateMenuInput(9999);

        // stoi() exception handling
        } catch (invalid_argument &e) { 
          cerr << e.what() << endl;
          continue;

        // handle the case when the given value is above the limit of the possible ECT Values.
        } catch (out_of_range &e) {
          cerr << e.what() << endl;
          continue;
        }

        break;
      }

      student->setECTs(NewECTs);
      cout << "| Modified Student's ECTs." << endl;
      break;
    }

    case 3: {
      while (true) {
        cout << "> Enter Student's new Date Of Birth: ";
        try {
          Buffer = this->ValidateDateInput();

        // handle the case when the user inserts a wrongly formatted date.
        } catch (invalid_argument &e) {
          cerr << e.what() << endl;
          continue;
        }

        break;
      }

      student->setDateOfBirth(Buffer);
      cout << "| Modified Student's Date of Birth." << endl;
      break;
    }

    case 4: {
      while (true) {
        cout << "> Enter Student's new Date Of Registration: ";
        try {
          Buffer = this->ValidateDateInput();

        // handle the case when the user inserts a wrongly formatted date.
        } catch (invalid_argument &e) {
          cerr << e.what() << endl;
          continue;
        }

        break;
      }

      student->setDateOfRegistration(Buffer);
      cout << "| Modified Student's Date of Registration." << endl;
      break;
    }

    default:
      return;
    }
  }
}