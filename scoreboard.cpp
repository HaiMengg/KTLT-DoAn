#include <iostream>
#include <fstream>
#include <string>

#include "struct.h"

bool exportCourseStudent(Login data)
{
    std::cout << "Input ID of a course to export students (or input 1 to go back): ";
    std::string courseId;
    std::cin >> courseId;

    if (courseId == "1")
    {
        std::cout << "----------------\n";
        return true;
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
            return true;
        }
        cur = cur -> nodeNext;
    }

    std::cout << "Could not find that course.\n";
    std::cout << "----------------\n";
    return true;
}