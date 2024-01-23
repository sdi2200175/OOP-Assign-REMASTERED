/**
 * @file validation.hpp
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

/**
 * @brief This MACRO is used to check whether a returning function gives code
 * EXIT in which case we also return EXIT and close the program.
 *
 */
#define VALIDATE_EXIT(function)        \
    if ((function) == interface::EXIT) \
    return interface::EXIT

namespace validation {

const std::string user_prompt_prefix = "> ";

/**
 * @brief Prompts the user for a name type input and returns the user's input if
 * it passes all the checks.
 *
 * @param input The input stream.
 * @param output The output stream for the prompt.
 * @param error The error stream for the various exceptions.
 * @param user_prompt The prompt that is presented to the user.
 * @return std::string The user input is returned if the validation is
 * successful.
 */
inline std::string validateNameInput(std::istream& input, std::ostream& output,
    std::ostream& error,
    const std::string& user_prompt) {

    std::string buffer;

    // keep going in the loop until the function returns.
    while (true) {

        output << user_prompt_prefix << user_prompt;
        std::getline(input, buffer);

        // we check each character in the buffer to make sure it's as expected. if
        // something unexpected is found we throw an internal exception and catch it
        // to exit the internal loop and continue the external one.
        try {

            if (buffer.length() == 0)
                throw std::invalid_argument("! ERROR: No input.");

            for (std::string::iterator itr = buffer.begin(); itr != buffer.end();
                 itr++)
                if ((*itr >= 'a' && *itr <= 'z') || (*itr >= 'A' && *itr <= 'Z') || *itr == ' ')
                    continue;
                else
                    throw std::invalid_argument("! ERROR: Invalid Character '" + std::string(1, *itr) + "' inserted.");
        } catch (std::invalid_argument& e) {
            error << e.what() << std::endl;
            continue;
        }

        // if all the checks pass and no exception is thrown we return the user's
        // input.
        return buffer;
    }
}

/**
 * @brief Prompts the user for a date type input and returns the user's input if
 * it passes all the checks.
 *
 * @param input The input stream.
 * @param output The output stream for the prompt.
 * @param error The error stream for the various exceptions.
 * @param user_prompt The prompt that is presented to the user.
 * @return std::string The user input is returned if the validation is
 * successful.
 */
inline std::string validateDateInput(std::istream& input, std::ostream& output,
    std::ostream& error,
    const std::string& user_prompt) {

    std::string buffer;

    while (true) {

        output << user_prompt_prefix << user_prompt << "(DD/MM/YYYY) ";
        getline(input, buffer);

        // we check each character in the buffer to make sure it's as expected. if
        // something unexpected is found we throw an internal exception and catch it
        // to exit the internal loop and continue the external one.
        try {

            if (buffer.length() == 0)
                throw std::invalid_argument("! ERROR: No input.");

            // first we check the dates format and length to make sure its correct
            if (buffer.length() != 10 || buffer[2] != '/' || buffer[5] != '/')
                throw std::invalid_argument("! ERROR: Invalid Date Format.");

            // afterwards we check the particular substrings in  the buffer to ensure
            // they are numbers within the valid range.
            std::string temp = buffer.substr(0, 2);
            for (std::string::iterator itr = temp.begin(); itr != temp.end(); itr++)
                if (*itr >= '0' && *itr <= '9')
                    continue;
                else
                    throw std::invalid_argument("! ERROR: Character '" + std::string(1, *itr) + "' is not a valid numerical value.");

            int num = stoi(temp);
            if (num > 31)
                throw std::out_of_range("! ERROR: No month has more than 31 days.");

            temp = buffer.substr(3, 2);
            for (std::string::iterator itr = temp.begin(); itr != temp.end(); itr++)
                if (*itr >= '0' && *itr <= '9')
                    continue;
                else
                    throw std::invalid_argument("! ERROR: Character '" + std::string(1, *itr) + "' is not a valid numerical value.");

            num = stoi(temp);
            if (num > 12)
                throw std::out_of_range("! ERROR: No year has more than 12 months.");

            temp = buffer.substr(6, 4);
            for (std::string::iterator itr = temp.begin(); itr != temp.end(); itr++)
                if (*itr >= '0' && *itr <= '9')
                    continue;
                else
                    throw std::invalid_argument("! ERROR: Character '" + std::string(1, *itr) + "' is not a valid numerical value.");
        } catch (std::invalid_argument& e) {
            output << e.what() << std::endl;
            continue;
        } catch (std::out_of_range& e) {
            std::cout << e.what() << std::endl;
            continue;
        }

        // if all the checks pass and no exception is thrown we return the user's
        // input.
        return buffer;
    }
}

/**
 * @brief Prompts the user for a yes or no type of input and returns true if the
 * user typed 'Y' and false if they typed 'N'.
 *
 * @param input The input stream.
 * @param output The output stream for the prompt.
 * @param error The error stream for the various exceptions.
 * @param user_prompt The prompt that is presented to the user.
 * @return true If the user typed 'Y'
 * @return false If the user typed 'N'
 */
inline bool validateBoolInput(std::istream& input, std::ostream& output,
    std::ostream& error,
    const std::string& user_prompt) {

    std::string buffer;

    while (true) {

        output << user_prompt_prefix << user_prompt << "(Y or N) ";
        getline(input, buffer);

        // we check each character in the buffer to make sure it's as expected. if
        // something unexpected is found we throw an internal exception and catch it
        // to exit the internal loop and continue the external one.
        try {

            if (buffer.length() == 0)
                throw std::invalid_argument("! ERROR: No input.");

            if (!buffer.compare("Y") || !buffer.compare("y"))
                return true;
            else if (!buffer.compare("N") || !buffer.compare("n"))
                return false;
            else
                throw std::invalid_argument("! ERROR: Input '" + buffer + "' is not valid for this type of input.");

        } catch (std::invalid_argument& e) {
            output << e.what() << std::endl;
            continue;
        }
    }
}

/**
 * @brief Template function for validating numerical user input and limiting it
 * to a user defined value and variable type.
 *
 * @tparam T The type of number the user has been requested to input.
 * @param input The input stream.
 * @param output The output stream for the prompt.
 * @param error The error stream for the various exceptions.
 * @param user_prompt The prompt that is presented to the user.
 * @param maximum_value The maximum numerical value the user is allowed to
 * input.
 * @return T The user rinput as a T number if the validation is successful.
 */
template <typename T>
T validateNumericalInput(std::istream& input, std::ostream& output,
    std::ostream& error, const std::string& user_prompt,
    T maximum_value) {

    T value;
    std::string buffer;

    // keep going in the loop until the function returns.
    while (true) {

        output << user_prompt_prefix << user_prompt;
        std::getline(input, buffer);

        // check the exit condition.
        if (!buffer.compare("q!"))
            return 0;

        try {

            if (buffer.length() == 0)
                throw std::invalid_argument("! ERROR: No input.");

            for (std::string::iterator itr = buffer.begin(); itr != buffer.end();
                 itr++)
                if (*itr >= '0' && *itr <= '9')
                    continue;
                else
                    throw std::invalid_argument("! ERROR: Character '" + std::string(1, *itr) + "' is not a valid numerical value.");

            long long temp = std::stoll(buffer);
            if (temp > maximum_value)
                throw std::out_of_range("placeholder");
            value = (T)temp;

        } catch (std::invalid_argument& e) {
            error << e.what() << std::endl;
            continue;
        } catch (std::out_of_range& e) {
            error << "! ERROR: Inserted number is too large." << std::endl;
            continue;
        }

        return value;
    }
}

/**
 * @brief Template function for validating search criteria and performing search
 * based on id or on name with the specified pointer functions.
 *
 * @tparam T The class type the user wants to search.
 * @param input The input stream.
 * @param output The output stream for the prompt.
 * @param error The error stream for the various exceptions.
 * @param user_prompt The prompt that is presented to the user.
 * @param id_search Pointer to a function that searches based on id.
 * @param name_search Pointer to a function that searches based on a name
 * string.
 * @return T* Pointer to the class object the user searched for or nullptr if
 * the object doesn't exist in the searched database.
 */
template <typename T>
T* validateSearchCriteria(std::istream& input, std::ostream& output,
    std::ostream& error, const std::string& user_prompt,
    T* (secretary::*id_search)(unsigned int),
    T* (secretary::*name_search)(const std::string&),
    secretary& secretary) {

    std::string buffer;

    output << user_prompt_prefix << user_prompt;
    std::getline(input, buffer);

    // if the user's input has an id format
    if (buffer[0] == T::id_prefix && buffer[1] == '-' && buffer[6] == '-' && buffer.length() == 14) {

        unsigned int uni_id;
        std::string temp = buffer.substr(7, 7);
        try {
            for (std::string::iterator itr = temp.begin(); itr != temp.end(); itr++)
                if (*itr >= '0' && *itr <= '9')
                    continue;
                else
                    throw std::invalid_argument("! ERROR: Character '" + std::string(1, *itr) + "' is not a valid numerical value.");
        } catch (std::invalid_argument& e) {
            error << e.what() << std::endl;
            return nullptr;
        }

        uni_id = stoi(temp);
        return (secretary.*id_search)(uni_id);
    } else {
        return (secretary.*name_search)(buffer);
    }
}
}; // namespace validation
