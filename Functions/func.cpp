#include "func.h"

bool isDigit_w(std::string givenString) {
    for (int i = 0; i < givenString.size(); i++) {
        if (isdigit(givenString[i]) == 0) return 0;
    }
    return 1;
}

std::string toLower_w(std::string givenString) {
    for (int i = 0; i < givenString.size(); i++) {
        if (isdigit(givenString[i]) == 0) givenString[i] = tolower(givenString[i]);
    }
    return givenString;
}

std::string toUpper_w(std::string givenString) {
    for (int i = 0; i < givenString.size(); i++) {
        if (isdigit(givenString[i]) == 0) givenString[i] = toupper(givenString[i]);
    }
    return givenString;
}

int countElement(std::string givenString, char needle) {
    int count = 0;
    for (int i = 0; i < givenString.size(); i++) {
        if (givenString[i] == needle) count++;
    }
    return count;
}