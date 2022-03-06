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

    cout << "----------------\n"
    << "Welcome!\nPlease login to continue.\n\n";

    string username, password;
    int identity = 0;

    loginCheck(staffData, studentData, username, password, identity);

    // Output linked lists (only for testing)
    // displayStaff(staffData);
    // displayStudent(studentData);

    // Delete linked lists
    deleteData(staffData, studentData);
}