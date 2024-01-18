/**
 * @file professor_interface.cpp
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
 * @brief Manages the Add, Modify and Delete Operations for the Professor Objects in Secretary and handles the Display of them.
 * 
 */
void Interface::ProfessorManagement() {

  while(true) {

    cout << "|" << endl << "+----- Professor Management Menu ------+" << endl;
    cout << "| Choose one of the following options: " << endl;
    cout << "1. Add a Professor to the Secretary" << endl;
    cout << "2. Modify an existing Professor of the Secretary" << endl;
    cout << "3. Delete an existing Professor from the Secretary" << endl;
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
      
      // Add a Professor to the Secretary
      case 1: {
        cout << "+------- Constructing Professor -------+" << endl;
        this->secretary->addProfessor();
        cout << "+------- Constructed Professor --------+" << endl;
        break;
      }

      case 2: {
        string Buffer;
        Professor *professor = nullptr;

        while (true) {
          cout << "> Enter the Full Name or the University ID of the Student you want to modify: ";
          try {
            Professor* (Secretary::*retrieveByID)(unsigned int) = &Secretary::retrieveProfessor;
            Professor* (Secretary::*retrieveByName)(const string &) = &Secretary::retrieveProfessor;
            professor = ValidateSearchCriteria<Professor>(retrieveByID, retrieveByName);
          
          // handle the case where the id inserted is outside the allowed range of number lengths.
          } catch (out_of_range &e) {
            cerr << e.what() << endl;
            continue;
          
          // handle the case where the id and/or name is invalid or uses invalid characters.
          } catch (invalid_argument &e) {
            cerr << e.what() << endl;
            continue;
          }

          break;
        }

        cout << "| Found Professor named " << professor->getName() << " with University ID: " << professor->getFormattedID() << "." << endl;
        this->ProfessorModification(professor);
        SHOULD_EXIT();
        cout << "+--- Modified Professor in Secretary --+" << endl;
        break;
      }

      case 3: {
        string Buffer;
        Professor *professor = nullptr;

        while (true) {
          cout << "> Enter the Full Name or the University ID of the Student you want to delete: ";
          try {
            Professor* (Secretary::*retrieveByID)(unsigned int) = &Secretary::retrieveProfessor;
            Professor* (Secretary::*retrieveByName)(const string &) = &Secretary::retrieveProfessor;
            professor = ValidateSearchCriteria<Professor>(retrieveByID, retrieveByName);
          
          // handle the case where the id inserted is outside the allowed range of number lengths.
          } catch (out_of_range &e) {
            cerr << e.what() << endl;
            continue;
          
          // handle the case where the id and/or name is invalid or uses invalid characters.
          } catch (invalid_argument &e) {
            cerr << e.what() << endl;
            continue;
          }

          break;
        }

        cout << "| Found Professor named " << professor->getName() << " with University ID: " << professor->getFormattedID() << "." << endl;
        this->secretary->deleteProfessor(professor);
        cout << "+-- Deleted Professor from Secretary --+" << endl;
        return;
      }

      default:
        return;
    }
  }
}

/**
 * @brief Handles the Display and Modification of a Professor Object. Is Called by ProfessorManagement().
 * 
 * @param professor Takes a Professor Pointer as a parameter and performs all modifications on that Object.
 */
void Interface::ProfessorModification(Professor *professor) {

  while (true) {
    cout << "|" << endl << "+- Modifying Professor with ID " << professor->getFormattedID() << " -+" << endl;
    cout << "| Choose one of the following options: " << endl;
    cout << "1. Change Professor's Name" << endl;
    cout << "2. Go Back" << endl;
    cout << "> Enter the Number corresponding to the desired Action: ";

    unsigned short Choice;
    try {
      Choice = this->ValidateMenuInput(2);

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
        cout << "> Enter Professor's new Full Name: ";
        try {
          Buffer = this->ValidateNameInput();

        // handles the case where the user has input an invalid name.
        } catch (invalid_argument &e) {
          cerr << e.what() << endl;
          continue;
        }

        break;
      }
      
      this->secretary->removeProfessorFromDatabase(professor);
      professor->setName(Buffer);
      this->secretary->addProfessorToDatabase(professor);
      break;
    }

    default:
      return;
    }
  }
}