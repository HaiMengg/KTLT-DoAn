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
    Course *courseData = new Course;
    Staff* staffData = new Staff;
    Teacher* teacherData = new Teacher;
    Student* studentData = new Student;
    CourseScore* courseScoreData = new CourseScore;
    CourseScore* courseSem1Data = new CourseScore;
    CourseScore* courseSem2Data = new CourseScore;
    CourseScore* courseSem3Data = new CourseScore;

    // Read CSV files
    readCourse(courseData, course, schoolYear, semester);
    readStaff(staffData, staff);
    readTeacher(teacherData, teacher);
    readStudent(studentData, student);
    readScoreboard(courseSem1Data, schoolYear, 1);
    readScoreboard(courseSem2Data, schoolYear, 2);
    readScoreboard(courseSem3Data, schoolYear, 3);

    // Log in to the system
    Global data;

    data.course = courseData;
    data.staff = staffData;
    data.teacher = teacherData;
    data.student = studentData;

    data.courseSem1 = courseSem1Data;
    data.courseSem2 = courseSem2Data;
    data.courseSem3 = courseSem3Data;

    if (semester == 1) data.courseScore = courseSem1Data;
    if (semester == 2) data.courseScore = courseSem2Data;
    if (semester == 3) data.courseScore = courseSem3Data;

    data.semester = semester;
    data.year = schoolYear;
    loginCheck(data);

    // Delete data before exiting program
    deleteData(data);
}