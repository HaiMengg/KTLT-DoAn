#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>

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