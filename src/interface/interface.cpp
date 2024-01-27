/**
 * @file interface.cpp
 * @brief This file contains the definition of the interface class functions.
 * @authors Evaggelia Ragkousi, Spyros Strakosia
 * @date 26/01/2024
 */

#include "io.h"
#include "interface.h"

interface::interface() {

    // Print the title.
    std::cout << io::output::title;

    // File loading of secretary properties.
    std::cout << "? Attempting to load department information from files..." << std::endl;
    std::cout << "! ERROR: File loading failed. Proceeding manually..." << std::endl << std::endl;

    // Create the secretary manually and show its properties.
    this->sec = io::output::buildObj<secretary>("Building Department Secretary...");
    io::output::showAttr<secretary>("Department Information", this->sec, true);

    // Wait for user confirmation.
    io::input::await("Proceed to the Main Menu?");
}

interface::~interface() {
    delete sec;
}

io::SHOULD_EXIT interface::main_menu() {

    const std::string menu_title = "Main Menu";
    const std::string options[] = {"Manage Student(s)", "Manage Professor(s)", "Manage Course(s)",
                                   "Show Potential Graduates", "Move to the next Semester",
                                   "Save to Local Files and Exit"};

    while (true) {

        std::stringstream ss;
        ss << "  Department Information" << std::endl << io::output::divider << std::endl << *sec << io::output::divider
           << std::endl;
        io::output::menu(ss.str(), menu_title, sizeof(options) / sizeof(options[0]), options);

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

            case 1:
                CHECK_EXIT(studentManagement());
                break;

            case 2:
                CHECK_EXIT(professorManagement());
                break;

            case 3:
                CHECK_EXIT(courseManagement());
                break;

            case 5:
                sec->incrementSemester();
                io::input::await("Return to Main Menu?");
                break;

            default:
                return io::NO_EXIT;
        }
    }
}
