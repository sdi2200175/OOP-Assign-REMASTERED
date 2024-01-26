/**
 * @file interface.cpp
 * @brief This file contains the definition of the interface class functions for
 * the course interfacing parts.
 * @authors Evaggelia Ragkousi, Spyros Strakosia
 * @date 26/01/2024
 */

#include "io.h"
#include "interface.h"

io::SHOULD_EXIT interface::courseManagement() {

    const std::string menu_title = "Course Management Menu";
    const std::string options[] = { "Add a new Course",
                                    "Modify an existing Course",
                                    "Remove a Course",
                                    "Assign Professor to Course",
                                    "Register Student to Course",
                                    "Return to Main Menu"};

    // The inner menu loop.
    while (true) {

        io::output::menu(std::string(), menu_title, options);

        unsigned char option;
        while (true) {
            try {
                option = io::input::number<unsigned char>(std::cin, "Choose one of the options above:",
                                                          sizeof(options) / sizeof(options[0]));
                break;
            } catch (std::invalid_argument &e) {
                std::cout << e.what() << std::endl;
            }
        }

        CHECK_EXIT(option);

        switch (option) {
            default:
                return io::NO_EXIT;
        }
    }
}