#include "create.h"

void createClass(Node*& nodeHead, std::fstream& dataFile) {
    //Print currently existing classes
    std::cout << "Currently existing classes and their start year:\n";
    if (nodeHead != nullptr) printListSingle(nodeHead, false);
    else std::cout << "No class data found" << std::endl;

    std::cout << "Enter a new class ID (you can't enter an existing class ID) or a directory to the input file\n(format:\nclassID1\nclassID2\nclassID3,...):" << std::endl;
    std::string classInput;
    std::getline(std::cin, classInput);
    std::cin.ignore(10000, '\n');

    std::string dir = "(([A-Z]|[a-z])+(\\:)+(\\/)+.+input.txt)";
    std::regex regexDir(dir);
    if (std::regex_search(classInput, std::regex(regexDir))) {
        std::fstream fInput(dir, std::ios::in);
        SNode* fInputBatch = nullptr;

        createList(fInputBatch, fInput);
        appendListBatch(nodeHead, fInputBatch, dataFile);

        destructList(fInputBatch);
    }
    else {
        appendListSingle(nodeHead, classInput, dataFile);
    }
}