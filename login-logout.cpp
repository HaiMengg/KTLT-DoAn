#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#include "read-write-csv.cpp"

// Active data
struct LOGIN
{
    STAFF* staff;
    TEACHER* teacher;
    STUDENT* student;
    string username, password;
    int identity = 0;
};

// Login
void loginCheck(LOGIN &data)
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
            STAFF* cur = data.staff;
            while (cur != nullptr)
            {
                if (data.username == cur -> staffusr && data.password == cur -> staffpwd)
                {
                    data.identity = 1;
                    break;
                }
                cur = cur -> next;
            }
        }

        else if (option == "2")
        {
            TEACHER* cur = data.teacher;
            while (cur != nullptr)
            {
                if (data.username == cur -> teachusr && data.password == cur -> teachpwd)
                {
                    data.identity = 2;
                    break;
                }
                cur = cur -> next;
            }
        }

        else
        {
            STUDENT* cur = data.student;
            while (cur != nullptr)
            {
                if (data.username == cur -> studentusr && data.password == cur -> studentpwd)
                {
                    data.identity = 3;
                    break;
                }
                cur = cur -> next;
            }
        }

        if (data.identity != 0 && data.identity != -1)
        {
            cout << "----------------\n"
            "You're logged in as " << data.username << "\n\n"
            << "[1] View Info\n[2] Change Password\n[3] Log Out\n[4] Exit Program\n"
            << "----------------\n";
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