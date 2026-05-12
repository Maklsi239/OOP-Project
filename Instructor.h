#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include "Person.h"
#include <iostream>
#include <string>

using namespace std;

class Instructor : public Person {
private:
    string department;
    string course;

public:
    // Constructors
    Instructor();
    // id is a string so it can hold IDs like "S1001" (matches Course / manager code).
    Instructor(string name, string id, string department, string course);

    // Getters
    string getDepartment() const;
    string getCourse() const;

    // Setters
    void setDepartment(string department);
    void setCourse(string course);

    // Override display
    void displayInfo() override;
};

#endif