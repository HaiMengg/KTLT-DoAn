#include "create.h"

void create(Node*& schoolYears) {
	std::cout << "What do you want to create: " << std::endl;
	std::cout << "1. School year\n2. Semester\nInput: ";
	int choice;
	std::cin >> choice;

	switch(choice) {
		case 1:
		std::ifstream finSchoolYears("schoolyears.txt");
		createList(schoolYears, finSchoolYears);
		createSchoolYear(schoolYears);
		break;
	}
}

void createSchoolYear(Node*& nodeHead) {
    //Print currently existing school years
	std::cout << "Currently existing school year:\n";
    Node* nodeCurr = nodeHead;
	do {
		std::cout << std::stoi(nodeCurr->value) << "-" << std::stoi(nodeCurr->value) + 1 << std::endl;
        nodeCurr = nodeCurr->nodeNext;
	} while (nodeCurr != nodeHead);
	std::cout << "Enter the start of the new school year (you can't create an existing school year): ";
	int start;
	std::cin >> start;

    //Create and append the new school year to the current list
	Node* nodeNew = new Node;
    nodeNew->value = start;
    nodeNew->nodeNext = nullptr;
    nodeCurr->nodeNext = nodeNew;
}