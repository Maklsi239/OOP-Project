#include "attendancemanager.h"

#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

AttendanceManager::AttendanceManager() {
    loadDefaultCourses();
}

AttendanceManager::~AttendanceManager() {
    for (Student* student : students) { // cleaning memory
        delete student;
    }
    for (Instructor* instructor : instructors) {
        delete instructor;
    }
    for (Course* course : courses) {
        delete course;
    }
}

void AttendanceManager::loadDefaultCourses() {
    const int courseCount = 5;
    string courseCodes[courseCount] = {"CS101", "CS102", "DB101", "MATH101", "ENG101"};
    string courseNames[courseCount] = {"Programming Fundamentals", "Object Oriented Programming",
                                       "Database Systems", "Calculus I", "Academic English"};

    for (int i = 0; i < courseCount; i++) {
        courses.push_back(new Course(courseCodes[i], courseNames[i])); // adding courses to vector courses
    }
}

void AttendanceManager::printMenu() const {
    cout << "\n===== ATTENDANCE MANAGEMENT SYSTEM =====\n"
         << "1. View Courses\n"
         << "2. Add Student\n"
         << "3. Add Instructor\n"
         << "4. Add Student To Course\n"
         << "5. Delete Student\n"
         << "6. Delete Instructor\n"
         << "7. Mark Attendance\n"
         << "8. View Course Report\n"
         << "9. View Student Record\n"
         << "0. Exit\n";
}

void AttendanceManager::showStudents() const {
    if (students.empty()) {
        cout << "No students added yet." << endl;
        return;
    }
    cout << endl << " Students: " << endl;
    for (const Student* student : students) {
        if (student != nullptr) { // defensive habit to avoid crashing the program
            cout << student->getId() << " - " << student->getName() << endl;
        }
    }
}

void AttendanceManager::showCourseCodes() const {
    cout << endl << "Courses:" << endl;
    for (const Course* course : courses) {
        cout << course->getCourseCode() << " - " << course->getCourseName() << endl;
    }
}
bool AttendanceManager::readRequiredLine(string prompt, string& output) const {
    while (true) {
        cout << prompt;
        if (!getline(cin, output)) { //making sure that getline succeeds
            return false;
        }
        if (!output.empty()) {
            return true;
        }
        cout << "This field cannot be empty." << endl;
    }
}

bool AttendanceManager::readPositiveInt(string prompt, int& output) const {
    string input;

    while (readRequiredLine(prompt, input)) {
        istringstream stream(input);
        int value = 0; // catches numbers
        char extra = '\0'; // catches leftovers after numbers
        if ((stream >> value) && !(stream >> extra) && value > 0) {
            output = value;
            return true;
        }
        cout << "Please enter a positive whole number." << endl;
    }
    return false;
}

bool AttendanceManager::readMenuChoice(int& output) const {
    string input;

    while (true) {
        cout << "Enter choice: ";
        if (!getline(cin, input)) {
            return false;
        }
        istringstream stream(input);
        int value = 0;
        char extra = '\0';
        if ((stream >> value) && !(stream >> extra)) {
            output = value;
            return true;
        }
        cout << "Invalid input, Please enter a number " << endl;
    }
}

