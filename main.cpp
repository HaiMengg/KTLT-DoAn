#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>

#include "Login-Logout/struct.h"
#include "Linked-List/linkedlist.h"

int main() {
    Login loginData;
    Node allData;
    std::fstream schoolYearData("data/schoolyear.csv", std::ios::in | std::ios::out | std::ios::app);
    std::fstream classData("data/class.csv", std::ios::in | std::ios::out | std::ios::app);
    std::fstream studentData("data/student.csv", std::ios::in | std::ios::out | std::ios::app);
    std::fstream semesterData("data/semester.csv", std::ios::in | std::ios::out | std::ios::app);
    loginCheck(loginData, allData, schoolYearData, classData, studentData, semesterData);
}