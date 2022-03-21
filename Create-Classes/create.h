#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include <regex>
#include "../Linked-List/linkedlist.h"

void viewClasses(Classes* classHead);
void createClass(Classes*& classHead, std::fstream& dataFile, int startYear);
//"schoolYear" is only needed if bool == true
void appendNewClassList(Classes*& classHead, std::string newClass, int schoolYear = -1, bool = false);
void appendNewClassFile(std::fstream& dataFile, std::string newClass, int schoolYear = -1, bool = false);
void appendNewClassFolder(std::string newClass, int startYear);
void appendBatchClassList(Classes*& classHead, SNode* , int schoolYear = -1, bool = false);
void appendBatchClassFile(std::fstream& dataFile, SNode* batch, int schoolYear = -1, bool = false);
void appendBatchClassFolder(SNode* batch, int startYear);

void addStudentsToClass(Student*& totalStudentHead, std::fstream& totalFile, int schoolYear, std::string currentClass);
void appendNewStudentList(Student*& totalStudentHead, std::string newValue, int schoolYear, std::string currentClass, bool = true);
void appendBatchStudentList(Student*& totalStudentHead, SNode* batch, int schoolYear, std::string currentClass, bool = true);
void appendNewStudentFile(std::string newValue, std::fstream& dataFile, int schoolYear, std::string currentClass, bool = true);
void appendBatchStudentFile(SNode* batch, std::fstream& dataFile, int schoolYear, std::string currentClass, bool = true);
std::string getStudentDOB(std::string studentInfo);

bool checkInputFormat(std::fstream&, int);