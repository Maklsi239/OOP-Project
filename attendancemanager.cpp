#include "attendancemanager.h"
#include "ConsoleStyle.h"

#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

namespace {
    string trim(const string& value) {
        const string whitespace = " \t\r\n";

        size_t start = value.find_first_not_of(whitespace);
        if (start == string::npos) {
            return "";
        }

        size_t end = value.find_last_not_of(whitespace);
        return value.substr(start, end - start + 1);
    }

    void printMenu() {
        cout << endl;
        cout << ConsoleStyle::bold << ConsoleStyle::blue;
        cout << "===== ATTENDANCE MANAGEMENT SYSTEM =====";
        cout << ConsoleStyle::reset << endl;

        cout << ConsoleStyle::cyan << "1." << ConsoleStyle::reset << " Add Student" << endl;
        cout << ConsoleStyle::cyan << "2." << ConsoleStyle::reset << " Add Instructor" << endl;
        cout << ConsoleStyle::cyan << "3." << ConsoleStyle::reset << " Create Course" << endl;
        cout << ConsoleStyle::cyan << "4." << ConsoleStyle::reset << " Assign Student To Course" << endl;
        cout << ConsoleStyle::cyan << "5." << ConsoleStyle::reset << " Assign Instructor To Course" << endl;
        cout << ConsoleStyle::cyan << "6." << ConsoleStyle::reset << " Mark Attendance" << endl;
        cout << ConsoleStyle::cyan << "7." << ConsoleStyle::reset << " View Reports" << endl;
        cout << ConsoleStyle::cyan << "0." << ConsoleStyle::reset << " Exit" << endl;
    }

    bool readRequiredLine(const string& prompt, string& output) {
        while (true) {
            cout << ConsoleStyle::cyan << prompt << ConsoleStyle::reset;

            if (!getline(cin, output)) {
                return false;
            }

            output = trim(output);

            if (!output.empty()) {
                return true;
            }

            ConsoleStyle::warning("This field cannot be empty.");
        }
    }

    bool readPositiveInt(const string& prompt, int& output) {
        string input;

        while (readRequiredLine(prompt, input)) {
            istringstream stream(input);
            int value = 0;
            char extra = '\0';

            if ((stream >> value) && !(stream >> extra) && value > 0) {
                output = value;
                return true;
            }

            ConsoleStyle::warning("Please enter a positive whole number.");
        }

        return false;
    }

    bool readMenuChoice(int& output) {
        string input;

        while (true) {
            cout << ConsoleStyle::bold << "Enter choice: " << ConsoleStyle::reset;

            if (!getline(cin, input)) {
                return false;
            }

            input = trim(input);

            istringstream stream(input);
            int value = 0;
            char extra = '\0';

            if ((stream >> value) && !(stream >> extra)) {
                output = value;
                return true;
            }

            ConsoleStyle::error("Invalid input. Please enter a number.");
        }
    }

