#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <direct.h>

#include "../Linked-List/linkedlist.h"

// void UpString(std::string& stu);
// void DeleteANode(Course*& pCourse);
// void DeleteANode(Classes*& pClass);
// void InputStudent(Student*& pClassS, std::fstream& fin);
// void ReadClassStudent(Classes*& pClass, std::fstream& fin, std::string syear);
// void DisplayClass(Classes* pClass);
// void ChooseDisplayStudent(Classes* pClass);
// void DisplayStudent(Student* pStudent);
// void ReadClass(Classes*& pClass, std::fstream& fin);
// void ViewClass();
// void ViewClassStudent();

// void ReadCourse(Course*& pCourse, std::fstream& fin, std::string syear, int i);
// void ReadCourseSetUp(Course*& pCourse, std::string syear);
// void DisplayCourse(Course* pCourse);
// void ChooseDisplayStudent(Course* pClass);
// void ViewCourse();
// void ViewCourseStudent();

void viewClass(Classes* classesHead, int schoolYear);
void viewClassStudent(Classes* classesHead, int schoolYear, std::string classID);
void viewCourse(Semesters* semestersHead, int schoolYear, int semester);
void viewCourseStudent(Semesters* semestersHead, int schoolYear, int semester, std::string courseID);