#include "create.h"

void create(Node*& schoolYears) {
	std::cout << "What do you want to create: " << std::endl;
	std::cout << "1. School year\n2. Semester\nInput: ";
	int choice;
	std::cin >> choice;

	switch(choice) {
		case 1:
		std::fstream finSchoolYears("Create-School-Year/data/schoolyears.txt", std::ios::in | std::ios::app);
		createList(schoolYears, finSchoolYears);
		createSchoolYear(schoolYears, finSchoolYears);
		break;
	}
}

void createSchoolYear(Node*& nodeHead, std::fstream& dataFile) {
    //Print currently existing school years
	std::cout << "Currently existing school years:\n";
    Node* nodeCurr = nodeHead;
	if (nodeHead != nullptr) {
		do {
			std::cout << std::stoi(nodeCurr->value) << "-" << std::stoi(nodeCurr->value) + 1 << std::endl;
			nodeCurr = nodeCurr->nodeNext;
		} while (nodeCurr != nodeHead);
	}
	else std::cout << "No school year data found" << std::endl;

	std::cout << "Enter the start of the new school year (you can't create an existing school year): ";
	std::string start = "";
	do {
		//Display this message if "start" is already input but is invalid
		if (start != "") std::cout << "You can't create an existing school year. Enter another school year: ";
		std::cin >> start;
	} while (listSearchBool(nodeHead, start));

    //Create and append the new school year to the current list
	appendListSingle(nodeHead, start, dataFile);
}