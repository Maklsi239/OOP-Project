#ifndef ATTENDANCERECORD_H
#define ATTENDANCERECORD_H

#include <iostream>
#include <string>

using namespace std;

class AttendanceRecord {
private:
    string studentId;
    string date;
    string status;

public:
    AttendanceRecord();
    AttendanceRecord(string studentId, string date, string status);

    string getStudentId() const;
    string getDate() const;
    string getStatus() const;

    void setStudentId(string studentId);
    void setDate(string date);
    void setStatus(string status);

    bool isPresent() const;
    bool isAbsent() const;

    void displayInfo() const;

    friend ostream& operator<<(ostream& out, const AttendanceRecord& record);
};

#endif