#include "functionView.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void ViewClass() {
	fstream fin("class.csv");
	Class* pClass = nullptr;
	ReadClass(pClass, fin);
	DisplayClass(pClass);
	DeleteNode(pClass);
}