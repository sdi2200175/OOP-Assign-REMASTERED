/**
 * @file course_interface.cpp
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
 * @brief Manages the Add, Modify and Delete Operations for the Course Objects in Secretary and handles the Display of them.
 * 
 */
void Interface::CourseManagement() {

  while(true) {

    cout << "|" << endl << "+------- Course Management Menu -------+" << endl;
    cout << "| Choose one of the following options: " << endl;
    cout << "1. Add a Course to the Secretary" << endl;
    cout << "2. Modify an existing Course of the Secretary" << endl;
    cout << "3. Delete an existing Course from the Secretary" << endl;
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

      // Add a Course to the Secretary
      case 1: {
        cout << "|" << endl << "+--------- Constructing Course --------+" << endl;
        this->secretary->addCourse();
        cout << "+--------- Constructed Course ---------+" << endl;
        break;
      }

      // Modify a Course in the Secretary
      case 2: {
        string Buffer;
        Course *course = nullptr;

        while (true) {
          cout << "> Enter the Full Name or the Course ID of the Course you want to modify: ";
          try {
            Course* (Secretary::*retrieveByID)(unsigned int) = &Secretary::retrieveCourse;
            Course* (Secretary::*retrieveByName)(const string &) = &Secretary::retrieveCourse;
            course = ValidateSearchCriteria<Course>(retrieveByID, retrieveByName);
          
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

        cout << "| Found Course named " << course->getName() << " with Course ID: " << course->getFormattedCourseID() << "." << endl;
        bool flag = this->CourseModification(course);
        SHOULD_EXIT();
        if (flag)
          cout << "+---- Modified Course in Secretary ----+" << endl;
        break;
      }

      // Delete a Course from the Secretary
      case 3: {
        string Buffer;
        Course *course = nullptr;

        while (true) {
          cout << "> Enter the Full Name or the Course ID of the Course you want to delete: ";
          try {
            Course* (Secretary::*retrieveByID)(unsigned int) = &Secretary::retrieveCourse;
            Course* (Secretary::*retrieveByName)(const string &) = &Secretary::retrieveCourse;
            course = ValidateSearchCriteria<Course>(retrieveByID, retrieveByName);

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

        cout << "| Found Course named " << course->getName() << " with Course ID: " << course->getFormattedCourseID() << "." << endl;
        this->secretary->deleteCourse(course);
        cout << "+---- Deleted Course from Secretary ---+" << endl;
        break;
      }

      default:
        return;
    }
  }
}

/**
 * @brief Handles the Display and Modification of a Course Object. Is called by CourseManagement().
 * 
 * @param course Takes a Course Pointer as a parameter and performs all modifications on that Object.
 */
bool Interface::CourseModification(Course *course) {

  bool flag = false;

  while (true) {
    cout << "|" << endl << "+- Modifying Course with ID " << course->getFormattedCourseID() << " -+" << endl;
    cout << "| Choose one of the following options: " << endl;
    cout << "1. Change Course's Name" << endl;
    cout << "2. Change whether the Course is Mandatory or not" << endl;
    cout << "3. Change Course's ECTs" << endl;
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
    SHOULD_EXIT_2();

    string Buffer;
    switch (Choice) {
    case 1: {
      while (true) {
        cout << "> Enter Course's new Full Name: ";
        try {
          Buffer = this->ValidateNameInput();

        // handles the case where the user has input an invalid name.
        } catch (invalid_argument &e) {
          cerr << e.what() << endl;
          continue;
        }

        break;
      }

      this->secretary->removeCourseFromDatabase(course);
      course->setName(Buffer);
      this->secretary->addCourseToDatabase(course);
      flag = true;
      break;
    }

    case 2: {
      course->setMandatory(!(course->getMandatory()));
      if (course->getMandatory()) { cout << "| The Course is now Mandatory" << endl; }
	    else { cout << "| The Course is now non Mandatory" << endl; }
      flag = true;
      break;
    }

    case 3: {
      unsigned short NewECTs;
      while (true) {
        cout << "> Enter the Course's new ECT Amount: ";
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

      course->setECTs(NewECTs);
      flag = true;
      break;
    }

    default:
      return flag;
    }
  }
}

/**
 * @brief Searches for a Course Object.
 * 
 */
void Interface::CourseSearch(unsigned short Choice) {

  bool flag = false;
  string Buffer;
  Course *course = nullptr;

  while (true) {
    cout << "> Enter the Full Name or the Course ID of the Course whose ";
    if (Choice == 4) { cout << "assigned Professor(s) you want to modify: "; } 
    else { cout << "registered Student(s) you want to modify: "; }
    try {
      Course* (Secretary::*retrieveByID)(unsigned int) = &Secretary::retrieveCourse;
      Course* (Secretary::*retrieveByName)(const string &) = &Secretary::retrieveCourse;
      course = ValidateSearchCriteria<Course>(retrieveByID, retrieveByName);
          
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

  cout << "| Found Course named " << course->getName() << " with Course ID: " << course->getFormattedCourseID() << "." << endl;
  if (Choice == 4) { flag = this->ProfessorAssignment(course); }
  else { flag = this->StudentRegistration(course); }
  SHOULD_EXIT();
  if (Choice == 4 && flag) { cout << "+--- Modified assigned Professor(s) ---+" << endl; }
  else if (Choice == 5 && flag) { cout << "+--- Modified registered Students(s) --+" << endl; }
  return;
  
}

/**
 * @brief Assigns Professor Objects to a Course Object in Secretary. Is called by CourseSearch().
 * 
 * @param course Takes a Course Pointer as a parameter and performs all modifications on that Object.
 */
bool Interface::ProfessorAssignment(Course *course) {

  bool flag = false;

  while (true) {
    cout << "|" << endl << "+- Modifying assigned Professor(s) to Course with ID " << course->getFormattedCourseID() << " -+" << endl;
    cout << "| Choose one of the following options: " << endl;
    cout << "1. Assign Professor(s) to this Course" << endl;
    cout << "2. Remove assigned Professor(s) from this Course" << endl;
    cout << "3. Go Back" << endl;
    cout << "> Enter the Number corresponding to the desired Action: ";

    unsigned short Choice;
    try {
      Choice = this->ValidateMenuInput(3);

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
    SHOULD_EXIT_2();

    switch (Choice) {
    case 1: {

      string Buffer;
      Professor *professor = nullptr;

      while (true) {
        cout << "> Enter the Full Name or the University ID of the Professor you want to assign to this Course: ";
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
      course->addProfessorToAssignedProfessorsDatabase(professor);
      flag = true;
      break;
    }

    case 2: {

      string Buffer;
      Professor *professor = nullptr;

      while (true) {
        cout << "> Enter the Full Name or the University ID of the Professor you want to remove from this Course: ";
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
      course->removeProfessorFromAssignedProfessorsDatabase(professor);
      flag = true;
      break;
    }

    default:
      return flag;
    }
  }
}

/**
 * @brief Assigns Student Objects to a Course Object in Secretary. Is called by CourseSearch().
 * 
 * @param course Takes a Course Pointer as a parameter and performs all modifications on that Object.
 */
bool Interface::StudentRegistration(Course *course) {

  bool flag = false;

  while (true) {
    cout << "|" << endl << "+- Modifying registered Student(s) to Course with ID " << course->getFormattedCourseID() << " -+" << endl;
    cout << "| Choose one of the following options: " << endl;
    cout << "1. Register Student(s) to this Course" << endl;
    cout << "2. Unregister Student(s) from this Course" << endl;
    cout << "3. Go Back" << endl;
    cout << "> Enter the Number corresponding to the desired Action: ";

    unsigned short Choice;
    try {
      Choice = this->ValidateMenuInput(3);

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
    SHOULD_EXIT_2();

    switch (Choice) {
    case 1: {

      string Buffer;
      Student *student = nullptr;

      while (true) {
        cout << "> Enter the Full Name or the University ID of the Student you want to register to this Course: ";
        try {
          Student* (Secretary::*retrieveByID)(unsigned int) = &Secretary::retrieveStudent;
          Student* (Secretary::*retrieveByName)(const string &) = &Secretary::retrieveStudent;
          student = ValidateSearchCriteria<Student>(retrieveByID, retrieveByName);
          
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

      cout << "| Found Student named " << student->getName() << " with University ID: " << student->getFormattedID() << "." << endl;
      course->addStudentToRegisteredStudentsDatabase(student);
      flag = true;
      break;
    }

    case 2: {

      string Buffer;
      Student *student = nullptr;

      while (true) {
        cout << "> Enter the Full Name or the University ID of the Student you want to unregister from this Course: ";
        try {
          Student* (Secretary::*retrieveByID)(unsigned int) = &Secretary::retrieveStudent;
          Student* (Secretary::*retrieveByName)(const string &) = &Secretary::retrieveStudent;
          student = ValidateSearchCriteria<Student>(retrieveByID, retrieveByName);
          
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

      cout << "| Found Student named " << student->getName() << " with University ID: " << student->getFormattedID() << "." << endl;
      course->removeStudentFromRegisteredStudentsDatabase(student);
      flag = true;
      break;
    }

    default:
      return flag;
    }
  }
}