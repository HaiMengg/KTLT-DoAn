#include "create.h"

void createSemester(Semesters*& semestersHead, std::fstream& dataFile, int startYear) {
    std::string categories;
    getline(dataFile, categories);

    //Get all classes of the current school year
    std::fstream currentSemesters(std::string("data/" + std::to_string(startYear) + "/semester.csv").c_str(),  std::ios::app | std::ios::out | std::ios::in);
    std::string currentSemestersCatagories;
    std::getline(currentSemesters, currentSemestersCatagories);
    if (currentSemestersCatagories == "" && currentSemesters.eof())      //If the file is newly created, a line for category in the file is pre-written before any data gets added to it
    {
        currentSemesters.clear();
        currentSemesters << "1/2/3,startdate,enddate";
    }
    currentSemesters.seekg(0);

    Semesters* currentSemestersList = nullptr;
    createList(currentSemestersList, currentSemesters, startYear);

    bool inserted = 0;
    while (!inserted) {
        std::string choice = "a";
        while (!isDigit_w(choice)) {
            std::cout << "Choose the input method by which semesters' data are to be entered:\n"
            << "1. Single input (manually)\n2. CSV file\n0. Back to main menu\n: ";
            std::getline(std::cin, choice);
            if (!isDigit_w(choice)) {
                std::cout << "Invalid format for choice\n";
                continue;
            }
            switch(stoi(choice)) {
                case 1: {
                    std::string semesterInput;
                    std::cout << "Enter the data of a SINGLE new semester (already existing semester will not be added)\n(format: 1/2/3,startyear,enddate)\n(enter 0 to return to previous menu)\n: ";
                    std::getline(std::cin, semesterInput);
                    semesterInput = toLower_w(semesterInput);
                    if (semesterInput != "0") {
                        appendNewSemesterList(semestersHead, semesterInput, startYear, true);
                        appendNewSemesterFile(dataFile, semesterInput, startYear, true);
                        appendNewSemesterFile(currentSemesters, semesterInput, startYear);
                        inserted = 1;
                    }
                    else choice = "0";
                    break;
                }
                case 2: {
                    std::string fileSemesterInput;
                    std::cout << "Enter the directory of the CSV file containing data on multiple semesters\n"
                    << "(already existing semesters or semester with wrong-formatted data will not be added)\n"
                    <<"(enter 0 to return to previous menu)\n: ";
                    std::getline(std::cin, fileSemesterInput);
                    if (fileSemesterInput != "0") {
                        std::fstream fileClass(fileSemesterInput.c_str(), std::ios::in);
                        if (fileClass.is_open()) {
                            if (checkInputFormatSC(fileClass, 1)) {
                                SNode* fInputBatch = nullptr;

                                createList(fInputBatch, fileClass);
                                appendBatchSemesterList(semestersHead, fInputBatch, startYear, true);
                                appendBatchSemesterFile(dataFile, fInputBatch, startYear, true);
                                appendBatchSemesterFile(currentSemesters, fInputBatch, startYear);

                                destructList(fInputBatch);

                                inserted = 1;
                            }
                            else std::cout << "Invalid format.\n";
                        }
                        else std::cout << "\"" << fileSemesterInput << "\" couldn't be found.\n";
                    }
                    else choice = "0";
                    break;
                }
                case 0: {
                    return;
                }
            }
        }
    }
    destructList(currentSemestersList);
}
void appendNewSemesterList(Semesters*& semestersHead, std::string newSemesterData, int schoolYear, bool full) {
    if (!semesterCheckBool(newSemesterData, schoolYear)) return;

    if (semesterListSearchBool(semestersHead, stoi(newSemesterData.substr(0, 1)), schoolYear)) return;

    Semesters* nodeNew = new Semesters;
    readSemesterData(nodeNew, newSemesterData, full);
    if (!full) semestersHead->schoolYear = schoolYear;

	if (semestersHead == nullptr) {
		nodeNew->nodePrev = nullptr;
		nodeNew->nodeNext = nullptr;
		semestersHead = nodeNew;
		return;
	}

	Semesters* nodeCurr = semestersHead;
	while (nodeCurr->nodeNext != nullptr) {
		nodeCurr = nodeCurr->nodeNext;
	}
	nodeNew->nodePrev = nodeCurr;
	nodeNew->nodeNext = nullptr;
	nodeCurr->nodeNext = nodeNew;
}
void appendNewSemesterFile(std::fstream& dataFile, std::string newSemesterData, int schoolYear, bool full) {
    if (!semesterCheckBool(newSemesterData, schoolYear)) return;
    
    if (semesterFileSearchBool(dataFile, stoi(newSemesterData.substr(0, 1)), schoolYear, full)) return;

    //Get to end of file for appendage
    while (!dataFile.eof()) {
        std::string line;
        std::getline(dataFile, line);
    }
    dataFile.clear();       //Remove file's EOF flag so that new line can be added
    
	dataFile << std::endl << newSemesterData.substr(0, 1);
    if (full) dataFile << "," << schoolYear;
    dataFile << "," << newSemesterData.substr(2);
    dataFile.flush();

    dataFile.clear();
    dataFile.seekg(0); //Move to beginning of file

    appendNewSemesterFolder(newSemesterData, schoolYear);
}
void appendNewSemesterFolder(std::string newSemesterData, int startYear) {
    mkdir(std::string("data/" + std::to_string(startYear) + "/semesters/" + newSemesterData.substr(0, 1)).c_str());
}
void appendBatchSemesterList(Semesters*& semestersHead, SNode* batch , int schoolYear, bool full) {
    SNode* batchCurr = batch;
    while (batchCurr != nullptr) {
        appendNewSemesterList(semestersHead, batchCurr->value, schoolYear, full);
        batchCurr = batchCurr->nodeNext;
    }
}
void appendBatchSemesterFile(std::fstream& dataFile, SNode* batch, int schoolYear, bool full) {
    SNode* batchCurr = batch;
    while (batchCurr != nullptr) {
        appendNewSemesterFile(dataFile, batchCurr->value, schoolYear, full);
        batchCurr = batchCurr->nodeNext;
    }
}
void appendBatchSemesterFolder(SNode* batch, int startYear) {
    SNode* batchCurr = batch;
    while (batchCurr != nullptr) {
        appendNewSemesterFolder(batchCurr->value, startYear);
        batchCurr = batchCurr->nodeNext;
    }
}
bool semesterListSearchBool(Semesters* semestersHead, int semester, int startYear) {
    while (semestersHead != nullptr) {
        if (semestersHead->semester == semester && semestersHead->schoolYear == startYear) return 1;
        semestersHead = semestersHead->nodeNext;
    }
    return 0;
}
bool semesterFileSearchBool(std::fstream& semestersTotalFile, int semester, int startYear, bool full) {
    semestersTotalFile.clear();
    semestersTotalFile.seekg(0);

    std::string categories;
    std::getline(semestersTotalFile, categories);
    while (!semestersTotalFile.eof()) {
        std::string currentLine;
        std::getline(semestersTotalFile, currentLine);
        if (currentLine.find(std::to_string(semester) + ",") == 0 && currentLine.find(std::to_string(startYear)) != std::string::npos) return 1;
        if (currentLine.find(std::to_string(startYear) + ",") == 0 && !full) return 1;
    }
    return 0;
}

