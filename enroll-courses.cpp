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
int getSemester(std::fstream &input)
{
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

// Read course.csv
void readCourse(Course* &data, std::fstream &input)
{
    // Track current pointer
    Course* cur = data;

    // Ignore first line
    std::string str;
    std::getline(input, str);

    // Get data
    while (true)
    {
        getline(input, cur -> courseId, ',');
        getline(input, cur -> courseName, ',');
        getline(input, cur -> teacherName, ',');
        getline(input, cur -> numOfCredits, ',');
        getline(input, str, ',');
        getline(input, cur -> daySession);

        if (input.eof())
        {
            cur -> nodeNext = nullptr;
            break;
        }

        cur -> nodeNext = new Course;
        cur -> nodeNext -> nodePrev = cur;
        cur = cur -> nodeNext;   
    }
    cur = nullptr;
}

// Replace all same substrings with another string
void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if (from.empty()) return;

    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

// Show all available courses
void viewCourse(Course* data)
{
    Course* cur = data;

    std::cout << "----------------\n";
    std::cout << std::left
    << std::setw(15) << "ID"
    << std::setw(22) << "Course"
    << std::setw(25) << "Teacher"
    << std::setw(10) << "Credits"
    << std::setw(20) << "Sessions" << std::endl;

    while (cur != nullptr)
    {
        replaceAll(cur -> daySession, "|", ", ");
        replaceAll(cur -> daySession, "-S1", " (07:30-09:10)");
        replaceAll(cur -> daySession, "-S2", " (09:30-11:10)");
        replaceAll(cur -> daySession, "-S3", " (13:30-15:10)");
        replaceAll(cur -> daySession, "-S4", " (15:30-17:10)");

        std::cout << std::setw(15) << cur -> courseId;
        std::cout << std::setw(22) << cur -> courseName;
        std::cout << std::setw(25) << cur -> teacherName;
        std::cout << std::setw(10) << cur -> numOfCredits;
        std::cout << std::setw(20) << cur -> daySession << std::endl;

        cur = cur -> nodeNext;
    }

    std::cout << "----------------\n";
}