#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>
#include <winbase.h>
#include "../Linked-List/linkedlist.h"

void createSemester(Semesters*& semestersHead, std::fstream& dataFile, int startYear);
void appendNewSemesterList(Semesters*& semestersHead, std::string newSemesterData, int schoolYear, bool = false);
void appendNewSemesterFile(std::fstream& dataFile, std::string newSemesterData, int schoolYear, bool, std::fstream& totalFile);
void appendNewSemesterFolder(std::string newSemesterData, int startYear);
void appendBatchSemesterList(Semesters*& semestersHead, SNode* batch , int schoolYear, bool = false);
void appendBatchSemesterFile(std::fstream& dataFile, SNode* batch, int schoolYear, bool, std::fstream& totalFile);
void appendBatchSemesterFolder(SNode* batch, int startYear);
bool semesterListSearchBool(Semesters* semestersHead, int searchSemester, int startYear);
bool semesterFileSearchBool(std::fstream& semestersTotalFile, int searchSemester, int startYear, bool = true);
bool semesterCheckBool(std::string semesterData, int schoolYear, Semesters* semesterHead);
bool isValidSemesterDate(std::string startDate, std::string endDate, Semesters* semesterHead, int schoolYear);

void addCourseToSemester(Semesters*& semestersHead, int startYear);
void appendNewCourse(Semesters*& semestersHead, std::string newCourseData, int schoolYear);
void appendNewCourseFile(std::fstream& dataFile, Course* newCourseNode, int schoolYear);
void appendBatchCourse(Semesters*& semestersHead, SNode* batch, int schoolYear);
void updateCourse(Semesters* semestersHead, int schoolYear);
void updateCourseNext(Course*& currentCourseHead, std::fstream& currentCourseFile, std::string& courseID);
void deleteCourse(Semesters* semestersHead, int schoolYear);
void deleteCourseNext(Course*& currentCourseHead, std::fstream& currentCourseFile, std::string& courseID);
void readCourseData(Course*& courseHead, std::string courseData);
bool courseFormatCheck(std::string courseData);
bool courseListSearchBool(Course* courseHead, std::string courseID);
void createCourseReg(CourseReg*& courseRegHead, std::fstream& dataFile, int schoolYear, Semesters* semestersHead);
bool courseRegSearchBool(CourseReg* courseHead, int schoolYear, int semester);

bool checkInputFormatSC(std::fstream& inputFile, int mode);