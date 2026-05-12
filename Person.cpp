#include "Person.h"

// Default constructor: gives safe starting values so the object is never "empty"
// in a confusing way.
Person::Person() : name("Unknown"), id("0000") {}

// Parameterized constructor: "member initializer list" copies the parameters
// into the member variables. This is a common C++ style and is slightly faster
// for simple types.
Person::Person(std::string name, std::string id) : name(name), id(id) {}

// Destructor: runs when the Person object is destroyed.
// virtual in the header means deleting through Person* is safe for subclasses.
Person::~Person() {
    // We do not print here in the final project to avoid noisy output,
    // but you can uncomment for learning:
    // std::cout << "Person destructor called for: " << name << std::endl;
}

std::string Person::getName() const {
    return name;
}

void Person::setName(std::string name) {
    this->name = name;
}

std::string Person::getId() const {
    return id;
}

void Person::setId(std::string id) {
    this->id = id;
}

// Base version: prints only what every Person has.
// Student and Instructor will override this to add their extra fields.
void Person::displayInfo() {
    std::cout << "Name: " << name << std::endl;
    std::cout << "ID: " << id << std::endl;
}
