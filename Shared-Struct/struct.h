#include <iostream>
#include <string>
#include <fstream>

struct SchoolYear {
    SchoolYear* nodePrev;
    int schoolYear;
    SchoolYear* nodeNext;
};
struct Student {
    Student* nodePrev;
    std::string usr, pwd, studentID, firstName, lastName, gender, dob, socialID, startYear, classID;
    //Reset after each school year
    std::string studentCoursesSem1;
    std::string studentCoursesSem2;
    std::string studentCoursesSem3;
    Student* nodeNext;
};
struct Classes {
    Classes* nodePrev;
    std::string classID;
    int startYear;
    Student* classStudentHead;      //All students of this class
    Classes* nodeNext;
};
//Course can only exist in a semester
struct Course {
    Course* nodePrev;
    std::string courseId, courseName, teacherName, numOfCredits, daySession;    //Format: MON-S1|SAT-S4|TUE-S2|...
    int studentMax = 50;
    Student* courseStudentHead;     //All students of this course
    Course* nodeNext;
};
struct Semesters {
    Semesters* nodePrev;
    int schoolYear;
    std::string startDate, endDate;
    Course* semesterCourseHead;
    Semesters* nodeNext;
};

struct Node {
    SchoolYear* schoolYearHead = nullptr;
    Classes* classesHead = nullptr;
    Student* studentHead = nullptr;
    Semesters* semesterHead = nullptr;
};