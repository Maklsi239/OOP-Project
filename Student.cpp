#include "Student.h"
#include <iostream>

// Default student: uses Person() defaults, then sets student fields.
Student::Student() : Person(), program("Undeclared"), level(1), attendance(0.0f) {}

// Call Person(name, id) first, then store the student-specific members.
Student::Student(std::string name, std::string id, std::string program, int level,
                 float attendance)
    : Person(name, id), program(program), level(level), attendance(attendance) {}

std::string Student::getProgram() const {
    return program;
}

void Student::setProgram(std::string program) {
    this->program = program;
}

int Student::getLevel() const {
    return level;
}

void Student::setLevel(int level) {
    this->level = level;
}

float Student::getAttendance() const {
    return attendance;
}

void Student::setAttendance(float attendance) {
    this->attendance = attendance;
}

// Polymorphism example: same function name as Person, but student prints more.
void Student::displayInfo() {
    std::cout << "--- Student ---" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Program: " << program << std::endl;
    std::cout << "Level: " << level << std::endl;
    std::cout << "Attendance %: " << attendance << std::endl;
}