bool semesterCheckBool(std::string semesterData, int schoolYear) {
    int count = 0;
    for (int i = 0; i < semesterData.size(); i++) {
        if (semesterData[i] == ',') {
            switch(count) {
                case 0: {
                    //Check before the first comma
                    if (!isDigit_w(semesterData.substr(0, i))) return 0;

                    //Check after the first comma
                    i = i + 1;
                    int secondComma;
                    int slashCount = 0;
                    for (int j = i; j < semesterData.size(); j++) {
                        if (semesterData[j] == ',') {
                            secondComma = j;
                            break;
                        }
                        if (j == semesterData.size() - 1) return 0;     //This means the string doesn't have a second comma -> invalid format
                    }
                    if (!isValidDate(semesterData.substr(i, secondComma - i))) return 0;
                    for (int j = i; j < secondComma - j; j++) {
                        if (semesterData[j] == '/') {
                            if (semesterData.substr(i + 1, 1) == "/") return 0;
                            if (!isDigit_w(semesterData.substr(i + 1, j - i - 1))) return 0;
                            if (stoi(semesterData.substr(i + 1, j - i - 1)) < 1 && stoi(semesterData.substr(i + 1, j - i - 1)) > 31) return 0;
                            else { i = j + 1; slashCount++; }
                            if (slashCount == 1 && (stoi(semesterData.substr(i + 1, j - i - 1)) < 1 || stoi(semesterData.substr(i + 1, j - i - 1))) > 12) return 0;
                            else { i = j + 1; slashCount++; }
                        }
                        if (j == secondComma - j) {
                            if (!isDigit_w(semesterData.substr(i + 1, j - i - 1))) return 0;
                            if (slashCount == 2 && stoi(semesterData.substr(i + 1, j - i - 1)) < 0) return 0;
                        }
                    }
                    break;
                }
                case 1: {
                    //Check after the second comma
                    int slashCount = 0;
                    if (!isValidDate(semesterData.substr(i+ 1))) return 0;
                    for (int j = i + 1; j < semesterData.size(); j++) {
                        if (semesterData[j] == '/') {
                            if (semesterData.substr(i + 1, 1) == "/") return 0;
                            if (!isDigit_w(semesterData.substr(i + 1, j - i - 1))) return 0;
                            if (stoi(semesterData.substr(i + 1, j - i - 1)) < 1 && stoi(semesterData.substr(i + 1, j - i - 1)) > 31) return 0;
                            else { i = j + 1; slashCount++; }
                            if (slashCount == 1 && (stoi(semesterData.substr(i + 1, j - i - 1)) < 1 || stoi(semesterData.substr(i + 1, j - i - 1))) > 12) return 0;
                            else { i = j + 1; slashCount++; }
                        }
                        if (j == semesterData.size() - 1) {
                            if (!isDigit_w(semesterData.substr(i + 1, j - i - 1))) return 0;
                            if (slashCount == 2 && stoi(semesterData.substr(i + 1, j - i - 1)) < 0) return 0;
                        }
                    }
                    break;
                }
            }
            count++;
        }
    }
    if (count != 2) return 0;
    return 1;
}

