#include "linkedlist.h"

//Calls this in every functions that require the list (it's safe since its content only runs when the list is empty)
void createList(SNode*& nodeHead, std::fstream& dataFile) {
    if (nodeHead == nullptr) {
        SNode* nodeCurr = nullptr;
        int currentValue;
        std::string categories;
        std::getline(dataFile, categories);
        while (!dataFile.eof()) {
            std::string currentLine;
            std::getline(dataFile, currentLine);
            if (currentLine != "") {    //In case there are unneccessary extra empty lines in the file
                if (nodeHead == nullptr) {
                    nodeHead = new SNode;
                    nodeHead->value = currentLine;
                    nodeHead->nodeNext = nullptr;
                    nodeCurr = nodeHead;
                }
                else {
                    nodeCurr->nodeNext = new SNode;
                    nodeCurr = nodeCurr->nodeNext;
                    nodeCurr->value = currentLine;
                    nodeCurr->nodeNext = nullptr;
                }
            }
        }
    }
}

void createList(DNode*& nodeHead, std::fstream& dataFile) {
    if (nodeHead == nullptr) {
        DNode* nodeCurr = nullptr;
        int currentValue;
        std::string categories;
        std::getline(dataFile, categories);
        while (!dataFile.eof()) {
            std::string currentLine;
            std::getline(dataFile, currentLine);
            if (currentLine != "") {    //In case there are unneccessary extra empty lines in the file
                if (nodeHead == nullptr) {
                    nodeHead = new DNode;
                    nodeHead->nodePrev = nullptr;
                    nodeHead->value = currentLine;
                    nodeHead->nodeNext = nullptr;
                    nodeCurr = nodeHead;
                }
                else {
                    nodeCurr->nodeNext = new DNode;
                    DNode* nodeTemp = nodeCurr;
                    nodeCurr = nodeCurr->nodeNext;
                    nodeCurr->nodePrev = nodeTemp;
                    nodeCurr->value = currentLine;
                    nodeCurr->nodeNext = nullptr;
                }
            }
        }
    }
}

void createList(SchoolYear*& schoolYearHead, std::fstream& dataFile) {
    if (schoolYearHead == nullptr) {
        SchoolYear* curr = nullptr;
        std::string categories;
        std::getline(dataFile, categories);

        while (!dataFile.eof()) {
            std::string currentLine;
            std::getline(dataFile, currentLine);
            if (currentLine != "") {    //In case there are unneccessary extra empty lines in the file
                if (schoolYearHead == nullptr) {
                    schoolYearHead = new SchoolYear;
                    schoolYearHead->nodePrev = nullptr;
                    schoolYearHead->schoolYear = stoi(currentLine);
                    schoolYearHead->nodeNext = nullptr;
                    curr = schoolYearHead;
                }
                else {
                    curr->nodeNext = new SchoolYear;
                    SchoolYear* prev = curr;
                    curr = curr->nodeNext;
                    curr->nodePrev = prev;
                    curr->schoolYear = stoi(currentLine);
                    curr->nodeNext = nullptr;
                }
            }
        }
    }
    
    dataFile.clear();
    dataFile.seekg(0);      //Reset cursor's position so the file will be more controller the next time it is used (since you will know where the cursor will be)
}

void createList(Classes*& classHead, std::fstream& dataFile) {
    if (classHead == nullptr) {
        Classes* curr = nullptr;
        std::string categories;
        std::getline(dataFile, categories);

        while (!dataFile.eof()) {
            std::string currentLine;
            std::getline(dataFile, currentLine);
            if (currentLine != "") {    //In case there are unneccessary extra empty lines in the file
                if (classHead == nullptr) {
                    classHead = new Classes;
                    classHead->nodePrev = nullptr;
                    classHead->classID = currentLine.substr(0, currentLine.size() - 5);
                    if (currentLine.size() - 4 >= 0 && isDigit_w(currentLine.substr(currentLine.size() - 4))) classHead->startYear = stoi(currentLine.substr(currentLine.size() - 4));
                    classHead->nodeNext = nullptr;
                    curr = classHead;
                }
                else {
                    Classes* prev = curr;
                    curr->nodeNext = new Classes;
                    curr = curr->nodeNext;
                    curr->nodePrev = prev;
                    curr->classID = currentLine.substr(0, currentLine.size() - 5);
                    if (currentLine.size() - 4 >= 0 && isDigit_w(currentLine.substr(currentLine.size() - 4))) curr->startYear = stoi(currentLine.substr(currentLine.size() - 4));
                    curr->nodeNext = nullptr;
                }
            }
        }
    }

    dataFile.clear();
    dataFile.seekg(0);      //Reset cursor's position so the file will be more controller the next time it is used (since you will know where the cursor will be)
}

