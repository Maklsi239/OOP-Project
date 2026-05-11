#ifndef COURSE_H
#define COURSE_H
#include <iostream>
#include <vector>
#include <string>

#include "Student.h"
#include "Instructor.h"
#include "AttendanceRecord.h"

using namespace std;
class Course{
//Classs private data
string CourseCode;
string CourseName;
Instructor* instructor ;
vector <Student*> students;
vector<AttendanceRecord> attendanceRecords;

public:
//define the constructors
    Course();
    Course(string CourseCode, string CourseName);
    ~Course();
//Class Methods
    void setCorseCode(string code);
    string getCourseCode()const;
    void setCorseName(string Name);
    string getCourseName()const;
    void addStudent(Student* student);
    void removeStudents(string studentId);
    void assignInstructor(Instructor* instructor);
    void markAttendance(string studentsId,string date,string status);
    void showCourseReport()const;
    bool hasStudent(string studentId)const;
};
#endif