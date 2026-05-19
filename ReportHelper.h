#pragma once
#include <string>
#include <vector>
#include <stdexcept>
 
// ─── AttendanceRecord ───
class AttendanceRecord {
public:
    AttendanceRecord(const std::string& id, const std::string& status)
        : studentId(id), status(status) {}
 
    std::string getStudentId() const { return studentId; }
    std::string getStatus()    const { return status; }
 
private:
    std::string studentId;
    std::string status;
};
 
// ─── Base Student (pointer-based polymorphism) ───
class Student {
public:
    Student(const std::string& id, const std::string& name)
        : id(id), name(name) {}
 
    virtual ~Student() = default;
 
    std::string getId()   const { return id; }
    std::string getName() const { return name; }
 
    // Polymorphic hook: subclasses can override for custom report headers
    virtual std::string getType() const { return "Student"; }
 
private:
    std::string id;
    std::string name;
};
 
// ─── Derived types (pointer-based polymorphism) ────
class UndergraduateStudent : public Student {
public:
    UndergraduateStudent(const std::string& id, const std::string& name)
        : Student(id, name) {}
    std::string getType() const override { return "Undergraduate"; }
};
 
class GraduateStudent : public Student {
public:
    GraduateStudent(const std::string& id, const std::string& name)
        : Student(id, name) {}
    std::string getType() const override { return "Graduate"; }
};
 
// ─── ReportHelper ───
class ReportHelper {
public:
    // Returns -1 / throws std::invalid_argument on bad input
    static int    countTotalClasses  (const std::string& studentId,
                                      const std::vector<AttendanceRecord>& records);
    static int    countPresentClasses(const std::string& studentId,
                                      const std::vector<AttendanceRecord>& records);
    static double calculatePercentage(const std::string& studentId,
                                      const std::vector<AttendanceRecord>& records);
 
    // Accepts any Student* (polymorphic); throws std::invalid_argument if null
    static void   printStudentReport (const Student* student,
                                      const std::vector<AttendanceRecord>& records);
};
