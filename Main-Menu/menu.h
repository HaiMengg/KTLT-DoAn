#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include "../Linked-List/linkedlist.h"
#include "../Create-Classes/create.h"
#include "../Create-School-Year/create.h"

void currentMenu(Node&, std::fstream&, std::fstream&, std::fstream&);

void createClassMenu(Classes*& classHead, std::fstream& classData);
int viewMenu();