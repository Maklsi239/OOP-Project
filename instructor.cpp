#include "Instructor.h"

// Default constructor
Instructor::Instructor()
    : Person(), department("Unknown"), course("Unknown") {}

// Parameterized constructor
Instructor::Instructor(string name, string id, string department, string course)
    : Person(name, id) {

    this->department = department;
    this->course = course;
}

// Getters
string Instructor::getDepartment() const {
    return department;
}

string Instructor::getCourse() const {
    return course;
}

// Setters
void Instructor::setDepartment(string department) {
    this->department = department;
}

void Instructor::setCourse(string course) {
    this->course = course;
}

// Display
void Instructor::displayInfo() {
    cout << "Instructor Name: " << name << endl;
    cout << "ID: " << id << endl;
    cout << "Department: " << department << endl;
    cout << "Course: " << course << endl;
}