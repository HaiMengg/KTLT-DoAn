#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <direct.h>
#include "../Functions/func.h"

struct SNode {
    std::string value;
    SNode* nodeNext;
};

struct DNode {
    DNode* nodePrev;
    std::string value;
    DNode* nodeNext;
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
struct CourseReg {
    CourseReg* nodePrev;
    int schoolYear, semester;
    std::string startDate, endDate;
    CourseReg* nodeNext;
};

struct Node {
    SchoolYear* schoolYearHead = nullptr;
    Classes* classesHead = nullptr;
    Student* studentHead = nullptr;
    Semesters* semesterHead = nullptr;
    CourseReg* courseRegHead = nullptr;
};

void createList(SNode*& nodeHead, std::fstream& dataFile);
void createList(DNode*& nodeHead, std::fstream& dataFile);
void createList(SchoolYear*& schoolYearHead, std::fstream& dataFile);
void createList(Classes*& classHead, std::fstream& dataFile);

//For reading all students
void createList(Student*& studentHead, std::fstream& dataFile);
//For reading students of a single class
void createList(Student*& studentHead, std::fstream& dataFile, int schoolYear, std::string currentClass);
//For reading students of a single course
void createStuCoList(Student*& studentHead, std::fstream& dataFile);
void readStudentData(Student*& studentNode, std::string studentData, bool = true);

void createList(Semesters*& semestersHead, std::fstream& dataFile, int = -1);
void readSemesterData(Semesters*& semestersHead, std::string semesterData, bool = true);

void createList(Course*& courseHead, std::fstream& dataFile, int schoolYear, int semester);
void readCourseData(Course*& courseHead, std::string courseData);
void readList(Course* courseHead, std::fstream& courseFile);

void createList(StudentCourse*& studentCourseHead, std::string courseData, int schoolYear);

void createList(CourseReg*& courseRegHead, std::fstream& dataFile);
void readCourseRegData(CourseReg*& courseHead, std::string courseData);
void readList(CourseReg* courseRegHead, std::fstream& dataFile);

// bool appendListSingle(Node*& nodeHead, std::string newValue);
// bool appendListBatch(Node*& nodeHead, SNode* batch);
// void appendFileSingle(std::string newValue, std::fstream& dataFile);
// void appendFileBatch(SNode* batch, std::fstream& dataFile);

bool listSearchBool(SchoolYear* schoolYearHead, int searchSchoolYear);
bool listSearchBool(Classes* classesHead, std::string searchClass, int startYear);
bool listSearchBool(Student* studentHead, std::string searchStudentClass, std::string searchStudentID);

// void printListSingle(Node* nodeHead, bool reverse);
// void printStringSegment(std::string str, int segmentStart, int segmentEnd);

// int listLength(Node* nodeHead);

void destructList(Node&);
void destructList(SNode*&);
void destructList(DNode*&);
void destructList(Classes*&);
void destructList(Student*&);
void destructList(Semesters*&);