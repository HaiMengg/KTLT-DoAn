#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#include "read-write-csv.cpp"

// Login
void loginCheck(STAFF* data, STUDENT* studentData, string &username, string &password, int &identity)
{
    cout << "[1] Login as Staff\n[2] Login as Student\n" << "----------------\n";

    string option;
    cin >> option;

    if (option == "1" || option == "2")
    {
        cout << "Username: ";
        cin >> username;

        cout << "Password: ";
        cin >> password;

        if (option == "1")
        {
            STAFF* pCur = data;
            while (pCur != nullptr)
            {
                if (username == pCur -> staffusr && password == pCur -> staffpwd)
                {
                    identity = 1;
                    break;
                }
                pCur = pCur -> next;
            }
        }
        
        else
        {
            STUDENT* pCur = studentData;
            while (pCur != nullptr)
            {
                if (username == pCur -> studentusr && password == pCur -> studentpwd)
                {
                    identity = 2;
                    break;
                }
                pCur = pCur -> next;
            }
        }

        if (identity)
        {
            cout << "----------------\n"
            "You're logged in as " << username << "\n\n"
            << "[1] View Info\n[2] Change Password\n[3] Log Out\n"
            << "----------------\n";
        }

        else
        {
            cout << "Incorrect username or password. Please try again.\n\n";
            return loginCheck(data, studentData, username, password, identity);
        }
    }

    else
    {
        cout << "Invalid input. Please try again.\n\n";
        return loginCheck(data, studentData, username, password, identity);
    }
}