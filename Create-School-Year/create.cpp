#include "create.h"

//Print currently existing school years
void viewSchoolYear(SchoolYear* schoolYearHead) {
	std::cout << "\n";
	std::cout << "Currently existing school years:\n";
    SchoolYear* schoolYearCurr = schoolYearHead;
	if (schoolYearHead != nullptr) {
		do {
			std::cout << schoolYearCurr->schoolYear << "-" << schoolYearCurr->schoolYear + 1 << std::endl;
			schoolYearCurr = schoolYearCurr->nodeNext;
		} while (schoolYearCurr != schoolYearHead && schoolYearCurr != nullptr);
	}
	else std::cout << "No school year data found" << std::endl;
	std::cout << "\n";
}

void inputSchoolYear(SchoolYear* schoolYearHead, std::string& inputYear) {
	bool valid = 0;
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

		if (inputYear != "" && isDigit_w(inputYear) && schoolYearSearchBool(schoolYearHead, stoi(inputYear))) valid = 1;
		std::cout << "Enter the start of the new school year (you can't create an existing school year) (enter \"0\" to return to main menu): ";
		std::getline(std::cin, inputYear);
		if (inputYear == "0") return;
	} while (!valid);
}

void createSchoolYear(SchoolYear*& schoolYearHead, std::fstream& dataFile, std::string inputYear) {
    //Create and append the new school year to the current list
	appendNewYearList(schoolYearHead, stoi(inputYear));
	appendNewYearFile(dataFile, stoi(inputYear));

	std::string newDir = "data/" + inputYear;
	mkdir(newDir.c_str());
	newDir = "data/" + inputYear + "/classes";
	mkdir(newDir.c_str());
	newDir = "data/" + inputYear + "/semesters";
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