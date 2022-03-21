#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#include "struct.h"
#include "read-write-csv.cpp"

// Login
void loginCheck(Login &data)
{
    if (data.identity == 0) cout << "----------------\n" << "Welcome!\nPlease login to continue.\n\n";
    cout << "[1] Login as Staff\n[2] Login as Teacher\n[3] Login as Student\n[4] Exit Program\n"
    << "----------------\n";

    string option;
    cin >> option;

    if (option == "1" || option == "2" || option == "3")
    {
        cout << "Username: ";
        cin >> data.username;

        cout << "Password: ";
        cin >> data.password;

        if (option == "1")
        {
            Staff* cur = data.staff;
            while (cur != nullptr)
            {
                if (data.username == cur -> usr && data.password == cur -> pwd)
                {
                    data.identity = 1;
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
                    break;
                }
                cur = cur -> nodeNext;
            }
        }

        if (data.identity != 0 && data.identity != -1)
        {
            cout << "----------------\n"
            "You're logged in as " << data.username << "\n\n"
            << "[1] View Info\n[2] Change Password\n[3] Log Out\n[4] Exit Program\n"
            << "----------------\n";
            loginMenu(data);
        }

        else
        {
            cout << "Incorrect username or password. Please try again.\n\n";
            data.identity = -1;
            return loginCheck(data);
        }
    }

    else if (option == "4") return;

    else
    {
        cout << "Invalid input. Please try again.\n\n";
        data.identity = -1;
        return loginCheck(data);
    }
}

// Basic menu
void loginMenu(Login &data)
{
    string option;
    cin >> option;

    if (option == "1") viewInfo(data);
    else if (option == "2") changePassword(data);
    else if (option == "3") logOut(data);
    else if (option == "4") return;
    else
    {
        cout << "Invalid input. Please try again.\n\n";
        return loginMenu(data);
    }
}

// 1. View info
void viewInfo(Login data)
{
    if (data.identity == 1)
    {
        Staff* cur = data.staff;
        while (cur != nullptr)
        {
            if (data.username == cur -> usr && data.password == cur -> pwd)
            {
                cout << "----------------\n";
                cout << "Username: " << cur -> usr << endl;
                cout << "First Name: " << cur -> firstName << endl;
                cout << "Last Name: " << cur -> lastName << endl;
                cout << "Date of Birth: " << cur -> dob << endl;
                cout << "Gender: " << cur -> gender << endl;
                cout << "----------------\n";
                return loginMenu(data);
            }
            cur = cur -> nodeNext;
        }
        cout << endl;
    }

    else if (data.identity == 2)
    {
        Teacher* cur = data.teacher;
        while (cur != nullptr)
        {
            if (data.username == cur -> usr && data.password == cur -> pwd)
            {
                cout << "----------------\n";
                cout << "Username: " << cur -> usr << endl;
                cout << "First Name: " << cur -> firstName << endl;
                cout << "Last Name: " << cur -> lastName << endl;
                cout << "Date of Birth: " << cur -> dob << endl;
                cout << "Gender: " << cur -> gender << endl;
                cout << "----------------\n";
                return loginMenu(data);
            }
            cur = cur -> nodeNext;
        }
        cout << endl;
    }

    else
    {
        Student* cur = data.student;
        while (cur != nullptr)
        {
            if (data.username == cur -> usr && data.password == cur -> pwd)
            {
                cout << "----------------\n";
                cout << "Username: " << cur -> usr << endl;
                cout << "Student ID: " << cur -> studentID << endl;
                cout << "First Name: " << cur -> firstName << endl;
                cout << "Last Name: " << cur -> lastName << endl;
                cout << "Date of Birth: " << cur -> dob << endl;
                cout << "Gender: " << cur -> gender << endl;
                cout << "Social ID: " << cur -> socialID << endl;
                cout << "Start Year: " << cur -> startYear << endl;
                cout << "Class ID: " << cur -> classID << endl;
                cout << "----------------\n";
                return loginMenu(data);
            }
            cur = cur -> nodeNext;
        }
        cout << endl;
    }
}

// 2. Change password
void changePassword(Login &data)
{
    string pass;
    cout << "Input new password: ";
    cin >> pass;

    if (data.identity == 1)
    {
        Staff* cur = data.staff;
        while (cur != nullptr)
        {
            if (data.username == cur -> usr && data.password == cur -> pwd)
            {
                cur -> pwd = pass;
                writeStaff(data.staff);
                break;
            }
            cur = cur -> nodeNext;
        }
    }

    else if (data.identity == 2)
    {
        Teacher* cur = data.teacher;
        while (cur != nullptr)
        {
            if (data.username == cur -> usr && data.password == cur -> pwd)
            {
                cur -> pwd = pass;
                writeTeacher(data.teacher);
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
                cur -> pwd = pass;
                writeStudent(data.student);
                break;
            }
            cur = cur -> nodeNext;
        }
    }

    data.password = pass;
    cout << "Password changed successfully!\n" << "----------------\n";
    loginMenu(data);
}

// 3. Log out
void logOut(Login &data)
{
    data.username = "";
    data.password = "";
    data.identity = 0;
    loginCheck(data);
}