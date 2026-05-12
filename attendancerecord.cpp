#include "AttendanceRecord.h"

AttendanceRecord::AttendanceRecord()
    : studentId(""), date(""), status("Absent") {}

AttendanceRecord::AttendanceRecord(std::string studentId, std::string date,
                                   std::string status)
    : studentId(studentId), date(date), status(status) {
    // Basic validation (Course also checks, but this keeps the object safe).
    if (status != "Present" && status != "Absent") {
        this->status = "Absent";
    }
}

std::string AttendanceRecord::getStudentId() const {
    return studentId;
}

std::string AttendanceRecord::getDate() const {
    return date;
}

std::string AttendanceRecord::getStatus() const {
    return status;
}

void AttendanceRecord::displayInfo() const {
    std::cout << "Student ID: " << studentId << std::endl;
    std::cout << "Date: " << date << std::endl;
    std::cout << "Status: " << status << std::endl;
}
void AttendanceRecord::setStatus(std::string status) {
    if (status == "Present" || status == "Absent") {
        this->status = status;
    }
}

std::ostream& operator<<(std::ostream& out, const AttendanceRecord& r) {
    out << r.studentId << " | " << r.date << " | " << r.status;
    return out;
}
