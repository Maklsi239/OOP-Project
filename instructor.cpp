#include "Instructor.h"

#include <iostream>

Instructor::Instructor()
    : Person(), department("Unknown"), course("Unknown") {}

Instructor::Instructor(std::string name, std::string id, std::string department, std::string course)
    : Person(name, id), department(department), course(course) {}

std::string Instructor::getDepartment() const {
    return department;
}

std::string Instructor::getCourse() const {
    return course;
}

void Instructor::setDepartment(std::string department) {
    this->department = department;
}

void Instructor::setCourse(std::string course) {
    this->course = course;
}

void Instructor::displayInfo() const {
    std::cout << "Instructor Name: " << name << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Department: " << department << std::endl;
    std::cout << "Course: " << course << std::endl;
}
