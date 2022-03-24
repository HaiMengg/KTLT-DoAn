#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>
#include "../Linked-List/linkedlist.h"

void createSemester(Semesters*& semestersHead, std::fstream& dataFile, int startYear);
void appendNewSemesterList(Semesters* semestersHead, std::string newSemesterData, int schoolYear, bool = false);
void appendNewSemesterFile(std::fstream& dataFile, std::string newSemesterData, int schoolYear, bool = false);
void appendNewSemesterFolder(std::string newSemesterData, int startYear);
void appendBatchSemesterList(Semesters* semestersHead, SNode* batch , int schoolYear, bool = false);
void appendBatchSemesterFile(std::fstream& dataFile, SNode* batch, int schoolYear, bool = false);
void appendBatchSemesterFolder(SNode* batch, int startYear);
bool semesterListSearchBool(Semesters* semestersHead, int searchSemester, int startYear);
bool semesterFileSearchBool(std::fstream& semestersTotalFile, int searchSemester, int startYear, bool = true);

bool checkInputFormatSC(std::fstream& inputFile, int mode);
bool semesterCheckBool(std::string semesterData);