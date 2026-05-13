#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>

#include "Student.h"
#include "Instructor.h"
#include "AttendanceRecord.h"

using namespace std;

class Course {
private:
    string courseCode;
    string courseName;

    // Pointer: Course has one instructor assigned to it
    Instructor* instructor;

    // Vector + Pointer: Course has many students
    vector<Student*> students;

    // Composition: Course owns attendance records
    vector<AttendanceRecord> attendanceRecords;

public:
    // Constructors
    Course();
    Course(string courseCode, string courseName);

    // Destructor
    ~Course();

    // Setters and getters
    void setCourseCode(string code);
    string getCourseCode() const;

    void setCourseName(string name);
    string getCourseName() const;

    // Course management functions
    void addStudent(Student* student);
    void removeStudent(string studentId);

    // Extra wrapper if old code uses removeStudents()
    void removeStudents(string studentId);

    void assignInstructor(Instructor* instructor);

    // Attendance functions
    void markAttendance(string studentId, string date, string status);

    // Report function
    void showCourseReport() const;

    // Helper function
    bool hasStudent(string studentId) const;
};

#endif