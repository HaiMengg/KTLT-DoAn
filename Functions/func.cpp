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

bool isValidDate(std::string givenDate) {
    if (countElement(givenDate, '/') != 2) return 0;

    int d = getDateData(givenDate, 'd');
    int m = getDateData(givenDate, 'm');
    int y = getDateData(givenDate, 'y');
    if (d == -1 || m == -1 || y == -1) return 0;

    if (y < 0) return 0;
    if (m <= 0 || m > 12) return 0;
    if (d <= 0) return 0;
    
    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) {
        if (d > 31) return 0;
    }
    else {
        if (m != 2) {
            if (d > 30) return 0;
        }
        else {
            if (d == 29 && y % 4 != 0 && y % 400 != 0) return 0;
            if (d > 29) return 0;
        }
    }
    return 1;
}

int getDateData(std::string givenDate, char mode) {
    int d, m, y;

    int firstSlash = givenDate.find('/');
    d = (givenDate.substr(0, firstSlash) != "" && isDigit_w(givenDate.substr(0, firstSlash))) ? stoi(givenDate.substr(0, firstSlash)) : -1;
    if (mode == 'd') return d;
    givenDate = givenDate.substr(firstSlash + 1);

    firstSlash = givenDate.find('/');
    m = (givenDate.substr(0, firstSlash) != "" && isDigit_w(givenDate.substr(0, firstSlash))) ? stoi(givenDate.substr(0, firstSlash)) : -1;
    if (mode == 'm') return m;
    givenDate = givenDate.substr(firstSlash + 1);

    y = (givenDate != "" && isDigit_w(givenDate)) ? stoi(givenDate) : -1;
    if (mode == 'y') return y;
}

void updateDate(std::string& currentDate) {
    std::cout << "Enter the current date (enter \"0\" to return to previous menu): ";
    std::getline(std::cin, currentDate);
    if (currentDate == "0") return;
    
    while (!isValidDate(currentDate)) {
        std::cout << "Invalid date. Re-enter (enter \"0\" to return to previous menu): ";
        std::getline(std::cin, currentDate);
        if (currentDate == "0") return;
    }
}

void dateZeroFill(std::string& givenDate) {
    
}

//Check if date1 is later than or equal to date2
bool isDateLaterThanOrEqualTo(std::string date1, std::string date2) {
    if (getDateData(date1, 'y') < getDateData(date2, 'y')) return 0;
    else if (getDateData(date1, 'y') == getDateData(date2, 'y')) {
        if (getDateData(date1, 'm') < getDateData(date2, 'm')) return 0;
        else if (getDateData(date1, 'm') == getDateData(date2, 'm')) {
            if (getDateData(date1, 'd') < getDateData(date2, 'd')) return 0;
            else return 1;
        }
        else return 1;
    }
    else return 1;
}

//Check if date1 is earlier than or equal to date2
bool isDateEarlierThanOrEqualTo(std::string date1, std::string date2) {
    if (getDateData(date1, 'y') > getDateData(date2, 'y')) return 0;
    else if (getDateData(date1, 'y') == getDateData(date2, 'y')) {
        if (getDateData(date1, 'm') > getDateData(date2, 'm')) return 0;
        else if (getDateData(date1, 'm') == getDateData(date2, 'm')) {
            if (getDateData(date1, 'd') > getDateData(date2, 'd')) return 0;
            else return 1;
        }
        else return 1;
    }
    else return 1;
}