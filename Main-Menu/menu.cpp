#include "menu.h"

void currentMenu(Node& data, std::fstream& schoolYearData, std::fstream& classData, std::fstream& studentData) {
    bool cont = 1;
    do {
        std::cout << "Which action do you want to take?\n"
        << "create school year: create a new school year\n"
        << "create class: create new class/classes\n"
        << "add students: add new students to a class\n"
        << "view: get access to the view feature (from which you can perform further actions)\n"
        << "exit: exit the program\n: ";

        std::string choice;
        std::getline(std::cin, choice);

        // if (choice == "view") level = 1;
        if (choice == "create school year") {
            std::string schoolYearInput;
            inputSchoolYear(data.schoolYearHead, schoolYearInput);
            createSchoolYear(data.schoolYearHead, schoolYearData, schoolYearInput);
        }
        else if (choice == "create class")
            createClassMenu(data.classesHead, classData);
        else if (choice == "add students")
            addStudentMenu(data.studentHead, studentData);
        else if (choice == "view")
            viewMenu(data);
        else if (choice == "exit") cont = 0;
        else std::cout << "Invalid action\n";

        std::cout << std::endl << "================================================" << std::endl << std::endl;
        system("pause");
    } while (cont);
}

void createClassMenu(Classes*& classHead, std::fstream& classData) {
    std::cout << "Enter the school year to create a new class for: ";
    int currentSchoolYear;
    std::cin >> currentSchoolYear;
    std::cin.ignore(10000, '\n');

    createClass(classHead, classData, currentSchoolYear);
}

void addStudentMenu(Student* studentHead, std::fstream& studentData) {
    std::cout << "Enter the school year in which a class was created: ";
    int currentSchoolYear;
    std::cin >> currentSchoolYear;
    std::cin.ignore(10000, '\n');

    std::cout << "Enter the class to add new students: ";
    std::string currentClass;
    std::getline(std::cin, currentClass);

    addStudentsToClass(studentHead, studentData, currentSchoolYear, currentClass);
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
        if (choice == "school year") viewSchoolYear(allData.schoolYearHead);
        else if (choice == "class") viewClasses(allData.classesHead);
        else if (choice == "back") back = 1;
        else std::cout << "Invalid choice\n";
        system("pause");
        std::cout << std::endl;
    } while (!back);
}

