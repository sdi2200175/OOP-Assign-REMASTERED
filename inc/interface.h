//
// Created by Spyros Strakosia on 25/1/24.
//

#ifndef UNIMANAGEMENT_INTERFACE_H
#define UNIMANAGEMENT_INTERFACE_H

#include "io.h"
#include "secretary.h"

class interface {

private:
    secretary *sec;

public:
    interface();

    ~interface();

    /// Displays the application's main menu.
    io::SHOULD_EXIT main_menu();

    // Student Management

    /// Manages the student interfacing parts of the interface.
    io::SHOULD_EXIT studentManagement();

    /// Manages the student modification part of the interface.
    io::SHOULD_EXIT studentModification(student *stud);

    // Professor Management

    /// Manages the professor interfacing parts of the interface.
    io::SHOULD_EXIT professorManagement();

    /// Manages the professor modification part of the interface.
    io::SHOULD_EXIT professorModification(professor *prof);

    // Course Management

    /// Manages the course interfacing part of the interface.
    io::SHOULD_EXIT courseManagement();

    /// Manages the course modification part of the interface.
    io::SHOULD_EXIT courseModification();

    // Helper Functions.

    /// Handles registering a particular student to a particular course.
    void courseRegistration();

    /// Handles assigning a particular professor to a particular course.
    void courseAssignment();
};


#endif //UNIMANAGEMENT_INTERFACE_H
