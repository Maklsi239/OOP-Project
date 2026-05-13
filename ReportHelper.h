#ifndef REPORTHELPER_H
#define REPORTHELPER_H

#include <string>
#include <vector>

#include "Student.h"
#include "AttendanceRecord.h"

using namespace std;

class ReportHelper {
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