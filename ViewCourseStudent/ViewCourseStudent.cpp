#include "ViewCourseStudent.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void UpString(string stu)
{
	for (int i = 0; i < stu.size(); i++)
		if (isalpha(stu[i]) == true)
			stu[i] = toupper(stu[i]);
}

fstream ChooseCourse()
{
	fstream fin;
	string stu;
	cout << "Input course that you want to see all students: ";	cin >> stu;
	UpString(stu);
	stu = "course/" + stu + "/student.csv";
	fin.open(stu);
	while (!fin.is_open())
	{
		cout << "Can't not find course that you want,please input course again: "; cin >> stu;
		UpString(stu);
		stu = "course/" + stu + "/student.csv";
		fin.open(stu);
	}
	system("cls");
	return fin;
}

void InputStudent(CourseStudent*& pClass, fstream& fin)
{
	getline(fin, pClass->student.studentusr, ',');
	getline(fin, pClass->student.studentpwd, ',');
	getline(fin, pClass->student.studentID, ',');
	getline(fin, pClass->student.firstname, ',');
	getline(fin, pClass->student.lastname, ',');
	getline(fin, pClass->student.dob, ',');
	getline(fin, pClass->student.gender, ',');
	getline(fin, pClass->student.socialID, ',');
	getline(fin, pClass->student.startyear, ',');
	getline(fin, pClass->student.classID, ',');
	getline(fin, pClass->student.CoursesID);
}

void ReadClass(CourseStudent*& pClass, fstream& fin) { //fin ->  LList
	string temp;
	CourseStudent* pCur = pClass;
	getline(fin, temp);
	if (pClass == nullptr && !fin.eof())
	{
		pClass = new CourseStudent;
		InputStudent(pClass, fin);
		pCur = pClass;
	}
	while (!fin.eof())
	{

		pCur->pNext = new CourseStudent;
		pCur = pCur->pNext;
		InputStudent(pCur, fin);
	}
}

void DisplayClass(CourseStudent* pClass)
{
	CourseStudent* pCur = pClass;
	cout << "All the students in the course are: \n";
	while (pCur->pNext != nullptr)
	{
		cout << pCur->student.studentID << " - " << pCur->student.firstname << " " << pCur->student.lastname << endl;
		pCur = pCur->pNext;
	}
}

void DeleteNode(CourseStudent*& pClass)
{
	CourseStudent* pRemove;
	while (pClass != nullptr)
	{
		pRemove = pClass;
		pClass = pClass->pNext;
		delete pRemove;
	}
}

void ViewCourseStudent() {
	fstream fin= ChooseCourse();
	CourseStudent* pClass = nullptr;
	ReadClass(pClass, fin);
	DisplayClass(pClass);
	DeleteNode(pClass);
}