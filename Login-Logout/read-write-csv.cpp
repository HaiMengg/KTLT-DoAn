#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "struct.h"

// Read student's courses
void readCourse(std::string courses, std::string schoolYear, StudentCourse* &head)
{
    int count = 3;
    StudentCourse* headCourse = new StudentCourse;
    StudentCourse* curCourse = headCourse;

    std::istringstream iss(courses);
    std::string item;
    while (getline(iss, item, '|'))
    {
        if (count % 3 == 0)
        {
            if (count != 3)
            {
                curCourse -> nodeNext = new StudentCourse;
                curCourse -> nodeNext -> nodePrev = curCourse;
                curCourse = curCourse -> nodeNext;
            }

            curCourse -> schoolYear = atoi(schoolYear.c_str());
            curCourse -> sem1Courses = item;
        }

        if (count % 3 == 1)
        curCourse -> sem2Courses = item;

        if (count % 3 == 2)
        curCourse -> sem3Courses = item;

        count++;
    }

    curCourse -> nodeNext = nullptr;
    head = headCourse;
}

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

        std::string schoolYear = cur -> startYear;
        std::string rawCourses;
        getline(input, rawCourses);
        readCourse(rawCourses, schoolYear, cur -> studentCourseHead);

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

        StudentCourse* curCourse = cur -> studentCourseHead;
        while (curCourse != nullptr)
        {
            if (curCourse -> sem1Courses[0] == '-')
            curCourse -> sem1Courses.erase(0, 1);

            if (curCourse -> sem2Courses[0] == '-')
            curCourse -> sem2Courses.erase(0, 1);

            if (curCourse -> sem3Courses[0] == '-')
            curCourse -> sem3Courses.erase(0, 1);

            if (curCourse != cur -> studentCourseHead)
            output << "|";

            output << curCourse -> sem1Courses << "|"
            << curCourse -> sem2Courses << "|"
            << curCourse -> sem3Courses;

            curCourse = curCourse -> nodeNext;
        }

        if (cur -> nodeNext != nullptr)
        output << std::endl;

        cur = cur -> nodeNext;
    }
}

// Delete data
void deleteData(Login &data)
{
    Staff *fCur = data.staff, *fDel;
    Teacher *rCur = data.teacher, *rDel;
    Student *tCur = data.student, *tDel;
    Course *cCur = data.course, *cDel;

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

    while (cCur != nullptr)
    {
        cDel = cCur -> nodeNext;
        delete cCur;
        cCur = cDel;
    }

    data.staff = nullptr;
    data.teacher = nullptr;
    data.staff = nullptr;
    data.course = nullptr;
}