//For reading all students
void createList(Student*& studentHead, std::fstream& dataFile) {
    if (studentHead == nullptr) {
        Student* curr = nullptr;
        std::string categories;
        std::getline(dataFile, categories);

        Student* prev = nullptr;
        while (!dataFile.eof()) {
            std::string currentLine;
            std::getline(dataFile, currentLine);
            if (currentLine != "") {    //In case there are unneccessary extra empty lines in the file
                if (studentHead == nullptr) {
                    studentHead = new Student;

                    studentHead->nodePrev = nullptr;

                    //Read and store current student data
                    readStudentData(studentHead, currentLine);

                    studentHead->nodeNext = nullptr;
                    curr = studentHead;
                }
                else {
                    Student* prev = curr;
                    curr->nodeNext = new Student;
                    curr = curr->nodeNext;
                    
                    curr->nodePrev = prev;

                    //Read and store current student data
                    readStudentData(studentHead, currentLine);
                    
                    curr->nodeNext = nullptr;
                }
            }
        }
    }
    
    dataFile.clear();
    dataFile.seekg(0);      //Reset cursor's position so the file will be more controller the next time it is used (since you will know where the cursor will be)
}
//For reading students of a single class (csv format: "")
void createList(Student*& studentHead, std::fstream& dataFile, int schoolYear, std::string currentClass) {
    if (studentHead == nullptr) {
        Student* curr = nullptr;
        std::string categories;
        std::getline(dataFile, categories);

        Student* prev = nullptr;
        while (!dataFile.eof()) {
            std::string currentLine;
            std::getline(dataFile, currentLine);
            if (currentLine != "") {    //In case there are unneccessary extra empty lines in the file
                if (studentHead == nullptr) {
                    studentHead = new Student;

                    studentHead->nodePrev = nullptr;

                    //Read and store current student data
                    readStudentData(studentHead, currentLine, false);
                    studentHead->usr = studentHead->studentID;
                    studentHead->pwd = studentHead->dob;
                    studentHead->startYear = std::to_string(schoolYear);
                    studentHead->classID = currentClass;

                    studentHead->nodeNext = nullptr;
                    curr = studentHead;
                }
                else {
                    Student* prev = curr;
                    curr->nodeNext = new Student;
                    curr = curr->nodeNext;
                    
                    curr->nodePrev = prev;

                    //Read and store current student data
                    readStudentData(studentHead, currentLine, false);
                    curr->usr = curr->studentID;
                    curr->pwd = curr->dob;
                    curr->startYear = std::to_string(schoolYear);
                    curr->classID = currentClass;
                    
                    curr->nodeNext = nullptr;
                }
            }
        }
    }
    
    dataFile.clear();
    dataFile.seekg(0);      //Reset cursor's position so the file will be more controller the next time it is used (since you will know where the cursor will be)
}

void readStudentData(Student*& studentNode, std::string studentData, bool full) {
    int level;
    if (!full) level = 0;
    else level = -1;
    int previousComma;
    for (int i = 0; i < studentData.size(); i++) {
        if (studentData[i] == ',') {
            switch(level) {
                case 1:
                studentNode->studentID = studentData.substr(previousComma + 1, i - previousComma);
                if (full) studentNode->usr = studentNode->studentID;
                break;
                case 2:
                studentNode->firstName = studentData.substr(previousComma + 1, i - previousComma);
                break;
                case 3:
                studentNode->lastName = studentData.substr(previousComma + 1, i - previousComma);
                break;
                case 4:
                studentNode->gender = studentData.substr(previousComma + 1, i - previousComma);
                break;
                case 5:
                studentNode->dob = studentData.substr(previousComma + 1, i - previousComma);
                if (full) studentNode->pwd = studentNode->dob;
                break;
                case 6:
                studentNode->socialID = studentData.substr(previousComma + 1, i - previousComma);
                break;
            }
            if (full) {
                switch(level) {
                    case 7:
                    studentNode->startYear = studentData.substr(previousComma + 1, i - previousComma);
                    break;
                    case 8:
                    studentNode->classID = studentData.substr(previousComma + 1, i - previousComma);
                    break;
                }
            }
            previousComma = i;
            level++;
        }
    }
}

