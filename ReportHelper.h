#ifndef REPORTHELPER_H
#define REPORTHELPER_H

#include "AttendanceRecord.h"
#include "Student.h"

#include <string>
#include <vector>

using namespace std;
                                 //this class will helps us to work with student attendance
class ReportHelper {
private:
    static void validateStudentId(const string& studentId);                             //only used inside the class to check the ID is not empty
    static void validateStudentPointer(const Student* student);                         // smae thing only insid this class to check if the student exists

public:
    static int countTotalClasses(const string& studentId,                          //to get total number of classes
                                 const vector<AttendanceRecord>& records);

    static int countPresentClasses(const string& studentId,                        // to get how many classes the student attended
                                   const vector<AttendanceRecord>& records);

    static double calculatePercentage(const string& studentId,                    //to get attendes %
                                      const vector<AttendanceRecord>& records);

    static void printStudentReport(const Student* student,                        //to print full attendes report
                                   const vector<AttendanceRecord>& records);
};

#endif
