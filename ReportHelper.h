#ifndef REPORTHELPER_H
#define REPORTHELPER_H

#include "AttendanceRecord.h"
#include "Student.h"

#include <string>
#include <vector>

using namespace std;

class ReportHelper {
private:
    static void validateStudentId(const string& studentId);
    static void validateStudentPointer(const Student* student);

public:
    static int countTotalClasses(const string& studentId,
                                 const vector<AttendanceRecord>& records);

    static int countPresentClasses(const string& studentId,
                                   const vector<AttendanceRecord>& records);

    static double calculatePercentage(const string& studentId,
                                      const vector<AttendanceRecord>& records);

    static void printStudentReport(const Student* student,
                                   const vector<AttendanceRecord>& records);
};

#endif
