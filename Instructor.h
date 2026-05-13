#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include "Person.h"
#include <string>

class Instructor : public Person {
private:
    std::string department;
    std::string course;

public:
    Instructor();
    Instructor(std::string name, std::string id, std::string department, std::string course);

    std::string getDepartment() const;
    std::string getCourse() const;

    void setDepartment(std::string department);
    void setCourse(std::string course);

    void displayInfo() const override;
};

#endif
