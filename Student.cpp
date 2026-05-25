#include "Student.h"
#include <iostream>

using namespace std;

Student::Student() : Person() {
    program = "Unknown";
    year = 1;
}

Student::Student(string name, string id, string program, int year)
    : Person(name, id) {
    this->program = program;

    if (year > 0) {
        this->year = year;
    } else {
        this->year = 1;
    }
}

string Student::getProgram() const {
    return program;
}

void Student::setProgram(string program) {
    this->program = program;
}

int Student::getYear() const {
    return year;
}

void Student::setYear(int year) {
    if (year > 0) {
        this->year = year;
    }
}

string Student::getType() const {
    return "Student";
}

void Student::displayInfo() const {
    cout << "Student Name: " << name << endl;
    cout << "ID: " << id << endl;
    cout << "Program: " << program << endl;
    cout << "Year: " << year << endl;
}