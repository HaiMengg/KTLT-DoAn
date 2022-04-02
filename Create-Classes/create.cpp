#include "create.h"

/*Class*/
void viewClasses(Classes* classHead) {
    int viewType;
    do {
        std::cout << "Select view type:\n1. Classes of a single school year\n2. All classes\n0. Return to previous menu\n: ";
        std::cin >> viewType;
        if (viewType < 0 || viewType > 2) std::cout << "Invalid view type. Please re-enter.\n";
    } while (viewType < 0 || viewType > 2);

    switch (viewType) {
        case 1: {
            std::cout << "Enter the school year whose classes you want to view: ";
            int schoolYear;
            std::cin >> schoolYear;
            Classes* classCurr = classHead;
            bool found = 0;
            while (classCurr != nullptr) {
                if (classCurr->startYear == schoolYear) {
                    found = 1;
                    std::cout << classCurr->classID << std::endl;
                }
                classCurr = classCurr->nodeNext;
            }
            if (!found) std::cout << "No class data found";     //Display this if no valid class is found
            break;
        }
        case 2: {
            Classes* classCurr = classHead;
            bool first; int prevYear = -1;
            if (classCurr == nullptr) std::cout << "No class data found";     //Display this if no valid class is found
            while (classCurr != nullptr) {
                //Print the school year of these classes before printing them
                if (prevYear != classCurr->startYear) {
                    first = 1;
                    prevYear = classCurr->startYear;
                }
                if (first) {
                    first = 0;
                    std::cout << classCurr->startYear << ":" << std::endl;
                }

                std::cout << classCurr->classID << std::endl;
                classCurr = classCurr->nodeNext;
            }
            break;
        }
        case 0:
            return;
    }
}

