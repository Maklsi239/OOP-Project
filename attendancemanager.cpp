#include "attendancemanager.h"
#include "ConsoleStyle.h"

#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

namespace {
namespace Style = ConsoleStyle;

std::string trim(const std::string& value) {
    const std::string whitespace = " \t\r\n";
    const size_t start = value.find_first_not_of(whitespace);
    if (start == std::string::npos) {
        return "";
    }

    const size_t end = value.find_last_not_of(whitespace);
    return value.substr(start, end - start + 1);
}

void printMenu() {
    std::cout << '\n'
              << Style::bold << Style::blue
              << "===== ATTENDANCE MANAGEMENT SYSTEM ====="
              << Style::reset << '\n'
              << Style::cyan << "1." << Style::reset << " Add Student\n"
              << Style::cyan << "2." << Style::reset << " Add Instructor\n"
              << Style::cyan << "3." << Style::reset << " Create Course\n"
              << Style::cyan << "4." << Style::reset << " Assign Student To Course\n"
              << Style::cyan << "5." << Style::reset << " Assign Instructor To Course\n"
              << Style::cyan << "6." << Style::reset << " Mark Attendance\n"
              << Style::cyan << "7." << Style::reset << " View Reports\n"
              << Style::cyan << "0." << Style::reset << " Exit\n";
}

bool readRequiredLine(const std::string& prompt, std::string& output) {
    while (true) {
        std::cout << Style::cyan << prompt << Style::reset;
        if (!std::getline(std::cin, output)) {
            return false;
        }

        output = trim(output);
        if (!output.empty()) {
            return true;
        }

        Style::warning("This field cannot be empty.");
    }
}

bool readPositiveInt(const std::string& prompt, int& output) {
    std::string input;

    while (readRequiredLine(prompt, input)) {
        std::istringstream stream(input);
        int value = 0;
        char extra = '\0';

        if ((stream >> value) && !(stream >> extra) && value > 0) {
            output = value;
            return true;
        }

        Style::warning("Please enter a positive whole number.");
    }

    return false;
}

bool readMenuChoice(int& output) {
    std::string input;

    while (true) {
        std::cout << Style::bold << "Enter choice: " << Style::reset;
        if (!std::getline(std::cin, input)) {
            return false;
        }

        input = trim(input);
        std::istringstream stream(input);
        int value = 0;
        char extra = '\0';

        if ((stream >> value) && !(stream >> extra)) {
            output = value;
            return true;
        }

        Style::error("Invalid input. Please enter a number.");
    }
}

std::string normalizeStatus(const std::string& input) {
    std::string lower;
    for (char c : input) {
        lower += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }

    if (lower == "present" || lower == "p") {
        return "Present";
    }

    if (lower == "absent" || lower == "a") {
        return "Absent";
    }

    return "";
}
}

// ---------------- FIND FUNCTIONS ----------------

Student* AttendanceManager::findStudentById(std::string id) {
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i]->getId() == id) {
            return students[i];
        }
    }

    return nullptr;
}

Instructor* AttendanceManager::findInstructorById(std::string id) {
    for (size_t i = 0; i < instructors.size(); i++) {
        if (instructors[i]->getId() == id) {
            return instructors[i];
        }
    }

    return nullptr;
}

Course* AttendanceManager::findCourseByCode(const std::string& code) {
    for (size_t i = 0; i < courses.size(); i++) {
        if (courses[i]->getCourseCode() == code) {
            return courses[i];
        }
    }

    return nullptr;
}

// ---------------- ADD STUDENT ----------------

void AttendanceManager::addStudent() {
    std::string name;
    std::string id;
    std::string program;
    int level = 1;

    if (!readRequiredLine("Enter student name: ", name) ||
        !readRequiredLine("Enter student ID: ", id)) {
        return;
    }

    if (findStudentById(id) != nullptr) {
        Style::error("Student ID already exists.");
        return;
    }

    if (!readRequiredLine("Enter program: ", program) ||
        !readPositiveInt("Enter level: ", level)) {
        return;
    }

    Student* s = new Student(name, id, program, level);
    students.push_back(s);

    Style::success("Student added successfully.");
}

// ---------------- ADD INSTRUCTOR ----------------

