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

void createList(SNode*& nodeHead, std::ifstream& finData);
void createList(DNode*& nodeHead, std::ifstream& finData);
void createList(CNode*& nodeFirst, std::ifstream& finData);
void createList(Node*& nodeHead, std::ifstream& finData);

bool appendList(SNode* nodeHead);

void printListSingle(Node* nodeHead, bool reverse);

int listLength(Node* nodeHead);

void destructList(Node*& nodeHead);