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

struct CourseStudent {
	STUDENT student;
	CourseStudent* pNext = nullptr;
};

void UpString(string stu);
fstream ChooseCourse();
void InputStudent(CourseStudent*& pClass, fstream& fin);
bool CheckString(string a, string b);
void ReadClass(CourseStudent*& pClass, fstream& fin);
void DisplayClass(CourseStudent* pClass);
void DeleteNode(CourseStudent*& pClass);
void ViewCourseStudent();