void AttendanceManager::addInstructor() {
    std::string name;
    std::string id;
    std::string department;
    std::string course;

    if (!readRequiredLine("Enter instructor name: ", name) ||
        !readRequiredLine("Enter instructor ID: ", id)) {
        return;
    }

    if (findInstructorById(id) != nullptr) {
        Style::error("Instructor ID already exists.");
        return;
    }

    if (!readRequiredLine("Enter department: ", department) ||
        !readRequiredLine("Enter course taught: ", course)) {
        return;
    }

    Instructor* i = new Instructor(name, id, department, course);
    instructors.push_back(i);

    Style::success("Instructor added successfully.");
}

// ---------------- CREATE COURSE ----------------

void AttendanceManager::createCourse() {
    std::string code;
    std::string name;

    if (!readRequiredLine("Enter course code: ", code)) {
        return;
    }

    if (findCourseByCode(code) != nullptr) {
        Style::error("Course code already exists.");
        return;
    }

    if (!readRequiredLine("Enter course name: ", name)) {
        return;
    }

    Course* c = new Course(code, name);
    courses.push_back(c);

    Style::success("Course created successfully.");
}

// ---------------- ASSIGN STUDENT ----------------

void AttendanceManager::assignStudentToCourse() {
    std::string studentId;
    std::string courseCode;

    if (!readRequiredLine("Enter student ID: ", studentId) ||
        !readRequiredLine("Enter course code: ", courseCode)) {
        return;
    }

    Student* s = findStudentById(studentId);
    Course* c = findCourseByCode(courseCode);

    if (s == nullptr) {
        Style::error("Student not found.");
        return;
    }

    if (c == nullptr) {
        Style::error("Course not found.");
        return;
    }

    c->addStudent(s);
}

// ---------------- ASSIGN INSTRUCTOR ----------------

void AttendanceManager::assignInstructorToCourse() {
    std::string instructorId;
    std::string courseCode;

    if (!readRequiredLine("Enter instructor ID: ", instructorId) ||
        !readRequiredLine("Enter course code: ", courseCode)) {
        return;
    }

    Instructor* i = findInstructorById(instructorId);
    Course* c = findCourseByCode(courseCode);

    if (i == nullptr) {
        Style::error("Instructor not found.");
        return;
    }

    if (c == nullptr) {
        Style::error("Course not found.");
        return;
    }

    c->assignInstructor(i);
}

// ---------------- MARK ATTENDANCE ----------------

void AttendanceManager::markAttendance() {
    std::string courseCode;
    std::string studentId;
    std::string date;
    std::string statusInput;

    if (!readRequiredLine("Enter course code: ", courseCode) ||
        !readRequiredLine("Enter student ID: ", studentId) ||
        !readRequiredLine("Enter date: ", date) ||
        !readRequiredLine("Enter status (Present/Absent or P/A): ", statusInput)) {
        return;
    }

    Course* c = findCourseByCode(courseCode);

    if (c == nullptr) {
        Style::error("Course not found.");
        return;
    }

    const std::string status = normalizeStatus(statusInput);
    if (status.empty()) {
        Style::error("Invalid status. Use Present, Absent, P, or A.");
        return;
    }

    c->markAttendance(studentId, date, status);
}

// ---------------- VIEW REPORTS ----------------

void AttendanceManager::viewReports() {
    std::string courseCode;

    if (!readRequiredLine("Enter course code: ", courseCode)) {
        return;
    }

    Course* c = findCourseByCode(courseCode);

    if (c == nullptr) {
        Style::error("Course not found.");
        return;
    }

    c->showCourseReport();
}

// ---------------- DESTRUCTOR ----------------

AttendanceManager::~AttendanceManager() {
    for (size_t i = 0; i < students.size(); i++) {
        delete students[i];
    }
    for (size_t i = 0; i < instructors.size(); i++) {
        delete instructors[i];
    }
    for (size_t i = 0; i < courses.size(); i++) {
        delete courses[i];
    }
}

// ---------------- MAIN MENU ----------------

void AttendanceManager::run() {
    int choice = -1;

    do {
        printMenu();
        if (!readMenuChoice(choice)) {
            break;
        }

        switch (choice) {
        case 1:
            addStudent();
            break;

        case 2:
            addInstructor();
            break;

        case 3:
            createCourse();
            break;

        case 4:
            assignStudentToCourse();
            break;

        case 5:
            assignInstructorToCourse();
            break;

        case 6:
            markAttendance();
            break;

        case 7:
            viewReports();
            break;

        case 0:
            std::cout << Style::yellow << "Exiting program..." << Style::reset << '\n';
            break;

        default:
            Style::warning("Invalid choice.");
        }

    } while (choice != 0);
}
