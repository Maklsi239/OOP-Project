#include "Course.h"

/*
    Course(); OK
    Course(string CourseCode, string CourseName); OK
    ~Course(); OK
//Class Methods
    void setCorseCode(string code); OK
    void getCourseCode(); OK 
    void setCorseName(string code); OK 
    void getCourseName(); OK 
    void addStudent(Student* student); OK 
    void removeStudents(string studentId); OK
    void assignInstructor(Instructor* instructor); OK
    void markAttendance(string studentsId,string date,string status); OK
    void showCourseReport()const; OK
    void hasStudent(string studentId); OK
*/




Course::Course(){instructor = NULL;}  //adding this so we not getting error when it is empty 
Course::Course(string CourseCode, string CourseName):CourseCode(CourseCode),CourseName(CourseName){instructor = NULL;}

void Course::setCorseCode(string code){
    CourseCode = code;
}
string Course::getCourseCode()const{
    return CourseCode;
}

void Course::setCorseName(string Name){
    CourseName = Name;
}
string Course::getCourseName()const{
    return CourseName;
}

void Course::addStudent(Student* student){
    if (student == NULL){
        cout<<"Invalid student"<<endl;
        return;
    }
    if(hasStudent(student->getId())){
        cout<<"Student already exists in this course "<<endl;
        return;
    }
    students.push_back(student);
    cout<<"Student added successfully"<<endl;

}


void Course::removeStudents(string studentId){
    for (size_t i=0; i<students.size(); i++){
        if (students[i]->getId() == studentId){
            students.erase(students.begin()+i);
            cout<<"Student - "<<studentId <<" removed successfully"<<endl;
            return;
        }
    }
    cout<<"Student not Found"<<endl;
}

void Course::assignInstructor(Instructor* instructor){
    if (instructor == NULL){
        cout<<"Invalid instructor"<<endl;
        return;
    }
    this->instructor = instructor;
    cout<<"Instructor assigned successfully"<<endl;
}

void Course::markAttendance(string studentID, string date, string status) {
    if (!hasStudent(studentID)) {
        cout << "Student not found in this course" << endl;
        return;
    }

    if (status != "Present" && status != "Absent") {
        cout << "Invalid status. Use Present or Absent." << endl;
        return;
    }

    for (size_t i = 0; i < attendanceRecords.size(); i++) {
        if (attendanceRecords[i].getStudentId() == studentID &&
            attendanceRecords[i].getDate() == date) {

            attendanceRecords[i].setStatus(status);
            cout << "Attendance updated successfully" << endl;
            return;
        }
    }

    AttendanceRecord record(studentID, date, status);
    attendanceRecords.push_back(record);

    cout << "Attendance marked successfully" << endl;
}

void Course::showCourseReport()const{
    cout<<"====== Course Report ======"<<endl;
    cout<<"Course Name : "<<CourseName<<endl;
    cout<<"Course Code : "<<CourseCode<<endl;

    cout<<"Instructor Info : "<<endl;
    if(instructor != NULL){
        instructor->displayInfo();
    }else{
        cout<<"No instructor assigned"<<endl;
    }

    cout<<"Students : "<<endl;
    if (students.size()!=0){
        for (size_t i=0; i<students.size(); i++){
            students[i]->displayInfo();
            cout<<endl;
        }
    }else{
        cout<<"No students added"<<endl;
    }

    cout<<"Attendance Records :"<<endl;
    if (attendanceRecords.size()!=0){
        for (size_t i=0; i<attendanceRecords.size(); i++){
            attendanceRecords[i].displayInfo();
            cout<<endl;
        }
    }else{
        cout<<"No Attendance Records"<<endl;
    }
}

bool Course::hasStudent(string studentID)const{
    for (size_t i=0; i<students.size(); i++){
        if (students[i]->getId() == studentID){
            return true;
        }
    }
    return false;
}


Course::~Course(){};
