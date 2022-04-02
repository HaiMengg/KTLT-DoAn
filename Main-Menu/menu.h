#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include "../Linked-List/linkedlist.h"
#include "../Create-Classes/create.h"
#include "../Create-School-Year/create.h"
#include "../Create-Semester/create.h"
#include "../Functions/func.h"

void currentMenu(Node&, std::fstream&, std::fstream&, std::fstream&, std::fstream&, std::string& currentDate);

void viewMenu(Node allData);
void createSchoolYearMenu(SchoolYear*& schoolYearHead, std::fstream& schoolYearData, std::string currentDate);

void createClassMenu(Classes*& classHead, std::fstream& classData, SchoolYear* schoolYearHead);
void addStudentMenu(Student*& studentHead, std::fstream& studentData, SchoolYear* schoolYearHead, Classes*& classesHead);

void createSemesterMenu(Semesters*& semesterHead, std::fstream& semesterData, SchoolYear* schoolYearHead);
void addCourseMenu(Semesters*& semesterHead, SchoolYear* schoolYearHead);

int getCurrSemester(std::string, Semesters*);
void printCurrDate(std::string, Semesters*);