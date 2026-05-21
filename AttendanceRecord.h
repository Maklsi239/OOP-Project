#ifndef ATTENDANCERECORD_H
#define ATTENDANCERECORD_H

#include <iostream>
#include <string>

// Holds one attendance entry for a student on a date.
// (Your teammate owns the full design; this is a simple version so the project builds.)
// test

class AttendanceRecord {
private:
    std::string studentId;
    std::string date;
    std::string status; // "Present" or "Absent"

public:
    AttendanceRecord();

    // Validates status: only "Present" or "Absent" are accepted.
    AttendanceRecord(std::string studentId, std::string date, std::string status);

    std::string getStudentId() const;
    std::string getDate() const;
    std::string getStatus() const;
    void setStatus(std::string status);
    void displayInfo() const;

    friend std::ostream& operator<<(std::ostream& out, const AttendanceRecord& r);
};

#endif
