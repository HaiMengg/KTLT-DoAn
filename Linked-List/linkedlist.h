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

struct CNode {
    std::string value;
    CNode* nodeNext;
};

struct Node {
    Node* nodePrev;
    std::string value;
    Node* nodeNext;
};


struct SchoolYear {
    SchoolYear* nodePrev;
    int schoolYear;
    SchoolYear* nodeNext;
};
struct Classes {
    Classes* nodePrev;
    std::string classID;
    Student* classStudentHead;
    Classes* nodeNext;
};
struct Course {
    Course* nodePrev;
    std::string courseId, courseName, teacherName, numOfCredits, daySession;    //Format: MON-S1|SAT-S4|TUE-S2|...
    int studentMax = 50;
    Student* courseStudentHead;
    Course* nodeNext;
};
struct Student {
    Student* nodePrev;
    std::string usr, pwd, firstName, lastName, gender, dob, socialID, startYear, classID;
    Course* studentCourse;
    Student* nodeNext;
};

struct Node {
    SchoolYear* schoolYearHead;
    Classes* classesHead;
    Student* studentHead;
    Course* courseHead;
};

void createList(SNode*& nodeHead, std::fstream& dataFile);
void createList(DNode*& nodeHead, std::fstream& dataFile);
void createList(CNode*& nodeFirst, std::fstream& dataFile);
void createList(Node*& nodeHead, std::fstream& dataFile);

bool appendListSingle(Node*& nodeHead, std::string newValue);
bool appendListBatch(Node*& nodeHead, SNode* batch);
void appendFileSingle(std::string newValue, std::fstream& dataFile);
void appendFileBatch(SNode* batch, std::fstream& dataFile);

bool listSearchBool(Node* nodeHead, std::string searchValue);

void printListSingle(Node* nodeHead, bool reverse);
void printStringSegment(std::string str, int segmentStart, int segmentEnd);

int listLength(Node* nodeHead);

void destructList(Node*& nodeHead);
void destructList(SNode*& nodeHead);