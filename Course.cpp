#include "Course.h"
#include "ConsoleStyle.h"
#include "ReportHelper.h"

#include <algorithm>
#include <iostream>

using namespace std;

Course::Course() {
    courseCode = "";
    courseName = "";
    instructor = nullptr;
}

Course::Course(string courseCode, string courseName) {
    this->courseCode = courseCode;
    this->courseName = courseName;
    instructor = nullptr;
}

Course::~Course() {
}

void Course::setCourseCode(string code) {
    courseCode = code;
}

string Course::getCourseCode() const {
    return courseCode;
}

void Course::setCourseName(string name) {
    courseName = name;
}

string Course::getCourseName() const {
    return courseName;
}

void Course::addStudent(Student* student) {
    if (student == nullptr) {
        ConsoleStyle::error("Invalid student.");
        return;
    }

    if (hasStudent(student->getId())) {
        ConsoleStyle::warning("Student already exists in this course.");
        return;
    }

    students.push_back(student);
    ConsoleStyle::success("Student added to course successfully.");
}

void Course::removeStudent(string studentId) {
    auto student = find_if(
        students.begin(),
        students.end(),
        [&studentId](Student* current) {
            return current != nullptr && current->getId() == studentId;
        }
    );

    if (student == students.end()) {
        ConsoleStyle::warning("Student not found in this course.");
        return;
    }

    students.erase(student);

    attendanceRecords.erase(
        remove_if(
            attendanceRecords.begin(),
            attendanceRecords.end(),
            [&studentId](const AttendanceRecord& record) {
                return record.getStudentId() == studentId;
            }
        ),
        attendanceRecords.end()
    );

    ConsoleStyle::success("Student removed from course successfully.");
}

void Course::removeStudents(string studentId) {
    removeStudent(studentId);
}

void Course::assignInstructor(Instructor* instructor) {
    if (instructor == nullptr) {
        ConsoleStyle::error("Invalid instructor.");
        return;
    }

    this->instructor = instructor;
    ConsoleStyle::success("Instructor assigned successfully.");
}

void Course::markAttendance(string studentId, string date, string status) {
    if (!hasStudent(studentId)) {
        ConsoleStyle::error("Student not found in this course.");
        return;
    }

    if (status != "Present" && status != "Absent") {
        ConsoleStyle::error("Invalid status. Use Present or Absent.");
        return;
    }

    for (AttendanceRecord& record : attendanceRecords) {
        if (record.getStudentId() == studentId &&
            record.getDate() == date) {
            record.setStatus(status);
            ConsoleStyle::success("Attendance updated successfully.");
            return;
        }
    }

    AttendanceRecord record(studentId, date, status);
    attendanceRecords.push_back(record);

    ConsoleStyle::success("Attendance marked successfully.");
}

void Course::showCourseReport() const {
    cout << ConsoleStyle::bold << ConsoleStyle::blue;
    cout << "\n========== COURSE REPORT ==========" << ConsoleStyle::reset << endl;

    cout << ConsoleStyle::cyan << "Course Name: " << ConsoleStyle::reset
         << courseName << endl;

    cout << ConsoleStyle::cyan << "Course Code: " << ConsoleStyle::reset
         << courseCode << endl;

    cout << ConsoleStyle::bold << "\n----- Instructor Info -----"
         << ConsoleStyle::reset << endl;

    if (instructor != nullptr) {
        instructor->displayInfo();
    } else {
        ConsoleStyle::warning("No instructor assigned.");
    }

    cout << ConsoleStyle::bold << "\n----- Students In Course -----"
         << ConsoleStyle::reset << endl;

    if (!students.empty()) {
        for (const Student* student : students) {
            if (student != nullptr) {
                student->displayInfo();
                cout << endl;
            }
        }
    } else {
        ConsoleStyle::warning("No students added to this course.");
    }

    cout << ConsoleStyle::bold << "\n----- Attendance Percentage Report -----"
         << ConsoleStyle::reset << endl;

    if (!students.empty()) {
        for (const Student* student : students) {
            try {
                ReportHelper::printStudentReport(student, attendanceRecords);
                cout << endl;
            } catch (const exception& e) {
                ConsoleStyle::error(e.what());
            }
        }
    } else {
        ConsoleStyle::warning("No students available for attendance report.");
    }

    cout << ConsoleStyle::bold << "\n----- Attendance Records -----"
         << ConsoleStyle::reset << endl;

    if (!attendanceRecords.empty()) {
        for (const AttendanceRecord& record : attendanceRecords) {
            cout << record << endl;
        }
    } else {
        ConsoleStyle::warning("No attendance records found.");
    }
}

bool Course::hasStudent(string studentId) const {
    for (const Student* student : students) {
        if (student != nullptr && student->getId() == studentId) {
            return true;
        }
    }

    return false;
}