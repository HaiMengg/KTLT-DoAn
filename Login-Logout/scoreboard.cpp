#include <iostream>
#include <fstream>
#include <string>

#include "struct.h"

// Calculate total mark
float getTotalMark(float mid, float final, float other)
{
    return (other + mid * 2 + final * 3) / 6;
}

// Export students in a course to a csv file
void exportScoreboard(Login data)
{
    std::cout << "Input ID of a course to export students (or input 0 to go back): ";
    std::string courseId;
    std::getline(std::cin, courseId);

    if (courseId == "0")
    {
        std::cout << "----------------\n";
        system("cls");
        return;
    }

    std::fstream output;
    output.open(
        "data/" + std::to_string(data.year) + "/semesters/" + std::to_string(data.semester) + "/"
        + courseId + "/scoreboard.csv",
        std::ios::out
    );
    output << "no,studentID,fullname,midtermmark,finalmark,othermark,totalmark";

    int count = 1;
    Course* cur = data.course;
    while (cur != nullptr)
    {
        if (cur -> courseId == courseId)
        {
            Student* curStudent = cur -> courseStudentHead;
            if (curStudent != nullptr) output << std::endl;
            while (curStudent != nullptr)
            {
                output << count << ","
                << curStudent -> studentID << ","
                << curStudent -> firstName + " " + curStudent -> lastName << ","
                << "0,0,0,0";

                if (curStudent -> nodeNext != nullptr)
                output << std::endl;

                count++;
                curStudent = curStudent -> nodeNext;
            }
            std::cout << "File exported successfully!\n";
            std::cout << "----------------\n";
            return;
        }
        cur = cur -> nodeNext;
    }

    std::cout << "Could not find that course.\n";
    std::cout << "----------------\n";
    return;
}

void exportScoreboardTeacher(Login data) {
    std::cout << "Input ID of a course to export students (or input 0 to go back): ";
    std::string courseId;
    std::getline(std::cin, courseId);

    if (courseId == "0")
    {
        std::cout << "----------------\n";
        system("cls");
        return;
    }

    std::cout << "Input the directory to the folder to export the scoreboard to (or input 0 to go back):\n";
    std::string exDir;
    std::getline(std::cin, exDir);
    if (exDir == "0")
    {
        std::cout << "----------------\n";
        system("cls");
        return;
    }
    if (exDir[exDir.size() - 1] == '\\' && exDir[exDir.size() - 1] == '/') exDir.erase(exDir.begin() + exDir.size() - 1);

    std::fstream output;
    output.open(exDir + "/scoreboard.csv", std::ios::out);
    if (!output.good() && !output.is_open()) {
        std::cout << "Invalid export directory\n";
        system("pause");
        system("cls");
        return;
    }

    output << "no,studentID,fullname,midtermmark,finalmark,othermark,totalmark";

    int count = 1;
    Course* cur = data.course;      //Courses change each semester so there wont be no duplicates
    bool foundCourse = 0, foundStudent = 0;
    while (cur != nullptr)
    {
        if (cur -> courseId == courseId)
        {
            Student* curStudent = cur -> courseStudentHead;
            if (curStudent != nullptr) output << std::endl;
            while (curStudent != nullptr)
            {
                CourseScore* curCourseScore = data.courseScore;
                while (curCourseScore != nullptr) {
                    if (curCourseScore->studentID == curStudent->studentID) {
                        output << count << ","
                        << curStudent -> studentID << ","
                        << curStudent -> firstName + " " + curStudent -> lastName << ","
                        << curCourseScore->midterm << "," << curCourseScore->final << "," << curCourseScore->other << "," << curCourseScore->total;

                        if (curStudent -> nodeNext != nullptr)
                        output << std::endl;

                        count++;

                        foundStudent = 1;
                    }
                    curCourseScore = curCourseScore->nodeNext;
                }
                curStudent = curStudent -> nodeNext;
            }
            foundCourse = 1;
            if (!foundStudent) break;
        }
        cur = cur -> nodeNext;
    }

    if (!foundCourse) std::cout << "Could not find that course.\n";
    else if (!foundStudent) std::cout << "Could not find student in course " << cur->courseId << "\n";
    else std::cout << "File exported successfully!\n";
}

void importScoreboardTeacher() {
    std::cout << "Input the directory of the \"scoreboard.csv\" to import the scoreboard FROM:\n";
    std::string fromDir;
    std::getline(std::cin, fromDir);
    std::fstream fin(fromDir, std::ios::in);
    if (fin.is_open()) {
        std::cout << "File not found\n";
        system("pause"); system("cls");
        return;
    }

    std::cout << "Input the directory of the \"scoreboard.csv\" to import the scoreboard TO:\n";
    std::string toDir;
    std::getline(std::cin, toDir);
    

}

