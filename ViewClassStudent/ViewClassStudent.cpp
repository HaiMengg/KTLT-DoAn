#include "ViewClassStudent.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void UpString(string stu)
{
	for (int i = 0; i < stu.size(); i++)
		if (isalpha(stu[i]) == true)
			stu[i]=toupper(stu[i]);
}

fstream ChooseClass()
{
	fstream fin;
	string stu;
	cout << "Input class that you want to see all students: ";	cin >> stu;
	UpString(stu);
	stu = "class/" + stu + "/student.csv";
	fin.open(stu);
	while (!fin.is_open())
	{
		cout << "Can't not find class that you want,please input class again: "; cin >> stu;
		UpString(stu);
		stu = "class/" + stu + "/student.csv";
		fin.open(stu);
	}
	system("cls");
	return fin;
}

void InputStudent(ClassStudent*& pClass, fstream& fin)
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

void ReadClass(ClassStudent*& pClass, fstream& fin) { //fin ->  LList
	string temp;
	ClassStudent* pCur = pClass;
	getline(fin,temp);
	if (pClass == nullptr && !fin.eof())
	{
		pClass = new ClassStudent;
		InputStudent(pClass, fin);
		pCur = pClass;
	}
	while (!fin.eof())
	{

		pCur->pNext = new ClassStudent;
		pCur = pCur->pNext;
		InputStudent(pCur, fin);
	}
}

void DisplayClass(ClassStudent* pClass)
{
	ClassStudent* pCur = pClass;
	cout << "All the students in the class are: \n";
	while (pCur->pNext != nullptr)
	{
		cout <<pCur->student.studentID <<" - "<< pCur->student.firstname<<" "<< pCur->student.lastname << endl;
		pCur = pCur->pNext;
	}
}

void DeleteNode(ClassStudent* &pClass)
{
	ClassStudent* pRemove;
	while (pClass != nullptr)
	{
		pRemove = pClass;
		pClass = pClass->pNext;
		delete pRemove;
	}
}

void ViewClassStudent() {
	fstream fin=ChooseClass();
	ClassStudent* pClass = nullptr;
	ReadClass(pClass, fin);
	DisplayClass(pClass);
	DeleteNode(pClass);
}