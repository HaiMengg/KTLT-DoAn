#include "create.h"

void createClass(Node*& nodeHead, std::fstream& dataFile, int startYear) {
    std::string categories;
    dataFile >> categories;
    //Print currently existing classes
    std::cout << "Currently existing classes of the school year " << startYear << "-" << startYear + 1 << ":\n";
    if (nodeHead != nullptr) printListSingle(nodeHead, false);
    else std::cout << "No class data found" << std::endl;

    bool inserted = 0;
    while (!inserted) {
        std::cout << "Enter a new class ID (you can't enter an existing class ID)\nor a directory to a \"input.csv\" file\nformat: \"classID\":" << std::endl;
        std::string classInput;
        std::getline(std::cin, classInput);

        std::string dir = "((([A-Z]|[a-z])+(\\:)+(\\/|\\\\)+.+input.csv)|(([A-Z]|[a-z])+(\\:)+(\\/|\\\\)+input.csv)|(.+input.csv)|input.csv)";
        std::regex regexDir(dir);
        std::smatch searchResult;
        if (std::regex_search(classInput, searchResult, regexDir)) {
            std::fstream fInput(searchResult.str(), std::ios::in);
            if (fInput.is_open()) {
                SNode* fInputBatch = nullptr;

                createList(fInputBatch, fInput);
                appendListBatch(nodeHead, fInputBatch, dataFile);

                destructList(fInputBatch);

                inserted = 1;
            }
            else std::cout << "\"" << searchResult.str() << "\" doesn't exist." << std::endl;
        }
        else {
            appendListSingle(nodeHead, classInput, dataFile);
            inserted = 1;
        }
    }
}