//Returns true on search found, false otherwise
bool listSearchBool(SchoolYear* schoolYearHead, int searchSchoolYear) {
    while (schoolYearHead != nullptr) {
        if (schoolYearHead->schoolYear == searchSchoolYear) return 1;
        schoolYearHead = schoolYearHead->nodeNext;
    }
    return 0;
}
bool listSearchBool(Classes* classesHead, std::string searchClass, int startYear) {
    while (classesHead != nullptr) {
        if (classesHead->classID == searchClass && classesHead->startYear == startYear) return 1;
        classesHead = classesHead->nodeNext;
    }
    return 0;
}
bool listSearchBool(Student* studentHead, std::string searchStudentClass, std::string searchStudentID) {
    while (studentHead != nullptr) {
        if (studentHead->classID == searchStudentClass || studentHead->studentID == searchStudentID) return 1;
        studentHead = studentHead->nodeNext;
    }
    return 0;
}

// //Print the entire string contained in each node of the list
// void printListSingle(Node* nodeHead, bool reverse) {
//     Node* nodeCurr = nodeHead;
//     while (nodeHead != nullptr) {
//         if (reverse) {
//             nodeCurr = nodeCurr->nodePrev;        //Move nodeCurr to last node in the list before printing starts
//             std::cout << nodeCurr->value << std::endl;
//         }
//         else {
//             std::cout << nodeCurr->value << std::endl;
//             nodeCurr = nodeCurr->nodeNext;
//         }
//         if (nodeCurr == nodeHead) break;
//     }
//     std::cout << std::endl;
// }

// //Print a segment of a given string
// void printStringSegment(std::string str, int segmentStart, int segmentEnd) {

// }

// int listLength(Node* nodeHead) {
//     Node* nodeCurr = nodeHead;
//     int nodeCount = 0;
//     while (nodeHead != nullptr) {
//         nodeCurr = nodeCurr->nodeNext;
//         nodeCount++;
//         if (nodeCurr == nodeHead) {
//             break;
//         }
//     }

//     return nodeCount;
// }

//Destruct the list
void destructList(Node& node) {
    SchoolYear* sy = node.schoolYearHead;
    Classes* cl = node.classesHead;
    Semesters* sem = node.semesterHead;
    Student* stu = node.studentHead;
    while (sy != nullptr || cl != nullptr || sem != nullptr || stu != nullptr) {
        if (sy != nullptr) {
            SchoolYear* rmv = sy;
            sy = sy->nodeNext;
            delete rmv;
        }
        if (cl != nullptr) {
            Classes* rmv = cl;
            cl = cl->nodeNext;
            delete rmv;
        }
        if (sem != nullptr) {
            Semesters* rmv = sem;
            sem = sem->nodeNext;
            delete rmv;
        }
        if (stu != nullptr) {
            Student* rmv = stu;
            stu = stu->nodeNext;
            delete rmv;
        }
    }
    sy, cl, sem, stu = nullptr;
}
void destructList(SNode*& nodeHead) {
    while (nodeHead != nullptr) {
        SNode* temp = nodeHead;
        nodeHead = nodeHead->nodeNext;
        delete temp;
    }
}
void destructList(DNode*& nodeHead) {
    while (nodeHead != nullptr) {
        DNode* temp = nodeHead;
        nodeHead = nodeHead->nodeNext;
        delete temp;
    }
}
void destructList(Classes*& nodeHead) {
    while (nodeHead != nullptr) {
        Classes* temp = nodeHead;
        nodeHead = nodeHead->nodeNext;
        delete temp;
    }
}
void destructList(Student*& nodeHead) {
    while (nodeHead != nullptr) {
        Student* temp = nodeHead;
        nodeHead = nodeHead->nodeNext;
        delete temp;
    }
}