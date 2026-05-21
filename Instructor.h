#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include "Person.h"

#include <string>

using namespace std;

class Instructor : public Person {
private:
    string department;
    string course;

public:
    Instructor();
    Instructor(string name, string id, string department, string course);

    string getDepartment() const;
    string getCourse() const;

    void setDepartment(string department);
    void setCourse(string course);

    void displayInfo() const override;
};

#endif