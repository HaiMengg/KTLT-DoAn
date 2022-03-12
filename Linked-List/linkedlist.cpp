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

//A combination of circular linked list and doubly linked list
void createList(Node*& nodeHead, std::fstream& dataFile) {
    if (nodeHead == nullptr) {
        Node* curr = nullptr;
        std::string categories;
        std::getline(dataFile, categories);

        Node* prev = nullptr;
        while (!dataFile.eof()) {
            std::string currentLine;
            std::getline(dataFile, currentLine);
            if (currentLine != "") {    //In case there are unneccessary extra empty lines in the file
                if (nodeHead == nullptr) {
                    nodeHead = new Node;
                    nodeHead->value = currentLine;
                    nodeHead->nodePrev = prev;
                    nodeHead->nodeNext = nullptr;
                    curr = nodeHead;
                }
                else {
                    curr->nodeNext = new Node;
                    prev = curr;
                    curr = curr->nodeNext;
                    curr->value = currentLine;
                    prev->nodeNext = curr;
                    curr->nodePrev = prev;
                }
            }
        }
        //Check if the list is still empty (in case there's no node)
        if (nodeHead != nullptr) {
            curr->nodeNext = nodeHead;
            nodeHead->nodePrev = curr;
        }
    }
}

//This appends a new line (containing new value) to the file
bool appendListSingle(Node*& nodeHead, std::string newValue) {
    Node* nodeNew = new Node;
    nodeNew->value = newValue;

    if (nodeHead != nullptr) {
        //Connects new node to the head and tail of the list
        nodeNew->nodeNext = nodeHead;
        nodeNew->nodePrev = nodeHead->nodePrev;
        //Connects the head and tail of the list to the new node
        nodeHead->nodePrev->nodeNext = nodeNew;
        nodeHead->nodePrev = nodeNew;
    }
    else {
        nodeNew->nodeNext = nodeNew;
        nodeNew->nodePrev = nodeNew;
        nodeHead = nodeNew;
    }

    return 1;
}

//This appends multiple new lines to the file the file
//"batch" must not be nullptr
bool appendListBatch(Node*& nodeHead, SNode* batch) {
    SNode* batchCurr = batch;
    
    while (batchCurr != nullptr) {
        appendListSingle(nodeHead, batchCurr->value);
        batchCurr = batchCurr->nodeNext;
    }

    return 1;
}

void appendFileSingle(std::string newValue, std::fstream& dataFile) {
    if (dataFile.eof()) dataFile.clear();       //Resets dataFile's EOF state flag
    dataFile << std::endl << newValue;
}

void appendFileBatch(SNode* batch, std::fstream& dataFile) {
    SNode* batchCurr = batch;

    while (batchCurr != nullptr) {
        appendFileSingle(batchCurr->value, dataFile);
        batchCurr = batchCurr->nodeNext;
    }
}

//Returns true on search value found, false otherwise
bool listSearchBool(Node* nodeHead, std::string searchValue) {
    if (nodeHead == nullptr) return 0;

    Node* nodeCurr = nodeHead;
    while (nodeCurr->value.find(searchValue, 0) == std::string::npos) {
        nodeCurr = nodeCurr->nodeNext;
        if (nodeCurr == nodeHead) break;        //Break loop if there's the end of list is reached
    }
    if (nodeCurr->value.find(searchValue, 0) != std::string::npos) return 1;

    return 0;
}

//Print the entire string contained in each node of the list
void printListSingle(Node* nodeHead, bool reverse) {
    Node* nodeCurr = nodeHead;
    while (nodeHead != nullptr) {
        if (reverse) {
            nodeCurr = nodeCurr->nodePrev;        //Move nodeCurr to last node in the list before printing starts
            std::cout << nodeCurr->value << std::endl;
        }
        else {
            std::cout << nodeCurr->value << std::endl;
            nodeCurr = nodeCurr->nodeNext;
        }
        if (nodeCurr == nodeHead) break;
    }
    std::cout << std::endl;
}

//Print a segment of a given string
void printStringSegment(std::string str, int segmentStart, int segmentEnd) {

}

int listLength(Node* nodeHead) {
    Node* nodeCurr = nodeHead;
    int nodeCount = 0;
    while (nodeHead != nullptr) {
        nodeCurr = nodeCurr->nodeNext;
        nodeCount++;
        if (nodeCurr == nodeHead) {
            break;
        }
    }

    return nodeCount;
}

//Destruct the list
void destructList(Node*& nodeHead) {
    int len = listLength(nodeHead);
    while (len--) {
        Node* nodeRmv = nodeHead;
        nodeHead = nodeHead->nodeNext;
        delete nodeRmv;
    }
    nodeHead = nullptr;
}
void destructList(SNode*& nodeHead) {
    while (nodeHead != nullptr) {
        SNode* temp = nodeHead;
        nodeHead = nodeHead->nodeNext;
        delete temp;
    }
}
