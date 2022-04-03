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
    std::fstream staff, teacher, student, course;
    staff.open("staff.csv", std::ios::in);
    teacher.open("teacher.csv", std::ios::in);
    student.open("student.csv", std::ios::in);

    // Get year
    int schoolYear = getYear();

    // Get semester
    std::fstream semesterInput;
    semesterInput.open("semester/semester.csv", std::ios::in);
    int semester = getSemester(semesterInput);
    course.open("semester/" + std::to_string(semester) + "/course.csv", std::ios::in);

    // Linked lists
    Course* courseData = new Course;
    Staff* staffData = new Staff;
    Teacher* teacherData = new Teacher;
    Student* studentData = new Student;
    CourseScore* courseScoreData = new CourseScore;

    // Read CSV files
    readCourse(courseData, course, schoolYear, semester);
    readStaff(staffData, staff);
    readTeacher(teacherData, teacher);
    readStudent(studentData, student);
    readScoreboard(courseScoreData, schoolYear, semester);

    // Log in to the system
    Login data;
    data.course = courseData;
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