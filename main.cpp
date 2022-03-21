#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#include "login-logout.cpp"

int main()
{
    // Get CSV files
    fstream staff, teacher, student;
    staff.open("staff.csv", ios::in);
    teacher.open("teacher.csv", ios::in);
    student.open("student.csv", ios::in);

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