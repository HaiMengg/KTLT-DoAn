#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "login-logout.cpp"
#include "enroll-courses.cpp"
#include "scoreboard.cpp"

int main()
{
    // Get CSV files
    std::fstream staff, teacher, student;
    staff.open("staff.csv", std::ios::in);
    teacher.open("teacher.csv", std::ios::in);
    student.open("student.csv", std::ios::in);

    // Get year
    int schoolYear = getYear();

    // Get semester
    std::fstream semesterInput, courseSem1, courseSem2, courseSem3;
    semesterInput.open("semester/semester.csv", std::ios::in);
    int semester = getSemester(semesterInput);
    courseSem1.open("semester/1/course.csv", std::ios::in);
    courseSem2.open("semester/2/course.csv", std::ios::in);
    courseSem3.open("semester/3/course.csv", std::ios::in);

    // Linked lists
    Course *courseDataSem1 = new Course, *courseDataSem2 = new Course, *courseDataSem3 = new Course;
    Staff* staffData = new Staff;
    Teacher* teacherData = new Teacher;
    Student* studentData = new Student;
    CourseScore* courseScoreData = new CourseScore;

    // Read CSV files
    readCourse(courseDataSem1, courseSem1, schoolYear, 1);
    readCourse(courseDataSem2, courseSem2, schoolYear, 2);
    readCourse(courseDataSem3, courseSem3, schoolYear, 3);
    readStaff(staffData, staff);
    readTeacher(teacherData, teacher);
    readStudent(studentData, student);
    readScoreboard(courseScoreData, schoolYear, semester);

    // Log in to the system
    Global data;

    data.courseSem1 = courseDataSem1;
    data.courseSem2 = courseDataSem2;
    data.courseSem3 = courseDataSem3;

    if (semester == 1) data.course = courseDataSem1;
    if (semester == 2) data.course = courseDataSem2;
    if (semester == 3) data.course = courseDataSem3;

    data.staff = staffData;
    data.teacher = teacherData;
    data.student = studentData;
    data.courseScore = courseScoreData;
    data.semester = semester;
    data.year = schoolYear;
    loginCheck(data);

    // Delete data before exiting program
    deleteData(data);
}