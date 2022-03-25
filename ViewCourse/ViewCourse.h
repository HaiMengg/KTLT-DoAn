#pragma once
#include"Header1.h"
#include<iomanip>
#define del system("cls")
using namespace std;

void UpString(string& stu);
void InputStudent(Student*& pClassS, fstream& fin);
void ReadCourse(Course*& pCourse, fstream& fin, string syear, int& max, int& max2, int& max1);
void DisplayCourse(Course* pCourse, int max, int max2, int max1);
void DeleteNode(Course*& pClass);
void ChooseDisplayStudent(Course* pClass);
void DisplayStudent(Student* pStudent);
void InputStudentCourse(Student*& pClassS, fstream& fin, string temp);
void ViewCourse();