#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "struct.h"
#include "../Main-Menu/menu.h"

// Login
void loginCheck(Login &data, Node& node, std::fstream& sY, std::fstream& cl, std::fstream& stu, std::fstream& sem, std::string& currentDate)
{   
    if (data.identity == 0) std::cout << "----------------\n" << "Welcome!\nPlease login to continue.\n\n";
    std::cout << "[1] Login as staff\n[2] Login as teacher\n[3] Login as student\n[4] Change current date\n[5] Exit program\n"
    << "----------------\n";

    std::cout << "Input: ";
    std::string option;
    std::getline(std::cin, option);

    if (option == "1" || option == "2" || option == "3")
    {
        std::cout << "Username: ";
        std::getline(std::cin, data.username);

        std::cout << "Password: ";
        std::getline(std::cin, data.password);

        if (option == "1")
        {
            Staff* cur = data.staff;
            while (cur != nullptr)
            {
                if (data.username == cur -> usr && data.password == cur -> pwd)
                {
                    data.identity = 1;
                    data.curStaff = cur;
                    break;
                }
                cur = cur -> nodeNext;
            }
        }

        else if (option == "2")
        {
            Teacher* cur = data.teacher;
            while (cur != nullptr)
            {
                if (data.username == cur -> usr && data.password == cur -> pwd)
                {
                    data.identity = 2;
                    data.curTeacher = cur;
                    break;
                }
                cur = cur -> nodeNext;
            }
        }

        else
        {
            Student* cur = data.student;
            while (cur != nullptr)
            {
                if (data.username == cur -> usr && data.password == cur -> pwd)
                {
                    data.identity = 3;
                    data.curStudent = cur;
                    break;
                }
                cur = cur -> nodeNext;
            }
        }

        if (data.identity == 1)
        {
            std::cout << "----------------\n"
            "Welcome " << data.username << "!\n\n"
            << "[1] View info\n[2] Export students in a course\n[3] Import all scoreboards\n"
            << "[4] View scoreboard of a course\n[5] Update a student result\n"
            << "[6] Other actions\n[7] Change password\n"
            << "[8] Log out\n[9] Change current date\n[10] Exit program\n"
            << "----------------\n";
            staffMenu(data, node, sY, cl, stu, sem, currentDate);
        }

        else if (data.identity == 2)
        {
            std::cout << "----------------\n"
            "Welcome " << data.username << "!\n\n"
            << "[1] View info\n[2] Update scoreboard\n[3] Change password\n[4] Log out\n[5] Exit program\n"
            << "----------------\n";
            teacherMenu(data, node, sY, cl, stu, sem, currentDate);
        }

        else if (data.identity == 3)
        {
            std::cout << "----------------\n"
            "Welcome " << data.username << "!\n\n"
            << "[1] View info\n[2] View my courses\n[3] Enroll in a course\n[4] Remove a course\n"
            << "[5] Change password\n[6] Log out\n[7] Change current date\n[8] Exit program\n"
            << "----------------\n";
            studentMenu(data, node, sY, cl, stu, sem, currentDate);
        }

        else
        {
            std::cout << "Incorrect username or password. Please try again.\n\n";
            data.identity = -1;
            return loginCheck(data, node, sY, cl, stu, sem, currentDate);
        }
    }
    else if (option == "4") {
        updateDate(currentDate);
        printCurrentDate(currentDate, node.semesterHead);
        return loginCheck(data, node, sY, cl, stu, sem, currentDate); 
    }
    else if (option == "5") return;

    else
    {
        std::cout << "Invalid input. Please try again.\n\n";
        data.identity = -1;
        return loginCheck(data, node, sY, cl, stu, sem, currentDate);
    }
}

