#include <string>
#pragma once

struct STAFF
{
    string staffusr, staffpwd, firstname, lastname, dob, gender;
    STAFF* next;
};

struct TEACHER
{
    string teacherusr, teacherpwd, firstname, lastname, dob, gender;
    TEACHER* next;
};

struct STUDENT
{
    string studentusr, studentpwd, studentID, firstname, lastname, dob, gender, socialID, startyear, classID, CoursesID;
    STUDENT* next;
};

struct LOGIN
{
    STAFF* staff;
    TEACHER* teacher;
    STUDENT* student;
    string username, password;
    int identity = 0;
};

void loginCheck(LOGIN &data);
void loginMenu(LOGIN &data);
void viewInfo(LOGIN data);
void logOut(LOGIN &data);