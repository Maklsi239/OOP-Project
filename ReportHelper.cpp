#include "ReportHelper.h"
#include <iomanip>
#include <iostream>
#include <stdexcept>
using namespace std;
 
// ─── countTotalClasses ───────────────────────────────────────────────────────
int ReportHelper::countTotalClasses(const string& studentId,
                                    const vector<AttendanceRecord>& records) {
    // Exception handling: reject empty ID
    if (studentId.empty()) {
        throw invalid_argument("countTotalClasses: studentId must not be empty.");
    }
 
    int total = 0;
    for (const AttendanceRecord& record : records) {
        if (record.getStudentId() == studentId) {
            total++;
        }
    }
    return total;
}
 
// ─── countPresentClasses ─────────────────────────────────────────────────────
int ReportHelper::countPresentClasses(const string& studentId,
                                      const vector<AttendanceRecord>& records) {
    // Exception handling: reject empty ID
    if (studentId.empty()) {
        throw invalid_argument("countPresentClasses: studentId must not be empty.");
    }
 
    int present = 0;
    for (const AttendanceRecord& record : records) {
        if (record.getStudentId() == studentId &&
            record.getStatus() == "Present") {
            present++;
        }
    }
    return present;
}
 
// ─── calculatePercentage ─────────────────────────────────────────────────────
double ReportHelper::calculatePercentage(const string& studentId,
                                         const vector<AttendanceRecord>& records) {
    // Exception handling: reject empty ID
    if (studentId.empty()) {
        throw invalid_argument("calculatePercentage: studentId must not be empty.");
    }
 
    int total = countTotalClasses(studentId, records);
    if (total == 0) {
        return 0.0;   // guard against division-by-zero
    }
    int present = countPresentClasses(studentId, records);
    return (present * 100.0) / total;
}
 
// ─── printStudentReport ──────────────────────────────────────────────────────
void ReportHelper::printStudentReport(const Student* student,
                                      const vector<AttendanceRecord>& records) {
    // Exception handling: null pointer check
    if (student == nullptr) {
        throw invalid_argument("printStudentReport: student pointer must not be null.");
    }
 
    // Pointer-based polymorphism: getType() dispatches to the correct subclass
    string studentId   = student->getId();
    int    total       = countTotalClasses(studentId, records);
    int    present     = countPresentClasses(studentId, records);
    double percentage  = calculatePercentage(studentId, records);
 
    // ── Report output ──────────────────────────────────────────────────────
    cout << "=============================" << endl;
    cout << "  Attendance Report"           << endl;
    cout << "=============================" << endl;
    cout << "Type:                 " << student->getType()         << endl;  // polymorphic
    cout << "Student Name:         " << student->getName()         << endl;
    cout << "Student ID:           " << studentId                  << endl;
    cout << "Present Classes:      " << present                    << endl;
    cout << "Total Classes:        " << total                      << endl;
    cout << "Attendance %:         "
         << fixed << setprecision(2) << percentage << "%" << endl;
    cout << "=============================" << endl;
}
 
 
// ─── main  (testing / debugging) ─────────────────────────────────────────────
int main() {
    // Build a mixed record list
    vector<AttendanceRecord> records = {
        {"S001", "Present"},
        {"S001", "Absent"},
        {"S001", "Present"},
        {"S002", "Present"},
        {"S002", "Present"},
    };
 
    // Pointer-based polymorphism: base-class pointers to derived objects
    Student* students[] = {
        new UndergraduateStudent("S001", "Alice"),
        new GraduateStudent    ("S002", "Bob"),
    };
 
    // ── Test 1: normal reports ─────────────────────────────────────────────
    cout << "\n[Test 1] Normal reports\n";
    for (Student* s : students) {
        try {
            ReportHelper::printStudentReport(s, records);
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
 
    // ── Test 2: student with no records ───────────────────────────────────
    cout << "\n[Test 2] Student with no records\n";
    try {
        Student* ghost = new UndergraduateStudent("S999", "Ghost");
        ReportHelper::printStudentReport(ghost, records);
        delete ghost;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
 
    // ── Test 3: null pointer (exception handling) ──────────────────────────
    cout << "\n[Test 3] Null pointer\n";
    try {
        ReportHelper::printStudentReport(nullptr, records);
    } catch (const invalid_argument& e) {
        cout << "Caught expected exception: " << e.what() << endl;
    }
 
    // ── Test 4: empty student ID (exception handling) ──────────────────────
    cout << "\n[Test 4] Empty student ID\n";
    try {
        ReportHelper::countTotalClasses("", records);
    } catch (const invalid_argument& e) {
        cout << "Caught expected exception: " << e.what() << endl;
    }
 
    // Clean up
    for (Student* s : students) {
        delete s;
    }
 
    return 0;
}
