#include "ReportHelper.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>

using namespace std;

// ---------------- VALIDATION FUNCTIONS ----------------

void ReportHelper::validateStudentId(const string& studentId) {
    if (studentId.empty()) {
        throw invalid_argument("Student ID cannot be empty.");
    }
}

void ReportHelper::validateStudentPointer(const Student* student) {
    if (student == nullptr) {
        throw invalid_argument("Student pointer cannot be null.");
    }
}

// ---------------- COUNT TOTAL CLASSES ----------------

int ReportHelper::countTotalClasses(const string& studentId,
                                    const vector<AttendanceRecord>& records) {
    try {
        validateStudentId(studentId);

        int total = 0;

        for (const AttendanceRecord& record : records) {
            if (record.getStudentId() == studentId) {
                total++;
            }
        }

        return total;
    }
    catch (const invalid_argument& error) {
        throw;
    }
    catch (const exception& error) {
        throw runtime_error("Error while counting total classes: " + string(error.what()));
    }
}

// ---------------- COUNT PRESENT CLASSES ----------------

int ReportHelper::countPresentClasses(const string& studentId,
                                      const vector<AttendanceRecord>& records) {
    try {
        validateStudentId(studentId);

        int present = 0;

        for (const AttendanceRecord& record : records) {
            if (record.getStudentId() == studentId &&
                record.getStatus() == "Present") {
                present++;
            }
        }

        return present;
    }
    catch (const invalid_argument& error) {
        throw;
    }
    catch (const exception& error) {
        throw runtime_error("Error while counting present classes: " + string(error.what()));
    }
}

// ---------------- CALCULATE PERCENTAGE ----------------

double ReportHelper::calculatePercentage(const string& studentId,
                                         const vector<AttendanceRecord>& records) {
    try {
        validateStudentId(studentId);

        int total = countTotalClasses(studentId, records);

        if (total == 0) {
            return 0.0;
        }

        int present = countPresentClasses(studentId, records);

        return (present * 100.0) / total;
    }
    catch (const invalid_argument& error) {
        throw;
    }
    catch (const exception& error) {
        throw runtime_error("Error while calculating attendance percentage: " + string(error.what()));
    }
}

// ---------------- PRINT STUDENT REPORT ----------------

void ReportHelper::printStudentReport(const Student* student,
                                      const vector<AttendanceRecord>& records) {
    try {
        validateStudentPointer(student);

        string studentId = student->getId();
        validateStudentId(studentId);

        int total = countTotalClasses(studentId, records);
        int present = countPresentClasses(studentId, records);
        double percentage = calculatePercentage(studentId, records);

        cout << "=============================" << endl;
        cout << "Attendance Report" << endl;
        cout << "=============================" << endl;
        cout << "Type: " << student->getType() << endl;
        cout << "Student Name: " << student->getName() << endl;
        cout << "Student ID: " << studentId << endl;
        cout << "Present Classes: " << present << endl;
        cout << "Total Classes: " << total << endl;
        cout << "Attendance %: " << fixed << setprecision(2) << percentage << "%" << endl;
        cout << "=============================" << endl;
    }
    catch (const invalid_argument& error) {
        cerr << "[ReportHelper Invalid Argument] " << error.what() << endl;
        throw;
    }
    catch (const runtime_error& error) {
        cerr << "[ReportHelper Runtime Error] " << error.what() << endl;
        throw;
    }
    catch (const exception& error) {
        cerr << "[ReportHelper Unknown Error] " << error.what() << endl;
        throw;
    }
}