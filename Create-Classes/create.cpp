#include "create.h"

/*Class*/
void createClass(Classes*& classHead, std::fstream& dataFile, int startYear) {
    std::string categories;
    getline(dataFile, categories);

    //Get all classes of the current school year
    std::fstream currentClasses(std::string("data/" + std::to_string(startYear) + "/class.csv").c_str(), std::ios::app | std::ios::out);
    if (currentClasses.peek() == EOF)      //If the file is newly created, a line for category in the file is pre-written before any data gets added to it
    {
        currentClasses.clear();
        currentClasses << "classID";
    }
    Classes* currentClassesList = nullptr;
    createList(currentClassesList, currentClasses);

    //Print currently existing classes
    std::cout << "Currently existing classes of the school year " << startYear << "-" << startYear + 1 << ":\n";
    if (currentClassesList != nullptr) std::cout << currentClassesList->classID << std::endl;
    else std::cout << "No class data found" << std::endl;

    bool inserted = 0;
    while (!inserted) {
        std::string choice = "0";
        while (choice == "0") {
            std::cout << "Choose the input method by which students' data are to be entered:\n"
            << "1. Single input (manually)\n2. CSV file\n: ";
            std::getline(std::cin, choice);
            switch(stoi(choice)) {
                case 1: {
                    std::string classInput;
                    std::cout << "Enter the ID of a SINGLE new class (you can't create an already existing class): ";
                    std::getline(std::cin, classInput);
                    if (classInput != "0") {
                        appendNewClassList(classHead, classInput);
                        appendNewClassFile(dataFile, classInput);
                        appendNewClassFile(currentClasses, classInput);
                        appendNewClassFolder(classInput, startYear);
                        inserted = 1;
                    }
                    else choice = "0";
                    break;
                }
                case 2: {
                    std::string fileClassInput;
                    std::cout << "Enter the directory of the CSV file containing data on multiple classes (EACH CLASS ID MUST BE SEPERATED BY A NEW LINE):";
                    std::getline(std::cin, fileClassInput);
                    if (fileClassInput != "0") {
                        std::fstream fileClass(fileClassInput.c_str(), std::ios::in);
                        if (fileClass.is_open()) {
                            if (checkInputFormat(fileClass, 1)) {
                                SNode* fInputBatch = nullptr;

                                createList(fInputBatch, fileClass);
                                appendBatchClassList(classHead, fInputBatch);
                                appendBatchClassFile(dataFile, fInputBatch);
                                appendBatchClassFile(currentClasses, fInputBatch);
                                appendBatchClassFolder(fInputBatch, startYear);

                                destructList(fInputBatch);

                                inserted = 1;
                            }
                            else std::cout << "Invalid format.\n";
                        }
                        else std::cout << "\"" << fileClassInput << "\" couldn't be found.\n";
                    }
                    else choice = "0";
                    break;
                }
            }
        }
    }
    destructList(currentClassesList);
}

void appendNewClassList(Classes*& classHead, std::string newClass) {
    Classes* nodeNew = new Classes;
    nodeNew->classID = newClass;

	if (classHead == nullptr) {
		nodeNew->nodePrev = nullptr;
		nodeNew->nodeNext = nullptr;
		classHead = nodeNew;
		return;
	}

	Classes* nodeCurr = classHead;
	while (nodeCurr->nodeNext != nullptr) {
		nodeCurr = nodeCurr->nodeNext;
	}
	nodeNew->nodePrev = nodeCurr;
	nodeNew->nodeNext = nullptr;
	nodeCurr->nodeNext = nodeNew;
}
void appendNewClassFile(std::fstream& dataFile, std::string newClass) {
	if (dataFile.eof()) dataFile.clear();       //Resets dataFile's EOF state flag
	dataFile << std::endl << newClass;
    dataFile.flush();
}
void appendNewClassFolder(std::string newClass, int startYear) {
    mkdir(std::string("data/" + std::to_string(startYear) + "/classes/" + newClass).c_str());
}
void appendBatchClassList(Classes*& classHead, SNode* batch) {
    SNode* batchCurr = batch;
    while (batchCurr != nullptr) {
        appendNewClassList(classHead, batchCurr->value);
        batchCurr = batchCurr->nodeNext;
    }
}
void appendBatchClassFile(std::fstream& dataFile, SNode* batch) {
    SNode* batchCurr = batch;
    while (batchCurr != nullptr) {
        appendNewClassFile(dataFile, batchCurr->value);
        batchCurr = batchCurr->nodeNext;
    }
}
void appendBatchClassFolder(SNode* batch, int startYear) {
    SNode* batchCurr = batch;
    while (batchCurr != nullptr) {
        appendNewClassFolder(batch->value, startYear);
        batchCurr = batchCurr->nodeNext;
    }
}