// Basic menu
void staffMenu(Login &data, Node& node, std::fstream& sY, std::fstream& cl, std::fstream& stu, std::fstream& sem, std::string& currentDate)
{
    std::cout << "Input: ";
    std::string option;
    std::getline(std::cin, option);

    if (option == "1") viewInfo(data, node, sY, cl, stu, sem, currentDate);
    else if (option == "2")
    {
        exportScoreboard(data);
        staffMenu(data, node, sY, cl, stu, sem, currentDate);
    }
    else if (option == "3")
    {
        importScoreboard(data);
        staffMenu(data, node, sY, cl, stu, sem, currentDate);
    }
    else if (option == "4")
    {
        viewScoreboardCourse(data);
        staffMenu(data, node, sY, cl, stu, sem, currentDate);
    }
    else if (option == "5")
    {
        updateStudentResult(data);
        staffMenu(data, node, sY, cl, stu, sem, currentDate);
    }
    else if (option == "6") {
        system("cls");
        currentMenu(node, sY, cl, stu, sem, currentDate);
        std::cout << "----------------\n"
        "Welcome " << data.username << "!\n\n"
        << "[1] View info\n[2] Change password\n[3] Log out\n[4] Available actions\n[5] Change current date\n[6] Exit program\n"
        << "----------------\n";
        return loginMenu(data, node, sY, cl, stu, sem, currentDate);
    }
    else if (option == "7") changePassword(data, node, sY, cl, stu, sem, currentDate);
    else if (option == "8") logOut(data, node, sY, cl, stu, sem, currentDate);
    else if (option == "9") {
        updateDate(currentDate);
        printCurrentDate(currentDate, node.semesterHead);
        return loginMenu(data, node, sY, cl, stu, sem, currentDate);
    }
    else if (option == "10") return;
    else
    {
        std::cout << "Invalid input. Please try again.\n\n";
        std::cout << "----------------\n";
        return loginMenu(data, node, sY, cl, stu, sem, currentDate);
    }
}

// Teacher menu
void teacherMenu(Login &data, Node& node, std::fstream& sY, std::fstream& cl, std::fstream& stu, std::fstream& sem, std::string& currentDate)
{
    std::cout << "Input: ";
    std::string option;
    std::cin >> option;

    if (option == "1") viewInfo(data, node, sY, cl, stu, sem, currentDate);
    else if (option == "2")
    {
        updateScoreboard(data);
        teacherMenu(data, node, sY, cl, stu, sem, currentDate);
    }
    else if (option == "3") changePassword(data, node, sY, cl, stu, sem, currentDate);
    else if (option == "4") logOut(data, node, sY, cl, stu, sem, currentDate);
    else if (option == "5") return;
    else
    {
        std::cout << "Invalid input. Please try again.\n";
        std::cout << "----------------\n";
        return teacherMenu(data, node, sY, cl, stu, sem, currentDate);
    }
}

// Student menu
void studentMenu(Login &data, Node& node, std::fstream& sY, std::fstream& cl, std::fstream& stu, std::fstream& sem, std::string& currentDate)
{
    std::cout << "Input: ";
    std::string option;
    std::cin >> option;

    if (option == "1") viewInfo(data, node, sY, cl, stu, sem, currentDate);
    else if (option == "2") viewCourse(data, node, sY, cl, stu, sem, currentDate);
    else if (option == "3")
    {
        showCourses(data.course);
        enrollCourse(data, node, sY, cl, stu, sem, currentDate);
    }
    else if (option == "4") removeCourse(data, node, sY, cl, stu, sem, currentDate);
    else if (option == "5") changePassword(data, node, sY, cl, stu, sem, currentDate);
    else if (option == "6") logOut(data, node, sY, cl, stu, sem, currentDate);
    else if (option == "7") {
        updateDate(currentDate);
        printCurrentDate(currentDate, node.semesterHead);
        return studentMenu(data, node, sY, cl, stu, sem, currentDate);
    }
    else if (option == "8") return;
    else
    {
        std::cout << "Invalid input. Please try again.\n";
        std::cout << "----------------\n";
        return studentMenu(data, node, sY, cl, stu, sem, currentDate);
    }
}

