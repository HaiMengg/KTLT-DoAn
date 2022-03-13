#include "create.h"

void createClass(Node*& nodeHead, std::fstream& dataFile, int startYear) {
    std::string categories;
    getline(dataFile, categories);
    //Print currently existing classes
    std::cout << "Currently existing classes of the school year " << startYear << "-" << startYear + 1 << ":\n";
    if (nodeHead != nullptr) printListSingle(nodeHead, false);
    else std::cout << "No class data found" << std::endl;

    bool inserted = 0;
    while (!inserted) {
        std::cout << "Enter a new class ID (you can't enter an existing class ID)\n"
        << "or a directory to a \"input.csv\" file\n"
        << "(format: \"classID\"):\n";
        std::string classInput;
        std::getline(std::cin, classInput);

        std::string dir = "((([A-Z]|[a-z])+(\\:)+(\\/|\\\\)+.+input.csv)|(([A-Z]|[a-z])+(\\:)+(\\/|\\\\)+input.csv)|(.+input.csv)|input.csv)";
        std::regex regexDir(dir);
        std::smatch searchResult;
        //Check for valid directory input
        if (std::regex_search(classInput, searchResult, regexDir)) {
            std::fstream fInput(searchResult.str(), std::ios::in);
            //Check if file (directory) exists
            if (fInput.is_open()) {
                SNode* fInputBatch = nullptr;

                createList(fInputBatch, fInput);
                appendListBatch(nodeHead, fInputBatch);
                appendFileBatch(fInputBatch, dataFile);

                destructList(fInputBatch);

                inserted = 1;
            }
            else std::cout << "\"" << classInput << "\" doesn't exist." << std::endl;
        }
        //Runs if a directory isn't entered
        else {
            //This won't check for .csv file since it's already checked previously
            if (std::regex_search(classInput, std::regex("((([A-Z]|[a-z])+(\\:)+(\\/|\\\\)+(.)+)|(([A-Z]|[a-z])+(\\:)+(\\/|\\\\)+(.)+)|(([A-Z]|[a-z])+(\\/|\\\\)+(.)+))")))
                std::cout << "\"" << classInput << "\" doesn't exist." << std::endl;
            else {
                appendListSingle(nodeHead, classInput);
                appendFileSingle(classInput, dataFile);
                inserted = 1;
            }
        }
    }
}

void addStudentsToClass(Node*& totalStudentHead, std::fstream& totalFile, int schoolYear, std::string currentClass) {
    std::string classFileDir = "data/" + std::to_string(schoolYear) + "/classes/" + currentClass;
    _mkdir(classFileDir.c_str());
    classFileDir = "data/" + std::to_string(schoolYear) + "/classes/" + currentClass + "/student.csv";
    std::fstream classFile(classFileDir.c_str(), std::ios::app);

    char cont = 'y';
    while (cont == 'y') {
        std::cout << "Enter the information of the individual student to be added\n"
        << "or enter the directory of a \"input.csv\" file that contains a list of more than one student's information\n"
        << "(format: \"Student ID,First name,Last name,Gender,Date of Birth,Social ID\"):\n";
        std::string classStudentInput;
        std::getline(std::cin, classStudentInput, '\n');

        std::string inputDir = "((([A-Z]|[a-z])+(\\:)+(\\/|\\\\)+.+input.csv)|(([A-Z]|[a-z])+(\\:)+(\\/|\\\\)+input.csv)|(.+input.csv)|input.csv)";
        std::regex regInputDir(inputDir);
        std::smatch regResult;

        bool inserted = 0;

        if (std::regex_search(classStudentInput, regResult, regInputDir)) {
        std::fstream fInput(regResult.str(), std::ios::in);
            if (fInput.is_open()) {
                SNode* fInputBatch = nullptr;

                createList(fInputBatch, fInput);
                addListStudentBatch(totalStudentHead, fInputBatch, schoolYear, currentClass);
                addFileStudentBatch(fInputBatch, totalFile, schoolYear, currentClass);
                addFileStudentBatch(fInputBatch, classFile, schoolYear, currentClass);

                destructList(fInputBatch);

                inserted = 1;
            }
            else std::cout << "\"" << regResult.str() << "\" doesn't exist." << std::endl;
        }
        else {
            if (std::regex_search(classStudentInput, std::regex("((([A-Z]|[a-z])+(\\:)+(\\/|\\\\)+(.)+)|(([A-Z]|[a-z])+(\\:)+(\\/|\\\\)+(.)+)|(([A-Z]|[a-z])+(\\/|\\\\)+(.)+))")))
                std::cout << "\"" << classStudentInput << "\" doesn't exist." << std::endl;
            else {
                addListStudentSingle(totalStudentHead, classStudentInput, schoolYear, currentClass);
                addFileStudentSingle(classStudentInput, totalFile, schoolYear, currentClass);
                addFileStudentSingle(classStudentInput, classFile, schoolYear, currentClass);

                inserted = 1;
            }
        }

        if (inserted) {
            std::cout << "Do you want to add more students? ('y' to continue, 'n' or anything else to stop adding): ";
            std::cin >> cont;
        }
    }
}

