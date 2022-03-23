#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include <regex>
#include "../Linked-List/linkedlist.h"
#include "../Functions/func.h"

void viewClasses(Classes* classHead);
void createClass(Classes*& classHead, std::fstream& dataFile, int startYear);
//"schoolYear" is only needed if bool == true
void appendNewClassList(Classes*& classHead, std::string newClass, int schoolYear, bool = false);
void appendNewClassFile(std::fstream& dataFile, std::string newClass, int schoolYear, bool = false);
void appendNewClassFolder(std::string newClass, int startYear);
void appendBatchClassList(Classes*& classHead, SNode* , int schoolYear, bool = false);
void appendBatchClassFile(std::fstream& dataFile, SNode* batch, int schoolYear, bool = false);
void appendBatchClassFolder(SNode* batch, int startYear);
bool classListSearchBool(Classes* classesHead, std::string searchClass, int startYear);
bool classFileSearchBool(std::fstream& classesTotalFile, std::string searchClass, int startYear, bool = true);

void addStudentsToClass(Student*& totalStudentHead, std::fstream& totalFile, int schoolYear, std::string currentClass);
void appendNewStudentList(Student*& totalStudentHead, std::string newValue, int schoolYear, std::string currentClass, bool = true);
void appendBatchStudentList(Student*& totalStudentHead, SNode* batch, int schoolYear, std::string currentClass, bool = true);
void appendNewStudentFile(std::string newValue, std::fstream& dataFile, int schoolYear, std::string currentClass, bool = true);
void appendBatchStudentFile(SNode* batch, std::fstream& dataFile, int schoolYear, std::string currentClass, bool = true);
std::string getStudentDOB(std::string studentInfo);
bool studentListSearchBool(Student* studentHead, std::string searchStudentClass, std::string searchStudentID);
bool studentFileSearchBool(std::fstream& studentTotalFile, std::string searchStudentClass, std::string searchStudentID, bool = true);
bool studentFormatCheck(std::string);

bool checkInputFormat(std::fstream&, int);