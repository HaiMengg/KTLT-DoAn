#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// Struct for staffs
struct STAFF
{
    string staffusr, staffpwd, firstname, lastname, dob, gender;
    STAFF* next;
};

// Struct for students
struct STUDENT
{
    string studentusr, studentpwd, studentID, firstname, lastname, dob, gender, socialID, startyear, classID, CoursesID;
    STUDENT* next;
};

// Read CSV files
void readCSV(STAFF* &staffData, STUDENT* &studentData)
{
    // Open CSV files
    fstream staff, student;
    staff.open("staff.csv", ios::in);
    student.open("student.csv", ios::in);

    // Track current pointers
    STAFF* fCur = staffData;
    STUDENT* tCur = studentData;

    // Ignore first line of CSV files
    string str;
    getline(staff, str);
    getline(student, str);

    // Get data from staff.csv
    while (!staff.eof())
    {
        getline(staff, fCur -> staffusr, ',');
        getline(staff, fCur -> staffpwd, ',');
        getline(staff, fCur -> firstname, ',');
        getline(staff, fCur -> lastname, ',');
        getline(staff, fCur -> dob, ',');
        getline(staff, fCur -> gender);

        fCur -> next = new STAFF;
        fCur = fCur -> next;   
    }
    fCur = nullptr;

    // Get data from student.csv
    while (!student.eof())
    {
        getline(student, tCur -> studentusr, ',');
        getline(student, tCur -> studentpwd, ',');
        getline(student, tCur -> studentID, ',');
        getline(student, tCur -> firstname, ',');
        getline(student, tCur -> lastname, ',');
        getline(student, tCur -> dob, ',');
        getline(student, tCur -> gender, ',');
        getline(student, tCur -> socialID, ',');
        getline(student, tCur -> startyear, ',');
        getline(student, tCur -> classID, ',');
        getline(student, tCur -> CoursesID);

        tCur -> next = new STUDENT;
        tCur = tCur -> next;
    }
    tCur = nullptr;
}

// Log in to the system
void loginCheck(STAFF* staffData, STUDENT* studentData, string &username, string &password, int &identity)
{
    cout << "[1] Login as Staff\n[2] Login as Student\n"
    << "----------------\n";

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
            STAFF* pCur = staffData;
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
            return loginCheck(staffData, studentData, username, password, identity);
        }
    }

    else
    {
        cout << "Invalid input. Please try again.\n\n";
        return loginCheck(staffData, studentData, username, password, identity);
    }
}

// Display staff info
void displayStaff(STAFF* staffData)
{
    STAFF* fCur = staffData;
    while (fCur != nullptr)
    {
        cout << fCur -> staffusr << " ";
        fCur = fCur -> next;
    }
    cout << endl;
}

// Display student info
void displayStudent(STUDENT* studentData)
{
    STUDENT* tCur = studentData;
    while (tCur != nullptr)
    {
        cout << tCur -> studentusr << " ";
        tCur = tCur -> next;
    }
}

// Delete data
void deleteData(STAFF* &staffData, STUDENT* &studentData)
{
    STAFF* fCur = staffData;
    STUDENT* tCur = studentData;
    STAFF* fDel;
    STUDENT* tDel;

    while (fCur != nullptr)
    {
        fDel = fCur -> next;
        delete fCur;
        fCur = fDel;
    }

    while (tCur != nullptr)
    {
        tDel = tCur -> next;
        delete tCur;
        tCur = tDel;
    }

    staffData = nullptr;
    studentData = nullptr;
}