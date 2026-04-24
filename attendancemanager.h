#ifndef ATTENDANCEMANAGER_H
#define ATTENDANCEMANAGER_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

#include "Student.h"
#include "Instructor.h"
#include "Course.h"

class AttendanceManager {
private:
    vector<Student> students;
    vector<Instructor> instructors;
    vector<Course> courses;

    Student* findStudentById(int id);
    Instructor* findInstructorById(int id);
    Course* findCourseByCode(const string& code);

public:
    void addStudent();
    void addInstructor();
    void createCourse();
    void assignStudentToCourse();
    void assignInstructorToCourse();
    void markAttendance();
    void viewReports();

    void run();
};

#endif