//This appends a new student (containing new info) to the file
bool addListStudentSingle(Node*& totalStudentHead, std::string newValue, int schoolYear, std::string currentClass) {
    Node* nodeNew = new Node;
    int afterComma = newValue.find_first_of(',');
    nodeNew->value = newValue.substr(0, 8) + "," + getStudentDOB(newValue) + "," + newValue.substr(afterComma + 1, newValue.size()) + "," + std::to_string(schoolYear) + "," + currentClass + ",";

    if (totalStudentHead != nullptr) {
        //Connects new node to the head and tail of the list
        nodeNew->nodeNext = totalStudentHead;
        nodeNew->nodePrev = totalStudentHead->nodePrev;
        //Connects the head and tail of the list to the new node
        totalStudentHead->nodePrev->nodeNext = nodeNew;
        totalStudentHead->nodePrev = nodeNew;
    }
    else {
        nodeNew->nodeNext = nodeNew;
        nodeNew->nodePrev = nodeNew;
        totalStudentHead = nodeNew;
    }

    return 1;
}

//This appends multiple new students to the file
//"batch" must not be nullptr
bool addListStudentBatch(Node*& totalStudentHead, SNode* batch, int schoolYear, std::string currentClass) {
    SNode* batchCurr = batch;
    
    while (batchCurr != nullptr) {
        addListStudentSingle(totalStudentHead, batchCurr->value, schoolYear, currentClass);
        batchCurr = batchCurr->nodeNext;
    }

    return 1;
}

void addFileStudentSingle(std::string newValue, std::fstream& dataFile, int schoolYear, std::string currentClass) {
    if (dataFile.eof()) dataFile.clear();       //Resets dataFile's EOF state flag
    int afterComma = newValue.find_first_of(',');
    dataFile << std::endl << newValue.substr(0, 8) << "," << getStudentDOB(newValue) << "," << newValue.substr(afterComma + 1, newValue.size()) << "," << std::to_string(schoolYear) << "," << currentClass << ",";
}

void addFileStudentBatch(SNode* batch, std::fstream& dataFile, int schoolYear, std::string currentClass) {
    SNode* batchCurr = batch;

    while (batchCurr != nullptr) {
        addFileStudentSingle(batchCurr->value, dataFile, schoolYear, currentClass);
        batchCurr = batchCurr->nodeNext;
    }
}

std::string getStudentDOB(std::string studentInfo) {
    int count = 0;
    for (int i = 0; i < studentInfo.size(); i++) {
        if (isdigit(studentInfo[i]) != 0) {
            for (int j = i + 1; j < studentInfo.size(); j++) {
                if (studentInfo[j] == '-' && j == i + 2) count++;
                if (studentInfo[j] == '-' && j == i + 5) count++;
            }
            if (count == 2) {
                return studentInfo.substr(i, 10);
            }
        }
    }
    return "";
}