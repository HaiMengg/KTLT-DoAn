#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include <ctime>

#include "Login-Logout/struct.h"
#include "Linked-List/linkedlist.h"
#include "Functions/func.h"

int main() {
    Node allData;
    std::fstream schoolYearData("data/schoolyear.csv", std::ios::in | std::ios::out | std::ios::app);
    std::fstream classData("data/class.csv", std::ios::in | std::ios::out | std::ios::app);
    std::fstream studentData("data/student.csv", std::ios::in | std::ios::out | std::ios::app);
    std::fstream semesterData("data/semester.csv", std::ios::in | std::ios::out | std::ios::app);
    std::fstream courseRegData("data/coursereg.csv", std::ios::in | std::ios::out);
    createList(allData.schoolYearHead, schoolYearData);
    createList(allData.classesHead, classData);
    createList(allData.studentHead, studentData);
    createList(allData.semesterHead, semesterData);
    createList(allData.courseRegHead, courseRegData);

    std::time_t time = std::time(0);
    std::tm* now = std::localtime(&time);
    std::string currentDate = std::to_string(now->tm_mday) + "/" + std::to_string(now->tm_mon + 1) + "/" + std::to_string(now->tm_year + 1900);
    
    loginInit(allData, schoolYearData, classData, studentData, semesterData, courseRegData, currentDate);

    destructList(allData);
}