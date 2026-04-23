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
string CourseID;
string CourseName;
vector <Student> students; //To make the list extendable
Instructor Instructor ;
vector <AttendanceRecord> attendance;

public:
//define the constructors
    Course();
    Course(string CID, string CName, Instructor tech);
//Class Methods
void AddStudent(Student s); 
void RemoveStudent(string id);
void AssignInstructor(string name);
void MarkAttendance(string StudentID , string date, bool present);
void ShowCourseReport() const;};
#endif