/*Course*/
void addCourseToSemester(Semesters*& semestersHead, int schoolYear) {
    bool inserted = 0;
    while (!inserted) {
        std::string choice = "a";
        while (!isDigit_w(choice)) {
            std::cout << "Choose the input method by which courses' data are to be entered:\n"
            << "1. Single input (manually)\n2. CSV file\n0. Back to main menu\n: ";
            std::getline(std::cin, choice);
            if (!isDigit_w(choice)) {
                std::cout << "Invalid format for choice\n";
                continue;
            }
            switch(stoi(choice)) {
                case 1: {
                    std::string semesterInput;
                    std::cout << "Enter the data of a SINGLE new course (already existing course will not be added)\n(format: semester,courseid,coursename,teachername,numberofcredits,studentmax,daySession (ex: MON-S1|TUE-S4|....))\n(enter 0 to return to previous menu)\n: ";
                    std::getline(std::cin, semesterInput);
                    if (semesterInput != "0") {
                        appendNewCourse(semestersHead, semesterInput, schoolYear);
                        inserted = 1;
                    }
                    else choice = "0";
                    break;
                }
                case 2: {
                    std::string fileSemesterInput;
                    std::cout << "Enter the directory of the CSV file containing data on multiple courses\n"
                    << "(format: semester,courseid,coursename,teachername,numberofcredits,studentmax,daySession (ex: MON-S1|TUE-S4|....))\n"
                    << "(already existing courses or courses with wrong-formatted data will not be added)\n"
                    <<"(enter 0 to return to previous menu)\n: ";
                    std::getline(std::cin, fileSemesterInput);
                    if (fileSemesterInput != "0") {
                        std::fstream fileClass(fileSemesterInput.c_str(), std::ios::in);
                        if (fileClass.is_open()) {
                            if (checkInputFormatSC(fileClass, 2)) {
                                SNode* fInputBatch = nullptr;

                                createList(fInputBatch, fileClass);
                                appendBatchCourse(semestersHead, fInputBatch, schoolYear);

                                destructList(fInputBatch);

                                inserted = 1;
                            }
                            else std::cout << "Invalid format.\n";
                        }
                        else std::cout << "\"" << fileSemesterInput << "\" couldn't be found.\n";
                    }
                    else choice = "0";
                    break;
                }
                case 0: {
                    return;
                }
            }
        }
    }
}

