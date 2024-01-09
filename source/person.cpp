/**
 * @file person.cpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief 
 * @version 
 * @date 2024-01-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "person.hpp"

unsigned int Person::Amount = 0;

Person::Person() : UniID(++Amount) {

}

Person::~Person() {}