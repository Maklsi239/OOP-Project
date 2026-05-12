#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

// Person is the BASE class for Student and Instructor.
// Inheritance: Student and Instructor are kinds of Person.
// Polymorphism: displayInfo() is virtual so the correct version runs
// when we call it through a Person pointer/reference.

class Person {
protected:
    // "protected" means:
    // - Not visible outside the class (like private)
    // - BUT child classes (Student, Instructor) can use these directly.
    // We keep data hidden from the rest of the program (encapsulation),
    // while still letting subclasses show them in displayInfo().
    std::string name;
    std::string id;

public:
    // Default constructor: creates a "blank" person with placeholder values.
    Person();

    // Parameterized constructor: sets name and id when the object is created.
    Person(std::string name, std::string id);

    // Virtual destructor: important when we delete objects through a Person*.
    // It makes sure the correct destructor runs for Student or Instructor.
    virtual ~Person();

    // --- Getters (read values) and Setters (change values) ---
    // This is encapsulation: outside code uses these functions instead of
    // touching the variables directly.
    std::string getName() const;
    void setName(std::string name);

    std::string getId() const;
    void setId(std::string id);

    // Virtual = "can be replaced in a child class with a different version".
    // Student and Instructor will override this to print their own details.
    virtual void displayInfo();
};

#endif
