#include "menu.h"

void currentMenu(Node& data, std::fstream& schoolYearData, std::fstream& classData, std::fstream& studentData) {
    bool cont = 1;
    while (cont) {
        std::cout << "Which action do you want to take?\n"
        << "create school year: create a new school year\n"
        << "create class: create new class/classes\n"
        << "view: get access to the view feature (from which you can perform further actions)\n"
        << "exit: exit the program\n:";

        std::string choice;
        std::getline(std::cin, choice);

        // if (choice == "view") level = 1;
        if (choice == "create school year") {
            std::string schoolYearInput;
            inputSchoolYear(data.schoolYearHead, schoolYearInput);
            createSchoolYear(data.schoolYearHead, schoolYearData, schoolYearInput);
        }
        if (choice == "create class") {
            createClassMenu(data.classesHead, classData);
        }
        if (choice == "exit") cont = 0;

        std::cout << std::endl << "================================================" << std::endl;
    }
}

void createClassMenu(Classes*& classHead, std::fstream& classData) {
    std::cout << "Enter the school year to create a new class for: ";
    int currentSchoolYear;
    std::cin >> currentSchoolYear;
    std::cin.ignore(10000, '\n');

    createClass(classHead, classData, currentSchoolYear);
}

int viewMenu() {
    std::cout << "Which do you want to view?\n"
    << "all school years: view all school years\n"
    << "school year [school_year]: view a specified school years\n:";
    std::string choice;
    std::getline(std::cin, choice);

    if (choice == "all school years") return 9;
    else if (choice.find("school year")) return 10 + stoi(choice.substr(choice.size() - 5, 4));
    else std::cout << "Invalid choice. Returning to previous menu";
    return 0;
}

