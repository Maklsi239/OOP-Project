#include "Person.h"

#include <iostream>

using namespace std;

Person::Person() {
    name = "Unknown";
    id = "0000";
}

Person::Person(string name, string id) {
    this->name = name;
    this->id = id;
}

Person::~Person() {
}

string Person::getName() const {
    return name;
}

void Person::setName(string name) {
    this->name = name;
}

string Person::getId() const {
    return id;
}

void Person::setId(string id) {
    this->id = id;
}

void Person::displayInfo() const {
    cout << "Name: " << name << endl;
    cout << "ID: " << id << endl;
}