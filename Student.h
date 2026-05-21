#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"

#include <string>

using namespace std;

class Student : public Person {
private:
    string program;
    int level;

public:
    Student();
    Student(string name, string id, string program, int level);

    string getProgram() const;
    void setProgram(string program);

    int getLevel() const;
    void setLevel(int level);

    string getType() const;

    void displayInfo() const override;
};

#endif