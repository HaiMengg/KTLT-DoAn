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
        staffMenu(data);
        return false;
    }

    std::fstream output;
    output.open("exportedStudent.csv", std::ios::out);
    output << "studentID,firstName,lastName,dob,gender,socialID,classID";

    Course* cur = data.course;
    while (cur != nullptr)
    {
        if (cur -> courseId == courseId)
        {
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
            std::cout << "File exported successfully!\n";
            std::cout << "----------------\n";
            return true;
        }
        cur = cur -> nodeNext;
    }

    std::cout << "Could not find that course. Please try again.\n";
    exportCourseStudent(data);
    return false;
}