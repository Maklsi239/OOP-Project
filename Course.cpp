#include "Course.h"
#include "ConsoleStyle.h"
#include "ReportHelper.h"

#include <algorithm>
#include <iostream>

using namespace std;

namespace {
namespace Style = ConsoleStyle;
}


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
        Style::error("Invalid student.");
        return;
    }

    if (hasStudent(student->getId())) {
        Style::warning("Student already exists in this course.");
        return;
    }

    students.push_back(student);
    Style::success("Student added to course successfully.");
}


void Course::removeStudent(string studentId) {
    vector<Student*>::iterator student = find_if(
        students.begin(),
        students.end(),
        [&studentId](Student* current) {
            return current->getId() == studentId;
        }
    );

    if (student == students.end()) {
        Style::warning("Student not found in this course.");
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

    Style::success("Student removed from course successfully.");
}

void Course::removeStudents(string studentId) {
    removeStudent(studentId);
}


void Course::assignInstructor(Instructor* instructor) {
    if (instructor == nullptr) {
        Style::error("Invalid instructor.");
        return;
    }

    this->instructor = instructor;
    Style::success("Instructor assigned successfully.");
}


void Course::markAttendance(string studentId, string date, string status) {
    if (!hasStudent(studentId)) {
        Style::error("Student not found in this course.");
        return;
    }

    if (status != "Present" && status != "Absent") {
        Style::error("Invalid status. Use Present or Absent.");
        return;
    }

    // If same student and same date already exists, update it
    for (AttendanceRecord& record : attendanceRecords) {
        if (record.getStudentId() == studentId && record.getDate() == date) {
            record.setStatus(status);
            Style::success("Attendance updated successfully.");
            return;
        }
    }

    // If not create new attendance record
    AttendanceRecord record(studentId, date, status);
    attendanceRecords.push_back(record);

    Style::success("Attendance marked successfully.");
}


void Course::showCourseReport() const {
    cout << Style::bold << Style::blue
         << "\n========== COURSE REPORT =========="
         << Style::reset << endl;

    cout << Style::cyan << "Course Name: " << Style::reset << courseName << endl;
    cout << Style::cyan << "Course Code: " << Style::reset << courseCode << endl;

    // Instructor info
    cout << Style::bold << "\n----- Instructor Info -----" << Style::reset << endl;

    if (instructor != nullptr) {
        instructor->displayInfo();
    } else {
        Style::warning("No instructor assigned.");
    }

    // Students info
    cout << Style::bold << "\n----- Students In Course -----" << Style::reset << endl;

    if (!students.empty()) {
        for (const Student* student : students) {
            student->displayInfo();
            cout << endl;
        }
    } else {
        Style::warning("No students added to this course.");
    }

    // Attendance percentage using ReportHelper
    cout << Style::bold << "\n----- Attendance Percentage Report -----" << Style::reset << endl;

    if (!students.empty()) {
        for (const Student* student : students) {
            ReportHelper::printStudentReport(student, attendanceRecords);
            cout << endl;
        }
    } else {
        Style::warning("No students available for attendance report.");
    }

    //  attendance records
    cout << Style::bold << "\n----- Attendance Records -----" << Style::reset << endl;

    if (!attendanceRecords.empty()) {
        for (const AttendanceRecord& record : attendanceRecords) {
            cout << record << endl;
        }
    } else {
        Style::warning("No attendance records found.");
    }
}


bool Course::hasStudent(string studentId) const {
    for (const Student* student : students) {
        if (student->getId() == studentId) {
            return true;
        }
    }

    return false;
}