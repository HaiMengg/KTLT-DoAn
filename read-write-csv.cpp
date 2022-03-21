#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#include "struct.h"

// Read staff.csv
void readStaff(Staff* &data, fstream &input)
{
    // Track current pointer
    Staff* cur = data;

    // Ignore first line
    string str;
    getline(input, str);

    // Get data
    while (true)
    {
        getline(input, cur -> usr, ',');
        getline(input, cur -> pwd, ',');
        getline(input, cur -> firstName, ',');
        getline(input, cur -> lastName, ',');
        getline(input, cur -> dob, ',');
        getline(input, cur -> gender);

        if (input.eof())
        {
            cur -> nodeNext = nullptr;
            break;
        }

        cur -> nodeNext = new Staff;
        cur -> nodeNext -> nodePrev = cur;
        cur = cur -> nodeNext;   
    }
    cur = nullptr;
}

// Read teacher.csv
void readTeacher(Teacher* &data, fstream &input)
{
    // Track current pointer
    Teacher* cur = data;

    // Ignore first line
    string str;
    getline(input, str);

    // Get data
    while (true)
    {
        getline(input, cur -> usr, ',');
        getline(input, cur -> pwd, ',');
        getline(input, cur -> firstName, ',');
        getline(input, cur -> lastName, ',');
        getline(input, cur -> dob, ',');
        getline(input, cur -> gender);

        if (input.eof())
        {
            cur -> nodeNext = nullptr;
            break;
        }

        cur -> nodeNext = new Teacher;
        cur -> nodeNext -> nodePrev = cur;
        cur = cur -> nodeNext;   
    }
    cur = nullptr;
}

// Read student.csv
void readStudent(Student* &data, fstream &input)
{
    // Track current pointer
    Student* cur = data;

    // Ignore first line
    string str;
    getline(input, str);

    // Get data from student.csv
    while (true)
    {
        getline(input, cur -> usr, ',');
        getline(input, cur -> pwd, ',');
        getline(input, cur -> firstName, ',');
        getline(input, cur -> lastName, ',');
        getline(input, cur -> dob, ',');
        getline(input, cur -> gender, ',');
        getline(input, cur -> socialID, ',');
        getline(input, cur -> startYear, ',');
        getline(input, cur -> classID, ',');

        if (input.eof())
        {
            cur -> nodeNext = nullptr;
            break;
        }

        cur -> nodeNext = new Student;
        cur -> nodeNext -> nodePrev = cur;
        cur = cur -> nodeNext;
    }
    cur = nullptr;
}

// Write to staff.csv
void writeStaff(Staff* data)
{
    fstream output;
    output.open("staff.csv", ios::out);
    output << "usr,pwd,firstName,lastName,dob,gender\n";

    Staff* cur = data;
    while (cur != nullptr)
    {
        output << cur -> usr << ","
        << cur -> pwd << ","
        << cur -> firstName << ","
        << cur -> lastName << ","
        << cur -> dob << ","
        << cur -> gender;

        if (cur -> nodeNext != nullptr)
        output << endl;

        cur = cur -> nodeNext;
    }
}

// Write to teacher.csv
void writeTeacher(Teacher* data)
{
    fstream output;
    output.open("teacher.csv", ios::out);
    output << "usr,pwd,firstName,lastName,dob,gender\n";

    Teacher* cur = data;
    while (cur != nullptr)
    {
        output << cur -> usr << ","
        << cur -> pwd << ","
        << cur -> firstName << ","
        << cur -> lastName << ","
        << cur -> dob << ","
        << cur -> gender;

        if (cur -> nodeNext != nullptr)
        output << endl;

        cur = cur -> nodeNext;
    }
}

// Write to student.csv
void writeStudent(Student* data)
{
    fstream output;
    output.open("student.csv", ios::out);
    output << "usr,pwd,studentID,firstName,lastName,dob,gender,socialID,startYear,classID,CoursesID\n";

    Student* cur = data;
    while (cur != nullptr)
    {
        output << cur -> usr << ","
        << cur -> pwd << ","
        << cur -> firstName << ","
        << cur -> lastName << ","
        << cur -> dob << ","
        << cur -> gender << ","
        << cur -> socialID << ","
        << cur -> startYear << ","
        << cur -> classID;

        if (cur -> nodeNext != nullptr)
        output << endl;

        cur = cur -> nodeNext;
    }
}

// Delete data
void deleteData(Staff* &data, Teacher* &teacherData, Student* &studentData)
{
    Staff *fCur = data, *fDel;
    Teacher *rCur = teacherData, *rDel;
    Student *tCur = studentData, *tDel;

    while (fCur != nullptr)
    {
        fDel = fCur -> nodeNext;
        delete fCur;
        fCur = fDel;
    }

    while (rCur != nullptr)
    {
        rDel = rCur -> nodeNext;
        delete rCur;
        rCur = rDel;
    }

    while (tCur != nullptr)
    {
        tDel = tCur -> nodeNext;
        delete tCur;
        tCur = tDel;
    }

    data = nullptr;
    teacherData = nullptr;
    studentData = nullptr;
}