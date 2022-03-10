#include "functionView.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main() {
	fstream fin("class.csv");
	Class* pClass = nullptr;
	ReadClass(pClass, fin);
	DisplayClass(pClass);
	DeleteNode(pClass);
}