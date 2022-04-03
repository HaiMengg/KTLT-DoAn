#include <iostream>
#include <fstream>
#include <string>

#include "struct.h"

// Calculate total mark
float getTotalMark(float mid, float final, float other)
{
    return (other + mid * 2 + final * 3) / 6;
}

// Export students in a course to a csv file
void exportScoreboard(Global data)
{
    std::cout << "Input ID of a course to export students (or input 1 to go back): ";
    std::string courseId;
    std::cin >> courseId;

    if (courseId == "1")
    {
        std::cout << "----------------\n";
        return;
    }

    std::fstream output;
    output.open(
        "data/" + std::to_string(data.year) + "/semesters/" + std::to_string(data.semester) + "/"
        + courseId + "/scoreboard.csv",
        std::ios::out
    );
    output << "no,studentID,fullname,midtermmark,finalmark,othermark,totalmark";

    int count = 1;
    Course* cur = data.course;
    while (cur != nullptr)
    {
        if (cur -> courseId == courseId)
        {
            Student* curStudent = cur -> courseStudentHead;
            if (curStudent != nullptr) output << std::endl;
            while (curStudent != nullptr)
            {
                output << count << ","
                << curStudent -> studentID << ","
                << curStudent -> firstName + " " + curStudent -> lastName << ","
                << "0,0,0,0";

                if (curStudent -> nodeNext != nullptr)
                output << std::endl;

                count++;
                curStudent = curStudent -> nodeNext;
            }
            std::cout << "File exported successfully!\n";
            std::cout << "----------------\n";
            return;
        }
        cur = cur -> nodeNext;
    }

    std::cout << "Could not find that course.\n";
    std::cout << "----------------\n";
    return;
}

// Update scoreboard of a course
void updateScoreboard(Global data)
{
    std::cout << "Input ID of a course to update scoreboard (or input 1 to go back): ";
    std::string courseId;
    std::cin >> courseId;

    if (courseId == "1")
    {
        std::cout << "----------------\n";
        return;
    }

    bool check = false;
    Course* curCourse = data.course;
    while (curCourse != nullptr)
    {
        if (curCourse -> courseId == courseId
        && curCourse -> teacherName == data.curTeacher -> firstName + " " + data.curTeacher -> lastName)
        {
            check = true;
            break;
        }
        curCourse = curCourse -> nodeNext;
    }

    if (!check)
    {
        std::cout << "Could not find that course.\n";
        std::cout << "----------------\n";
        return;
    }

    std::fstream input, output;
    std::string dir = "data/" + std::to_string(data.year) + "/semesters/"
    + std::to_string(data.semester) + "/" + courseId + "/scoreboard.csv";

    input.open(dir, std::ios::in);

    std::string str;
    std::getline(input, str);

    Student* head = new Student;
    Student* cur = head;
    while (true)
    {
        getline(input, str, ',');
        getline(input, cur -> studentID, ',');
        getline(input, cur -> firstName, ',');
        getline(input, str, '\n');

        if (input.eof())
        {
            cur -> nodeNext = nullptr;
            break;
        }

        cur -> nodeNext = new Student;
        cur -> nodeNext -> nodePrev = cur;
        cur = cur -> nodeNext;
    }

    output.open(dir, std::ios::out);
    output << "no,studentID,fullname,midtermmark,finalmark,othermark,totalmark\n";

    int count = 1;
    cur = head;
    while (cur != nullptr)
    {
        output << count << ","
        << cur -> studentID << ","
        << cur -> firstName << ",";

        std::cout << cur -> studentID << " - " << cur -> firstName << std::endl;
        float mid, final, other;

        std::cout << "Input Midterm Mark: ";
        std::cin >> mid;
        output << mid << ",";

        std::cout << "Input Final Mark: ";
        std::cin >> final;
        output << final << ",";

        std::cout << "Input Other Mark: ";
        std::cin >> other;
        output << other << ",";

        output << getTotalMark(mid, final, other);

        if (cur -> nodeNext != nullptr)
        output << std::endl;

        count++;
        cur = cur -> nodeNext;
    }

    cur = head;
    while (cur != nullptr)
    {
        Student* temp = cur;
        cur = cur -> nodeNext;
        delete temp;
    }

    std::cout << "Scoreboard updated!\n";
    std::cout << "----------------\n";
    return;
}

