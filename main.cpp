#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "login-logout.cpp"
#include "enroll-courses.cpp"

int main()
{
    // Get CSV files
    std::fstream staff, teacher, student;
    staff.open("staff.csv", std::ios::in);
    teacher.open("teacher.csv", std::ios::in);
    student.open("student.csv", std::ios::in);

    // Linked lists
    Staff* staffData = new Staff;
    Teacher* teacherData = new Teacher;
    Student* studentData = new Student;

    // Read CSV files
    readStaff(staffData, staff);
    readTeacher(teacherData, teacher);
    readStudent(studentData, student);

    // Log in to the system
    Login data;
    data.staff = staffData;
    data.teacher = teacherData;
    data.student = studentData;
    loginCheck(data);

    // Delete linked lists
    deleteData(staffData, teacherData, studentData);
}