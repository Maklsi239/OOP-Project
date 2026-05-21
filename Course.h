#ifndef COURSE_H
#define COURSE_H

#include "AttendanceRecord.h"
#include "Instructor.h"
#include "Student.h"

#include <string>
#include <vector>

using namespace std;

class Course {
private:
    string courseCode;
    string courseName;

    Instructor* instructor;
    vector<Student*> students;
    vector<AttendanceRecord> attendanceRecords;

public:
    Course();
    Course(string courseCode, string courseName);

    ~Course();

    void setCourseCode(string code);
    string getCourseCode() const;

    void setCourseName(string name);
    string getCourseName() const;

    void addStudent(Student* student);
    void removeStudent(string studentId);
    void removeStudents(string studentId);

    void assignInstructor(Instructor* instructor);

    void markAttendance(string studentId, string date, string status);

    void showCourseReport() const;

    bool hasStudent(string studentId) const;
};

#endif