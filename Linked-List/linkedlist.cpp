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

        SchoolYear* prev = nullptr;
        while (!dataFile.eof()) {
            std::string currentLine;
            std::getline(dataFile, currentLine);
            if (currentLine != "") {    //In case there are unneccessary extra empty lines in the file
                if (schoolYearHead == nullptr) {
                    schoolYearHead = new SchoolYear;
                    schoolYearHead->schoolYear = stoi(currentLine);
                    schoolYearHead->nodePrev = prev;
                    schoolYearHead->nodeNext = nullptr;
                    curr = schoolYearHead;
                }
                else {
                    curr->nodeNext = new SchoolYear;
                    prev = curr;
                    curr = curr->nodeNext;
                    curr->schoolYear = stoi(currentLine);
                    prev->nodeNext = curr;
                    curr->nodePrev = prev;
                }
            }
        }
        //Check if the list is still empty (in case there's no node)
        if (schoolYearHead != nullptr) {
            curr->nodeNext = schoolYearHead;
            schoolYearHead->nodePrev = curr;
        }
    }
}

void createList(Classes*& classHead, std::fstream& dataFile) {
    if (classHead == nullptr) {
        Classes* curr = nullptr;
        std::string categories;
        std::getline(dataFile, categories);

        Classes* prev = nullptr;
        while (!dataFile.eof()) {
            std::string currentLine;
            std::getline(dataFile, currentLine);
            if (currentLine != "") {    //In case there are unneccessary extra empty lines in the file
                if (classHead == nullptr) {
                    classHead = new Classes;
                    classHead->classID = currentLine;
                    classHead->nodePrev = prev;
                    classHead->nodeNext = nullptr;
                    curr = classHead;
                }
                else {
                    curr->nodeNext = new Classes;
                    prev = curr;
                    curr = curr->nodeNext;
                    curr->classID = currentLine;
                    prev->nodeNext = curr;
                    curr->nodePrev = prev;
                }
            }
        }
        //Check if the list is still empty (in case there's no node)
        if (classHead != nullptr) {
            curr->nodeNext = classHead;
            classHead->nodePrev = curr;
        }
    }
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

                    //Read and store current student data
                    readStudentData(studentHead, currentLine);

                    studentHead->nodePrev = prev;
                    studentHead->nodeNext = nullptr;
                    curr = studentHead;
                }
                else {
                    curr->nodeNext = new Student;
                    prev = curr;
                    curr = curr->nodeNext;
                    
                    //Read and store current student data
                    readStudentData(studentHead, currentLine);
                    
                    prev->nodeNext = curr;
                    curr->nodePrev = prev;
                }
            }
        }
        //Check if the list is still empty (in case there's no node)
        if (studentHead != nullptr) {
            curr->nodeNext = studentHead;
            studentHead->nodePrev = curr;
        }
    }
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

                    //Read and store current student data
                    readStudentData(studentHead, currentLine, false);
                    studentHead->usr = studentHead->studentID;
                    studentHead->pwd = studentHead->dob;
                    studentHead->startYear = std::to_string(schoolYear);
                    studentHead->classID = currentClass;

                    studentHead->nodePrev = prev;
                    studentHead->nodeNext = nullptr;
                    curr = studentHead;
                }
                else {
                    curr->nodeNext = new Student;
                    prev = curr;
                    curr = curr->nodeNext;
                    
                    //Read and store current student data
                    readStudentData(studentHead, currentLine, false);
                    curr->usr = curr->studentID;
                    curr->pwd = curr->dob;
                    curr->startYear = std::to_string(schoolYear);
                    curr->classID = currentClass;
                    
                    prev->nodeNext = curr;
                    curr->nodePrev = prev;
                }
            }
        }
        //Check if the list is still empty (in case there's no node)
        if (studentHead != nullptr) {
            curr->nodeNext = studentHead;
            studentHead->nodePrev = curr;
        }
    }
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
                studentNode->studentID = studentData.substr(previousComma, i);
                if (full) studentNode->usr = studentNode->studentID;
                break;
                case 2:
                studentNode->firstName = studentData.substr(previousComma, i);
                break;
                case 3:
                studentNode->lastName = studentData.substr(previousComma, i);
                break;
                case 4:
                studentNode->gender = studentData.substr(previousComma, i);
                break;
                case 5:
                studentNode->dob = studentData.substr(previousComma, i);
                if (full) studentNode->pwd = studentNode->dob;
                break;
                case 6:
                studentNode->socialID = studentData.substr(previousComma, i);
                break;
            }
            if (full) {
                switch(level) {
                    case 7:
                    studentNode->startYear = studentData.substr(previousComma, i);
                    break;
                    case 8:
                    studentNode->classID = studentData.substr(previousComma, i);
                    break;
                }
            }
            previousComma = i;
            level++;
        }
    }
}

// //This appends a new line (containing new value) to the file
// bool appendListSingle(Node*& nodeHead, std::string newValue) {
//     Node* nodeNew = new Node;
//     nodeNew->value = newValue;

//     if (nodeHead != nullptr) {
//         //Connects new node to the head and tail of the list
//         nodeNew->nodeNext = nodeHead;
//         nodeNew->nodePrev = nodeHead->nodePrev;
//         //Connects the head and tail of the list to the new node
//         nodeHead->nodePrev->nodeNext = nodeNew;
//         nodeHead->nodePrev = nodeNew;
//     }
//     else {
//         nodeNew->nodeNext = nodeNew;
//         nodeNew->nodePrev = nodeNew;
//         nodeHead = nodeNew;
//     }

//     return 1;
// }

// //This appends multiple new lines to the file the file
// //"batch" must not be nullptr
// bool appendListBatch(Node*& nodeHead, SNode* batch) {
//     SNode* batchCurr = batch;
    
//     while (batchCurr != nullptr) {
//         appendListSingle(nodeHead, batchCurr->value);
//         batchCurr = batchCurr->nodeNext;
//     }

//     return 1;
// }

// void appendFileSingle(std::string newValue, std::fstream& dataFile) {
//     if (dataFile.eof()) dataFile.clear();       //Resets dataFile's EOF state flag
//     dataFile << std::endl << newValue;
// }

// void appendFileBatch(SNode* batch, std::fstream& dataFile) {
//     SNode* batchCurr = batch;

//     while (batchCurr != nullptr) {
//         appendFileSingle(batchCurr->value, dataFile);
//         batchCurr = batchCurr->nodeNext;
//     }
// }

// //Returns true on search value found, false otherwise
// bool listSearchBool(Node* nodeHead, std::string searchValue) {
//     if (nodeHead == nullptr) return 0;

//     Node* nodeCurr = nodeHead;
//     while (nodeCurr->value.find(searchValue, 0) == std::string::npos) {
//         nodeCurr = nodeCurr->nodeNext;
//         if (nodeCurr == nodeHead) break;        //Break loop if there's the end of list is reached
//     }
//     if (nodeCurr->value.find(searchValue, 0) != std::string::npos) return 1;

//     return 0;
// }

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
    Course* co = node.courseHead;
    Student* stu = node.studentHead;
    while (sy != nullptr || cl != nullptr || co != nullptr || stu != nullptr) {
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
        if (co != nullptr) {
            Course* rmv = co;
            co = co->nodeNext;
            delete rmv;
        }
        if (stu != nullptr) {
            Student* rmv = stu;
            stu = stu->nodeNext;
            delete rmv;
        }
    }
    sy, cl, co, stu = nullptr;
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