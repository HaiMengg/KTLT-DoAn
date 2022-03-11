#include "create.h"

void createClass(Node*& nodeHead, std::fstream& dataFile) {
    //Print currently existing classes
    std::cout << "Currently existing classes and their start year:\n";
    if (nodeHead != nullptr) printListSingle(nodeHead, false);
    else std::cout << "No class data found" << std::endl;

    std::cout << "Enter a new class ID (you can't enter an existing class ID) or a directory to a file (format: classID1,classID2,classID3,...): ";
    std::string classInput;
    std::getline(std::cin, classInput);
}