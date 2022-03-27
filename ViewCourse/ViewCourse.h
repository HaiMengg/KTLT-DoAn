#pragma once
#include"struct.h"
#include<iomanip>
#define del system("cls")
using namespace std;

void UpString(string& stu);
void InputStudent(Student*& pClassS, fstream& fin);
void ReadCourse(Course*& pCourse, fstream& fin, string syear, int i);
void ReadCourseSetUp(Course*& pCourse, string syear);
void DisplayCourse(Course* pCourse);
void DeleteNode(Course*& pClass);
void ChooseDisplayStudent(Course* pClass);
void DisplayStudent(Student* pStudent);
void ViewCourse();
void ViewCourseStudent();