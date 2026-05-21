#include "Student.h"

#include <iostream>

using namespace std;

Student::Student() : Person() {
    program = "Unknown";
    level = 1;
}

Student::Student(string name, string id, string program, int level)
    : Person(name, id) {
    this->program = program;

    if (level > 0) {
        this->level = level;
    } else {
        this->level = 1;
    }
}

string Student::getProgram() const {
    return program;
}

void Student::setProgram(string program) {
    this->program = program;
}

int Student::getLevel() const {
    return level;
}

void Student::setLevel(int level) {
    if (level > 0) {
        this->level = level;
    }
}

string Student::getType() const {
    return "Student";
}

void Student::displayInfo() const {
    cout << "Student Name: " << name << endl;
    cout << "ID: " << id << endl;
    cout << "Program: " << program << endl;
    cout << "Level: " << level << endl;
}