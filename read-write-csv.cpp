#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "struct.h"

// Read course.csv
void readCourse(Course* &data, std::fstream &input, int year, int sem)
{
    // Track current pointer
    Course* cur = data;

    // Ignore first line
    std::string str;
    std::getline(input, str);

    // Get data
    while (true)
    {
        getline(input, cur -> courseId, ',');
        getline(input, cur -> courseName, ',');
        getline(input, cur -> teacherName, ',');
        getline(input, cur -> numOfCredits, ',');
        getline(input, str, ',');
        getline(input, cur -> daySession);

        std::fstream inputStudent;
        inputStudent.open(
            "data/" + std::to_string(year) + "/semesters/" + std::to_string(sem) + "/"
            + cur -> courseId + "/student.csv",
            std::ios::in
        );
        std::getline(inputStudent, str);

        if (!inputStudent.eof())
        {
            cur -> courseStudentHead = new Student;
            Student* curCourseStudent = cur -> courseStudentHead;

            while (true)
            {
                getline(inputStudent, curCourseStudent -> studentID, ',');
                getline(inputStudent, curCourseStudent -> firstName, ',');
                getline(inputStudent, curCourseStudent -> lastName, ',');
                getline(inputStudent, curCourseStudent -> dob, ',');
                getline(inputStudent, curCourseStudent -> gender, ',');
                getline(inputStudent, curCourseStudent -> socialID, ',');
                getline(inputStudent, curCourseStudent -> classID);

                if (inputStudent.eof())
                {
                    curCourseStudent -> nodeNext = nullptr;
                    break;
                }

                curCourseStudent -> nodeNext = new Student;
                curCourseStudent -> nodeNext -> nodePrev = curCourseStudent;
                curCourseStudent = curCourseStudent -> nodeNext;
            }
        }

        if (input.eof())
        {
            cur -> nodeNext = nullptr;
            break;
        }

        cur -> nodeNext = new Course;
        cur -> nodeNext -> nodePrev = cur;
        cur = cur -> nodeNext;   
    }
    cur = nullptr;
}

// Read student course
void readStudentCourse(std::string courses, std::string schoolYear, StudentCourse* &head)
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
        readStudentCourse(rawCourses, schoolYear, cur -> studentCourseHead);

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

// Write to each course.csv
void writeCourseStudent(Course* data, std::string schoolYear, int semester)
{
    Course* cur = data;
    while (cur != nullptr)
    {
        std::fstream output;
        output.open(
            "data/" + schoolYear + "/semesters/" + std::to_string(semester) + "/"
            + cur -> courseId + "/student.csv",
            std::ios::out
        );
        output << "studentID,firstName,lastName,dob,gender,socialID,classID";

        Student* curStudent = cur -> courseStudentHead;

        if (curStudent != nullptr) output << std::endl;
        while (curStudent != nullptr)
        {
            output << curStudent -> studentID << ","
            << curStudent -> firstName << ","
            << curStudent -> lastName << ","
            << curStudent -> dob << ","
            << curStudent -> gender << ","
            << curStudent -> socialID << ","
            << curStudent -> classID;

            if (curStudent -> nodeNext != nullptr)
            output << std::endl;

            curStudent = curStudent -> nodeNext;
        }

        cur = cur -> nodeNext;
    }
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

            if (curCourse -> sem1Courses[curCourse -> sem1Courses.size() - 1] == '-')
            curCourse -> sem1Courses.erase(curCourse -> sem1Courses.size() - 1, 1);

            if (curCourse -> sem2Courses[curCourse -> sem2Courses.size() - 1] == '-')
            curCourse -> sem2Courses.erase(curCourse -> sem2Courses.size() - 1, 1);

            if (curCourse -> sem3Courses[curCourse -> sem3Courses.size() - 1] == '-')
            curCourse -> sem3Courses.erase(curCourse -> sem3Courses.size() - 1, 1);

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