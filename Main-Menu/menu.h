#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include "../Linked-List/linkedlist.h"
#include "../Create-Classes/create.h"
#include "../Create-School-Year/create.h"
#include "../Functions/func.h"

void currentMenu(Node&, std::fstream&, std::fstream&, std::fstream&);

void viewMenu(Node allData);
void createClassMenu(Classes*& classHead, std::fstream& classData, SchoolYear* schoolYearHead);
void addStudentMenu(Student* studentHead, std::fstream& studentData, SchoolYear* schoolYearHead, Classes* classesHead);