#pragma once
#include"Header1.h"
#include<cstring>
#define del system("cls")
using namespace std;

void UpString(string& stu);
void InputStudent(Student*& pClassS, fstream& fin);
void ReadClass(Classes*& pClass, fstream& fin, string syear);
void DisplayClass(Classes* pClass);
void DeleteNode(Classes*& pClass);
void ChooseDisplayStudent(Classes* pClass);
void DisplayStudent(Student* pStudent);
void InputCourse(Student*& pClassS, fstream& fin, string temp);
void ViewClass();