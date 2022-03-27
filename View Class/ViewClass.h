#pragma once
#include"struct.h"
#include<iomanip>
#define del system("cls")
using namespace std;

void UpString(string& stu);
void InputStudent(Student*& pClassS, fstream& fin);
void ReadClassStudent(Classes*& pClass, fstream& fin, string syear);
void DisplayClass(Classes* pClass);
void DeleteNode(Classes*& pClass);
void ChooseDisplayStudent(Classes* pClass);
void DisplayStudent(Student* pStudent);
void ReadClass(Classes*& pClass, fstream& fin);
void ViewClass();
void ViewClassStudent();