/**
 * @file main.cpp
 * @author Spyros Strakosia
 * @brief
 * @version 0.1
 * @date 2024-01-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "interface.hpp"
#include <iostream>

int main() {
    interface interface(std::cin, std::cout, std::cerr);
    interface.mainMenu();
    return 0;
}
