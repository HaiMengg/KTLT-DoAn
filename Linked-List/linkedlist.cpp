#include "linkedlist.h"

//Calls this in every functions that require the list (it's safe since its content only runs when the list is empty)
void createList(SNode*& nodeHead, std::ifstream& finData) {
    if (nodeHead == nullptr) {
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
}

bool appendList(Node*& nodeHead, std::string newValue) {
    if (nodeHead == nullptr) return 0;
    
    Node* nodeNew = new Node;
    nodeNew->value = newValue;
    //Connects new node to the head and tail of the list
    nodeNew->nodeNext = nodeHead;
    nodeNew->nodePrev = nodeHead->nodePrev;
    //Connects the head and tail of the list to the new node
    nodeHead->nodePrev->nodeNext = nodeNew;
    nodeHead->nodePrev = nodeNew;
    return 1;
}

//A combination of circular linked list and doubly linked list
void createList(Node*& nodeHead, std::ifstream& finData) {
    if (nodeHead == nullptr) {
        Node* curr = nullptr;
        std::string categories;
        finData >> categories;

        Node* prev = nullptr;
        while (!finData.eof()) {
            if (nodeHead == nullptr) {
                nodeHead = new Node;
                finData >> nodeHead->value;
                nodeHead->nodePrev = prev;
                nodeHead->nodeNext = nullptr;
                curr = nodeHead;
            }
            else {
                curr->nodeNext = new Node;
                prev = curr;
                curr = curr->nodeNext;
                finData >> curr->value;
                prev->nodeNext = curr;
                curr->nodePrev = prev;
            }
        }
        //Check if the list is still empty (in case there's no node)
        if (nodeHead != nullptr) {
            curr->nodeNext = nodeHead;
            nodeHead->nodePrev = curr;
        }
    }
}

//Print the entire string contained in each node of the list
void printListSingle(Node* nodeHead, bool reverse) {
    Node* nodeCurr = nodeHead;
    while (nodeHead != nullptr) {
        if (reverse) {
            nodeCurr = nodeCurr->nodePrev;        //Move nodeCurr to last node in the list before printing starts
            std::cout << nodeCurr->value << " ";
        }
        else {
            std::cout << nodeCurr->value << " ";
            nodeCurr = nodeCurr->nodeNext;
        }
        if (nodeCurr == nodeHead) break;
    }
    std::cout << std::endl;
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
