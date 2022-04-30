#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>
#include <windows.h>

bool isDigit_w(std::string);
std::string toLower_w(std::string);
std::string toUpper_w(std::string);
int countElement(std::string, char);

bool isValidDate(std::string);
int getDateData(std::string, char);
void updateDate(std::string&);
void dateZeroFill(std::string&);
bool isDateLaterThanOrEqualTo(std::string date1, std::string date2);
bool isDateEarlierThanOrEqualTo(std::string date1, std::string date2);

int getTerminalWidth();
void setMaximizedWindow();

bool sequenceSearch(std::string seq1, std::string seq2, int seqLength);