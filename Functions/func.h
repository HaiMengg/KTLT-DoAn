#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>

bool isDigit_w(std::string);
std::string toLower_w(std::string);
std::string toUpper_w(std::string);
int countElement(std::string, char);

bool isValidDate(std::string);
int getDateData(std::string, char);
void updateDate(std::string&);
void dateZeroFill(std::string&);