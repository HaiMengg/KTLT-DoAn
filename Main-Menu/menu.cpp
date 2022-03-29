#include "menu.h"

void currentMenu(Node& data, std::fstream& schoolYearData, std::fstream& classData, std::fstream& studentData, std::fstream& semesterData) {
    bool cont = 1;
    do {
        std::cout << "Which action do you want to take?\n"
        << "create school year: create a new school year\n"
        << "create class: create new class/classes\n"
        << "add students: add new students to a class\n"
        << "create semester: create new semester/semesters\n"
        << "add course: add new course/courses to semester\n"
        << "view: get access to the view feature (from which you can perform further actions)\n"
        << "exit: exit the program\n: ";

        std::string choice;
        std::getline(std::cin, choice);
        choice = toLower_w(choice);

        // if (choice == "view") level = 1;
        if (choice == "create school year")
            createSchoolYearMenu(data.schoolYearHead, schoolYearData);
        else if (choice == "create class")
            createClassMenu(data.classesHead, classData, data.schoolYearHead);
        else if (choice == "add students")
            addStudentMenu(data.studentHead, studentData, data.schoolYearHead, data.classesHead);
        else if (choice == "create semester")
            createSemesterMenu(data.semesterHead, semesterData, data.schoolYearHead);
        else if (choice == "add course")
            addCourseMenu(data.semesterHead, data.schoolYearHead);
        else if (choice == "view")
            viewMenu(data);
        else if (choice == "exit") cont = 0;
        else std::cout << "Invalid action\n";

        std::cout << std::endl << "================================================" << std::endl << std::endl;
        system("pause");
        system("cls");
    } while (cont);
}

void createSchoolYearMenu(SchoolYear*& schoolYearHead, std::fstream& schoolYearData) {
    bool valid = 0;
    std::string inputYear;
	do {
		if (inputYear != "" && !isDigit_w(inputYear)) {
			std::cout << "Invalid year\n";
			valid = 0;
		}
		else {
			if (inputYear != "" && schoolYearSearchBool(schoolYearHead, stoi(inputYear))) {
				std::cout << "You can't create an existing school year.\n";
				valid = 0;
			}
		}

		std::cout << "Enter the start of the new school year (you can't create an existing school year) (enter \"0\" to return to main menu): ";
		std::getline(std::cin, inputYear);
		if (inputYear == "0") return;
		if (inputYear != "" && isDigit_w(inputYear) && !schoolYearSearchBool(schoolYearHead, stoi(inputYear))) valid = 1;
	} while (!valid);

    createSchoolYear(schoolYearHead, schoolYearData, inputYear);
}

void createClassMenu(Classes*& classHead, std::fstream& classData, SchoolYear* schoolYearHead) {
    bool valid = 0;
    std::string currentSchoolYear = "a";
    while (!valid) {
        std::cout << "Enter the school year to create new class for (enter \"0\" to return to previous menu): ";
        std::getline(std::cin, currentSchoolYear);
        if (currentSchoolYear == "0") return;
        if (!isDigit_w(currentSchoolYear)) { std::cout << "Invalid year\n"; continue; }
        if (!schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) std::cout << "School year \"" + currentSchoolYear + "\" doesn't exist in current database\n";
        if (isDigit_w(currentSchoolYear) && schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) valid = 1;
    }
    createClass(classHead, classData, stoi(currentSchoolYear));
}

void addStudentMenu(Student*& studentHead, std::fstream& studentData, SchoolYear* schoolYearHead, Classes*& classesHead) {
    bool valid = 0;
    std::string currentSchoolYear = "a";
    while (!valid) {
        std::cout << "Enter the school year in which a class was created (enter \"0\" to return to previous menu): ";
        std::getline(std::cin, currentSchoolYear);
        if (currentSchoolYear == "0") return;
        if (!isDigit_w(currentSchoolYear)) { std::cout << "Invalid year\n"; continue; }
        if (!schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) std::cout << "School year \"" + currentSchoolYear + "\" doesn't exist in the current database\n";
        if (isDigit_w(currentSchoolYear) && schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) valid = 1;
    }
    
    std::string currentClass = "";
    while (!classListSearchBool(classesHead, currentClass, stoi(currentSchoolYear))) {
        std::cout << "Enter the class to add new students (enter \"0\" to return to previous menu): ";
        std::getline(std::cin, currentClass);
        if (currentClass == "0") return;
        currentClass = toUpper_w(currentClass);
        if (!classListSearchBool(classesHead, currentClass, stoi(currentSchoolYear))) std::cout << "Class \"" + currentClass + "\" of year \"" + currentSchoolYear + "\" doesn't exist in current database\n";
    }

    addStudentsToClass(studentHead, studentData, stoi(currentSchoolYear), currentClass, classesHead);
}

void createSemesterMenu(Semesters*& semesterHead, std::fstream& semesterData, SchoolYear* schoolYearHead) {
    bool valid = 0;
    std::string currentSchoolYear = "a";
    while (!valid) {
        std::cout << "Enter the school year to create new semester for (enter \"0\" to return to previous menu): ";
        std::getline(std::cin, currentSchoolYear);
        if (currentSchoolYear == "0") return;
        if (!isDigit_w(currentSchoolYear)) { std::cout << "Invalid year\n"; continue; }
        if (!schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) std::cout << "School year \"" + currentSchoolYear + "\" doesn't exist in current database\n";
        if (isDigit_w(currentSchoolYear) && schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) valid = 1;
    }
    createSemester(semesterHead, semesterData, stoi(currentSchoolYear));
}

void addCourseMenu(Semesters*& semesterHead, SchoolYear* schoolYearHead) {
    bool valid = 0;
    std::string currentSchoolYear = "a";
    while (!valid) {
        std::cout << "Enter the school year to create new course for (enter \"0\" to return to previous menu): ";
        std::getline(std::cin, currentSchoolYear);
        if (currentSchoolYear == "0") return;
        if (!isDigit_w(currentSchoolYear)) { std::cout << "Invalid year\n"; continue; }
        if (!schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) std::cout << "School year \"" + currentSchoolYear + "\" doesn't exist in current database\n";
        if (isDigit_w(currentSchoolYear) && schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) valid = 1;
    }
    addCourseToSemester(semesterHead, stoi(currentSchoolYear));
}

void viewMenu(Node allData) {
    bool back = 0;

    do {
        std::cout << "Which do you want to view?\n"
        << "school year: view all school years\n"
        << "class: view single class/classes\n"
        << "back: back to previous menu\n: ";
        std::string choice;
        std::getline(std::cin, choice);
        choice = toLower_w(choice);
        if (choice == "school year") viewSchoolYear(allData.schoolYearHead);
        else if (choice == "class") viewClasses(allData.classesHead);
        else if (choice == "back") back = 1;
        else std::cout << "Invalid choice\n";
        system("pause");
        std::cout << std::endl;
    } while (!back);
}

