#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "login-logout.cpp"
#include "enroll-courses.cpp"

int main()
{
    // Get CSV files
    std::fstream staff, teacher, student, course;
    staff.open("staff.csv", std::ios::in);
    teacher.open("teacher.csv", std::ios::in);
    student.open("student.csv", std::ios::in);

    // Get year
    int schoolYear = getYear();

    // Get semester
    std::fstream semester;
    semester.open("semester/semester.csv", std::ios::in);
    int sem = getSemester(semester);
    course.open("semester/" + std::to_string(sem) + "/course.csv", std::ios::in);

    // Linked lists
    Course* courseData = new Course;
    Staff* staffData = new Staff;
    Teacher* teacherData = new Teacher;
    Student* studentData = new Student;

    // Read CSV files
    readCourse(courseData, course, schoolYear, sem);
    readStaff(staffData, staff);
    readTeacher(teacherData, teacher);
    readStudent(studentData, student);

    // Log in to the system
    Login data;
    data.course = courseData;
    data.staff = staffData;
    data.teacher = teacherData;
    data.student = studentData;
    data.semester = sem;
    loginCheck(data);

    // Delete data before exiting program
    deleteData(data);
}