#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include <regex>
#include "../Linked-List/linkedlist.h"

void createClass(Classes*& classHead, std::fstream& dataFile, int startYear);
void appendNewClassList(Classes*& classHead, std::string newClass);
void appendNewClassFile(std::fstream& dataFile, std::string newClass);
void appendNewClassFolder(std::string newClass, int startYear);
void appendBatchClassList(Classes*& classHead, SNode* batch);
void appendBatchClassFile(std::fstream& dataFile, SNode* batch);
void appendBatchClassFolder(SNode* batch, int startYear);

void addStudentsToClass(Student*& totalStudentHead, std::fstream& totalFile, int schoolYear, std::string currentClass);
void appendNewStudentList(Student*& totalStudentHead, std::string newValue, int schoolYear, std::string currentClass, bool = true);
void appendBatchStudentList(Student*& totalStudentHead, SNode* batch, int schoolYear, std::string currentClass, bool = true);
void appendNewStudentFile(std::string newValue, std::fstream& dataFile, int schoolYear, std::string currentClass, bool = true);
void appendBatchStudentFile(SNode* batch, std::fstream& dataFile, int schoolYear, std::string currentClass, bool = true);
std::string getStudentDOB(std::string studentInfo);

bool checkInputFormat(std::fstream&, int);