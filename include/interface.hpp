/**
 * @file interface.hpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief 
 * @version 
 * @date 2024-01-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <iostream>

using namespace std;

class Interface {

  private:
    unsigned short ValidateMenuInput(unsigned short NumberOfChoices);
    void StudentManagement();

  public:
    void begin();
    void main();

};