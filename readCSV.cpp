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

// Print staff data (only for testing)
void outputStaff(STAFF* fHead)
{
    STAFF* fCur = fHead;
    while (fCur != nullptr)
    {
        cout << fCur -> staffusr << " ";
        fCur = fCur -> next;
    }
    cout << endl;
}

// Print student data (only for testing)
void outputStudent(STUDENT* tHead)
{
    STUDENT* tCur = tHead;
    while (tCur != nullptr)
    {
        cout << tCur -> studentusr << " ";
        tCur = tCur -> next;
    }
}

// Delete data
void deleteData(STAFF* &fHead, STUDENT* &tHead)
{
    STAFF* fCur = fHead;
    STUDENT* tCur = tHead;
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

    fHead = nullptr;
    tHead = nullptr;
}

int main()
{
    // Open CSV files
    fstream staff, student;
    staff.open("staff.csv", ios::in);
    student.open("student.csv", ios::in);

    // Create (singly) linked lists
    STAFF* fHead = new STAFF;
    STAFF* fCur = fHead;
    STUDENT* tHead = new STUDENT;
    STUDENT* tCur = tHead;

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

    // Output linked lists (only for testing)
    outputStaff(fHead);
    outputStudent(tHead);

    // Delete linked lists
    deleteData(fHead, tHead);
}