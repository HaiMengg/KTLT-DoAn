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

SNode* createList(SNode*& nodeHead, std::ifstream& finData);
DNode* createList(DNode*& nodeHead, std::ifstream& finData);
CNode* createList(CNode*& nodeFirst, std::ifstream& finData);