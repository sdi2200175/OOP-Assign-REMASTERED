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

unsigned int Person::Amount = 0;

Person::Person() : UniID(++Amount) {
  cout << "|" << endl << "+----------- Person Details -----------+" << endl;
  cin >> *this;
  cout << "+--------- Constructed Person ---------+" << endl;
}

Person::~Person() {}

ostream &operator<< (ostream &str, Person &per) {
  str << "| Full Name: " << per.Name << endl;
  str << "| University ID: " << per.UniID << endl;
  return str;
}

istream &operator>> (istream &str, Person &per) {
  string Buffer;
  cout << "- Enter First Name: " << endl;
  getline(str, per.Name);
  cout << "- Enter Father's Name: " << endl;
  getline(str, Buffer);
  per.Name = per.Name + " " + Buffer;
  cout << "- Enter Last Name: " << endl;
  getline(str, Buffer);
  per.Name = per.Name + " " + Buffer;
  return str;
}