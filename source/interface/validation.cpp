/**
 * @file validation.cpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief 
 * @version
 * @date 2024-01-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "interface.hpp"

/**
 * @brief Validates the input when the user is asked to choose among a number of operations. If the function detects an input of "!q" it changes the Should exit
 * value and returns 1.
 * 
 * @param NumberOfChoices The number of operations available to the user at the given time.
 * @return Either the choice the user made as a numerical value or 0 if the user's input was invalid;
 */
unsigned short Interface::ValidateMenuInput(unsigned short NumberOfChoices) {
  
  string Buffer;
  getline(cin, Buffer);

  if (!Buffer.compare("!q")) {
    ShouldExit = true;
    return 0;
  }

  for (string::iterator itr = Buffer.begin(); itr != Buffer.end(); itr++)
    if (*itr >= '0' && *itr <= '9') continue;
    else throw invalid_argument("! ERROR: Character '" + string(1, *itr) + "' is not acceptable as a numerical value.");

  int num = 0;
  try {
    num = stoi(Buffer);
  } catch (out_of_range &e) {
    throw out_of_range("! ERROR: Number '" + Buffer + "' is outside the allowed range.");
  } catch (invalid_argument &e) {
    throw invalid_argument("! ERROR: '" + Buffer + "' is not acceptable as a numerical value.");
  }

  if (num > NumberOfChoices) 
    throw out_of_range("! ERROR: Number '" + Buffer + "' is outside the allowed range of options.");
  else
    return num;
}

/**
  * @brief Validates the input when the user is asked for a date. Example of valid date input: DD/MM/YYYY. If it detecs the wrong user input it throws an
  * invalid argument exception.
  */
string Interface::ValidateDateInput() {

  string Buffer;
  getline(cin, Buffer);

  if (Buffer.length() != 10)
    throw invalid_argument("! ERROR: Invalid Date Format.");

  string::iterator itr = Buffer.begin();
  for (int i = 0; i < 2; i++)
    if (*itr >= '0' && *itr <= '9') itr++;
    else throw invalid_argument("! ERROR: Invalid Character '" + to_string(*itr) + "' inserted.");

  if (*itr == '/' || *itr == '-') itr++;
    else throw invalid_argument("! ERROR: Invalid Date Format.");

  for (int i = 0; i < 2; i++)
    if (*itr >= '0' && *itr <= '9') itr++;
    else throw invalid_argument("! ERROR: Invalid Character '" + to_string(*itr) + "' inserted.");

  if (*itr == '/' || *itr == '-') itr++;
  else throw invalid_argument("! ERROR: Invalid Date Format.");

  for (int i = 0; i < 4; i++)
    if (*itr >= '0' && *itr <= '9') itr++;
    else throw invalid_argument("! ERROR: Invalid Character '" + to_string(*itr) + "' inserted.");

  return Buffer;
}

/**
 * @brief Validates the input when the user is asked for a name. If it detects an unacceptable user input it throws an invalid_argument exception.
 * 
 * @return The string with the new name.
 * @exception Throws an invalid_argument exception when an invalid name has been inserted.
 */
string Interface::ValidateNameInput() {
  
  string Buffer;
  getline(cin, Buffer);

  for (string::iterator itr = Buffer.begin(); itr != Buffer.end(); itr++)
    if ((*itr >= 'a' && *itr <= 'z') || (*itr >= 'A' && *itr <= 'Z') || *itr == ' ') continue;
    else throw invalid_argument("! ERROR: Invalid Character '" + string(1, *itr) + "' inserted.");

  return Buffer;
}