#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>
#pragma once

struct Staff
{
    Staff* nodePrev = nullptr;
    std::string usr, pwd, firstName, lastName, gender, dob;
    Staff* nodeNext;
};

struct Teacher
{
    Teacher* nodePrev = nullptr;
    std::string usr, pwd, firstName, lastName, gender, dob;
    Teacher* nodeNext;
};

struct SchoolYear {
    SchoolYear* nodePrev;
    int schoolYear;
    SchoolYear* nodeNext;
};

struct StudentCourse {
    StudentCourse* nodePrev;
    int schoolYear;
    std::string sem1Courses;
    std::string sem2Courses;
    std::string sem3Courses;
    StudentCourse* nodeNext;
};

struct Student {
    Student* nodePrev;
    std::string usr, pwd, studentID, firstName, lastName, gender, dob, socialID, startYear, classID;
    StudentCourse* studentCourseHead = nullptr;
    Student* nodeNext;
};

struct Classes {
    Classes* nodePrev;
    std::string classID;
    int startYear;
    Student* classStudentHead = nullptr;      //All students of this class
    Classes* nodeNext;
};

//Course can only exist in a semester
struct Course {
    Course* nodePrev;
    std::string courseId, courseName, teacherName, numOfCredits, daySession;    //Format: MON-S1|SAT-S4|TUE-S2|...
    int studentMax = 50;
    Student* courseStudentHead = nullptr;     //All students of this course
    Course* nodeNext;
};

struct Semesters {
    Semesters* nodePrev;
    int semester;
    int schoolYear;
    std::string startDate, endDate;
    Course* semesterCourseHead = nullptr;
    Semesters* nodeNext;
};

struct Node {
    SchoolYear* schoolYearHead = nullptr;
    Classes* classesHead = nullptr;
    Student* studentHead = nullptr;
    Semesters* semesterHead = nullptr;
};

struct CourseScore {
    std::string studentID, fullname, courseID, final, total, midterm, other;
    CourseScore* nodeNext;
};

struct Global
{
    Staff* staff;
    Staff* curStaff;
    Teacher* teacher;
    Teacher* curTeacher;
    Student* student;
    Student* curStudent;
    Course* course;
    Course* courseSem1;
    Course* courseSem2;
    Course* courseSem3;
    CourseScore* courseScore;
    std::string username, password;
    int year = 0, semester = 0, identity = 0;
};

int getYear();
bool checkSemester(std::string start, std::string end);
int getSemester();
void replaceAll(std::string& str, const std::string& from, const std::string& to);
void showCourseNode(Course* data);
void showCourses(Course* data);
void enrollCourse(Global &data);
void viewCourse(Global data);
void removeCourse(Global &data);

void loginCheck(Global &data);
void loginMenu(Global &data);
void staffMenu(Global &data);
void teacherMenu(Global &data);
void studentMenu(Global &data);
void viewInfo(Global data);
void changePassword(Global &data);
void logOut(Global &data);

float getTotalMark(float mid, float final, float other);
void exportScoreboard(Global data);
void updateScoreboard(Global data);
void importScoreboard(Global data);
void viewScoreboardCourse(Global data);
void updateStudentResult(Global data);
void viewScoreboardStudent(Global data, std::string studentID);
void viewScoreboardClass(Global data);