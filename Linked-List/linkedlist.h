#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>

struct SNode {
    std::string value;
    SNode* nodeNext;
};

struct DNode {
    DNode* nodePrev;
    std::string value;
    DNode* nodeNext;
};

struct CNode {
    std::string value;
    CNode* nodeNext;
};

struct Node {
    Node* nodePrev;
    std::string value;
    Node* nodeNext;
};

void createList(SNode*& nodeHead, std::fstream& dataFile);
void createList(DNode*& nodeHead, std::fstream& dataFile);
void createList(CNode*& nodeFirst, std::fstream& dataFile);
void createList(Node*& nodeHead, std::fstream& dataFile);

bool appendListSingle(Node*& nodeHead, std::string newValue, std::fstream& dataFile);
bool appendListBatch(Node*& nodeHead, SNode* batch, std::fstream& dataFile);

bool listSearchBool(Node* nodeHead, std::string searchValue);

void printListSingle(Node* nodeHead, bool reverse);
void printStringSegment(std::string str, int segmentStart, int segmentEnd);

int listLength(Node* nodeHead);

void destructList(Node*& nodeHead);