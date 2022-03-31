#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>

#include "Login-Logout/struct.h"
#include "Linked-List/linkedlist.h"

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
    
    loginInit(allData, schoolYearData, classData, studentData, semesterData);

    destructList(allData);
}