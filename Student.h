#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"

#include <string>

using namespace std;

class Student : public Person {
private:
    string program;
    int year;

public:
    Student();
    Student(string name, string id, string program, int year);

    string getProgram() const;
    void setProgram(string program);

    int getYear() const;
    void setYear(int year);

    string getType() const;

    void displayInfo() const override;
};

#endif
