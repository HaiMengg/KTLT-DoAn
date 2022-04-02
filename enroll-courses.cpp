#include <iostream>
#include <sstream>
#include <fstream>
#include <locale>
#include <iomanip>
#include <time.h>
#include <string>

// Get current year
int getYear()
{
    std::time_t result = std::time(nullptr);
    std::istringstream iss(ctime(&result));

    iss.ignore(20);
    int year;
    iss >> year;
    return year - 1;
}

// Check if current time is between startDate and endDate
bool checkSemester(std::string start, std::string end)
{
    time_t currentDate;
    currentDate = time(NULL);

    time_t startDate, endDate;

    std::tm t = {};
    std::istringstream ssStart(start);
    ssStart >> std::get_time(&t, "%d/%m/%Y");
    startDate = std::mktime(&t);

    t = {};
    std::istringstream ssEnd(end);
    ssEnd >> std::get_time(&t, "%d/%m/%Y");
    endDate = std::mktime(&t);

    if (startDate < currentDate && currentDate < endDate) return true;
    return false;
}

// Get current semester based on current date
int getSemester(std::fstream &input)
{
    std::string str;
    std::getline(input, str);

    while (!input.eof())
    {
        std::string sem, startDate, endDate;
        std::getline(input, sem, ',');
        std::getline(input, startDate, ',');
        std::getline(input, endDate);

        if (checkSemester(startDate, endDate))
        return atoi(sem.c_str());
    }

    return 0;
}

// Replace all same substrings with another string
void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if (from.empty()) return;

    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

// Show a single course node
void showCourseNode(Course* data)
{
    Course* cur = data;

    replaceAll(cur -> daySession, "|", ", ");
    replaceAll(cur -> daySession, "-S1", " (07:30-09:10)");
    replaceAll(cur -> daySession, "-S2", " (09:30-11:10)");
    replaceAll(cur -> daySession, "-S3", " (13:30-15:10)");
    replaceAll(cur -> daySession, "-S4", " (15:30-17:10)");

    std::cout << std::setw(15) << cur -> courseId;
    std::cout << std::setw(22) << cur -> courseName;
    std::cout << std::setw(25) << cur -> teacherName;
    std::cout << std::setw(10) << cur -> numOfCredits;
    std::cout << std::setw(20) << cur -> daySession << std::endl;
}

// Show available courses in a semester
void showCourses(Course* data)
{
    std::cout << "----------------\n";
    std::cout << std::left
    << std::setw(15) << "ID"
    << std::setw(22) << "Course"
    << std::setw(25) << "Teacher"
    << std::setw(10) << "Credits"
    << std::setw(20) << "Sessions" << std::endl;

    Course* cur = data;
    while (cur != nullptr)
    {
        showCourseNode(cur);
        cur = cur -> nodeNext;
    }

    std::cout << "----------------\n";
}

// Enroll in a course
void enrollCourse(Login &data)
{
    std::cout << "Input ID of a course to enroll in (or input 1 to go back): ";
    std::string enrollId;
    std::cin >> enrollId;

    if (enrollId == "1")
    {
        std::cout << "----------------\n";
        studentMenu(data);
        return;
    }

    Course* cur = data.course;
    bool check = false;
    std::string enrolled, sessions;
    int amount = 0;

    StudentCourse* curCourse = data.curStudent -> studentCourseHead;
    while (curCourse != nullptr)
    {
        if (std::to_string(curCourse -> schoolYear) == data.curStudent -> startYear) break;
        curCourse = curCourse -> nodeNext;
    }

    if (data.semester == 1)
    enrolled = curCourse -> sem1Courses;

    else if (data.semester == 2)
    enrolled = curCourse -> sem2Courses;

    else
    enrolled = curCourse -> sem3Courses;

    if (enrolled != "")
    {
        std::istringstream iss(enrolled);
        std::string item;
        while (std::getline(iss, item, '-')) {
            amount++;
            cur = data.course;
            while (cur != nullptr)
            {
                if (cur -> courseId == item)
                {
                    sessions += cur -> daySession + "|";
                    break;
                }
                cur = cur -> nodeNext;
            }
        }
    }

    if (amount == 5)
    {
        std::cout << "You have reached the maximum amount of courses to enroll in a semester.\n";
        std::cout << "----------------\n";
        studentMenu(data);
        return;
    }

    bool reason = true;
    cur = data.course;

    while (cur != nullptr)
    {
        if (cur -> courseId == enrollId)
        {
            if (sessions.find(cur -> daySession) != std::string::npos)
            {
                reason = false;
                break;
            }

            if (data.semester == 1)
            curCourse -> sem1Courses += "-" + cur -> courseId;

            else if (data.semester == 2)
            curCourse -> sem2Courses += "-" + cur -> courseId;

            else
            curCourse -> sem3Courses += "-" + cur -> courseId;

            writeStudent(data.student);

            Student* curCourseStudent = cur -> courseStudentHead;
            while (curCourseStudent != nullptr && curCourseStudent -> nodeNext != nullptr)
            {
                curCourseStudent = curCourseStudent -> nodeNext;
            }

            Student* newStudent = new Student;
            newStudent -> studentID = data.curStudent -> studentID;
            newStudent -> firstName = data.curStudent -> firstName;
            newStudent -> lastName = data.curStudent -> lastName;
            newStudent -> dob = data.curStudent -> dob;
            newStudent -> gender = data.curStudent -> gender;
            newStudent -> socialID = data.curStudent -> socialID;
            newStudent -> classID = data.curStudent -> classID;

            if (curCourseStudent == nullptr)
            {
                cur -> courseStudentHead = new Student;
                cur -> courseStudentHead = newStudent;
                cur -> courseStudentHead -> nodeNext = nullptr;
            }

            else
            {
                curCourseStudent -> nodeNext = newStudent;
                newStudent -> nodeNext = nullptr;
                newStudent -> nodePrev = curCourseStudent;
            }

            writeCourseStudent(data.course, data.curStudent -> startYear, data.semester);

            std::cout << "Course enrolled!\n" << "----------------\n";
            studentMenu(data);

            return;
        }
        cur = cur -> nodeNext;
    }

    if (reason) std::cout << "Could not find that course. Please try again.\n";
    else std::cout << "You have already enrolled in this course or another one with conflicting sessions. Please try again.\n";

    enrollCourse(data);
}