// View info
void viewInfo(Login data, Node& node, std::fstream& sY, std::fstream& cl, std::fstream& stu, std::fstream& sem, std::string& currentDate)
{
    if (data.identity == 1)
    {
        Staff* cur = data.curStaff;
        std::cout << "----------------\n";
        std::cout << "Username: " << cur -> usr << std::endl;
        std::cout << "First Name: " << cur -> firstName << std::endl;
        std::cout << "Last Name: " << cur -> lastName << std::endl;
        std::cout << "Date of Birth: " << cur -> dob << std::endl;
        std::cout << "Gender: " << cur -> gender << std::endl;
        std::cout << "----------------\n";
        return staffMenu(data, node, sY, cl, stu, sem, currentDate);
    }

    else if (data.identity == 2)
    {
        Teacher* cur = data.curTeacher;
        std::cout << "----------------\n";
        std::cout << "Username: " << cur -> usr << std::endl;
        std::cout << "First Name: " << cur -> firstName << std::endl;
        std::cout << "Last Name: " << cur -> lastName << std::endl;
        std::cout << "Date of Birth: " << cur -> dob << std::endl;
        std::cout << "Gender: " << cur -> gender << std::endl;
        std::cout << "----------------\n";
        return teacherMenu(data, node, sY, cl, stu, sem, currentDate);
    }

    else
    {
        Student* cur = data.curStudent;
        std::cout << "----------------\n";
        std::cout << "Username: " << cur -> usr << std::endl;
        std::cout << "Student ID: " << cur -> studentID << std::endl;
        std::cout << "First Name: " << cur -> firstName << std::endl;
        std::cout << "Last Name: " << cur -> lastName << std::endl;
        std::cout << "Date of Birth: " << cur -> dob << std::endl;
        std::cout << "Gender: " << cur -> gender << std::endl;
        std::cout << "Social ID: " << cur -> socialID << std::endl;
        std::cout << "Start Year: " << cur -> startYear << std::endl;
        std::cout << "Class ID: " << cur -> classID << std::endl;
        std::cout << "----------------\n";
        return studentMenu(data, node, sY, cl, stu, sem, currentDate);
    }
}

// Change password
void changePassword(Login &data, Node& node, std::fstream& sY, std::fstream& cl, std::fstream& stu, std::fstream& sem, std::string& currentDate)
{
    std::string pass;
    std::cout << "Input current password: ";
    std::cin >> pass;

    while (pass != data.password)
    {
        std::cout << "Incorrect password. Try again: ";
        std::cin >> pass;
    }

    std::cout << "Input new password: ";
    std::cin >> pass;

    if (data.identity == 1)
    {
        Staff* cur = data.curStaff;
        cur -> pwd = pass;
        writeStaff(data.staff);
    }

    else if (data.identity == 2)
    {
        Teacher* cur = data.curTeacher;
        cur -> pwd = pass;
        writeTeacher(data.teacher);
    }

    else
    {
        Student* cur = data.curStudent;
        cur -> pwd = pass;
        writeStudent(data.student);
    }

    data.password = pass;
    std::cout << "Password changed successfully!\n" << "----------------\n";

    if (data.identity == 1) staffMenu(data, node, sY, cl, stu, sem, currentDate);
    else if (data.identity == 2) teacherMenu(data, node, sY, cl, stu, sem, currentDate);
    else studentMenu(data, node, sY, cl, stu, sem, currentDate);
}

// Log out
void logOut(Login &data, Node& node, std::fstream& sY, std::fstream& cl, std::fstream& stu, std::fstream& sem, std::string& currentDate)
{
    data.username = "";
    data.password = "";
    data.identity = 0;
    data.curStaff = nullptr;
    data.curTeacher = nullptr;
    data.curStudent = nullptr;
    loginCheck(data, node, sY, cl, stu, sem, currentDate);
}