/**
 * @file Person.hpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief 
 * @version 
 * @date 2024-01-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <map>
#include <string>
using namespace std;

/**
 * @brief Represents the two main types of Person objects that can be created.
 * 
 */
typedef enum {
  STUDENT, PROFESSOR
} PersonType;

/**
 * @brief Represents a base class for the Person
 * object type, containing rudamentary variables and being a pure virtual.
 * 
 */
class Person {

  private:
    string FullName;
    const unsigned int UniID;

  public:

    /* - Constructors and Destructor - */

    Person();
    virtual ~Person();

    /* - Virtual Method - */

    virtual PersonType getType() = 0;

    /* - Operator Overloads - */
    friend ostream &operator<<(ostream &str, Person &per);
    friend istream &operator>>(istream &str, Person &per);

    /**
     * @brief Class-wide variable that counts the amount of Person objects
     * created. Used for UniID generation upon Person object construction.
     * 
     */
    static unsigned int Amount;
};