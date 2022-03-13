#pragma once
#include<fstream>
#include<string>
using namespace std;

struct STUDENT
{
	string studentusr, studentpwd;
	string studentID, firstname, lastname, dob, gender, socialID;
	string startyear, classID, CoursesID;
};

struct ClassStudent {
	STUDENT student;
	ClassStudent* pNext=nullptr;
};

void UpString(string stu);
fstream ChooseClass();
void InputStudent(ClassStudent*& pClass, fstream& fin);
bool CheckString(string a, string b);
void ReadClass(ClassStudent*& pClass, fstream& fin);
void DisplayClass(ClassStudent* pClass);
void DeleteNode(ClassStudent*& pClass);
void ViewClassStudent();