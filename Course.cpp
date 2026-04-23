#include "Course.h"

Course::Course(){}
Course::Course(string CID, string CName, Instructor tech){
    CourseID = CID;
    CourseName = CName;
    Instructor = tech;

}
void Course::AddStudent(Student s){
    bool areadythere = false;
        for (int i = 0; i < students.size(); i++) {
        if (students[i].ID == s.ID) {
            areadythere = true;
            cout << "Student Already exists"<<endl;
            break;
        }
    }
    if (!areadythere){
    students.push_back(s);
    cout<<"Student successfully added"<<endl;
    }    
}
void Course::RemoveStudent(string id){
    bool found = false;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].ID == id) {
            students.erase(i);
            cout<<"Successfully deleted student : "<<id <<endl;
            found = true;
            break;
        }
    }
    if (!found)
cout<< "Student Not Found!" <<endl;
}


void Course::MarkAttendace(string StudentID , string date, bool present){
    bool found = false;

    for (int i =0; i<students.size();i++){
        if (students[i].ID == StudentID){
            found = true;
            break;
        }
    }
    if (found)
    attendance.push_back(AttendanceRecord(StudentID , date , present));
    else{
        cout <<"Student not found !"<<endl;
    }
}
void Course::AssignTecher(string name){
    Instructor = name;
}



void Course::ShowCourseReport(){
cout << "\n---------- COURSE REPORT ----------\n";
    cout << "Course ID: " << CourseID << endl;
    cout << "Course Name: " << CourseName << endl;
    cout << "Instructor: " << Instructor.Name << endl;
    cout << "      -----Students-----       "<<endl;

    if (students.size() ==0){
        cout<<"NO Students Submitted"<<endl;
    }else{
        for (int i=0;i<students.size();i++){
            cout<<i+1<<"- "<<students[i].Name<<" | "<<students[i].ID<<endl;
        }
    }
        cout << "      -----Attendance-----       "<<endl;

        if (attendance.size() ==0){
        cout<<"No Attendance submitted !"<<endl;
    }else{
        for (int i=0;i<attendance.size();i++){
            attendace[i].display();
                }
    }
    cout << "---------------------------------------";

}