// Update scoreboard of a course
void updateScoreboard(Login& data)
{
    std::cout << "Input ID of a course to update scoreboard (or input 0 to go back): ";
    std::string courseId;
    std::getline(std::cin, courseId);

    if (courseId == "0")
    {
        std::cout << "----------------\n";
        system("cls");
        return;
    }

    bool check = false;
    Course* curCourse = data.course;
    while (curCourse != nullptr)
    {
        if (curCourse -> courseId == courseId)
        {
            check = true;
            break;
        }
        curCourse = curCourse -> nodeNext;
    }

    if (!check)
    {
        std::cout << "Could not find that course.\n";
        std::cout << "----------------\n";
        return;
    }

    std::string course, temp;
    std::string dir = "data/" + std::to_string(data.year) + "/semesters/"
    + std::to_string(data.semester);

    std::fstream output;
    output.open(dir + "/scoreboard.csv", std::ios::out);
    output << "no,courseID,studentID,fullname,midtermmark,finalmark,othermark,totalmark\n";

    int count = 1;
    course = curCourse -> courseId;

    std::fstream input;
    input.open(dir + "/" + course + "/scoreboard.csv", std::ios::in);
    if (!input.good()) {
        std::cout << "No \"scoreboard.csv\" for course " << course << " found. Skipping...\n";
        return;
    }

    getline(input, temp);

    while (!input.eof())
    {
        getline(input, temp, ',');
        output << count << ",";
        count++;

        output << course << ",";

        for (int i = 0; i < 5; i++)
        {
            getline(input, temp, ',');
            output << temp << ",";
        }

        getline(input, temp);
        output << temp;

        if (curCourse -> nodeNext != nullptr || !input.eof())
        output << std::endl;
    }

    if (data.semester != -1) readScoreboard(data.courseSem1, data.year, data.semester);
    if (data.semester == 1) data.courseScore = data.courseSem1;
    else if (data.semester == 2) data.courseScore = data.courseSem2;
    else if (data.semester == 3) data.courseScore = data.courseSem3;
    else data.courseScore = nullptr;

    std::cout << "Scoreboard for course " << course << " successfully updated.\n";
    std::cout << "----------------\n";
    return;
}

// Import all scoreboards
void importScoreboard(Login& data)
{
    std::string course, temp;
    std::string dir = "data/" + std::to_string(data.year) + "/semesters/"
    + std::to_string(data.semester);

    std::fstream output;
    output.open(dir + "/scoreboard.csv", std::ios::out);
    output << "no,courseID,studentID,fullname,midtermmark,finalmark,othermark,totalmark\n";

    int count = 1;
    Course* curCourse = data.course;
    while (curCourse != nullptr)
    {
        course = curCourse -> courseId;

        std::fstream input;
        input.open(dir + "/" + course + "/scoreboard.csv", std::ios::in);
        if (!input.good()) {
            std::cout << "No \"scoreboard.csv\" for course " << course << " found. Skipping...\n";
            curCourse = curCourse->nodeNext;
            continue;
        }

        getline(input, temp);

        while (!input.eof())
        {
            getline(input, temp, ',');
            output << count << ",";
            count++;

            output << course << ",";

            for (int i = 0; i < 5; i++)
            {
                getline(input, temp, ',');
                output << temp << ",";
            }

            getline(input, temp);
            output << temp;

            if (curCourse -> nodeNext != nullptr || !input.eof())
            output << std::endl;
        }
        std::cout << "\"scoreboard.csv\" for course " << course << " imported.\n";

        curCourse = curCourse -> nodeNext;
    }

    readScoreboard(data.courseSem1, data.year, 1);
    readScoreboard(data.courseSem2, data.year, 2);
    readScoreboard(data.courseSem3, data.year, 3);
    if (data.semester == 1) data.courseScore = data.courseSem1;
    else if (data.semester == 2) data.courseScore = data.courseSem2;
    else if (data.semester == 3) data.courseScore = data.courseSem3;
    else data.courseScore = nullptr;

    std::cout << "Scoreboard imported!\n";
    std::cout << "----------------\n";
    return;
}

