#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include <regex>
#include "../Linked-List/linkedlist.h"

void createClass(Node*& nodeHead, std::fstream& dataFile, int startYear);
void addStudentsToClass(Node*& totalStudentHead, std::fstream& totalFile, int schoolYear, std::string currentClass);
bool addListStudentSingle(Node*& totalStudentHead, std::string newValue, int schoolYear, std::string currentClass);
bool addListStudentBatch(Node*& totalStudentHead, SNode* batch, int schoolYear, std::string currentClass);
void addFileStudentSingle(std::string newValue, std::fstream& dataFile, int schoolYear, std::string currentClass);
void addFileStudentBatch(SNode* batch, std::fstream& dataFile, int schoolYear, std::string currentClass);
std::string getStudentDOB(std::string studentInfo);