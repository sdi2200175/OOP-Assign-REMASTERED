/**
 * @file course_interface_2.cpp
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
    cout << "|" << endl << "+------ Professor Assignment Menu -----+" << endl;
    cout << "| Choose one of the following options: " << endl;
    cout << "1. Assign Professor(s) to this Course" << endl;
    cout << "2. Unassign Professor(s) from this Course" << endl;
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
      case 1: 
      case 2: {

        string Buffer;
        Professor *professor = nullptr;

        while (true) {
          cout << "> Enter the Full Name or the University ID of the Professor you want to ";
          if (Choice == 1) { cout << "assign to this Course: "; }
          else { cout << "unassign from this Course: "; }
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
        if (Choice == 1) { 
          course->addProfessorToAssignedProfessorsDatabase(professor); 
          professor->addCourseToAssignedCoursesDatabase(course);
        }
        else { 
          course->removeProfessorFromAssignedProfessorsDatabase(professor); 
          professor->removeCourseFromAssignedCoursesDatabase(course);
        }
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
    cout << "|" << endl << "+------ Student Registration Menu -----+" << endl;
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
      
      case 1:
      case 2: {

        string Buffer;
        Student *student = nullptr;

        while (true) {
          cout << "> Enter the Full Name or the University ID of the Student you want to ";
          if (Choice == 1) { cout << "register to this Course: "; }
          else { cout << "unregister from this Course "; }
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
        if (Choice == 1) { 
          course->addStudentToRegisteredStudentsDatabase(student); 
          student->addCourseToRegisteredCoursesDatabase(course);  
        }
        else { 
          course->removeStudentFromRegisteredStudentsDatabase(student); 
          student->removeCourseFromRegisteredCoursesDatabase(course);
        }
        flag = true;
        break;
      }

      default:
        return flag;
    }
  }
}