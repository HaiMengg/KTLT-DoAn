#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>

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
struct Student {
    Student* nodePrev;
    std::string usr, pwd, studentID, firstName, lastName, gender, dob, socialID, startYear, classID;
    std::string studentCourse;      //Courses this student is currently a part of
    Student* nodeNext;
};
struct Classes {
    Classes* nodePrev;
    std::string classID;
    Student* classStudentHead;      //All students of this class
    Classes* nodeNext;
};
struct Course {
    Course* nodePrev;
    std::string courseId, courseName, teacherName, numOfCredits, daySession;    //Format: MON-S1|SAT-S4|TUE-S2|...
    int studentMax = 50;
    Student* courseStudentHead;     //All students of this course
    Course* nodeNext;
};

struct Node {
    SchoolYear* schoolYearHead = nullptr;
    Classes* classesHead = nullptr;
    Student* studentHead = nullptr;
    Course* courseHead = nullptr;
};

void createList(SNode*& nodeHead, std::fstream& dataFile);
void createList(DNode*& nodeHead, std::fstream& dataFile);
void createList(SchoolYear*& schoolYearHead, std::fstream& dataFile);
void createList(Classes*& classHead, std::fstream& dataFile);

//For reading all students
void createList(Student*& studentHead, std::fstream& dataFile);
//For reading students of a single class
void createList(Student*& studentHead, std::fstream& dataFile, int schoolYear, std::string currentClass);

void createList(Course*& courseHead, std::fstream& dataFile);

void readStudentData(Student*& studentNode, std::string studentData, bool = true);

// bool appendListSingle(Node*& nodeHead, std::string newValue);
// bool appendListBatch(Node*& nodeHead, SNode* batch);
// void appendFileSingle(std::string newValue, std::fstream& dataFile);
// void appendFileBatch(SNode* batch, std::fstream& dataFile);

bool listSearchBool(Node* nodeHead, std::string searchValue);

// void printListSingle(Node* nodeHead, bool reverse);
// void printStringSegment(std::string str, int segmentStart, int segmentEnd);

// int listLength(Node* nodeHead);

void destructList(Node&);
void destructList(SNode*&);
void destructList(DNode*&);
void destructList(Classes*&);
void destructList(Student*&);