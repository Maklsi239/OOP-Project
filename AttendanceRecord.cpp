#include "AttendanceRecord.h"

#include <iostream>

using namespace std;

AttendanceRecord::AttendanceRecord() {
    studentId = "";
    date = "";
    status = "Absent";
}

AttendanceRecord::AttendanceRecord(string studentId, string date, string status) {
    this->studentId = studentId;
    this->date = date;

    if (status == "Present" || status == "Absent") {
        this->status = status;
    } else {
        this->status = "Absent";
    }
}

string AttendanceRecord::getStudentId() const {
    return studentId;
}

string AttendanceRecord::getDate() const {
    return date;
}

string AttendanceRecord::getStatus() const {
    return status;
}

void AttendanceRecord::setStudentId(string studentId) {
    this->studentId = studentId;
}

void AttendanceRecord::setDate(string date) {
    this->date = date;
}

void AttendanceRecord::setStatus(string status) {
    if (status == "Present" || status == "Absent") {
        this->status = status;
    }
}

void AttendanceRecord::displayInfo() const {
    cout << "Student ID: " << studentId << endl;
    cout << "Date: " << date << endl;
    cout << "Status: " << status << endl;
}

bool AttendanceRecord::isPresent() const {
    return status == "Present";
}

bool AttendanceRecord::isAbsent() const {
    return status == "Absent";
}

ostream& operator<<(ostream& out, const AttendanceRecord& record) {
    out << "Student ID: " << record.studentId
        << " | Date: " << record.date
        << " | Status: " << record.status;

    return out;
}