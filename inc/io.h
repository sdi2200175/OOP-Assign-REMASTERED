/**
 * @file io.h
 * @brief This file contains many helper functions that are used across the project
 * to validate user input.
 * @authors Evaggelia Ragkousi, Spyros Strakosia
 * @date 25/01/2024
 */

#ifndef UNIMANAGEMENT_IO_H
#define UNIMANAGEMENT_IO_H

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

#include "secretary.h"

/// This MACRO function check the output of a SHOULD_EXIT type of return value and
/// if it is equal to EXIT returns the EXIT value.
#define CHECK_EXIT(function)        \
    if ((function) == io::EXIT)  \
    return io::EXIT

namespace io {

    /// Constants for managing files.
    const std::string stud_db_name = "data/student_db";
    const std::string prof_db_name = "data/professor_db";
    const std::string cour_db_name = "data/course_db";

    /// This enum is used as a return value to check whether the program should exit
    /// at any given point or not.
    typedef enum {
        EXIT, NO_EXIT
    } SHOULD_EXIT;

    /// Namespace within the io namespace that contains input handling functions.
    namespace input {

        /// This prefix contains characters that will be displayed before any prompt to the
        /// user for an input.
        const std::string prompt_prefix = "> ";

        /**
         * Checks a user's input, when a string of type name is requested and if the input is valid
         * returns the input.
         * @param input The source from which we will draw the user's input.
         * @param prompt The prompt that will be display to the user as the reason their input
         * is requested.
         * @return If all checks out, the function will return a string containing the
         * user's input.
         * @throws invalid_argument If the user inputs an invalid character.
         */
        inline std::string name(std::istream &input, const std::string &prompt) {

            // We keep a buffer where we store the user input.
            std::string buffer;

            // Show the prompt and get the user's input.
            std::cout << prompt_prefix << prompt << " ";
            getline(input, buffer);

            // If the buffer is empty, i.e. the user has given no input, the function throws an
            // invalid_argument exception.
            if (buffer.empty())
                throw std::invalid_argument("! ERROR: No input given.");

            // Check each character in the string to make sure it contains only letters and spaces.
            // If the string contains anything else, the function throws an invalid_argument exception.
            for (auto itr = buffer.begin(); itr != buffer.end(); itr++)
                if (((*itr) < 'a' || (*itr) > 'z') && ((*itr) < 'A' || (*itr) > 'Z') && (*itr) != ' ')
                    throw std::invalid_argument(
                            "! ERROR: Character '" + std::string(1, (*itr)) + "' is not a valid character for a name.");

            // If all checks, we return the buffer.
            return buffer;
        }

        /**
         * Checks a user's input, when a boolean type is requested and if the input is valid
         * returns true or false accordingly.
         * @param input The source from which we will draw the user's input.
         * @param prompt The prompt that will be displayed to the user as the reason their input
         * is requested.
         * @return If all checks out, the function will return a bool containing true or false according
         * to the user's input.
         * @throw invalid_argument If the user input is invalid.
         */
        inline bool boolean(std::istream &input, const std::string &prompt) {

            // We keep a buffer where we store the user input.
            std::string buffer;

            // Show the prompt and get the user's input.
            std::cout << prompt_prefix << prompt << " (y / N) ";
            getline(input, buffer);

            // We transform the string to lowercase.
            std::string final = buffer;
            std::transform(buffer.begin(), buffer.end(), final.begin(), ::tolower);

            // We return false if the buffer is empty, i.e. the user has given no input, or if the user
            // has given any of the following inputs: "n", "N", "No", or any variation of the word no.
            if (final.empty() || final == "n" || final == "no")
                return false;

            // If the input is "y" or "yes" we return true.
            if (final == "y" || final == "yes")
                return true;

            // If the input is neither true nor false we throw an exception.
            throw std::invalid_argument("! ERROR: Input '" + buffer + "' is not a valid input.");
        }

        /**
         * Waits for the user to give any type of input before returning.
         * @param prompt The prompt that will be displayed to the user as the reason their input
         * is requested.
         */
        inline void await(const std::string &prompt) {

            // Show the prompt and get the user's input.
            std::cout << prompt_prefix << prompt << " (Press enter to proceed) ";
            std::cin.get();
        }

