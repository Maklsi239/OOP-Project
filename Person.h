#ifndef PERSON_H
#define PERSON_H

#include <string>

using namespace std;

class Person {
protected:
    string name;
    string id;

public:
    Person();
    Person(string name, string id);

    virtual ~Person();

    string getName() const;
    void setName(string name);

    string getId() const;
    void setId(string id);

    virtual void displayInfo() const;
};

#endif