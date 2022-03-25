#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "struct.h"

// Read staff.csv
void readStaff(Staff* &data, std::fstream &input)
{
    // Track current pointer
    Staff* cur = data;

    // Ignore first line
    std::string str;
    std::getline(input, str);

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
void readTeacher(Teacher* &data, std::fstream &input)
{
    // Track current pointer
    Teacher* cur = data;

    // Ignore first line
    std::string str;
    std::getline(input, str);

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
void readStudent(Student* &data, std::fstream &input)
{
    // Track current pointer
    Student* cur = data;

    // Ignore first line
    std::string str;
    std::getline(input, str);

    // Get data from student.csv
    while (true)
    {
        getline(input, cur -> usr, ',');
        getline(input, cur -> pwd, ',');
        getline(input, cur -> studentID, ',');
        getline(input, cur -> firstName, ',');
        getline(input, cur -> lastName, ',');
        getline(input, cur -> dob, ',');
        getline(input, cur -> gender, ',');
        getline(input, cur -> socialID, ',');
        getline(input, cur -> startYear, ',');
        getline(input, cur -> classID, ',');
        getline(input, cur -> studentCoursesSem1, '|');
        getline(input, cur -> studentCoursesSem2, '|');
        getline(input, cur -> studentCoursesSem3);

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
    std::fstream output;
    output.open("staff.csv", std::ios::out);
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
        output << std::endl;

        cur = cur -> nodeNext;
    }
}

// Write to teacher.csv
void writeTeacher(Teacher* data)
{
    std::fstream output;
    output.open("teacher.csv", std::ios::out);
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
        output << std::endl;

        cur = cur -> nodeNext;
    }
}

// Write to student.csv
void writeStudent(Student* data)
{
    std::fstream output;
    output.open("student.csv", std::ios::out);
    output << "usr,pwd,studentID,firstName,lastName,dob,gender,socialID,startYear,classID,coursesID\n";

    Student* cur = data;
    while (cur != nullptr)
    {
        output << cur -> usr << ","
        << cur -> pwd << ","
        << cur -> studentID << ","
        << cur -> firstName << ","
        << cur -> lastName << ","
        << cur -> dob << ","
        << cur -> gender << ","
        << cur -> socialID << ","
        << cur -> startYear << ","
        << cur -> classID << ",";

        if (cur -> studentCoursesSem1[0] == '-')
        cur -> studentCoursesSem1.erase(0, 1);

        if (cur -> studentCoursesSem2[0] == '-')
        cur -> studentCoursesSem2.erase(0, 1);

        if (cur -> studentCoursesSem3[0] == '-')
        cur -> studentCoursesSem3.erase(0, 1);

        output << cur -> studentCoursesSem1 << "|"
        << cur -> studentCoursesSem2 << "|"
        << cur -> studentCoursesSem3;

        // if (data.semester == 1)
        // output << cur -> studentCoursesSem1;

        // else if (data.semester == 2)
        // output << cur -> studentCoursesSem2;

        // else
        // output << cur -> studentCoursesSem3;

        if (cur -> nodeNext != nullptr)
        output << std::endl;

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