// View scoreboard of a course
void viewScoreboardCourse(Login data)
{
	std::ios_base::fmtflags f(std::cout.flags());
    std::cout << "Input ID of a course to view (or input 0 to go back): ";
    std::string courseId;
    std::getline(std::cin, courseId);

    if (courseId == "0")
    {
        std::cout << "----------------\n";
        system("cls");
        return;
    }

    bool check = false;
    Course* curCourse = data.course;
    while (curCourse != nullptr)
    {
        if (curCourse -> courseId == courseId)
        {
            check = true;
            break;
        }
        curCourse = curCourse -> nodeNext;
    }

    if (!check)
    {
        std::cout << "Could not find that course.\n";
        std::cout << "----------------\n";
        return;
    }

    std::fstream input;
    std::string dir = "data/" + std::to_string(data.year) + "/semesters/"
    + std::to_string(data.semester) + "/" + courseId + "/scoreboard.csv";

    input.open(dir, std::ios::in);

    if (!input.good()) {
        std::cout << "No appropriate \"scoreboard.csv\" found. Consider exporting students from course " << courseId << " to \"scoreboard.csv\" first.\n";
        return;
    }

    std::string str;
    std::getline(input, str);

    std::cout << "----------------\n";
    std::cout << std::left << std::setfill(' ')
    << std::setw(5) << "No"
    << std::setw(13) << "Student ID"
    << std::setw(20) << "Full Name"
    << std::setw(10) << "Midterm"
    << std::setw(10) << "Final"
    << std::setw(10) << "Other"
    << std::setw(10) << "Total" << std::endl;

    if (input.eof()) std::cout << "No course score data found\n";
    while (!input.eof())
    {
        std::getline(input, str, '\n');
        std::istringstream iss(str);
        std::string item;

        std::getline(iss, item, ',');
        std::cout << std::setw(5) << item;

        std::getline(iss, item, ',');
        std::cout << std::setw(13) << item;

        std::getline(iss, item, ',');
        std::cout << std::setw(20) << item;

        while (std::getline(iss, item, ','))
        {
            std::cout << std::setw(10) << item;
        }

        std::cout << std::endl;
    }

    std::cout << "----------------\n";
	std::cout.flags(f);
    return;
}

// Update a student result
void updateStudentResult(Login data)
{
    std::string courseId, studentId;
    float mid, final, other, total;
    bool check = false;

    std::cout << "Input student ID to update result (or input 0 to go back): ";
    std::getline(std::cin, studentId);

    if (studentId == "0")
    {
        std::cout << "----------------\n";
        system("cls");
        return;
    }

    Student* curStudent = data.student;
    while (curStudent != nullptr)
    {
        if (curStudent -> studentID == studentId)
        {
            check = true;
            break;
        }
        curStudent = curStudent -> nodeNext;
    }

    if (!check)
    {
        std::cout << "Could not find that student.\n";
        std::cout << "----------------\n";
        return;
    }

    check = false;

    std::cout << "Input course ID to update result (or input 0 to go back): ";
    std::getline(std::cin, courseId);

    if (courseId == "0")
    {
        std::cout << "----------------\n";
        return;
    }

    Course* curCourse = data.course;
    while (curCourse != nullptr)
    {
        if (curCourse -> courseId == courseId)
        {
            check = true;
            break;
        }
        curCourse = curCourse -> nodeNext;
    }

    if (!check)
    {
        std::cout << "Could not find that course.\n";
        std::cout << "----------------\n";
        return;
    }

    std::cout << "Input Midterm Mark: ";
    std::cin >> mid;

    std::cout << "Input Final Mark: ";
    std::cin >> final;

    std::cout << "Input Other Mark: ";
    std::cin >> other;

    std::cin.ignore(10000, '\n');

    total = getTotalMark(mid, final, other);

    CourseScore* curCourseScore = data.courseScore;
    while (curCourseScore != nullptr)
    {
        if (curCourseScore -> studentID == studentId && curCourseScore -> courseID == courseId)
        {
            curCourseScore -> midterm = std::to_string(mid);
            curCourseScore -> final = std::to_string(final);
            curCourseScore -> other = std::to_string(other);
            curCourseScore -> total = std::to_string(total);
            break;
        }
        curCourseScore = curCourseScore -> nodeNext;
    }

    writeScoreboard(data.courseScore, data.year, data.semester);

    std::cout << "Student result updated!\n";
    std::cout << "----------------\n";
    return;
}