void createClass(Classes*& classHead, std::fstream& dataFile, int startYear) {
    std::string categories;
    getline(dataFile, categories);

    //Get all classes of the current school year
    std::fstream currentClasses(std::string("data/" + std::to_string(startYear) + "/class.csv").c_str(),  std::ios::app | std::ios::out | std::ios::in);
    std::string currentClassesCatagories;
    std::getline(currentClasses, currentClassesCatagories);
    if (currentClassesCatagories == "" && currentClasses.eof())      //If the file is newly created, a line for category in the file is pre-written before any data gets added to it
    {
        currentClasses.clear();
        currentClasses << "classID";
    }
    currentClasses.seekg(0);

    Classes* currentClassesList = nullptr;
    createList(currentClassesList, currentClasses);

    bool inserted = 0;
    while (!inserted) {
        std::string choice = "a";
        while (!isDigit_w(choice)) {
            std::cout << "Choose the input method by which students' data are to be entered:\n"
            << "1. Single input (manually)\n2. CSV file\n0. Back to main menu\n: ";
            std::getline(std::cin, choice);
            if (!isDigit_w(choice) || choice == "") {
                std::cout << "Invalid format for choice\n";
                continue;
            }
            switch(stoi(choice)) {
                case 1: {
                    std::string classInput;
                    std::cout << "Enter the ID of a SINGLE new class (already existing class will not be added) (enter 0 to return to previous menu): ";
                    std::getline(std::cin, classInput);
                    classInput = toUpper_w(classInput);
                    if (classInput != "0") {
                        appendNewClassList(classHead, classInput, startYear, true);
                        appendNewClassFile(dataFile, classInput, startYear, true);
                        appendNewClassFile(currentClasses, classInput, startYear);
                        appendNewClassFolder(classInput, startYear);
                        inserted = 1;
                    }
                    else choice = "0";
                    break;
                }
                case 2: {
                    std::string fileClassInput;
                    std::cout << "Enter the directory of the CSV file containing data on multiple classes (EACH CLASS ID MUST BE SEPERATED BY A NEW LINE)\n"
                    << "(already existing classes will not be added) (enter 0 to return to previous menu)\n: ";
                    std::getline(std::cin, fileClassInput);
                    if (fileClassInput != "0") {
                        std::fstream fileClass(fileClassInput.c_str(), std::ios::in);
                        if (fileClass.is_open()) {
                            if (checkInputFormat(fileClass, 1)) {
                                SNode* fInputBatch = nullptr;

                                createList(fInputBatch, fileClass);
                                appendBatchClassList(classHead, fInputBatch, startYear, true);
                                appendBatchClassFile(dataFile, fInputBatch, startYear, true);
                                appendBatchClassFile(currentClasses, fInputBatch, startYear);
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
                case 0: {
                    return;
                }
            }
        }
    }
    destructList(currentClassesList);
}

void appendNewClassList(Classes*& classHead, std::string newClass, int schoolYear, bool full) {
    if (classListSearchBool(classHead, newClass, schoolYear)) return;

    Classes* nodeNew = new Classes;
    nodeNew->classID = newClass;
    if (full) nodeNew->startYear = schoolYear;

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
void appendNewClassFile(std::fstream& dataFile, std::string newClass, int schoolYear, bool full) {
    if (classFileSearchBool(dataFile, newClass, schoolYear, full)) return;

    //Get to end of file for appendage
    while (!dataFile.eof()) {
        std::string line;
        std::getline(dataFile, line);
    }
    dataFile.clear();       //Remove file's EOF flag so that new line can be added
    
	dataFile << std::endl << newClass;
    if (full) dataFile << "," << schoolYear;
    dataFile.flush();

    dataFile.clear();
    dataFile.seekg(0); //Move to beginning of file
}
void appendNewClassFolder(std::string newClass, int startYear) {
    mkdir(std::string("data/" + std::to_string(startYear) + "/classes/" + newClass).c_str());
}
void appendBatchClassList(Classes*& classHead, SNode* batch, int schoolYear, bool full) {
    SNode* batchCurr = batch;
    while (batchCurr != nullptr) {
        appendNewClassList(classHead, batchCurr->value, schoolYear, full);
        batchCurr = batchCurr->nodeNext;
    }
}
void appendBatchClassFile(std::fstream& dataFile, SNode* batch, int schoolYear, bool full) {
    SNode* batchCurr = batch;
    while (batchCurr != nullptr) {
        appendNewClassFile(dataFile, batchCurr->value, schoolYear, full);
        batchCurr = batchCurr->nodeNext;
    }
}
void appendBatchClassFolder(SNode* batch, int startYear) {
    SNode* batchCurr = batch;
    while (batchCurr != nullptr) {
        appendNewClassFolder(batchCurr->value, startYear);
        batchCurr = batchCurr->nodeNext;
    }
}
bool classListSearchBool(Classes* classesHead, std::string searchClass, int startYear) {
    while (classesHead != nullptr) {
        if (classesHead->classID == searchClass && classesHead->startYear == startYear) return 1;
        classesHead = classesHead->nodeNext;
    }
    return 0;
}
bool classFileSearchBool(std::fstream& classesTotalFile, std::string searchClass, int startYear, bool full) {
    classesTotalFile.clear();
    classesTotalFile.seekg(0);

    std::string categories;
    std::getline(classesTotalFile, categories);
    while (!classesTotalFile.eof()) {
        std::string currentLine;
        std::getline(classesTotalFile, currentLine);
        if (currentLine.find(searchClass) != std::string::npos && currentLine.find(std::to_string(startYear)) != std::string::npos) return 1;
        if (currentLine.find(searchClass) != std::string::npos && !full) return 1;
    }
    return 0;
}

/*Student*/
void addStudentsToClass(Student*& totalStudentHead, std::fstream& totalFile, int schoolYear, std::string currentClass, Classes*& totalClassList) {
    //Get all students of the current class
    std::fstream currentStudents(std::string("data/" + std::to_string(schoolYear) + "/classes/" + currentClass + "/student.csv").c_str(), std::ios::app | std::ios::out | std::ios::in);
    std::string currentStudentsCategories;
    std::getline(currentStudents, currentStudentsCategories);
    if (currentStudentsCategories == "" && currentStudents.eof())      //If the file is newly created, a line for category in the file is pre-written before any data gets added to it
    {
        currentStudents.clear();
        currentStudents << "studentID,firstname,lastname,gender,dob,socialID";
    }
    currentStudents.seekg(0);
    Student* currentStudentsList = nullptr;
    createList(currentStudentsList, currentStudents, schoolYear, currentClass);

    char cont = 'y';
    while (cont == 'y') {
        bool inserted = 0;
        std::string choice = "0";
        while (choice == "0") {
            do {
                if (choice == "" || !isDigit_w(choice)) std::cout << "Invalid format for choice\n";
                std::cout << "Choose the input method by which students' data are to be entered:\n"
                << "1. Single input (manually)\n2. CSV file\n0. Back to previous menu\n: ";
                std::getline(std::cin, choice);
                if (choice == "0") return;
            } while (choice == "" || !isDigit_w(choice));
            switch(stoi(choice)) {
                case 1: {
                    std::string studentInput;
                    std::cout << "Enter the data of a new student of class \"" << currentClass << "\"\n"
                    << "(format: \"studentID,firstname,lastname,gender,dob,socialID\")\n"
                    << "(already existing student or student data that don't match the given format won't be added)\n"
                    << "(enter \"0\" to return to previous menu)\n: ";
                    std::getline(std::cin, studentInput);
                    if (studentInput != "0") {
                        appendNewStudentList(totalStudentHead, studentInput, schoolYear, currentClass);
                        appendNewStudentList(currentStudentsList, studentInput, schoolYear, currentClass, false);
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
                    << "(format: \"studentID,firstname,lastname,gender,dob,socialID\")\n"
                    << "(already existing students or student data that don't match the given format won't be added)\n"
                    << "(enter \"0\" to return to previous menu)\n: ";
                    std::getline(std::cin, fileStudentInput);
                    if (fileStudentInput != "0") {
                        std::fstream fileStudent(fileStudentInput.c_str(), std::ios::in);
                        if (fileStudent.is_open()) {
                            if (checkInputFormat(fileStudent, 2)) {
                                SNode* fInputBatch = nullptr;

                                createList(fInputBatch, fileStudent);
                                appendBatchStudentList(totalStudentHead, fInputBatch, schoolYear, currentClass);
                                appendBatchStudentList(currentStudentsList, fInputBatch, schoolYear, currentClass);
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
            std::cin.ignore(10000, '\n');
        }
    }
    appendClassStudentList(currentStudentsList, totalClassList, currentClass);
    destructList(currentStudentsList);
}

//This appends a new student (containing new info) to the file
void appendNewStudentList(Student*& totalStudentHead, std::string newValue, int schoolYear, std::string currentClass, bool full) {
    if (!studentFormatCheck(newValue, schoolYear)) return;

    Student* nodeNew = new Student;
    readStudentData(nodeNew, newValue, full);

    //This is put here instead of at beginning of the function so that nodeNew->studentID can be checked
    if (studentListSearchBool(totalStudentHead, currentClass, nodeNew->studentID)) {
        delete nodeNew;
        return;
    }

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
    if (!studentFormatCheck(newValue, schoolYear)) return;

    int afterComma = newValue.find(',');

    //This is put here so that the current student's ID can be checked
    if (studentFileSearchBool(dataFile, currentClass, newValue.substr(afterComma + 1, 8), full)) return;

    //Get to end of file for appendage
    while (!dataFile.eof()) {
        std::string line;
        std::getline(dataFile, line);
    }
    dataFile.clear();       //Remove file's EOF flag so that new line can be added

    if (full) dataFile << std::endl << newValue.substr(afterComma + 1, 8) << "," << getStudentDOB(newValue) << "," << newValue.substr(afterComma + 1, newValue.size()) << "," << std::to_string(schoolYear) << "," << currentClass << ",";
    else dataFile << std::endl << newValue.substr(afterComma + 1, newValue.size());
    dataFile.flush();

    dataFile.clear();
    dataFile.seekg(0);          //Move to beginning of file
}

void appendBatchStudentFile(SNode* batch, std::fstream& dataFile, int schoolYear, std::string currentClass, bool full) {
    SNode* batchCurr = batch;

    while (batchCurr != nullptr) {
        appendNewStudentFile(batchCurr->value, dataFile, schoolYear, currentClass, full);
        batchCurr = batchCurr->nodeNext;
    }
}

void appendClassStudentList(Student* classStudent, Classes*& totalClassList, std::string currentClass) {
    Classes* classCurr = totalClassList;
    while (classCurr != nullptr) {
        if (classCurr->classID == currentClass) {
            classCurr->classStudentHead = classStudent;
            break;
        }
        classCurr = classCurr->nodeNext;
    }
}

std::string getStudentDOB(std::string studentInfo) {
    int count = 0;
    for (int i = 0; i < studentInfo.size(); i++) {
        if (isdigit(studentInfo[i]) != 0) {
            for (int j = i + 1; j < studentInfo.size(); j++) {
                if (studentInfo[j] == '/' && j == i + 2) count++;
                if (studentInfo[j] == '/' && j == i + 5) count++;
            }
            if (count == 2) {
                return studentInfo.substr(i, 10);
            }
        }
    }
    return "";
}

bool studentListSearchBool(Student* studentHead, std::string searchStudentClass, std::string searchStudentID) {
    while (studentHead != nullptr) {
        if (studentHead->classID == searchStudentClass && studentHead->studentID == searchStudentID) return 1;
        studentHead = studentHead->nodeNext;
    }
    return 0;
}
bool studentFileSearchBool(std::fstream& studentTotalFile, std::string searchStudentClass, std::string searchStudentID, bool full){
    std::string categories;
    std::getline(studentTotalFile, categories);
    while (!studentTotalFile.eof()) {
        std::string currentLine;
        std::getline(studentTotalFile, currentLine);
        if ((!full || currentLine.find(searchStudentClass) != std::string::npos) && currentLine.find(searchStudentID) != std::string::npos) {
            studentTotalFile.clear();
            studentTotalFile.seekg(0);

            return 1;
        }
    }
    studentTotalFile.clear();
    studentTotalFile.seekg(0);
    return 0;
}
bool studentFormatCheck(std::string studentData, int schoolYear) {
    int count = 0;
    for (int i = 0; i < studentData.size(); i++) {
        if (studentData[i] == ',') {
            count++;
            switch(count) {
                case 1: {
                    if (!isDigit_w(studentData.substr(i + 1, 8))) return 0;
                    break;
                }
                case 4: {
                    for (int j = i + 1; j < studentData.size(); j++) {
                        if (studentData[j] == ',') {
                            if (studentData.substr(i + 1, j - i - 1) != "Nam" && studentData.substr(i + 1, j - i - 1) != "Nu") return 0;
                            break;
                        }
                    }
                    break;
                }
                case 5: {
                    int startComma = i;     //Mark the start of date string
                    int slashCount = 0;
                    for (int j = i + 1; j < studentData.size(); j++) {
                        if (studentData[j] == '/') {
                            if (studentData.substr(i + 1, 1) == "/") return 0;
                            if (!isDigit_w(studentData.substr(i + 1, j - i - 1))) return 0;
                            if (slashCount == 0 && (stoi(studentData.substr(i + 1, j - i - 1)) < 1 && stoi(studentData.substr(i + 1, j - i - 1)) > 31)) return 0;
                            if (slashCount == 1 && (stoi(studentData.substr(i + 1, j - i - 1)) < 1 && stoi(studentData.substr(i + 1, j - i - 1)) > 12)) return 0;
                            i = j; slashCount++;
                        }
                        if (studentData[j] == ',' && slashCount == 2) {
                            if (!isDigit_w(studentData.substr(i + 1, j - i - 1))) return 0;
                            if (stoi(studentData.substr(i + 1, j - i - 1)) < 0) return 0;
                            i = j;
                            break;
                        }
                    }
                    if (!isValidDate(studentData.substr(startComma + 1, i - startComma - 1))) return 0;
                    if (!isDigit_w(studentData.substr(i + 1, studentData.size() - i))) return 0;
                    count++;
                    break;
                }
            }
        }
    }
    if (count != 6) return 0;
    return 1;
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