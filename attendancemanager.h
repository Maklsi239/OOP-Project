#ifndef ATTENDANCEMANAGER_H
#define ATTENDANCEMANAGER_H

#include <string>
#include <vector>

#include "Course.h"
#include "Instructor.h"
#include "Student.h"

class AttendanceManager {
private:
    std::vector<Student*> students;
    std::vector<Instructor*> instructors;
    std::vector<Course*> courses;

    Student* findStudentById(std::string id);
    Instructor* findInstructorById(std::string id);
    Course* findCourseByCode(const std::string& code);

public:
    ~AttendanceManager();

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
