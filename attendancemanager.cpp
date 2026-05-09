#include "AttendanceManager.h"

using namespace std;

// ---------------- FIND FUNCTIONS ----------------

Student* AttendanceManager::findStudentById(int id) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getId() == id) {
            return &students[i];
        }
    }

    return nullptr;
}

Instructor* AttendanceManager::findInstructorById(int id) {
    for (int i = 0; i < instructors.size(); i++) {
        if (instructors[i].getId() == id) {
            return &instructors[i];
        }
    }

    return nullptr;
}

Course* AttendanceManager::findCourseByCode(const string& code) {
    for (int i = 0; i < courses.size(); i++) {
        if (courses[i].getCourseCode() == code) {
            return &courses[i];
        }
    }

    return nullptr;
}

// ---------------- ADD STUDENT ----------------

void AttendanceManager::addStudent() {
    string name;
    string program;

    int id;
    int level;

    float attendance;

    cout << "Enter student name: ";
    cin >> name;

    cout << "Enter student ID: ";
    cin >> id;

    cout << "Enter program: ";
    cin >> program;

    cout << "Enter level: ";
    cin >> level;

    cout << "Enter attendance percentage: ";
    cin >> attendance;

    Student s(name, id, program, level, attendance);

    students.push_back(s);

    cout << "Student added successfully.\n";
}

// ---------------- ADD INSTRUCTOR ----------------

void AttendanceManager::addInstructor() {
    string name;
    string department;
    string course;

    int id;

    cout << "Enter instructor name: ";
    cin >> name;

    cout << "Enter instructor ID: ";
    cin >> id;

    cout << "Enter department: ";
    cin >> department;

    cout << "Enter course taught: ";
    cin >> course;

    Instructor i(name, id, department, course);

    instructors.push_back(i);

    cout << "Instructor added successfully.\n";
}

// ---------------- CREATE COURSE ----------------

void AttendanceManager::createCourse() {
    string code;
    string name;

    cout << "Enter course code: ";
    cin >> code;

    cout << "Enter course name: ";
    cin >> name;

    Course c(code, name);

    courses.push_back(c);

    cout << "Course created successfully.\n";
}

// ---------------- ASSIGN STUDENT ----------------

void AttendanceManager::assignStudentToCourse() {
    int studentId;
    string courseCode;

    cout << "Enter student ID: ";
    cin >> studentId;

    cout << "Enter course code: ";
    cin >> courseCode;

    Student* s = findStudentById(studentId);
    Course* c = findCourseByCode(courseCode);

    if (s == nullptr) {
        cout << "Student not found.\n";
        return;
    }

    if (c == nullptr) {
        cout << "Course not found.\n";
        return;
    }

    c->addStudent(*s);

    cout << "Student assigned successfully.\n";
}

// ---------------- ASSIGN INSTRUCTOR ----------------

void AttendanceManager::assignInstructorToCourse() {
    int instructorId;
    string courseCode;

    cout << "Enter instructor ID: ";
    cin >> instructorId;

    cout << "Enter course code: ";
    cin >> courseCode;

    Instructor* i = findInstructorById(instructorId);
    Course* c = findCourseByCode(courseCode);

    if (i == nullptr) {
        cout << "Instructor not found.\n";
        return;
    }

    if (c == nullptr) {
        cout << "Course not found.\n";
        return;
    }

    c->assignInstructor(*i);

    cout << "Instructor assigned successfully.\n";
}

// ---------------- MARK ATTENDANCE ----------------

void AttendanceManager::markAttendance() {
    string courseCode;
    int studentId;
    string date;
    string status;

    cout << "Enter course code: ";
    cin >> courseCode;

    cout << "Enter student ID: ";
    cin >> studentId;

    cout << "Enter date: ";
    cin >> date;

    cout << "Enter status (Present/Absent): ";
    cin >> status;

    Course* c = findCourseByCode(courseCode);

    if (c == nullptr) {
        cout << "Course not found.\n";
        return;
    }

    c->markAttendance(studentId, date, status);

    cout << "Attendance marked successfully.\n";
}

// ---------------- VIEW REPORTS ----------------

void AttendanceManager::viewReports() {
    string courseCode;

    cout << "Enter course code: ";
    cin >> courseCode;

    Course* c = findCourseByCode(courseCode);

    if (c == nullptr) {
        cout << "Course not found.\n";
        return;
    }

    c->showCourseReport();
}

// ---------------- MAIN MENU ----------------

void AttendanceManager::run() {
    int choice;

    do {
        cout << "\n===== ATTENDANCE MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. Add Instructor\n";
        cout << "3. Create Course\n";
        cout << "4. Assign Student To Course\n";
        cout << "5. Assign Instructor To Course\n";
        cout << "6. Mark Attendance\n";
        cout << "7. View Reports\n";
        cout << "0. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

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
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}