// Import all scoreboards
void importScoreboard(Global data)
{
    std::string course, temp;
    std::string dir = "data/" + std::to_string(data.year) + "/semesters/"
    + std::to_string(data.semester);

    std::fstream output;
    output.open(dir + "/scoreboard.csv", std::ios::out);
    output << "no,courseID,studentID,fullname,midtermmark,finalmark,othermark,totalmark\n";

    int count = 1;
    Course* curCourse = data.course;
    while (curCourse != nullptr)
    {
        course = curCourse -> courseId;

        std::fstream input;
        input.open(dir + "/" + course + "/scoreboard.csv", std::ios::in);
        getline(input, temp);

        while (!input.eof())
        {
            getline(input, temp, ',');
            output << count << ",";
            count++;

            output << course << ",";

            for (int i = 0; i < 5; i++)
            {
                getline(input, temp, ',');
                output << temp << ",";
            }

            getline(input, temp);
            output << temp;

            if (curCourse -> nodeNext != nullptr || !input.eof())
            output << std::endl;
        }

        curCourse = curCourse -> nodeNext;
    }

    std::cout << "Scoreboard imported!\n";
    std::cout << "----------------\n";
    return;
}

// View scoreboard of a course
void viewScoreboardCourse(Global data)
{
    std::cout << "Input ID of a course to view (or input 1 to go back): ";
    std::string courseId;
    std::cin >> courseId;

    if (courseId == "1")
    {
        std::cout << "----------------\n";
        return;
    }

    bool check = false;
    Course* curCourse = data.course;
    while (curCourse != nullptr)
    {
        if (curCourse -> courseId == courseId)
        {
            check = true;
            break;
        }
        curCourse = curCourse -> nodeNext;
    }

    if (!check)
    {
        std::cout << "Could not find that course.\n";
        std::cout << "----------------\n";
        return;
    }

    std::fstream input;
    std::string dir = "data/" + std::to_string(data.year) + "/semesters/"
    + std::to_string(data.semester) + "/" + courseId + "/scoreboard.csv";

    input.open(dir, std::ios::in);

    std::string str;
    std::getline(input, str);

    std::cout << "----------------\n";
    std::cout << std::left
    << std::setw(5) << "No"
    << std::setw(13) << "Student ID"
    << std::setw(20) << "Full Name"
    << std::setw(10) << "Midterm"
    << std::setw(10) << "Final"
    << std::setw(10) << "Other"
    << std::setw(10) << "Total" << std::endl;

    while (!input.eof())
    {
        std::getline(input, str, '\n');
        std::istringstream iss(str);
        std::string item;

        std::getline(iss, item, ',');
        std::cout << std::setw(5) << item;

        std::getline(iss, item, ',');
        std::cout << std::setw(13) << item;

        std::getline(iss, item, ',');
        std::cout << std::setw(20) << item;

        while (std::getline(iss, item, ','))
        {
            std::cout << std::setw(10) << item;
        }

        std::cout << std::endl;
    }

    std::cout << "----------------\n";
    return;
}

