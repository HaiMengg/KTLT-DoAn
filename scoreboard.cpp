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
void exportScoreboard(Login data)
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
void updateScoreboard(Login data)
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
void importScoreboard(Login data)
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