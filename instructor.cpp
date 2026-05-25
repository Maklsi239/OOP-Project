#include "Instructor.h"

#include <iostream>

using namespace std;

Instructor::Instructor() : Person() {
    department = "Unknown";
    course = "Unknown";
}

Instructor::Instructor(string name, string id, string department, string course)
    : Person(name, id) {
    this->department = department;
    this->course = course;
}

string Instructor::getDepartment() const {
    return department;
}

string Instructor::getCourse() const {
    return course;
}

void Instructor::setDepartment(string department) {
    this->department = department;
}

void Instructor::setCourse(string course) {
    this->course = course;
}

void Instructor::displayInfo() const {
    cout << "Instructor Name: " << name << "\n";
    cout << "ID: " << id << "\n";
    cout << "Department: " << department << "\n";
    cout << "Course: " << course << "\n";
}