// Update a student result
void updateStudentResult(Global data)
{
    std::string courseId, studentId;
    float mid, final, other, total;
    bool check = false;

    std::cout << "Input student ID to update result (or input 1 to go back): ";
    std::cin >> studentId;

    if (studentId == "1")
    {
        std::cout << "----------------\n";
        return;
    }

    Student* curStudent = data.student;
    while (curStudent != nullptr)
    {
        if (curStudent -> studentID == studentId)
        {
            check = true;
            break;
        }
        curStudent = curStudent -> nodeNext;
    }

    if (!check)
    {
        std::cout << "Could not find that student.\n";
        std::cout << "----------------\n";
        return;
    }

    check = false;

    std::cout << "Input course ID to update result (or input 1 to go back): ";
    std::cin >> courseId;

    if (courseId == "1")
    {
        std::cout << "----------------\n";
        return;
    }

    Course* curCourse = data.course;
    while (curCourse != nullptr)
    {
        if (curCourse -> courseId == courseId)
        {
            check = true;
            break;
        }
        curCourse = curCourse -> nodeNext;
    }

    if (!check)
    {
        std::cout << "Could not find that course.\n";
        std::cout << "----------------\n";
        return;
    }

    std::cout << "Input Midterm Mark: ";
    std::cin >> mid;

    std::cout << "Input Final Mark: ";
    std::cin >> final;

    std::cout << "Input Other Mark: ";
    std::cin >> other;

    total = getTotalMark(mid, final, other);

    CourseScore* curCourseScore = data.courseScore;
    while (true)
    {
        if (curCourseScore -> studentID == studentId && curCourseScore -> courseID == courseId)
        {
            curCourseScore -> midterm = std::to_string(mid);
            curCourseScore -> final = std::to_string(final);
            curCourseScore -> other = std::to_string(other);
            curCourseScore -> total = std::to_string(total);
            break;
        }
        curCourseScore = curCourseScore -> nodeNext;
    }

    writeScoreboard(data.courseScore, data.year, data.semester);

    std::cout << "Student result updated!\n";
    std::cout << "----------------\n";
    return;
}

// View scoreboard of a student
void viewScoreboardStudent(Global data, std::string studentID)
{
    std::cout << std::left
    << std::setw(15) << "Course"
    << std::setw(10) << "Midterm"
    << std::setw(10) << "Final"
    << std::setw(10) << "Other"
    << std::setw(10) << "Total" << std::endl;

    float sum;
    int count = 0;

    CourseScore* curCourseScore = data.courseScore;
    while (curCourseScore != nullptr)
    {
        if (curCourseScore -> studentID == studentID)
        {
            sum += std::stof(curCourseScore -> total);
            count++;

            std::cout << std::setw(15) << curCourseScore -> courseID
            << std::setw(10) << curCourseScore -> midterm
            << std::setw(10) << curCourseScore -> final
            << std::setw(10) << curCourseScore -> other
            << std::setw(10) << curCourseScore -> total << std::endl;
        }
        curCourseScore = curCourseScore -> nodeNext;
    }

    std::cout << "Average: " << sum / count << std::endl
    << "GPA: " << (sum / (10 * count)) * 4 << std::endl;
    std::cout << "----------------\n";
    return;
}

// View scoreboard of a class
void viewScoreboardClass(Global data)
{
    std::string classID;
    std::cout << "Input class ID to view scoreboard (or input 1 to go back): ";
    std::cin >> classID;

    if (classID == "1")
    {
        std::cout << "----------------\n";
        return;
    }

    bool check = false;
    Student* curStudent = data.student;
    while (curStudent != nullptr)
    {
        if (curStudent -> classID == classID)
        {
            check = true;
            break;
        }
        curStudent = curStudent -> nodeNext;
    }

    if (!check)
    {
        std::cout << "Could not find that class.\n";
        std::cout << "----------------\n";
        return;
    }

    std::cout << "----------------\n";
    std::string studentPrinted;

    CourseScore* curCourseScore = data.courseScore;
    while (curCourseScore != nullptr)
    {
        Student* curStudent = data.student;
        while (curStudent != nullptr)
        {
            if (curCourseScore -> studentID == curStudent -> studentID && curStudent -> classID == classID)
            {
                if (studentPrinted.find(curCourseScore -> studentID) == std::string::npos)
                {
                    studentPrinted += "-" + curCourseScore -> studentID;
                    std::cout << curCourseScore -> studentID << " - " << curCourseScore -> fullname << std::endl;
                    viewScoreboardStudent(data, curCourseScore -> studentID);
                    break;
                }
            }
            curStudent = curStudent -> nodeNext;
        }
        curCourseScore = curCourseScore -> nodeNext;
    }

    return;
}