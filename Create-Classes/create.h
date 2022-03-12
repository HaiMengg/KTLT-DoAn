#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include <regex>
#include "../Linked-List/linkedlist.h"

void createClass(Node*& nodeHead, std::fstream& dataFile, int startYear);
void addFirstYearStudents(Node*& nodeHead, std::fstream& dataFile);