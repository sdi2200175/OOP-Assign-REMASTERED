/**
 * @file interface.hpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief
 * @version 0.1
 * @date 2024-01-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "secretary.hpp"
#include <iostream>

class interface {

public:

    /**
     * @brief A Standard divided used across the interface of the program.
     * 
     */
    static const std::string divider;

    /**
     * @brief Gauges whether the program should exit or not. When a function with return type SHOULD_EXIT returns EXIT
     * the program will quit the mainMenu() function and close.
     *
     */
    typedef enum {
        EXIT = 0,
        NO_EXIT = 1
    } SHOULD_EXIT;

    /**
     * @brief Construct a new interface object
     *
     * @param input An input stream from which the interface will accept user input.
     * @param output An output stream the interface will use to display standard usage messages.
     * @param error An output stream the interface will use to display any errors and warnings.
     */
    interface(std::istream& input, std::ostream& output, std::ostream& error);

    /**
     * @brief Destroy the interface object
     *
     */
    ~interface();

    /**
     * @brief Display the main menu and handle the rest of the gui and display of the program.
     *
     * @return SHOULD_EXIT If this value is equal to EXIT the function above this one should always also return EXIT until the
     * program exits.
     */
    SHOULD_EXIT mainMenu();

private:
    secretary* sec;
    std::istream& input;
    std::ostream& output;
    std::ostream& error;

    void displayTitle();

    /**
     * @brief Manages all student-centric options in the program.
     *
     * @return SHOULD_EXIT Returns EXIT if the program should quit.
     */
    SHOULD_EXIT studentManagement();

    /**
     * @brief Manages all professor-centric options in the program.
     *
     * @return SHOULD_EXIT Returns EXIT if the program should quit.
     */
    SHOULD_EXIT professorManagement();

    /**
     * @brief Manages all course-centric options in the program.
     *
     * @return SHOULD_EXIT Returns EXIT if the program should quit.
     */
    SHOULD_EXIT courseManagement();

    /**
     * @brief This function handles modifying a given student object.
     *
     * @param interface Takes the interface since its not a member function.
     * @param student Takes the student which it is modifying.
     * @return SHOULD_EXIT Returns EXIT if it needs to exit.
     */
    friend interface::SHOULD_EXIT studentModification(interface& interface, student* student);

    /**
     * @brief This function handles modifying a given professor object.
     *
     * @param interface Takes the interface since its not a member function.
     * @param professor Takes the professor which it is modifying.
     * @return SHOULD_EXIT Returns EXIT if it needs to exit.
     */
    friend interface::SHOULD_EXIT professorModification(interface& interface, professor* professor);

    /**
     * @brief This function handles modifying a given course object.
     *
     * @param interface Takes the interface since its not a member function.
     * @param professor Takes the course which it is modifying.
     * @return SHOULD_EXIT Returns EXIT if it needs to exit.
     */
    friend interface::SHOULD_EXIT courseModification(interface& interface, course* course);
};
