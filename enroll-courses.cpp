#include <iostream>
#include <sstream>
#include <fstream>
#include <locale>
#include <iomanip>
#include <time.h>
#include <string>

// Check if current time is between startDate and endDate
bool checkSemester(std::string start, std::string end)
{
    time_t currentDate;
    currentDate = time(NULL);

    time_t startDate, endDate;

    std::tm t = {};
    std::istringstream ssStart(start);
    ssStart >> std::get_time(&t, "%d/%m/%Y");
    startDate = std::mktime(&t);

    t = {};
    std::istringstream ssEnd(end);
    ssEnd >> std::get_time(&t, "%d/%m/%Y");
    endDate = std::mktime(&t);

    if (startDate < currentDate && currentDate < endDate) return true;
    return false;
}

// Get current semester based on current date
int getSemester()
{
    std::fstream input;
    input.open("semester/semester.csv", std::ios::in);

    std::string str;
    std::getline(input, str);

    while (!input.eof())
    {
        std::string sem, startDate, endDate;
        std::getline(input, sem, ',');
        std::getline(input, startDate, ',');
        std::getline(input, endDate);

        if (checkSemester(startDate, endDate))
        return atoi(sem.c_str());
    }

    return 0;
}

// int main()
// {
//     int sem = getSemester();
//     std::cout << sem;
//     return 0;
// }