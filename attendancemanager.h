#ifndef ATTENDANCEMANAGER_H
#define ATTENDANCEMANAGER_H

#include "Course.h"
#include "Instructor.h"
#include "Student.h"

#include <string>
#include <vector>

using namespace std;

class AttendanceManager {
private:
    vector<Student*> students;
    vector<Instructor*> instructors;
    vector<Course*> courses;

    void loadDefaultCourses();
    void printMenu() const;
    void showStudents() const;
    void showCourseCodes() const;
    bool readRequiredLine(string prompt, string& output) const;
    bool readPositiveInt(string prompt, int& output) const;
    bool readMenuChoice(int& output) const;
    string normalizeStatus(string input) const;
    Course* chooseCourse() const;

    Student* findStudentById(string id);
    Instructor* findInstructorById(string id);
    Course* findCourseByCode(const string& code);

public:
    AttendanceManager();
    ~AttendanceManager();

    void addStudent();
    void addInstructor();
    void listCourses() const;

    void assignStudentToCourse();
    void deleteStudent();
    void deleteInstructor();

    void markAttendance();
    void viewReports();
    void viewStudentRecord();

    void run();
};

#endif
