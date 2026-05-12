#include "attendancemanager.h"
#include <limits>

using namespace std;

// ---------------- FIND FUNCTIONS ----------------

Student* AttendanceManager::findStudentById(string id) {
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i]->getId() == id) {
            return students[i];
        }
    }

    return nullptr;
}

Instructor* AttendanceManager::findInstructorById(string id) {
    for (size_t i = 0; i < instructors.size(); i++) {
        if (instructors[i]->getId() == id) {
            return instructors[i];
        }
    }

    return nullptr;
}

Course* AttendanceManager::findCourseByCode(const string& code) {
    for (size_t i = 0; i < courses.size(); i++) {
        if (courses[i]->getCourseCode() == code) {
            return courses[i];
        }
    }

    return nullptr;
}

// ---------------- ADD STUDENT ----------------

void AttendanceManager::addStudent() {
    string name;
    string program;

    string id;
    int level;

    cin.ignore();
    cout << "Enter student name: ";
    getline(cin, name);

    cout << "Enter student ID: ";
    getline(cin, id);

    cout << "Enter program: ";
    getline(cin, program);

    cout << "Enter level: ";
    cin >> level;
     if (findStudentById(id) != nullptr) {
        cout << "Student ID already exists.\n";
        return;
    }
    Student* s = new Student(name, id, program, level);

    students.push_back(s);

    cout << "Student added successfully.\n";
}

// ---------------- ADD INSTRUCTOR ----------------

void AttendanceManager::addInstructor() {
    string name;
    string department;
    string course;

    string id;
    cin.ignore();
    cout << "Enter instructor name: ";
    getline(cin, name);

    cout << "Enter instructor ID: ";
    getline(cin, id);

    cout << "Enter department: ";
    getline(cin, department);

    cout << "Enter course taught: ";
    getline(cin, course);
    if (findInstructorById(id) != nullptr) {
    cout << "Instructor ID already exists.\n";
    return;
}


    Instructor* i = new Instructor(name, id, department, course);

    instructors.push_back(i);

    cout << "Instructor added successfully.\n";
}

// ---------------- CREATE COURSE ----------------

void AttendanceManager::createCourse() {
    string code;
    string name;

    cout << "Enter course code: ";
    cin >> code;
    cin.ignore();
    cout << "Enter course name: ";
    getline(cin, name);
if (findCourseByCode(code) != nullptr) {
    cout << "Course code already exists.\n";
    return;
}
    Course* c = new Course(code, name);

    courses.push_back(c);

    cout << "Course created successfully.\n";
}

// ---------------- ASSIGN STUDENT ----------------

void AttendanceManager::assignStudentToCourse() {
    string studentId;
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

    c->addStudent(s);

}

// ---------------- ASSIGN INSTRUCTOR ----------------

void AttendanceManager::assignInstructorToCourse() {
    string instructorId;
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

    c->assignInstructor(i);

}

// ---------------- MARK ATTENDANCE ----------------

void AttendanceManager::markAttendance() {
    cin.ignore();

    string courseCode;
    string studentId;
    string date;
    string status;

    cout << "Enter course code: ";
    getline(cin,courseCode);

    cout << "Enter student ID: ";
    getline(cin,studentId);

    cout << "Enter date: ";
    getline(cin,date);

    cout << "Enter status (Present/Absent): ";
    getline(cin,status);

    Course* c = findCourseByCode(courseCode);

    if (c == nullptr) {
        cout << "Course not found.\n";
        return;
    }

    c->markAttendance(studentId, date, status);

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

//---------------- Destructor ----------------
AttendanceManager::~AttendanceManager() {
    for (size_t i = 0; i < students.size(); i++)
        delete students[i];
    for (size_t i = 0; i < instructors.size(); i++)
        delete instructors[i];
    for (size_t i = 0; i < courses.size(); i++)
        delete courses[i];
} // cleaned heap

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
        if (!(cin >> choice)) {
    cout << "Invalid input. Please enter a number.\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    continue;
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
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}