        /**
         * Checks a user's input, when a date type is requested and if the input is valid
         * returns the user's input.
         * @param input The source from which we will draw the user's input.
         * @param prompt The prompt that will be displayed to the user as the reason their input
         * is requested.
         * @return If all checks out, the function will return a string containing the user's input.
         * @throw invalid_argument If the user input is invalid.
         * @throw out_of_range If the user inputs a date with values beyond what is real.
         */
        inline std::string date(std::istream &input, const std::string &prompt) {

            // We keep a buffer where we store the user input.
            std::string buffer;

            // Show the prompt and get the user's input.
            std::cout << prompt_prefix << prompt << " (DD/MM/YYYY) ";
            getline(input, buffer);

            // If the buffer is empty, i.e. the user has given no input, the function throws an
            // invalid_argument exception.
            if (buffer.empty())
                throw std::invalid_argument("! ERROR: No input given.");

            // If the buffer doesn't have a length of 10 or doesn't have forward-slash dividers in the
            // right places we throw an exception.
            if (buffer.length() != 10 || buffer[2] != '/' || buffer[5] != '/')
                throw std::invalid_argument("! ERROR: Invalid date format.");

            // First we check the first 2 numbers of the date.
            std::string temp = buffer.substr(0, 2);

            // We check that the substring contains only numbers.
            for (auto itr = temp.begin(); itr != temp.end(); itr++)
                if ((*itr) < '0' || (*itr) > '9')
                    throw std::invalid_argument(
                            "! ERROR: Character '" + std::string((*itr), 1) + "' cannot be used in a date.");

            // If the numbers represent a value over 31 we throw an exception.
            if (std::stoi(temp) > 31)
                throw std::out_of_range("! ERROR: No month has more than 31 days.");

            // Now we check the next 2 consecutive numbers for the month.
            temp = buffer.substr(3, 2);

            // We check that the substring contains only numbers.
            for (auto itr = temp.begin(); itr != temp.end(); itr++)
                if ((*itr) < '0' || (*itr) > '9')
                    throw std::invalid_argument(
                            "! ERROR: Character '" + std::string((*itr), 1) + "' cannot be used in a date.");

            // If the numbers represent a value over 31 we throw an exception.
            if (std::stoi(temp) > 12)
                throw std::out_of_range("! ERROR: No year has more than 12 months.");

            // Now we check the next 4 consecutive numbers for the year.
            temp = buffer.substr(6, 4);

            // We check that the substring contains only numbers.
            for (auto itr = temp.begin(); itr != temp.end(); itr++)
                if ((*itr) < '0' || (*itr) > '9')
                    throw std::invalid_argument(
                            "! ERROR: Character '" + std::string((*itr), 1) + "' cannot be used in a date.");

            // If all checks are passed the date is valid, and we return the user's input.
            return buffer;
        }

        /**
         * Template function for checking a user's input, when a type of number is requested and
         * checks it against a numerical value. It returns the input as a number if all checks are passed.
         * @tparam T Number type used in the function.
         * @param input The source from which we will draw the user's input.
         * @param prompt The prompt that will be displayed to the user as the reason their input
         * is requested.
         * @param max_value The maximum value the function will accept as valid numerical input.
         * @return If all checks out, the function will return a number derived from the user's input.
         * @throw invalid_argument If the user input is invalid.
         * @throw out_of_range If the user inputs a number with values beyond what is allowed.
         */
        template<typename T>
        T number(std::istream &input, const std::string &prompt, T max_value) {

            // We keep a buffer where we store the user input.
            std::string buffer;

            // Show the prompt and get the user's input.
            std::cout << prompt_prefix << prompt << " ";
            getline(input, buffer);

            // If the buffer is equal to quit or exit we return 0 to signal a function exit;
            if (buffer == "quit" || buffer == "exit")
                return EXIT;

            // If the buffer is empty, i.e. the user has given no input, the function throws an
            // invalid_argument exception.
            if (buffer.empty())
                throw std::invalid_argument("! ERROR: No input given.");

            // We check that the string contains only numbers.
            for (auto itr = buffer.begin(); itr != buffer.end(); itr++)
                if ((*itr) < '0' || (*itr) > '9')
                    throw std::invalid_argument(
                            "! ERROR: Character '" + std::string(1, (*itr)) + "' cannot be used as a numerical input.");

            // We transform the buffer to a number and check whether the number is larger than
            // the maximum value.
            unsigned long temp = std::stol(buffer);
            if (temp > max_value)
                throw std::out_of_range("! ERROR: Inserted value '" + buffer + "' is outside the allowed range.");

            // Return the value as a T type.
            return (T) temp;
        }

