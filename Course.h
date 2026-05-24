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
//constructors and destructors
    Course();
    Course(string courseCode, string courseName);

    ~Course();

    //setters secton
    void setCourseCode(string code);
    void setCourseName(string name);

    //getters section
        int getStudentCount() const;
    int getAttendanceRecordCount() const;
    string getCourseName() const;
    string getInstructorName() const;
        string getCourseCode() const;


        //student section  
    void addStudent(Student* student);
    void removeStudent(string studentId);
        void showStudents() const;
    void showStudentRecord(string studentId) const;
        bool hasStudent(string studentId) const;
//instructor section
    void assignInstructor(Instructor* instructor);
    bool removeInstructorById(string instructorId);
        bool hasInstructor(string instructorId) const;
//course attendance and report
    void markAttendance(string studentId, string date, string status);
    void showCourseReport() const;
};

#endif
