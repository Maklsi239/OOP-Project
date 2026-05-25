#include "Course.h"
#include "ReportHelper.h"
#include <iostream>
using namespace std;

//-----------------------------------------------------> empty constructor
Course::Course() {
    courseCode = "";
    courseName = "";
    instructor = nullptr;};
//-------------------------------------------------------> constructor with args
Course::Course(string courseCode, string courseName) {
    this->courseCode = courseCode;
    this->courseName = courseName;
    instructor = nullptr;};
//------------------------------------------------------------> des
Course::~Course() {};
//------------------------------------------------------> setters section
void Course::setCourseCode(string code) {
    courseCode = code;}

void Course::setCourseName(string name) {
    courseName = name;}
//------------------------------------------------------->getters section
string Course::getCourseCode() const {
    return courseCode;}
//-------------
    string Course::getCourseName() const {
    return courseName;}
//------------
string Course::getInstructorName() const {
    if (instructor == nullptr) {
        return "Not assigned";}
    return instructor->getName();}
//------------
int Course::getStudentCount() const {
    return students.size();}
//-------------
    int Course::getAttendanceRecordCount() const {
    return attendanceRecords.size();}
//---------------------------------------------------------> student section
void Course::addStudent(Student* student) {
    if (student == nullptr) {
        cout << "Invalid student." << endl;
        return;

    }if (hasStudent(student->getId())) {
        cout << "Student already exists in this course." << endl;
        return;
    }
    students.push_back(student);
    cout << "Student added to course successfully." << endl;}
//----------------------------
void Course::showStudentRecord(string studentId) const {
    if (!hasStudent(studentId)) {
        return;}
    int total = ReportHelper::countTotalClasses(studentId, attendanceRecords);
    int present = ReportHelper::countPresentClasses(studentId, attendanceRecords);
    double percent = ReportHelper::calculatePercentage(studentId, attendanceRecords);
    cout << courseCode << "  " << courseName << "                  " << present << "          " << total << "       " << percent << "%" << endl;}
//-----------------------------------
void Course::removeStudent(string studentId) {
    bool found = false;
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i] != nullptr && students[i]->getId() == studentId) {
            students.erase(students.begin() + i);
            found = true;
            break;
        }}if (!found) {
        cout << "Student is not found in this course." << endl;
        return;}
    size_t i = 0;
    while (i < attendanceRecords.size()) {
        if (attendanceRecords[i].getStudentId() == studentId) {
            attendanceRecords.erase(attendanceRecords.begin() + i);
        } else {
            i++;
        }
    }cout << "Student removed from course successfully." << endl;};
//-------------------------
bool Course::hasStudent(string studentId) const {
    for (const Student* student : students) {
        if (student != nullptr && student->getId() == studentId) {
            return true;}}
    return false;}
    //----------------------------------------------------------------> instructor section
void Course::assignInstructor(Instructor* instructor) {
    if (instructor == nullptr) {
        cout << "Invalid instructor." << endl;
        return;}
        this->instructor = instructor;}
//---------------------------
bool Course::removeInstructorById(string instructorId) {
    if (hasInstructor(instructorId)) {
        instructor = nullptr;
        return true;
    }return false;}
//--------------------------------------
bool Course::hasInstructor(string instructorId) const {
    return instructor != nullptr && instructor->getId() == instructorId;}
    //---------------------------------------------------------------------> course attendance and report
void Course::markAttendance(string studentId, string date, string status) {
    if (!hasStudent(studentId)) {
        cout << "Student not found in this course." << endl;
        return;
    }if (status != "Present" && status != "Absent") {
        cout << "Invalid status. Use Present or Absent." << endl;
        return;}
    for (AttendanceRecord& record : attendanceRecords) {
        if (record.getStudentId() == studentId && record.getDate() == date) {
            record.setStatus(status);
            cout << "Attendance updated successfully." << endl;
            return;}}
    AttendanceRecord record(studentId, date, status);
    attendanceRecords.push_back(record);
    cout << "Attendance marked successfully." << endl;}
//-------------------------------------
void Course::showStudents() const {
    if (students.empty()) {
        cout << "No students assigned to this course." << endl;
        return;}
    cout << "Students in this course:" << endl;
    for (const Student* student : students) {
        if (student != nullptr) {
            cout << student->getId() << " - " << student->getName() << endl;
        }}}
//-------------------------------------------
void Course::showCourseReport() const {
    cout << "================ COURSE REPORT ================" << endl;
    cout << "Course Code" << ": "<< courseCode << endl;
    cout <<  "Course Name" << ": "<< courseName << endl;
    cout <<  "Students" << ": "<< students.size() << endl;
    cout <<  "Records" << ": "<< attendanceRecords.size() <<"\n"<< endl;
//--------------
    cout << "Instructor" << endl;
    cout << "------------------------------------------------" << endl;
    if (instructor != nullptr) {
        cout << "ID" << ": "<< instructor->getId() << endl;
        cout << "Name" << ": "<< instructor->getName() << endl;
        cout << "Department" << ": "<< instructor->getDepartment() << endl;
        cout << "Course Taught" << ": "<< instructor->getCourse() << endl;
    } else {
        cout << "No any instructor assigned." << "\n"<<endl;}

//--------------
    cout << "Students In Course" << endl;
    cout << "------------------------------------------------" << endl;
    if (!students.empty()) {
        cout << "Student ID"<< "                    " << "Name"<< "        " << "Program"<<"    "<< "Year" << endl;
        cout << string(65, '-') << endl;
        for (const Student* student : students) {
            if (student != nullptr) {
                cout << student->getId()<<"                                     " << student->getName()<< "         "  << student->getProgram()<<"      "<<student->getYear()<< endl;}
        }} else {
        cout << "No students added to this course." <<"\n"<< endl;}

//----------------
    cout << "Attendance Summary" << endl;
    cout << "------------------------------------------------" << endl;
    if (!students.empty()) {
        cout << "Student ID"<< "                    " << "Name"<< "            " << "Present"<< "       " << "Total"<<"    "<< "Percent" << endl;
        cout << string(72, '-') << endl;
        for (const Student* student : students) {
            try {
                int total = ReportHelper::countTotalClasses(student->getId(), attendanceRecords);
                int present = ReportHelper::countPresentClasses(student->getId(), attendanceRecords);
                double percentage = ReportHelper::calculatePercentage(student->getId(), attendanceRecords);
                cout << student->getId()<< "                                  " << student->getName()<< "            " << present<< "               " << total<< "      "<< percentage << "%" << endl;
            } catch (const exception& e) {
                cout << "" << e.what() << endl;}}} else {
        cout << "No students available for attendance report." <<"\n"<< endl;}

//-------------------
    cout << "Attendance Records" << endl;
    cout << "------------------------------------------------" << endl;
    if (!attendanceRecords.empty()) {
        cout << "Student ID"<< "                  " << "Date"<<"     "<< "Status" << endl;
        cout << string(45, '-') << endl;
        for (const AttendanceRecord& record : attendanceRecords) {
            cout << record.getStudentId()<< "                              " << record.getDate()<<"  " <<record.getStatus() << endl;}
    } else {
        cout << "No attendance records found." << endl;}
}