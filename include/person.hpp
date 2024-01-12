/**
 * @file person.hpp
 * @author Spyros Strakosia, Evaggelia Ragkousi
 * @brief 
 * @version
 * @date 2024-01-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <iostream>

using namespace std;

class Person {

  private:
    string Name;
    const unsigned int UniID;

  public:

    /* - Constructors and Destructor - */
    Person();
    virtual ~Person();

    /* - Getters - */
    inline const string &getName() const { return Name; }
    inline const unsigned int &getUniID() const { return UniID; }

    /* - Setters - */
    inline void setName(string Name) { this->Name = Name; }

    /* - Pure Virtual Function - */
    virtual string getFormattedID() = 0;

    /* - Operator Overloads - */
    friend ostream &operator<< (ostream &str, Person &per);
    friend istream &operator>> (istream &str, Person &per);

    /* - Static Universal Counter - */
    static unsigned int Amount;

};