// View scoreboard of a student
void viewScoreboardStudent(Login data, std::string studentID)
{
	std::ios_base::fmtflags f(std::cout.flags());
    std::cout << std::left << std::setfill(' ')
    << std::setw(15) << "Course"
    << std::setw(10) << "Midterm"
    << std::setw(10) << "Final"
    << std::setw(10) << "Other"
    << std::setw(10) << "Total" << std::endl;

    float sum, gpa;
    int count = 0;

    if (data.semester > 0)
    {
        CourseScore* curSem1 = data.courseSem1;
        while (curSem1 != nullptr)
        {
            if (curSem1 -> studentID == studentID)
            {
                sum += std::stof(curSem1 -> total);
                count++;
            }
            curSem1 = curSem1 -> nodeNext;
        }

        gpa += (sum / (10 * count)) * 4;
        sum = 0, count = 0;
    }

    if (data.semester > 1)
    {
        CourseScore* curSem2 = data.courseSem2;
        while (curSem2 != nullptr)
        {
            if (curSem2 -> studentID == studentID)
            {
                sum += std::stof(curSem2 -> total);
                count++;
            }
            curSem2 = curSem2 -> nodeNext;
        }

        gpa += (sum / (10 * count)) * 4;
        if (data.semester == 2) gpa = gpa / 2;
        sum = 0, count = 0;
    }

    if (data.semester > 2)
    {
        CourseScore* curSem3 = data.courseSem3;
        while (curSem3 != nullptr)
        {
            if (curSem3 -> studentID == studentID)
            {
                sum += std::stof(curSem3 -> total);
                count++;
            }
            curSem3 = curSem3 -> nodeNext;
        }

        gpa += (sum / (10 * count)) * 4;
        gpa = gpa / 3;
        sum = 0, count = 0;
    }

    CourseScore* curCourseScore = data.courseScore;
    while (curCourseScore != nullptr)
    {
        if (curCourseScore -> studentID == studentID)
        {
            sum += std::stof(curCourseScore -> total);
            count++;

            std::cout << std::setw(15) << curCourseScore -> courseID
            << std::setw(10) << curCourseScore -> midterm
            << std::setw(10) << curCourseScore -> final
            << std::setw(10) << curCourseScore -> other
            << std::setw(10) << curCourseScore -> total << std::endl;
        }
        curCourseScore = curCourseScore -> nodeNext;
    }
	std::cout.flags(f);

    std::cout << "Average: " << sum / count << std::endl
    << "GPA: " << (sum / (10 * count)) * 4 << std::endl
    << "Overall GPA: " << gpa << std::endl;
    std::cout << "----------------\n";
    return;
}

// View scoreboard of a class
void viewScoreboardClass(Login data)
{
    std::string classID;
    std::cout << "Input class ID to view scoreboard (or input 0 to go back): ";
    std::getline(std::cin, classID);

    if (classID == "0")
    {
        std::cout << "----------------\n";
        system("cls");
        return;
    }

    classID = toUpper_w(classID);

    bool check = false;
    Student* curStudent = data.student;
    while (curStudent != nullptr)
    {
        if (curStudent -> classID == classID)
        {
            check = true;
            break;
        }
        curStudent = curStudent -> nodeNext;
    }

    if (!check)
    {
        std::cout << "Could not find that class.\n";
        std::cout << "----------------\n";
        return;
    }

    std::cout << "----------------\n";
    std::string studentPrinted;

    CourseScore* curCourseScore = data.courseScore;
    bool found = 0;
    while (curCourseScore != nullptr)
    {
        curStudent = data.student;
        while (curStudent != nullptr)
        {
            if (curCourseScore -> studentID == curStudent -> studentID && curStudent -> classID == classID)
            {
                if (studentPrinted.find(curCourseScore -> studentID) == std::string::npos)
                {
                    studentPrinted += "-" + curCourseScore -> studentID;
                    std::cout << curCourseScore -> studentID << " - " << curCourseScore -> fullname << std::endl;
                    viewScoreboardStudent(data, curCourseScore -> studentID);
                    found = 1;
                    break;
                }
            }
            curStudent = curStudent -> nodeNext;
        }
        curCourseScore = curCourseScore -> nodeNext;
    }

    if (!found) std::cout << "No student data found\n";

    return;
}

void viewMyScoreboard(Login& data) {
	std::ios_base::fmtflags f(std::cout.flags());

    std::cout << std::left << std::setfill(' ')
    << std::setw(15) << "Course"
    << std::setw(10) << "Midterm"
    << std::setw(10) << "Final"
    << std::setw(10) << "Other"
    << std::setw(10) << "Total" << std::endl;

    Student* curStudent = data.student;
    bool isValidUsername = 0;
    while (curStudent != nullptr) {
        if (curStudent->usr == data.username) {
            isValidUsername = 1;
            break;
        }
        curStudent = curStudent->nodeNext;
    }

    bool found = 0;
    if (isValidUsername) {
        CourseScore* curCourseScore = data.courseScore;
        while (curCourseScore != nullptr)
        {
            if (curStudent->studentID == curCourseScore->studentID)
            {
                found = 1;
                std::cout << std::setw(15) << curCourseScore -> courseID
                << std::setw(10) << curCourseScore -> midterm
                << std::setw(10) << curCourseScore -> final
                << std::setw(10) << curCourseScore -> other
                << std::setw(10) << curCourseScore -> total << std::endl;
            }
            curCourseScore = curCourseScore -> nodeNext;
        }
    }
    if (!found) std::cout << "Scoreboard data on student ID " << curStudent->studentID <<" was either not found or not updated\n";
	std::cout.flags(f);
}