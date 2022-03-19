#include "create.h"

// void create(Node*& schoolYears) {
// 	std::cout << "What do you want to create: " << std::endl;
// 	std::cout << "1. School year\n2. Semester\nInput: ";
// 	int choice;
// 	std::cin >> choice;

// 	switch(choice) {
// 		case 1:
// 		std::fstream finSchoolYears("data/schoolyear.csv", std::ios::in | std::ios::app);
// 		createList(schoolYears, finSchoolYears);
// 		createSchoolYear(schoolYears, finSchoolYears);
// 		break;
// 	}
// }

void createSchoolYear(SchoolYear*& schoolYearHead, std::fstream& dataFile) {
    //Print currently existing school years
	std::cout << "Currently existing school years:\n";
    SchoolYear* schoolYearCurr = schoolYearHead;
	if (schoolYearHead != nullptr) {
		do {
			std::cout << schoolYearCurr->schoolYear << "-" << schoolYearCurr->schoolYear + 1 << std::endl;
			schoolYearCurr = schoolYearCurr->nodeNext;
		} while (schoolYearCurr != schoolYearHead);
	}
	else std::cout << "No school year data found" << std::endl;

	std::cout << "Enter the start of the new school year (you can't create an existing school year): ";
	std::string inputYear = "";
	do {
		//Display this message if "start" is already input but is invalid
		if (inputYear != "") std::cout << "You can't create an existing school year. Enter another school year: ";
		std::getline(std::cin, inputYear);
	} while (schoolYearSearchBool(schoolYearHead, stoi(inputYear)));

    //Create and append the new school year to the current list
	appendNewYearList(schoolYearHead, stoi(inputYear));
	appendNewYearFile(dataFile, stoi(inputYear));

	std::string newDir = "data/" + inputYear;
	mkdir(newDir.c_str());
	newDir = "data/" + inputYear + "/classes";
	mkdir(newDir.c_str());
	newDir = "data/" + inputYear + "/courses";
	mkdir(newDir.c_str());
}

bool schoolYearSearchBool(SchoolYear* schoolYearHead, int searchYear) {
	while (schoolYearHead != nullptr) {
		if (schoolYearHead->schoolYear == searchYear) return 1;
		schoolYearHead = schoolYearHead->nodeNext;
	}
	return 0;
}

void appendNewYearList(SchoolYear*& schoolYearHead, int newYear) {
    SchoolYear* nodeNew = new SchoolYear;
    nodeNew->schoolYear = newYear;

	if (schoolYearHead == nullptr) {
		nodeNew->nodePrev = nullptr;
		nodeNew->nodeNext = nullptr;
		schoolYearHead = nodeNew;
		return;
	}

	SchoolYear* nodeCurr = schoolYearHead;
	while (nodeCurr->nodeNext != nullptr) {
		nodeCurr = nodeCurr->nodeNext;
	}
	nodeNew->nodePrev = nodeCurr;
	nodeNew->nodeNext = nullptr;
	nodeCurr->nodeNext = nodeNew;
}
void appendNewYearFile(std::fstream& dataFile, int newYear) {
	if (dataFile.eof()) dataFile.clear();       //Resets dataFile's EOF state flag
	dataFile << std::endl << newYear;
	dataFile.flush();
}