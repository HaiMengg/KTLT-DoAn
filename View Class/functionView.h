#pragma once
#include<fstream>
#include<string>
using namespace std;

struct Class {
	string ClassID;
	int startyear;
	Class* pNext = nullptr;
};

void ReadClass(Class*& pClass, fstream& fin);
void DisplayClass(Class*& pClass);
void DeleteNode(Class* pClass);
void ViewClass();

