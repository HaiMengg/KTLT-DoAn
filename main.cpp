#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#include "read-write-csv.cpp"
#include "login-logout.cpp"

int main()
{
    // Open CSV files
    fstream staff, teacher, student;
    staff.open("staff.csv", ios::in);
    teacher.open("teacher.csv", ios::in);
    student.open("student.csv", ios::in);

    // Linked lists
    STAFF* staffData = new STAFF;
    TEACHER* teacherData = new TEACHER;
    STUDENT* studentData = new STUDENT;

    // Read CSV files
    readStaff(staffData, staff);
    readTeacher(teacherData, teacher);
    readStudent(studentData, student);

    // Log in to the system
    int identity = 0;
    string username, password;
    cout << "----------------\n" << "Welcome!\nPlease login to continue.\n\n";
    loginCheck(staffData, studentData, username, password, identity);

    // Delete linked lists
    deleteData(staffData, teacherData, studentData);
}