#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include <iomanip>
#include "../Linked-List/linkedlist.h"
#include "../Functions/func.h"

// void create(Node*&);
void viewSchoolYear(SchoolYear*);
void inputSchoolYear(SchoolYear*, std::string&);
void createSchoolYear(SchoolYear*&, std::fstream&, std::string);

bool schoolYearSearchBool(SchoolYear*, int);

void appendNewYearList(SchoolYear*&, int);
void appendNewYearFile(std::fstream&, int);