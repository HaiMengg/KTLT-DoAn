#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "struct.h"
#include "read-write-csv.cpp"

// Login
void loginCheck(Login &data)
{
    if (data.identity == 0) std::cout << "----------------\n" << "Welcome!\nPlease login to continue.\n\n";
    std::cout << "[1] Login as Staff\n[2] Login as Teacher\n[3] Login as Student\n[4] Exit Program\n"
    << "----------------\n";

    std::string option;
    std::cin >> option;

    if (option == "1" || option == "2" || option == "3")
    {
        std::cout << "Username: ";
        std::cin >> data.username;

        std::cout << "Password: ";
        std::cin >> data.password;

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

        if (data.identity != 0 && data.identity != -1)
        {
            std::cout << "----------------\n"
            "Welcome " << data.username << "!\n\n"
            << "[1] View Info\n[2] Change Password\n[3] Log Out\n[4] Exit Program\n"
            << "----------------\n";
            loginMenu(data);
        }

        else
        {
            std::cout << "Incorrect username or password. Please try again.\n\n";
            data.identity = -1;
            return loginCheck(data);
        }
    }

    else if (option == "4") return;

    else
    {
        std::cout << "Invalid input. Please try again.\n\n";
        data.identity = -1;
        return loginCheck(data);
    }
}

// Basic menu
void loginMenu(Login &data)
{
    std::string option;
    std::cin >> option;

    if (option == "1") viewInfo(data);
    else if (option == "2") changePassword(data);
    else if (option == "3") logOut(data);
    else if (option == "4") return;
    else
    {
        std::cout << "Invalid input. Please try again.\n\n";
        return loginMenu(data);
    }
}

// 1. View info
void viewInfo(Login data)
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
        return loginMenu(data);
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
        return loginMenu(data);
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
        return loginMenu(data);
    }
}

// 2. Change password
void changePassword(Login &data)
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
    loginMenu(data);
}

// 3. Log out
void logOut(Login &data)
{
    data.username = "";
    data.password = "";
    data.identity = 0;
    data.curStaff = nullptr;
    data.curTeacher = nullptr;
    data.curStudent = nullptr;
    loginCheck(data);
}