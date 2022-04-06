#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "struct.h"

void loginInit(Node& node, std::fstream& sY, std::fstream& cl, std::fstream& stu, std::fstream& semes, std::fstream& cR, std::string& currentDate) {
    // Get CSV files
    std::fstream staff, teacher, student, course;
    staff.open("data/staff.csv", std::ios::in);
    teacher.open("data/teacher.csv", std::ios::in);
    student.open("data/student.csv", std::ios::in);

    // Linked lists
    Staff* staffData = new Staff;
    Teacher* teacherData = new Teacher;
    Student* studentData = new Student;
    Course* courseData = nullptr;
    CourseScore* courseSem1Data = nullptr;
    CourseScore* courseSem2Data = nullptr;
    CourseScore* courseSem3Data = nullptr;

    // Read CSV files
    int sem, schoolYear;
    readStaff(staffData, staff);
    readTeacher(teacherData, teacher);
    readStudent(studentData, student);
    updateCourseHead(courseData, schoolYear, sem, currentDate, node.semesterHead);
    if (sem != -1) {
        readScoreboard(courseSem1Data, schoolYear, 1);
        readScoreboard(courseSem2Data, schoolYear, 2);
        readScoreboard(courseSem3Data, schoolYear, 3);
    }

    // Log in to the system
    Login data;
    data.staff = staffData;
    data.teacher = teacherData;
    data.student = node.studentHead;
    data.course = courseData;
    data.year = schoolYear;
    data.semester = sem;
    if (sem == 1) data.courseScore = courseSem1Data;
    else if (sem == 2) data.courseScore = courseSem2Data;
    else if (sem == 3) data.courseScore = courseSem3Data;
    else data.courseScore = nullptr;
    printCurrentDate(currentDate, node.semesterHead);
    loginCheck(data, node, sY, cl, stu, semes, cR, currentDate);
    deleteData(data);
}

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

// Read scoreboard.csv
void readScoreboard(CourseScore* &data, int year, int semester)
{
    std::fstream input;
    std::string dir = "data/" + std::to_string(year) + "/semesters/"
    + std::to_string(semester) + "/scoreboard.csv";

    input.open(dir, std::ios::in);
    if (!input.good()) {
        return;
    }

    std::string str;
    getline(input, str);

    if (input.eof()) {
        input.close();
        return;
    }

    data = new CourseScore;
    CourseScore* curCourseScore = data;
    while (true)
    {
        getline(input, str, ',');
        getline(input, curCourseScore -> courseID, ',');
        getline(input, curCourseScore -> studentID, ',');
        getline(input, curCourseScore -> fullname, ',');
        getline(input, curCourseScore -> midterm, ',');
        getline(input, curCourseScore -> final, ',');
        getline(input, curCourseScore -> other, ',');
        getline(input, curCourseScore -> total);

        if (input.eof())
        {
            curCourseScore -> nodeNext = nullptr;
            break;
        }

        curCourseScore -> nodeNext = new CourseScore;
        curCourseScore = curCourseScore -> nodeNext;
    }
    input.close();
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
    output.open("data/staff.csv", std::ios::out);
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
    output.open("data/teacher.csv", std::ios::out);
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
    output.open("data/student.csv", std::ios::out);
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

// Write to scoreboard.csv
void writeScoreboard(CourseScore* data, int year, int semester)
{
    std::fstream output;
    std::string dir = "data/" + std::to_string(year) + "/semesters/"
    + std::to_string(semester) + "/scoreboard.csv";

    output.open(dir, std::ios::out);
    if (!output.good()) return;

    output << "no,courseID,studentID,fullname,midtermmark,finalmark,othermark,totalmark\n";

    int count = 1;
    CourseScore* curCourseScore = data;
    while (curCourseScore != nullptr)
    {
        output << count << ","
        << curCourseScore -> courseID << ","
        << curCourseScore -> studentID << ","
        << curCourseScore -> fullname << ","
        << curCourseScore -> midterm << ","
        << curCourseScore -> final << ","
        << curCourseScore -> other << ","
        << curCourseScore -> total;

        if (curCourseScore -> nodeNext != nullptr)
        output << std::endl;

        count++;
        curCourseScore = curCourseScore -> nodeNext;
    }
}

// Delete data
void deleteData(Login &data)
{
    Staff *fCur = data.staff, *fDel;
    Teacher *rCur = data.teacher, *rDel;
    Student *tCur = data.student, *tDel;
    Course *cCur = data.course, *cDel;
    CourseScore *csCur = data.courseScore, *csDel;

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

    while (csCur != nullptr)
    {
        csDel = csCur -> nodeNext;
        delete csCur;
        csCur = csDel;
    }

    data.staff = nullptr;
    data.teacher = nullptr;
    data.staff = nullptr;
    data.course = nullptr;
    data.courseScore = nullptr;
}