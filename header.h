#include <string>
#include <fstream>
#pragma once

struct STAFF
{
    STAFF* nodePrev = nullptr;
    std::string usr, pwd, firstName, lastName, gender, dob;
    STAFF* nodeNext;
};

struct TEACHER
{
    TEACHER* nodePrev = nullptr;
    std::string usr, pwd, firstName, lastName, gender, dob;
    TEACHER* nodeNext;
};

struct STUDENT
{
    STUDENT* nodePrev = nullptr;
    std::string usr, pwd, firstName, lastName, gender, dob, socialID, startYear, classID;
    STUDENT* nodeNext;
};

struct LOGIN
{
    STAFF* staff;
    TEACHER* teacher;
    STUDENT* student;
    std::string username, password;
    int identity = 0;
};

void loginCheck(LOGIN &data);
void loginMenu(LOGIN &data);
void viewInfo(LOGIN data);
void changePassword(LOGIN &data);
void logOut(LOGIN &data);