    string normalizeStatus(const string& input) {
        string lower;

        for (char c : input) {
            lower += static_cast<char>(tolower(static_cast<unsigned char>(c)));
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

AttendanceManager::AttendanceManager() {
}

AttendanceManager::~AttendanceManager() {
    for (Student* student : students) {
        delete student;
    }

    for (Instructor* instructor : instructors) {
        delete instructor;
    }

    for (Course* course : courses) {
        delete course;
    }
}

Student* AttendanceManager::findStudentById(string id) {
    for (Student* student : students) {
        if (student != nullptr && student->getId() == id) {
            return student;
        }
    }

    return nullptr;
}

Instructor* AttendanceManager::findInstructorById(string id) {
    for (Instructor* instructor : instructors) {
        if (instructor != nullptr && instructor->getId() == id) {
            return instructor;
        }
    }

    return nullptr;
}

Course* AttendanceManager::findCourseByCode(const string& code) {
    for (Course* course : courses) {
        if (course != nullptr && course->getCourseCode() == code) {
            return course;
        }
    }

    return nullptr;
}

void AttendanceManager::addStudent() {
    string name;
    string id;
    string program;
    int level = 1;

    if (!readRequiredLine("Enter student name: ", name) ||
        !readRequiredLine("Enter student ID: ", id)) {
        return;
    }

    if (findStudentById(id) != nullptr) {
        ConsoleStyle::error("Student ID already exists.");
        return;
    }

    if (!readRequiredLine("Enter program: ", program) ||
        !readPositiveInt("Enter level: ", level)) {
        return;
    }

    Student* student = new Student(name, id, program, level);
    students.push_back(student);

    ConsoleStyle::success("Student added successfully.");
}

void AttendanceManager::addInstructor() {
    string name;
    string id;
    string department;
    string course;

    if (!readRequiredLine("Enter instructor name: ", name) ||
        !readRequiredLine("Enter instructor ID: ", id)) {
        return;
    }

    if (findInstructorById(id) != nullptr) {
        ConsoleStyle::error("Instructor ID already exists.");
        return;
    }

    if (!readRequiredLine("Enter department: ", department) ||
        !readRequiredLine("Enter course taught: ", course)) {
        return;
    }

    Instructor* instructor = new Instructor(name, id, department, course);
    instructors.push_back(instructor);

    ConsoleStyle::success("Instructor added successfully.");
}

void AttendanceManager::createCourse() {
    string code;
    string name;

    if (!readRequiredLine("Enter course code: ", code)) {
        return;
    }

    if (findCourseByCode(code) != nullptr) {
        ConsoleStyle::error("Course code already exists.");
        return;
    }

    if (!readRequiredLine("Enter course name: ", name)) {
        return;
    }

    Course* course = new Course(code, name);
    courses.push_back(course);

    ConsoleStyle::success("Course created successfully.");
}

void AttendanceManager::assignStudentToCourse() {
    string studentId;
    string courseCode;

    if (!readRequiredLine("Enter student ID: ", studentId) ||
        !readRequiredLine("Enter course code: ", courseCode)) {
        return;
    }

    Student* student = findStudentById(studentId);
    Course* course = findCourseByCode(courseCode);

    if (student == nullptr) {
        ConsoleStyle::error("Student not found.");
        return;
    }

    if (course == nullptr) {
        ConsoleStyle::error("Course not found.");
        return;
    }

    course->addStudent(student);
}

void AttendanceManager::assignInstructorToCourse() {
    string instructorId;
    string courseCode;

    if (!readRequiredLine("Enter instructor ID: ", instructorId) ||
        !readRequiredLine("Enter course code: ", courseCode)) {
        return;
    }

    Instructor* instructor = findInstructorById(instructorId);
    Course* course = findCourseByCode(courseCode);

    if (instructor == nullptr) {
        ConsoleStyle::error("Instructor not found.");
        return;
    }

    if (course == nullptr) {
        ConsoleStyle::error("Course not found.");
        return;
    }

    course->assignInstructor(instructor);
}

void AttendanceManager::markAttendance() {
    string courseCode;
    string studentId;
    string date;
    string statusInput;

    if (!readRequiredLine("Enter course code: ", courseCode) ||
        !readRequiredLine("Enter student ID: ", studentId) ||
        !readRequiredLine("Enter date: ", date) ||
        !readRequiredLine("Enter status (Present/Absent or P/A): ", statusInput)) {
        return;
    }

    Course* course = findCourseByCode(courseCode);

    if (course == nullptr) {
        ConsoleStyle::error("Course not found.");
        return;
    }

    string status = normalizeStatus(statusInput);

    if (status.empty()) {
        ConsoleStyle::error("Invalid status. Use Present, Absent, P, or A.");
        return;
    }

    course->markAttendance(studentId, date, status);
}

void AttendanceManager::viewReports() {
    string courseCode;

    if (!readRequiredLine("Enter course code: ", courseCode)) {
        return;
    }

    Course* course = findCourseByCode(courseCode);

    if (course == nullptr) {
        ConsoleStyle::error("Course not found.");
        return;
    }

    course->showCourseReport();
}

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
            cout << ConsoleStyle::yellow << "Exiting program..." << ConsoleStyle::reset << endl;
            break;

        default:
            ConsoleStyle::warning("Invalid choice.");
            break;
        }

    } while (choice != 0);
}