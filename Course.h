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
string CourseID;
string CourseName;
vector <Student> students; //creat dynamic list of students
Instructor Instructor ;
vector <AttendanceRecord> attendance;//creat dynamic list of attendance

public:
Course(){}
Course(string CID, string CName, Instructor tech){
    CourseID = CID;
    CourseName = CName;
    Instructor = tech;
}
void AddStudent(Student s);
void RemoveStudent(string id);
void MarkAttendace(string StudentID , string date, bool present);
void ShowCourseReport() const;};
#endif