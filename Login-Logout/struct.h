#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>
#pragma once
#include "../Linked-List/linkedlist.h"

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

struct Login
{
    Staff* staff;
    Staff* curStaff;
    Teacher* teacher;
    Teacher* curTeacher;
    Student* student;
    Student* curStudent;
    Course* course;
    std::string username, password;
    int semester = 0, identity = 0;
};

void loginInit(Node& node, std::fstream& sY, std::fstream& cl, std::fstream& stu, std::fstream& semes, std::string& currentDate);

void readCourse(std::string courses, std::string schoolYear, StudentCourse* &head);
void readStaff(Staff* &data, std::fstream &input);
void readTeacher(Teacher* &data, std::fstream &input);
void readStudent(Student* &data, std::fstream &input);
void writeStaff(Staff* data);
void writeTeacher(Teacher* data);
void writeStudent(Student* data);
void deleteData(Login &data);

bool checkSemester(std::string start, std::string end);
int getSemester(std::fstream &input);
int getCurrentSemester(std::string, Semesters*);
void printCurrentDate(std::string, Semesters*);
void readCourse(Course* &data, std::fstream &input);
void replaceAll(std::string& str, const std::string& from, const std::string& to);
void showCourseNode(Course* data);
void showCourses(Course* data);
void enrollCourse(Login data, Node& node, std::fstream& sY, std::fstream& cl, std::fstream& stu, std::fstream& sem, std::string& currentDate);
void viewCourse(Login data, Node& node, std::fstream& sY, std::fstream& cl, std::fstream& stu, std::fstream& sem, std::string& currentDate);
void removeCourse(Login data, Node& node, std::fstream& sY, std::fstream& cl, std::fstream& stu, std::fstream& sem, std::string& currentDate);

void loginCheck(Login &data, Node& node, std::fstream& sY, std::fstream& cl, std::fstream& stu, std::fstream& sem, std::string& currentDate);
void loginMenu(Login &data, Node& node, std::fstream& sY, std::fstream& cl, std::fstream& stu, std::fstream& sem, std::string& currentDate);
void studentMenu(Login &data, Node& node, std::fstream& sY, std::fstream& cl, std::fstream& stu, std::fstream& sem, std::string& currentDate);
void viewInfo(Login data, Node& node, std::fstream& sY, std::fstream& cl, std::fstream& stu, std::fstream& sem, std::string& currentDate);
void changePassword(Login &data, Node& node, std::fstream& sY, std::fstream& cl, std::fstream& stu, std::fstream& sem, std::string& currentDate);
void logOut(Login &data, Node& node, std::fstream& sY, std::fstream& cl, std::fstream& stu, std::fstream& sem, std::string& currentDate);