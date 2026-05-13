#ifndef PERSON_SYSTEM_H
#define PERSON_SYSTEM_H

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// Base class
class person {
public:
    virtual void display();
    virtual ~person();
};

// Student class
class student : public person {
private:
    int id;
    string name;
    int attended;
    int total;

public:
    student(int i, string n, int a, int t);

    int getAttended();
    int getTotal();
    string getName();

    void display() override;
};

// Instructor class
class instructor : public person {
public:
    void display() override;
};

// Report helper class
class reporthelper {
public:
    static double calcpercent(student s);
    static void printreport(student s);
};

#endif