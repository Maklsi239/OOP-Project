#include "Course.h"

Course::Course(){}  //adding this so we not getting error when it is empty 
Course::Course(string CID, string CName, Instructor tech){ 
    CourseID = CID;
    CourseName = CName;
    Instructor = tech;

}


//Course Adding Students Method 
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

//Course Removing Students method
void Course::RemoveStudent(string id){
    bool found = false;
 for (int i = 0; i < students.size(); i++){
        if (students[i].ID == id){

            // shift for the left side
            for (int j = i; j < students.size() - 1; j++){
                students[j] = students[j + 1];
            }

            students.pop_back(); 
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Student Not Found!" << endl;
    
}

//Course MarkAtt Method 
void Course::MarkAttendance(string StudentID , string date, bool present){
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
//To Assign the Instructor name 

void Course::AssignInstructor(string name){
    Instructor = name;
}



//This will gives you a full report about the course
void Course::ShowCourseReport() const {
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
            attendance[i].display();
                }
    }
    cout << "---------------------------------------";

}

