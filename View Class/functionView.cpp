#include "functionView.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void ReadClass(Class*& pClass, fstream& fin) { //fin ->  LList
	string temp;
	Class* pCur = pClass;
	fin >> temp;
	if (pClass == nullptr && !fin.eof())
	{
		pClass = new Class;
		getline(fin, pClass->ClassID, ',');
		pClass->ClassID.erase(0, 1);
		fin >> pClass->startyear;
		pCur = pClass;
	}
	while (!fin.eof())
	{

		pCur->pNext = new Class;
		pCur = pCur->pNext;
		getline(fin, pCur->ClassID, ',');
		fin >> pCur->startyear;
		pCur->ClassID.erase(0, 1);
	}
}

void DisplayClass(Class*& pClass)
{
	Class* pCur = pClass;
	while (pCur->pNext != nullptr)
	{
		cout << "ClassID:      " << pCur->ClassID << "		StartYear:		" << pCur->startyear << endl;
		pCur = pCur->pNext;
	}
}

void DeleteNode(Class* &pClass)
{
	Class* pRemove;
	while (pClass != nullptr)
	{
		pRemove = pClass;
		pClass = pClass->pNext;
		delete pRemove;
	}
}

void ViewClass() {
	fstream fin("class.csv");
	Class* pClass = nullptr;
	ReadClass(pClass, fin);
	DisplayClass(pClass);
	DeleteNode(pClass);
}