void appendNewCourse(Semesters*& semestersHead, std::string newCoursedata, int schoolYear) {
    //Remove semester from the original string, therefore semester should be checked for isDigit first (even before the check on the entire string)
    if (!isDigit_w(newCoursedata.substr(0, 1))) return;
    int semester = stoi(newCoursedata.substr(0, 1));
    newCoursedata = newCoursedata.substr(2);

    Semesters* semesterCurr = semestersHead;
    bool foundSemester = 0;
    while (semesterCurr != nullptr) {
        if (semesterCurr->semester == semester && semesterCurr->schoolYear == schoolYear) { foundSemester = 1; break; }
        semesterCurr = semesterCurr->nodeNext;
    }
    if (!foundSemester) return;
    
    Course* coursesHead = semesterCurr->semesterCourseHead;
    if (!courseFormatCheck(newCoursedata)) return;

    std::fstream courseFileData(std::string("data/" + std::to_string(schoolYear) + "/semesters/" + std::to_string(semester) + "/course.csv").c_str(), std::ios::app | std::ios::out | std::ios::in);
    std::string courseFileCategories;
    std::getline(courseFileData, courseFileCategories);
    if (courseFileCategories == "" && courseFileData.eof())      //If the file is newly created, a line for category in the file is pre-written before any data gets added to it
    {
        courseFileData.clear();
        courseFileData << "courseid,coursename,teachername,numberofcredits,studentmax,daySession (ex: MON-S1|TUE-S4|....)";
    }
    courseFileData.seekg(0);
    createList(semestersHead->semesterCourseHead, courseFileData);

    Course* nodeNew = new Course;
    readCourseData(nodeNew, newCoursedata);

    //This is put here instead of at beginning of the function so that nodeNew->studentID can be checked
    if (courseListSearchBool(coursesHead, nodeNew->courseId)) {
        delete nodeNew;
        return;
    }

	if (semestersHead->semesterCourseHead == nullptr) {
		nodeNew->nodePrev = nullptr;
		nodeNew->nodeNext = nullptr;
		semestersHead->semesterCourseHead = nodeNew;
	}
    else {
        Course* nodeCurr = semestersHead->semesterCourseHead;
        while (nodeCurr->nodeNext != nullptr) {
            nodeCurr = nodeCurr->nodeNext;
        }
        nodeNew->nodePrev = nodeCurr;
        nodeNew->nodeNext = nullptr;
        nodeCurr->nodeNext = nodeNew;
    }

    appendNewCourseFile(courseFileData, nodeNew, schoolYear);
    mkdir(std::string("data/" + std::to_string(schoolYear) + "/semesters/" + std::to_string(semester) + "/" + nodeNew->courseId).c_str());
}

void appendNewCourseFile(std::fstream& dataFile, Course* newCourseNode, int schoolYear) {
    //Get to end of file for appendage
    while (!dataFile.eof()) {
        std::string line;
        std::getline(dataFile, line);
    }
    dataFile.clear();       //Remove file's EOF flag so that new line can be added
    
	dataFile << std::endl << newCourseNode->courseId << "," << newCourseNode->courseName
    << "," << newCourseNode->teacherName << "," << newCourseNode->numOfCredits
    << "," << newCourseNode->studentMax << "," << newCourseNode->daySession;
    dataFile.flush();

    dataFile.clear();
    dataFile.seekg(0); //Move to beginning of file
}

void appendBatchCourse(Semesters*& semestersHead, SNode* batch, int schoolYear) {
    SNode* batchCurr = batch;
    while (batchCurr != nullptr) {
        appendNewCourse(semestersHead, batchCurr->value, schoolYear);
        batchCurr = batchCurr->nodeNext;
    }
}

bool courseFormatCheck(std::string courseData) {
    int level = 0;
    int commaCount = 0;
    int afterComma;
    for (int i = 0; i < courseData.size(); i++) {
        if (courseData[i] == ',') {
            switch(level) {
                case 0: {
                    commaCount++;
                    break;
                }
                case 1: {
                    commaCount++;
                    break;
                }
                case 2: {
                    commaCount++;
                    break;
                }
                case 3: {
                    if (!isDigit_w(courseData.substr(afterComma + 1, i - afterComma - 1))) return 0;
                    commaCount++;
                    break;
                }
                case 4: {
                    if (!isDigit_w(courseData.substr(afterComma + 1, i - afterComma - 1))) return 0;
                    commaCount++;
                    break;
                }
            }
            afterComma = i;
            level++;
        }
        if (level == 5 && i == courseData.size() - 1) {
            std::string daySession = courseData.substr(afterComma + 1);
            if (daySession == "") return 0;
            if (daySession[daySession.size() - 1] == '|') return 0;
        }
    }
    if (commaCount != 5) return 0;
    return 1;
}

bool courseListSearchBool(Course* courseHead, std::string courseID) {
    while (courseHead != nullptr) {
        if (courseHead->courseId == courseID) return 1;
        courseHead = courseHead->nodeNext;
    }
    return 0;
}

bool checkInputFormatSC(std::fstream& inputFile, int mode) {
    /*
    1. Semester
    2. Course
    */
    bool validFormat = 1;
    switch(mode) {
        case 1: {
            std::string categories;
            std::getline(inputFile, categories);
            if (categories != "1/2/3,startdate,enddate") return 0;
            break;
        }
        case 2: {
            std::string categories;
            std::getline(inputFile, categories);
            if (categories.find("semester,courseid,coursename,teachername,numberofcredits,studentmax,daySession") == std::string::npos) return 0;
        }
    }

    inputFile.clear();
    inputFile.seekg(0);
    return 1;
}