// View courses that are enrolled
void viewCourse(Login data)
{
    Course* cur;
    std::string enrolled;

    StudentCourse* curCourse = data.curStudent -> studentCourseHead;
    while (curCourse != nullptr)
    {
        if (std::to_string(curCourse -> schoolYear) == data.curStudent -> startYear) break;
        curCourse = curCourse -> nodeNext;
    }

    if (data.semester == 1)
    enrolled = curCourse -> sem1Courses;

    else if (data.semester == 2)
    enrolled = curCourse -> sem2Courses;

    else
    enrolled = curCourse -> sem3Courses;

    if (enrolled == "")
    {
        std::cout << "----------------\n"
        << "Nothing to see here.\n"
        << "----------------\n";
        studentMenu(data);
        return;
    }

    std::cout << "----------------\n";
    std::cout << std::left
    << std::setw(15) << "ID"
    << std::setw(22) << "Course"
    << std::setw(25) << "Teacher"
    << std::setw(10) << "Credits"
    << std::setw(20) << "Sessions" << std::endl;

    std::istringstream iss(enrolled);
    std::string item;
    while (std::getline(iss, item, '-')) {
        cur = data.course;
        while (cur != nullptr)
        {
            if (cur -> courseId == item)
            {
                showCourseNode(cur);
            }
            cur = cur -> nodeNext;
        }
    }

    std::cout << "----------------\n";
    studentMenu(data);
}

// Remove an enrolled course
void removeCourse(Login &data)
{
    std::cout << "Input ID of an enrolled course to remove (or input 1 to go back): ";
    std::string removeId;
    std::cin >> removeId;

    if (removeId == "1")
    {
        std::cout << "----------------\n";
        return studentMenu(data);
    }

    std::string enrolled;
    StudentCourse* curCourse = data.curStudent -> studentCourseHead;
    while (curCourse != nullptr)
    {
        if (std::to_string(curCourse -> schoolYear) == data.curStudent -> startYear) break;
        curCourse = curCourse -> nodeNext;
    }

    if (data.semester == 1)
    enrolled = curCourse -> sem1Courses;

    else if (data.semester == 2)
    enrolled = curCourse -> sem2Courses;

    else
    enrolled = curCourse -> sem3Courses;

    std::istringstream iss(enrolled);
    std::string item;
    while (std::getline(iss, item, '-')) {
        if (item == removeId)
        {
            replaceAll(enrolled, item, "");
            replaceAll(enrolled, "--", "-");

            if (data.semester == 1)
            curCourse -> sem1Courses = enrolled;

            else if (data.semester == 2)
            curCourse -> sem2Courses = enrolled;

            else
            curCourse -> sem3Courses = enrolled;

            writeStudent(data.student);

            Course* cur = data.course;
            while (cur != nullptr)
            {
                if (cur -> courseId == removeId)
                {
                    Student* curCourseStudent = cur -> courseStudentHead;
                    while (curCourseStudent != nullptr)
                    {
                        if (curCourseStudent -> studentID == data.curStudent -> studentID)
                        {
                            if (curCourseStudent == cur -> courseStudentHead)
                            {
                                cur -> courseStudentHead = curCourseStudent -> nodeNext;
                                delete curCourseStudent;
                                break;
                            }

                            curCourseStudent -> nodePrev -> nodeNext = curCourseStudent -> nodeNext;
                            curCourseStudent -> nodeNext -> nodePrev = curCourseStudent -> nodePrev;
                            delete curCourseStudent;
                            break;
                        }
                        curCourseStudent = curCourseStudent -> nodeNext;
                    }
                    break;
                }
                cur = cur -> nodeNext;
            }

            writeCourseStudent(data.course, data.curStudent -> startYear, data.semester);

            std::cout << "Course removed!\n" << "----------------\n";
            studentMenu(data);
            return;
        }
    }

    std::cout << "Could not find that course. Please try again.\n";
    removeCourse(data);
}