string AttendanceManager::normalizeStatus(string input) const { // making a string organized
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

Course* AttendanceManager::chooseCourse() const {
    int choice = 0;

    cout << "\nChoose a course:" << endl;
    for (int i = 0; i < static_cast<int>(courses.size()); i++) {
        cout << i + 1 << ". "
             << courses[i]->getCourseCode() << " - "
             << courses[i]->getCourseName() << endl;
    }

    if (!readPositiveInt("Enter course number: ", choice)) {
        return nullptr;
    }
    if (choice < 1 || choice > static_cast<int>(courses.size())) {
        cout << "Invalid course choice" << endl;
        return nullptr;
    }
    return courses[choice - 1];
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
    int year = 1;

    if (!readRequiredLine("Enter student name: ", name) ||
        !readRequiredLine("Enter student ID: ", id)) {
        return;
    }

    if (findStudentById(id) != nullptr) {
        cout << "Student ID exists" << endl;
        return;
    }

    if (!readRequiredLine("Enter program: ", program) ||
        !readPositiveInt("Enter year: ", year)) {
        return;
    }

    Student* student = new Student(name, id, program, year);
    students.push_back(student);

    cout << "Student added successfully" << endl;
}

void AttendanceManager::addInstructor() {
    string name;
    string id;
    string department;
    Course* selectedCourse = nullptr;

    if (!readRequiredLine("Enter instructor name: ", name) ||
        !readRequiredLine("Enter instructor ID: ", id)) {
        return;
    }

    if (findInstructorById(id) != nullptr) {
        cout << "Instructor ID already exists" << endl;
        return;
    }

    if (!readRequiredLine("Enter department:", department)) {
        return;
    }

    selectedCourse = chooseCourse();
    if (selectedCourse == nullptr) {
        return;
    }

    Instructor* instructor = new Instructor(name, id, department, selectedCourse->getCourseName());
    instructors.push_back(instructor);
    selectedCourse->assignInstructor(instructor);

    cout << "Instructor added and assigned to course" << endl;
}

void AttendanceManager::listCourses() const {
    cout << "\n================ VIEW COURSES ================" << endl;

    cout << left << setw(12) << "Code" // putting text on the left and spaces on the right
         << setw(34) << "Course Name" 
         << setw(24) << "Instructor"
         << setw(10) << "Students" << "Records" << endl;
    cout << string(88, '-') << endl;

    for (const Course* course : courses) {
        if (course != nullptr) {
            cout << left << setw(12) << course->getCourseCode()
                 << setw(34) << course->getCourseName()
                 << setw(24) << course->getInstructorName()
                 << setw(10) << course->getStudentCount()
                 << course->getAttendanceRecordCount() << endl;
        }
    }
}

void AttendanceManager::assignStudentToCourse() {
    string studentId;
    string courseCode;

    showStudents(); // line 51

    if (!readRequiredLine("Enter student ID: ", studentId)) {
        return;
    }

    showCourseCodes();

    if (!readRequiredLine("Enter course code: ", courseCode)) {
        return;
    }

    Student* student = findStudentById(studentId);
    Course* course = findCourseByCode(courseCode);

    if (student == nullptr) {
        cout << "Student not found." << endl;
        return;
    }

    if (course == nullptr) {
        cout << "Course not found." << endl;
        return;
    }

    course->addStudent(student);
}

void AttendanceManager::deleteStudent() {
    string studentId;

    if (!readRequiredLine("Enter a student ID to delete: ", studentId)) {
        return;
    }

    for (auto student = students.begin(); student != students.end(); ++student) {
        if (*student != nullptr && (*student)->getId() == studentId) {
            for (Course* course : courses) {
                if (course != nullptr && course->hasStudent(studentId)) {
                    course->removeStudent(studentId);
                }
            }

            delete *student; // removing student from heap
            students.erase(student); // removing student pointer from vector
            cout << " Student deleted from the system successfully" << endl;
            return;
        }
    }

    cout << "Student not found!" << endl;
}

void AttendanceManager::deleteInstructor() {
    string instructorId;

    if (!readRequiredLine("Enter instructor ID to delete: ", instructorId)) {
        return;
    }

    for (auto instructor = instructors.begin(); instructor != instructors.end(); ++instructor) {
        if (*instructor != nullptr && (*instructor)->getId() == instructorId) {
            int removedAssignments = 0; // number of courses this instructor will be removed from

            for (Course* course : courses) {
                if (course != nullptr && course->removeInstructorById(instructorId)) {
                    removedAssignments++;
                }
            }

            delete *instructor;
            instructors.erase(instructor);

            if (removedAssignments > 0) {
                cout << "Instructor removed from assigned courses." << endl;
            }

            cout << "Instructor deleted from the system successfully" << endl;
            return;
        }
    }

    cout << "Instructor not found." << endl;
}

void AttendanceManager::markAttendance() {
    string courseCode;
    string studentId;
    string date;
    string statusInput;

    showCourseCodes();

    if (!readRequiredLine(" Enter course code: ", courseCode)) {
        return;
    }

    Course* course = findCourseByCode(courseCode);

    if (course == nullptr) {
        cout << "Course not found." << endl;
        return;
    }

    course->showStudents();

    if (!readRequiredLine("Enter student ID: ", studentId) || !readRequiredLine("Enter date: ", date) || !readRequiredLine("Enter status (Present/Absent or P/A): ", statusInput)) {
        return;
    }

    string status = normalizeStatus(statusInput);

    if (status.empty()) {
        cout << "Invalid status please use Present, Absent, P, or A" << endl;
        return;
    }

    course->markAttendance(studentId, date, status);
}

void AttendanceManager::viewReports() {
    string courseCode;

    showCourseCodes();

    if (!readRequiredLine("Enter course code: ", courseCode)) {
        return;
    }

    Course* course = findCourseByCode(courseCode);

    if (course == nullptr) {
        cout << "Course not found" << endl;
        return;
    }

    course->showCourseReport();
}

void AttendanceManager::viewStudentRecord() {
    string studentId;
    showStudents();

    if (!readRequiredLine("Enter student ID: ", studentId)) {
        return;
    }

    Student* student = findStudentById(studentId);
    if (student == nullptr) {
        cout << "Student not found! " << endl;
        return;
    }

    cout << "\nStudent Record" << endl
         << "Name: " << student->getName() << endl
         << "ID: " << student->getId() << endl
         << left << setw(12) << "Code" << setw(34) << "Course"
         << setw(12) << "Present" << setw(12) << "Total" << "Percent" << endl;
    cout << string(78, '-') << endl;

    bool foundCourse = false;
    for (Course* course : courses) {
        if (course != nullptr && course->hasStudent(studentId)) {
            course->showStudentRecord(studentId);
            foundCourse = true;
        }
    }

    if (!foundCourse) {
        cout << "This student is not assigned to any course! " << endl;
    }
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
            listCourses();
            break;

        case 2:
            addStudent();
            break;

        case 3:
            addInstructor();
            break;

        case 4:
            assignStudentToCourse();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            deleteInstructor();
            break;

        case 7:
            markAttendance();
            break;

        case 8:
            viewReports();
            break;

        case 9:
            viewStudentRecord();
            break;

        case 0:
            cout << "Exiting program..." << endl;
            break;

        default: //default case
            cout << "Invalid choice." << endl;
            break;
        }

    } while (choice != 0);
}
