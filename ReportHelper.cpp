#include "ReportHelper.h"
#include <iomanip>
#include <iostream>
#include <stdexcept>
using namespace std;

void ReportHelper::validateStudentId(const string& studentId) {          //to check that student id is not empty
    if (studentId.empty()) {
        throw invalid_argument("student ID can not be empty") ;
    }
}

void ReportHelper::validateStudentPointer(const Student* student) {    //to make sure that student pointer is valid
    if (student ==nullptr) {
        throw invalid_argument("the student pointer is empty");
    }
}
int ReportHelper::countTotalClasses(const string& studentId,                     //here we will hagve all number of classes that attended by the given student id
                                    const vector<AttendanceRecord>& records) {
    try {                                                                         //check before run
        validateStudentId(studentId);

        int total=0;
        for (const AttendanceRecord& record :records) {                     //loop around each record and count the same things
            if (record.getStudentId() ==studentId) {
                total++;                                                     //add for each matching thing
            }
        }
        return total;
    }
    catch (const invalid_argument& error) {
        throw;
    }                                                                 //we used catch 2 timesor we can call it multiple catch blocks cuz each one handle
                                                                      //different type of error
    catch (const exception& error) {
        throw runtime_error("Error when counting all classes: " + string(error.what()));
    }
}

int ReportHelper::countPresentClasses(const string& studentId,
                                      const vector<AttendanceRecord>& records) {
    try {
        validateStudentId(studentId);

        int present=0;

        for (const AttendanceRecord& record : records) {
            if (record.getStudentId() == studentId &&
                record.isPresent()) {                                    //line40-60 it counts the classes when the student actually showed
                                                                         //not all classes
                present++;
            }
        }

        return present  ;
    }
    catch (const invalid_argument& error) {
        throw;
    }
    catch (const exception& error) {
        throw runtime_error("error when counting present classes: " + string(error.what()));
    }
}
double ReportHelper::calculatePercentage(const string& studentId,
                                         const vector<AttendanceRecord>& records) {
    try {
        validateStudentId(studentId);

        int total = countTotalClasses(studentId, records);

        if (total == 0) {
            return 0.0;
        }
                                                                     //line 66-86 will calculate the student attendes % using previous function
        int present = countPresentClasses(studentId, records);

        return (present * 100.0) / total;
    }
    catch (const invalid_argument& error) {
        throw;
    }
    catch (const exception& error) {
        throw runtime_error("error while calculating attendance % : " + string(error.what()));
    }
}
void ReportHelper::printStudentReport(const Student* student,
                                      const vector<AttendanceRecord>& records) {
    try {
        validateStudentPointer(student);

        string studentId =student->getId();
        validateStudentId(studentId);
        int total= countTotalClasses(studentId, records);
        int present = countPresentClasses(studentId, records);
        double percentage= calculatePercentage(studentId, records);
                                                                                           //line 86-120 this is the main function that add everything together and prints the report
        cout << "=====================================" << endl;
        cout << "Attendance Report" <<endl;
        cout << "======================" <<endl;
        cout << "Type : " <<student->getType() <<endl;
        cout << "Student Name :" <<student->getName() << endl;
        cout << "Student ID :" << studentId << endl;
        cout << "Present Classes :" <<present <<endl;
        cout << "Total Classes :"<< total << endl;
        cout << "Attendance % :" << fixed << setprecision(2)<< percentage<< "%" << endl;
        cout << "==================" <<endl;
    }
    catch (const invalid_argument& error) {
        cerr << "[ReportHelper input is not valid] " << error.what() << endl;
        throw;
    }
    catch (const runtime_error& error) {
        cerr << "[ReportHelper Runtime Error] " << error.what() << endl;
        throw;
    }
    catch (const exception& error) {
        cerr << "[ReportHelper failed due to an unknown problem] " << error.what() << endl;
        throw;
    }
}
