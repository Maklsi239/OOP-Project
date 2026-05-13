#include "ReportHelper.h"

#include <iomanip>
#include <iostream>

using namespace std;

int ReportHelper::countTotalClasses(const string& studentId,
                                    const vector<AttendanceRecord>& records) {
    int total = 0;

    for (const AttendanceRecord& record : records) {
        if (record.getStudentId() == studentId) {
            total++;
        }
    }

    return total;
}

int ReportHelper::countPresentClasses(const string& studentId,
                                      const vector<AttendanceRecord>& records) {
    int present = 0;

    for (const AttendanceRecord& record : records) {
        if (record.getStudentId() == studentId && record.getStatus() == "Present") {
            present++;
        }
    }

    return present;
}

double ReportHelper::calculatePercentage(const string& studentId,
                                         const vector<AttendanceRecord>& records) {
    int total = countTotalClasses(studentId, records);

    if (total == 0) {
        return 0.0;
    }

    int present = countPresentClasses(studentId, records);

    return (present * 100.0) / total;
}

void ReportHelper::printStudentReport(const Student* student,
                                      const vector<AttendanceRecord>& records) {
    if (student == nullptr) {
        return;
    }

    string studentId = student->getId();

    int total = countTotalClasses(studentId, records);
    int present = countPresentClasses(studentId, records);
    double percentage = calculatePercentage(studentId, records);

    cout << "Student Name: " << student->getName() << endl;
    cout << "Student ID: " << studentId << endl;
    cout << "Present Classes: " << present << endl;
    cout << "Total Classes: " << total << endl;
    cout << "Attendance Percentage: "
         << fixed << setprecision(2)
         << percentage << "%" << endl;
}