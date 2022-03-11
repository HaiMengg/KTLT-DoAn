#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#include "header.h"

// Read staff.csv
void readStaff(STAFF* &data, fstream &input)
{
    // Track current pointer
    STAFF* cur = data;

    // Ignore first line
    string str;
    getline(input, str);

    // Get data
    while (!input.eof())
    {
        getline(input, cur -> staffusr, ',');
        getline(input, cur -> staffpwd, ',');
        getline(input, cur -> firstname, ',');
        getline(input, cur -> lastname, ',');
        getline(input, cur -> dob, ',');
        getline(input, cur -> gender);

        cur -> next = new STAFF;
        cur = cur -> next;   
    }
    cur = nullptr;
}

// Read teacher.csv
void readTeacher(TEACHER* &data, fstream &input)
{
    // Track current pointer
    TEACHER* cur = data;

    // Ignore first line
    string str;
    getline(input, str);

    // Get data
    while (!input.eof())
    {
        getline(input, cur -> teacherusr, ',');
        getline(input, cur -> teacherpwd, ',');
        getline(input, cur -> firstname, ',');
        getline(input, cur -> lastname, ',');
        getline(input, cur -> dob, ',');
        getline(input, cur -> gender);

        cur -> next = new TEACHER;
        cur = cur -> next;   
    }
    cur = nullptr;
}

// Read student.csv
void readStudent(STUDENT* &data, fstream &input)
{
    // Track current pointer
    STUDENT* cur = data;

    // Ignore first line
    string str;
    getline(input, str);

    // Get data from student.csv
    while (!input.eof())
    {
        getline(input, cur -> studentusr, ',');
        getline(input, cur -> studentpwd, ',');
        getline(input, cur -> studentID, ',');
        getline(input, cur -> firstname, ',');
        getline(input, cur -> lastname, ',');
        getline(input, cur -> dob, ',');
        getline(input, cur -> gender, ',');
        getline(input, cur -> socialID, ',');
        getline(input, cur -> startyear, ',');
        getline(input, cur -> classID, ',');
        getline(input, cur -> CoursesID);

        cur -> next = new STUDENT;
        cur = cur -> next;
    }
    cur = nullptr;
}

// Write to staff.csv
void writeStaff(STAFF* data, fstream &output)
{
    output << "staffusr,staffpwd,firstname,lastname,dob,gender\n";
    STAFF* cur = data;

    while (cur != nullptr)
    {
        output << cur -> staffusr << ","
        << cur -> staffpwd << ","
        << cur -> firstname << ","
        << cur -> lastname << ","
        << cur -> dob << ","
        << cur -> gender << endl;
        cur = cur -> next;
    }
}

// Write to teacher.csv
void writeTeacher(TEACHER* data, fstream &output)
{
    output << "teacherusr,teacherpwd,firstname,lastname,dob,gender\n";
    TEACHER* cur = data;

    while (cur != nullptr)
    {
        output << cur -> teacherusr << ","
        << cur -> teacherpwd << ","
        << cur -> firstname << ","
        << cur -> lastname << ","
        << cur -> dob << ","
        << cur -> gender << endl;
        cur = cur -> next;
    }
}

// Write to student.csv
void writeStudent(STUDENT* data, fstream &output)
{
    output << "studentusr,studentpwd,studentID,firstname,lastname,dob,gender,socialID,startyear,classID,CoursesID\n";
    STUDENT* cur = data;

    while (cur != nullptr)
    {
        output << cur -> studentusr << ","
        << cur -> studentpwd << ","
        << cur -> studentID << ","
        << cur -> firstname << ","
        << cur -> lastname << ","
        << cur -> dob << ","
        << cur -> gender << ","
        << cur -> socialID << ","
        << cur -> startyear << ","
        << cur -> classID << ","
        << cur -> CoursesID << endl;
        cur = cur -> next;
    }
}

// Delete data
void deleteData(STAFF* &data, TEACHER* &teacherData, STUDENT* &studentData)
{
    STAFF *fCur = data, *fDel;
    TEACHER *rCur = teacherData, *rDel;
    STUDENT *tCur = studentData, *tDel;

    while (fCur != nullptr)
    {
        fDel = fCur -> next;
        delete fCur;
        fCur = fDel;
    }

    while (rCur != nullptr)
    {
        rDel = rCur -> next;
        delete rCur;
        rCur = rDel;
    }

    while (tCur != nullptr)
    {
        tDel = tCur -> next;
        delete tCur;
        tCur = tDel;
    }

    data = nullptr;
    teacherData = nullptr;
    studentData = nullptr;
}