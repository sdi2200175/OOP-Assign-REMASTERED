/**
 * @file person.cpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief 
 * @version
 * @date 2024-01-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "person.hpp"

unsigned int Person::PersonAmount = 0;

Person::Person() : UniID(++PersonAmount) {}
Person::Person(string Name) : Name(Name), UniID(++PersonAmount) {}
Person::~Person() { PersonAmount--; }