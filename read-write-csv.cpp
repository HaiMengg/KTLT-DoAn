#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// Struct for staff
struct STAFF
{
    string staffusr, staffpwd, firstname, lastname, dob, gender;
    STAFF* next;
};

// Struct for teacher
struct TEACHER
{
    string teachusr, teachpwd, firstname, lastname, dob, gender;
    TEACHER* next;
};

// Struct for student
struct STUDENT
{
    string studentusr, studentpwd, studentID, firstname, lastname, dob, gender, socialID, startyear, classID, CoursesID;
    STUDENT* next;
};

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
        getline(input, cur -> teachusr, ',');
        getline(input, cur -> teachpwd, ',');
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