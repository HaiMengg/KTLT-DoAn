#include "linkedlist.h"

SNode* createList(SNode*& nodeHead, std::ifstream& finData) {
    SNode* nodeCurr = nullptr;
    int currentValue;
    std::string categories;
    finData >> categories;
    while (!finData.eof()) {
        if (nodeHead == nullptr) {
            nodeHead = new SNode;
            finData >> nodeHead->value;
            nodeHead->nodeNext = nullptr;
            nodeCurr = nodeHead;
        }
        else {
            nodeCurr->nodeNext = new SNode;
            nodeCurr = nodeCurr->nodeNext;
            finData >> nodeCurr->value;
            nodeCurr->nodeNext = nullptr;
        }
    }
}