#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>

#include "Login-Logout/struct.h"
#include "Linked-List/linkedlist.h"
#include "Functions/func.h"

int main() {
    Node allData;
    std::fstream schoolYearData("data/schoolyear.csv", std::ios::in | std::ios::out | std::ios::app);
    std::fstream classData("data/class.csv", std::ios::in | std::ios::out | std::ios::app);
    std::fstream studentData("data/student.csv", std::ios::in | std::ios::out | std::ios::app);
    std::fstream semesterData("data/semester.csv", std::ios::in | std::ios::out | std::ios::app);
    createList(allData.schoolYearHead, schoolYearData);
    createList(allData.classesHead, classData);
    createList(allData.studentHead, studentData);
    createList(allData.semesterHead, semesterData);

    std::string currentDate;
    updateDate(currentDate);
    
    loginInit(allData, schoolYearData, classData, studentData, semesterData, currentDate);

    destructList(allData);
}