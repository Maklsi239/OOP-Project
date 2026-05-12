#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include <string>

// Student IS-A Person (inheritance).
// A student has everything a person has (name, id), plus school details.

class Student : public Person {
private:
    // Extra data only students have:
    std::string program; // e.g. "Computer Science"
    int level;           // e.g. year 1, 2, 3 ...
    float attendance;    // attendance percentage (0 to 100)

public:
    Student();

    // This constructor forwards name and id to the Person part of the object.
    Student(std::string name, std::string id, std::string program, int level,
            float attendance);

    // Getters / setters for the student-only fields
    std::string getProgram() const;
    void setProgram(std::string program);

    int getLevel() const;
    void setLevel(int level);

    float getAttendance() const;
    void setAttendance(float attendance);

    // Override: replaces Person::displayInfo() for Student objects.
    void displayInfo() override;
};

#endif