/*Student*/
void addStudentsToClass(Student*& totalStudentHead, std::fstream& totalFile, int schoolYear, std::string currentClass) {
    //Get all students of the current class
    std::fstream currentStudents(std::string("data/" + std::to_string(schoolYear) + "/classes/" + currentClass + "/student.csv").c_str(), std::ios::app);
    if (currentStudents.peek() == EOF)      //If the file is newly created, a line for category in the file is pre-written before any data gets added to it
    {
        currentStudents.clear();
        currentStudents << "studentID,firstname,lastname,gender,dob,socialID";
    }
    Student* currentStudentsList = nullptr;
    createList(currentStudentsList, currentStudents, schoolYear, currentClass);

    char cont = 'y';
    while (cont == 'y') {
        bool inserted = 0;
        std::string choice = "0";
        while (choice == "0") {
            std::cout << "Choose the input method by which students' data are to be entered:\n"
            << "1. Single input (manually)\n2. CSV file\n: ";
            std::getline(std::cin, choice);
            switch(stoi(choice)) {
                case 1: {
                    std::string studentInput;
                    std::cout << "Enter the data of a new student of class \"" << currentClass << "\" (you can't add an already existing student)\n"
                    << "(format: \"studentID,firstname,lastname,gender,dob,socialID\")\n:";
                    std::getline(std::cin, studentInput);
                    if (studentInput != "0") {
                        appendNewStudentList(totalStudentHead, studentInput, schoolYear, currentClass);
                        appendNewStudentFile(studentInput, totalFile, schoolYear, currentClass);
                        appendNewStudentFile(studentInput, currentStudents, schoolYear, currentClass, false);

                        inserted = 1;
                    }
                    else choice = "0";
                    break;
                }
                case 2: {
                    std::string fileStudentInput;
                    std::cout << "Enter the directory of the CSV file containing data on multiple students of class \"" << currentClass << "\"\n"
                    << "(format: \"studentID,firstname,lastname,gender,dob,socialID\")\n:";
                    std::getline(std::cin, fileStudentInput);
                    if (fileStudentInput != "0") {
                        std::fstream fileStudent(fileStudentInput.c_str(), std::ios::in);
                        if (fileStudent.is_open()) {
                            if (checkInputFormat(fileStudent, 2)) {
                                SNode* fInputBatch = nullptr;

                                createList(fInputBatch, fileStudent);
                                appendBatchStudentList(totalStudentHead, fInputBatch, schoolYear, currentClass);
                                appendBatchStudentFile(fInputBatch, totalFile, schoolYear, currentClass);
                                appendBatchStudentFile(fInputBatch, currentStudents, schoolYear, currentClass, false);

                                destructList(fInputBatch);

                                inserted = 1;
                            }
                            else std::cout << "Invalid format.\n";
                        }
                        else std::cout << "\"" << fileStudentInput << "\" couldn't be found.\n";
                    }
                    else choice = "0";
                    break;
                }
            }
        }

        if (inserted) {
            std::cout << "Do you want to add more students? ('y' to continue, 'n' or anything else to stop adding): ";
            std::cin >> cont;
        }
    }
    destructList(currentStudentsList);
}

//This appends a new student (containing new info) to the file
void appendNewStudentList(Student*& totalStudentHead, std::string newValue, int schoolYear, std::string currentClass, bool full) {
    Student* nodeNew = new Student;
    readStudentData(nodeNew, newValue, full);
    if (full) {
        nodeNew->usr = nodeNew->studentID;
        nodeNew->pwd = nodeNew->dob;
        nodeNew->startYear = std::to_string(schoolYear);
        nodeNew->classID = currentClass;
    }

	if (totalStudentHead == nullptr) {
		nodeNew->nodePrev = nullptr;
		nodeNew->nodeNext = nullptr;
		totalStudentHead = nodeNew;
		return;
	}

	Student* nodeCurr = totalStudentHead;
	while (nodeCurr->nodeNext != nullptr) {
		nodeCurr = nodeCurr->nodeNext;
	}
	nodeNew->nodePrev = nodeCurr;
	nodeNew->nodeNext = nullptr;
	nodeCurr->nodeNext = nodeNew;
}

//This appends multiple new students to the file
//"batch" must not be nullptr
void appendBatchStudentList(Student*& totalStudentHead, SNode* batch, int schoolYear, std::string currentClass, bool full) {
    SNode* batchCurr = batch;
    
    while (batchCurr != nullptr) {
        appendNewStudentList(totalStudentHead, batchCurr->value, schoolYear, currentClass, full);
        batchCurr = batchCurr->nodeNext;
    }
}

void appendNewStudentFile(std::string newValue, std::fstream& dataFile, int schoolYear, std::string currentClass, bool full) {
    if (dataFile.eof()) dataFile.clear();       //Resets dataFile's EOF state flag
    int afterComma = newValue.find_first_of(',');
    if (full) dataFile << std::endl << newValue.substr(afterComma + 1, 8) << "," << getStudentDOB(newValue) << "," << newValue.substr(afterComma + 1, newValue.size()) << "," << std::to_string(schoolYear) << "," << currentClass << ",";
    else dataFile << std::endl << newValue.substr(afterComma + 1, newValue.size());
    dataFile.flush();
}

void appendBatchStudentFile(SNode* batch, std::fstream& dataFile, int schoolYear, std::string currentClass, bool full) {
    SNode* batchCurr = batch;

    while (batchCurr != nullptr) {
        appendNewStudentFile(batchCurr->value, dataFile, schoolYear, currentClass, full);
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

bool checkInputFormat(std::fstream& inputFile, int mode) {
    /*
    1. Class
    2. Student
    */
    bool validFormat = 1;
    switch(mode) {
        case 1: {
            std::string categories;
            std::getline(inputFile, categories);
            if (categories != "classID") return 0;
            break;
        }
        case 2: {
            std::string categories;
            std::getline(inputFile, categories);
            if (categories != "no,studentID,firstname,lastname,gender,dob,socialID") return 0;
        }
    }

    inputFile.clear();
    inputFile.seekg(0);
    return 1;
}