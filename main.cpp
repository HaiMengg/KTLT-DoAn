#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#include "functions.cpp"

int main()
{
    // Read CSV files into linked lists
    STAFF* staffData = new STAFF;
    STUDENT* studentData = new STUDENT;
    readCSV(staffData, studentData);

    // Log in to the system
    int identity = 0;
    string username, password;
    cout << "----------------\n" << "Welcome!\nPlease login to continue.\n\n";
    loginCheck(staffData, studentData, username, password, identity);

    // Output linked lists (only for testing)
    // displayStaff(staffData);
    // displayStudent(studentData);

    // Delete linked lists
    deleteData(staffData, studentData);
}