        /**
         * Template function for checking a user's input, when a type of search criteria is requested and
         * checks it to determine whether it's a name or a university id and searches for the requested class accordingly
         * using the provided functions and secretary object.
         * @tparam T Class being searched for.
         * @param input The source from which we will draw the user's input.
         * @param prompt The prompt that will be displayed to the user as the reason their input
         * is requested.
         * @param secretary Instance of secretary whose databases will be searched.
         * @param id_search Function pointer to function that can be used to search for the requested object using a university id.
         * @param name_search Function pointer to function that can be used to search for the requested object using a name.
         * @return A pointer to the object found.
         * @throw invalid_argument If the university id uses invalid characters after the second dash.
         * @throw out_of_range If the class being searched for was not found.
         */
        template<class T>
        T *search(std::istream &input, const std::string &prompt, secretary &secretary,
                  T *(secretary::*id_search)(unsigned int),
                  T *(secretary::*name_search)(const std::string &name)) {

            // We keep a buffer where we store the user input.
            std::string buffer;

            // Show the prompt and get the user's input.
            std::cout << prompt_prefix << prompt << " ";
            getline(input, buffer);

            // Check if the input doesn't have the university id format and if it doesn't we perform a name
            // search instead.
            if (buffer[0] != T::id_prefix || buffer[1] != '-' || buffer[6] != '-' || buffer.length() != 14) {
                auto value = (secretary.*name_search)(buffer);
                if (value->getFormattedUniId()[0] == T::id_prefix)
                    return (T *) value;
                else
                    throw std::out_of_range("! ERROR: No match.");
            }

            // If it has a university format we proceed.

            // We get the last 7 digits of the string, as this is the real university id number that will
            // be used in search,
            std::string temp = buffer.substr(7, 7);

            // We check that the string contains only numbers.
            for (auto itr = temp.begin(); itr != temp.end(); itr++)
                if ((*itr) < '0' || (*itr) > '9')
                    throw std::invalid_argument(
                            "! ERROR: Character '" + std::string(1, (*itr)) + "' cannot be used in university ids.");

            // The real university id number.
            unsigned int uni_id = std::stoi(temp);

            // We perform a university id search.
            auto value = (secretary.*id_search)(uni_id);
            if (value->getFormattedUniId()[0] == T::id_prefix)
                return (T *) value;
            else
                throw std::out_of_range("! ERROR: No match.");
        }
    }

    /// Namespace within the io namespace that contains output handling functions.
    namespace output {

        /// Standard divider string that will be printed whenever a content divider is needed.
        const std::string divider = "+==========================================================+";

        /// Title that will be displayed at the top of every menu.
        const std::string title = divider + "\n"
                                            "|                                                          |\n"
                                            "|               University Management System               |\n"
                                            "|                                                          |\n"
                                  + divider;

        template<class T>
        void items(std::ostream &stream, const std::string &list_title, const std::vector<T> array, bool clear) {

            // Clear the screen for a minimal look.
            if (clear)
                system("clear");

            // Print the title and the title of the menu being printed.
            stream << title << std::endl
                   << std::endl << "  " << list_title << std::endl
                   << divider << std::endl;

            // Print all the items.
            for (auto itr = array.begin(); itr != array.end(); itr++)
                stream << *(*itr) << divider << std::endl;

            // Add divider.
            stream << divider << std::endl;
        }

        /**
         * Prints the attributes of an object.
         * @tparam T The object type.
         * @param attr_title The title of the attributes pane.
         * @param object The object whose properties we want printed.
         */
        template<class T>
        void showAttr(const std::string &attr_title, const T *object, bool show_title) {

            // Print the title and the title of the attributes being printed.
            if (show_title) {
                // Clear the screen for a minimal look.
                system("clear");
                std::cout << title << std::endl;
            }

            std::cout << std::endl << "  " << attr_title << std::endl
                      << divider << std::endl;

            // Print object attributes.
            std::cout << *object;

            // Add divider.
            std::cout << divider << std::endl;
        }

        /**
         * Prints the options of a menu.
         * @param menu_title Title of the menu being printed.
         * @param options The options within the menu.
         */
        inline void menu(const std::string &prelude, const std::string &menu_title, unsigned int amount_of_options,
                         const std::string options[]) {

            // Clear the screen for a minimal look.
            system("clear");

            // Print the title and the title of the menu being printed.
            std::cout << title << std::endl;

            if (!prelude.empty())
                std::cout << std::endl << prelude << std::endl;

            std::cout << "  " << menu_title << std::endl
                      << divider << std::endl;

            // Print the actual options.
            for (unsigned int i = 0; i < amount_of_options; i++)
                std::cout << "| " << i + 1 << ". " << options[i] << std::endl;

            // Print a divider below the menu.
            std::cout << divider << std::endl;
        }

        /**
         * Builds an object of type T from user input.
         * @tparam T The type of object we want built.
         * @param build_title The title of the build pane.
         * @return The object that was built.
         */
        template<class C, typename T>
        C *buildObj(const std::string &build_title, T constructor_arg) {

            // Clear the screen for a minimal look.
            system("clear");

            // Print the title and the title of the menu being printed.
            std::cout << title << std::endl
                      << std::endl << "  " << build_title << std::endl
                      << divider << std::endl;

            // Create the class.
            C *value = new C(constructor_arg);

            // Print final divider.
            std::cout << divider << std::endl;
            return value;
        }

        /// Same as above function, just without a constructor argument requirement.
        template<class C>
        C *buildObj(const std::string &build_title) {

            // Clear the screen for a minimal look.
            system("clear");

            // Print the title and the title of the menu being printed.
            std::cout << title << std::endl
                      << std::endl << "  " << build_title << std::endl
                      << divider << std::endl;

            // Create the class.
            C *value = new C;

            // Print final divider.
            std::cout << divider << std::endl;
            return value;
        }
    }
}

#endif //UNIMANAGEMENT_IO_H
