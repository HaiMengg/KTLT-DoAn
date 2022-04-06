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
        while (choice == "" || !isDigit_w(choice)) {
            std::cout << "Choose the input method by which semesters' data are to be entered:\n"
            << "1. Single input (manually)\n2. CSV file\n0. Back to main menu\n: ";
            std::getline(std::cin, choice);
            if (choice == "" || !isDigit_w(choice)) {
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
                        appendNewSemesterList(semestersHead, semesterInput, startYear, false);
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
                                appendBatchSemesterList(semestersHead, fInputBatch, startYear, false);
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
    if (!semesterCheckBool(newSemesterData, schoolYear, semestersHead)) return;

    if (semesterListSearchBool(semestersHead, stoi(newSemesterData.substr(0, 1)), schoolYear)) return;

    Semesters* nodeNew = new Semesters;
    readSemesterData(nodeNew, newSemesterData, full);
    if (!full) nodeNew->schoolYear = schoolYear;

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
    Semesters* semesterHead = nullptr;
    if (full) createList(semesterHead, dataFile);
    else createList(semesterHead, dataFile, schoolYear);
    if (!semesterCheckBool(newSemesterData, schoolYear, semesterHead)) {
        destructList(semesterHead);
        return;
    }
    destructList(semesterHead);
    
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

bool semesterCheckBool(std::string semesterData, int schoolYear, Semesters* semesterHead) {
    std::string startDate, endDate;
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
                    startDate = semesterData.substr(i, secondComma - i);
                    if (!isValidDate(startDate)) return 0;
                    for (int j = i; j < secondComma - j; j++) {
                        if (semesterData[j] == '/') {
                            if (!isDigit_w(semesterData.substr(i, j - i))) return 0;
                            if (stoi(semesterData.substr(i, j - i)) < 1 && stoi(semesterData.substr(i, j - i)) > 31) return 0;
                            else { i = j + 1; slashCount++; }
                            if (slashCount == 1 && (stoi(semesterData.substr(i, j - i)) < 1 || stoi(semesterData.substr(i, j - i)) > 12)) return 0;
                            else { i = j + 1; slashCount++; }
                        }
                        if (j == secondComma - j) {
                            if (!isDigit_w(semesterData.substr(i + 1, j - i - 1))) return 0;
                            if (slashCount == 2 && stoi(semesterData.substr(i, j - i)) < 0) return 0;
                        }
                    }
                    break;
                }
                case 1: {
                    //Check after the second comma
                    int slashCount = 0;
                    endDate = semesterData.substr(i+ 1);
                    if (!isValidDate(endDate)) return 0;
                    for (int j = i + 1; j < semesterData.size(); j++) {
                        if (semesterData[j] == '/') {
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
    if (!isValidSemesterDate(startDate, endDate, semesterHead, schoolYear)) return 0;

    if (count != 2) return 0;
    return 1;
}

bool isValidSemesterDate(std::string startDate, std::string endDate, Semesters* semesterHead, int schoolYear) {
    if (startDate == endDate) return 0;
    if (getDateData(endDate, 'y') - getDateData(startDate, 'y') > 1) return 0;

    //Check if start-end period can actually exist and if it lasts for more than 4 months
    if (schoolYear - getDateData(startDate, 'y') > 1 || schoolYear - getDateData(endDate, 'y') > 1) return 0;
    if (schoolYear > getDateData(startDate, 'y')) return 0;
    if (getDateData(startDate, 'y') == getDateData(endDate, 'y')) {
        if (getDateData(endDate, 'm') - getDateData(startDate, 'm') < 0) return 0;
        else if (getDateData(endDate, 'm') - getDateData(startDate, 'm') > 4) return 0;
    }
    if (getDateData(startDate, 'y') == getDateData(endDate, 'y') - 1) {
        if (12 - getDateData(startDate, 'm') + getDateData(endDate, 'm') > 4) return 0;
    }

    //Check if the current start-end period overlaps with any other periods of the same school year or of the previous or the next school year
    Semesters* curr = semesterHead;
    while (curr != nullptr) {
        if (curr->schoolYear == schoolYear) {
            //The current period can only exist either before or after
            bool checked = 0;
            if (!checked && getDateData(startDate, 'm') < getDateData(curr->endDate, 'm')) return 0;
            else if (!checked && getDateData(startDate, 'm') == getDateData(curr->endDate, 'm')) {
                if (getDateData(startDate, 'd') < getDateData(curr->endDate, 'd')) return 0;
                else checked = 1;
            }
            else checked = 1;

            if (!checked && getDateData(curr->startDate, 'm') < getDateData(endDate, 'm')) return 0;
            else if (!checked && getDateData(curr->startDate, 'm') == getDateData(endDate, 'm')) {
                if (getDateData(curr->startDate, 'd') < getDateData(endDate, 'd')) return 0;
            }
        }

        if (curr->schoolYear - schoolYear == -1) {
            if (getDateData(startDate, 'm') < getDateData(curr->endDate, 'm')) return 0;
            else if (getDateData(startDate, 'm') == getDateData(curr->endDate, 'm')) {
                if (getDateData(startDate, 'd') < getDateData(curr->endDate, 'd')) return 0;
            }
        }

        if (curr->schoolYear - schoolYear == 1) {
            if (getDateData(curr->startDate, 'm') < getDateData(endDate, 'm')) return 0;
            else if (getDateData(curr->startDate, 'm') == getDateData(endDate, 'm')) {
                if (getDateData(curr->startDate, 'd') < getDateData(endDate, 'd')) return 0;
            }
        }

        curr = curr->nodeNext;
    }

    return 1;
}

/*Course*/
void addCourseToSemester(Semesters*& semestersHead, int schoolYear) {
    bool inserted = 0;
    while (!inserted) {
        std::string choice = "a";
        while (choice == "" || !isDigit_w(choice)) {
            std::cout << "Choose the input method by which courses' data are to be entered:\n"
            << "1. Single input (manually)\n2. CSV file\n0. Back to main menu\n: ";
            std::getline(std::cin, choice);
            if (choice == "" || !isDigit_w(choice)) {
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
    createList(semestersHead->semesterCourseHead, courseFileData, schoolYear, semester);

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

void updateCourse(Semesters* semestersHead, int schoolYear) {
    Semesters* curr;
    std::string cont = "y";
    while (cont == "y") {
        curr = semestersHead;
        bool isFound = 0;
        std::cout << "Enter the ID of the course whose information you want to update (enter \"0\" to return to previous menu): ";
        std::string courseID;
        std::getline(std::cin, courseID);
        while (curr != nullptr) {
            if (curr->schoolYear == schoolYear) {
                Course* semesterCourseHead = curr->semesterCourseHead;

                if (courseID == "0") return;

                while (semesterCourseHead != nullptr) {
                    if (semesterCourseHead->courseId == courseID) {
                        std::string originalCourseID = courseID;

                        isFound = 1;
                        std::fstream currentCourseFile;
                        currentCourseFile.open(std::string("data/" + std::to_string(schoolYear) + "/semesters/" + std::to_string(curr->semester) + "/course.csv").c_str(), std::ios::out);
                        updateCourseNext(semesterCourseHead, currentCourseFile, courseID);

                        //Rename course ID folder to suit change
                        if (originalCourseID != courseID) {
                            std::string oldDir = "data/" + std::to_string(schoolYear) + "/semesters/" + std::to_string(curr->semester) + "/" + originalCourseID;
                            std::string newDir = "data/" + std::to_string(schoolYear) + "/semesters/" + std::to_string(curr->semester) + "/" + courseID;
                            MoveFile(std::string(oldDir).c_str(), std::string(newDir).c_str());
                        }

                        currentCourseFile.close();
                        break;
                    }
                    semesterCourseHead = semesterCourseHead->nodeNext;
                }
            }
            curr = curr->nodeNext;
        }
        if (!isFound) std::cout << "No course with the given ID found\n";

        std::cout << "Do you want to choose another course? \"y\" to continue, \"n\" or anything else to return to previous menu: ";
        std::getline(std::cin, cont);
    }
}

void updateCourseNext(Course*& currentCourseNode, std::fstream& currentCourseFile, std::string& courseID) {
    std::string newCourseID = courseID;
    std::string courseName,teacherName,creditNum,maxStudent,daySession;
    bool validForFile = 1;
    while (true) {
        system("cls");
        std::cout << "Enter \"0\" at anytime to return to previous menu and for changes to be applied\n\nWhich data of course " << courseID << " do you want to change?\n";

        std::cout << "[1] Course ID\n[2] Course name\n[3] Teacher name\n[4] Number of credits\n[5] Max number of students\n[6] Day-session's of the week (ex: MON-S1|TUE-S4)\n[0] Return to previous menu\n: ";
        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "0") {
            if (validForFile) {
                readList(currentCourseNode, currentCourseFile);
            }
            return;
        }

        while (choice != "0") {
            if (choice == "1") {
                std::cout << "Enter the new course ID for course " << courseID << ": ";
                std::getline(std::cin, courseID);
                if (courseID == "0") break;
                currentCourseNode->courseId = courseID;
                std::cout << "Course ID changed successfully\n";
                system("pause");
                system("cls");
            }
            else if (choice == "2") {
                std::cout << "Enter the new course name for course " << courseID << ": ";
                std::getline(std::cin, courseName);
                if (courseName == "0") break;
                currentCourseNode->courseName = courseName;
                std::cout << "Course name changed successfully\n";
                system("pause");
                system("cls");
            }
            else if (choice == "3") {
                std::cout << "Enter the new teacher name for course " << courseID << ": ";
                std::getline(std::cin, teacherName);
                if (teacherName == "0") break;
                currentCourseNode->teacherName = teacherName;
                std::cout << "Teacher name changed successfully\n";
                system("pause");
                system("cls");
            }
            else if (choice == "5") {
                std::cout << "Enter the new maximum number of student for course " << courseID << ": ";
                std::getline(std::cin, maxStudent);
                if (maxStudent == "0") break;
                if (isDigit_w(maxStudent)) {
                    std::cout << "Max number of student changed successfully\n";
                    currentCourseNode->studentMax = stoi(maxStudent);
                }
                else {
                    std::cout << "Input error: value entered is not a number\n";
                    validForFile = 0;
                }
                system("pause");
                system("cls");
            }
            else if (choice == "4") {
                std::cout << "Enter the new number of credits for course " << courseID << ": ";
                std::getline(std::cin, creditNum);
                if (creditNum == "0") break;
                if (isDigit_w(creditNum)) {
                    std::cout << "Number of credits changed successfully\n";
                    currentCourseNode->numOfCredits = creditNum;
                }
                else {
                    std::cout << "Input error: value entered is not a number\n";
                    validForFile = 0;
                }
                system("pause");
                system("cls");
            }
            else if (choice == "6") {
                std::cout << "Enter the day-session (format: [weekday1]-[S1/S2/S3/S4]|[weekday2]-[S1/S2/S3/S4]|...) for course " << courseID << ": ";
                std::getline(std::cin, daySession);
                if (daySession == "0") break;
                currentCourseNode->daySession = daySession;
                std::cout << "Course name changed successfully\n";
                system("pause");
                system("cls");
            }
            choice = "0";
        }
    }
}

void deleteCourse(Semesters* semestersHead, int schoolYear) {
    Semesters* curr;
    std::string cont = "y";
    while (cont == "y") {
        std::cout << "Enter the ID of the course whose information you want to delete (enter \"0\" to return to previous menu): ";
        std::string courseID;
        std::getline(std::cin, courseID);
        bool isFound = 0;
        curr = semestersHead;
        while (curr != nullptr) {
            if (curr->schoolYear == schoolYear) {
                Course* semesterCourseHead = curr->semesterCourseHead;

                if (courseID == "0") return;

                Course* semesterCourseCurr = semesterCourseHead;
                while (semesterCourseCurr != nullptr) {
                    if (semesterCourseCurr->courseId == courseID) {
                        std::string originalCourseID = courseID;
                        isFound = 1;
                        std::fstream currentCourseFile;
                        currentCourseFile.open(std::string("data/" + std::to_string(schoolYear) + "/semesters/" + std::to_string(curr->semester) + "/course.csv").c_str(), std::ios::out);
                        //If there is only one node in the list, the program has no way to know that there is no node left so the head itself is assigned to point to null right before the deletion
                        if (semesterCourseCurr->nodePrev == nullptr && semesterCourseHead->nodeNext == nullptr) semesterCourseHead = nullptr;
                        deleteCourseNext(semesterCourseCurr, currentCourseFile, courseID);

                        if (courseID == "") {
                            std::string rmvDir = "data/" + std::to_string(schoolYear) + "/semesters/" + std::to_string(curr->semester) + "/" + originalCourseID;
                            remove(std::string(rmvDir + "/student.csv").c_str());
                            rmdir(rmvDir.c_str());
                        }

                        currentCourseFile.close();

                        system("pause");
                        break;
                    }
                    semesterCourseCurr = semesterCourseCurr->nodeNext;
                }
            }
            curr = curr->nodeNext;
        }
        if (!isFound) std::cout << "No course with the given ID found\n";

        std::cout << "Do you want to choose another course? \"y\" to continue, \"n\" or anything else to return to previous menu: ";
        std::getline(std::cin, cont);
        system("cls");
    }
}

void deleteCourseNext(Course*& currentCourseHead, std::fstream& currentCourseFile, std::string& courseID) {
    Course* rmv = currentCourseHead;
    if (rmv->nodePrev != nullptr || rmv->nodeNext != nullptr) {
        if (rmv->nodePrev != nullptr) {
            rmv->nodePrev->nodeNext = rmv->nodeNext;
            currentCourseHead = rmv->nodePrev;
        }
        if (rmv->nodeNext != nullptr) {
            rmv->nodeNext->nodePrev = rmv->nodePrev;
            currentCourseHead = rmv->nodeNext;
        }
    }
    else if (rmv->nodePrev == nullptr && rmv->nodeNext == nullptr) currentCourseHead = nullptr;
    delete rmv;
    std::cout << "Course " << courseID << " deleted successfully\n";
    courseID = "";

    Course* curr = currentCourseHead;
    if (curr != nullptr) {
        while (curr->nodePrev != nullptr) {
            curr = curr->nodePrev;
        }
    }
    readList(curr, currentCourseFile);
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
            if (countElement(daySession, '|') > 1) return 0;

            bool isWDay = 0;
            if (daySession.substr(0, 3) == "MON" || daySession.substr(0, 3) == "TUE" || daySession.substr(0, 3) == "WED" || daySession.substr(0, 3) == "THU") isWDay = 1;
            if (daySession.substr(0, 3) == "FRI" || daySession.substr(0, 3) == "SAT" || daySession.substr(0, 3) == "SUN") isWDay = 1;
            if (!isWDay) return 0;
            isWDay = 0;
            if (daySession.substr(7, 3) == "MON" || daySession.substr(7, 3) == "TUE" || daySession.substr(7, 3) == "WED" || daySession.substr(7, 3) == "THU") isWDay = 1;
            if (daySession.substr(7, 3) == "FRI" || daySession.substr(7, 3) == "SAT" || daySession.substr(7, 3) == "SUN") isWDay = 1;
            if (!isWDay) return 0;

            bool isValidSession = 0;
            if (daySession.substr(4, 2) == "S1" || daySession.substr(4, 2) == "S2" || daySession.substr(4, 2) == "S3" || daySession.substr(4, 2) == "S4") isValidSession = 1;
            if (daySession.substr(11, 2) == "S1" || daySession.substr(11, 2) == "S2" || daySession.substr(11, 2) == "S3" || daySession.substr(11, 2) == "S4") isValidSession = 1;
            if (!isValidSession) return 0;
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

void createCourseReg(CourseReg*& courseRegHead, std::fstream& dataFile, int schoolYear, Semesters* semestersHead) {
    std::string input;
    std::string cont = "y";
    CourseReg* newNode = nullptr;

    CourseReg* curr = courseRegHead;
    if (curr != nullptr) {
        while (curr->nodeNext != nullptr) {
            curr = curr->nodeNext;
        }
    }
    
    while (cont == "y") {
        while (input != "0") {
            std::cout << "\n====================================\n\nEnter \"0\" at anytime to return to previous menu\n\n";
            if (newNode == nullptr) newNode = new CourseReg;
            newNode->schoolYear = schoolYear;

            std::cout << "Enter the semester this course registration session belongs to: ";
            std::getline(std::cin, input);
            if (input == "0") break;
            if (!isDigit_w(input)) break;
            newNode->semester = stoi(input);

            if (!courseRegSearchBool(courseRegHead, newNode->schoolYear, newNode->semester)) {
                std::cout << "Enter the date this course registration session starts: ";
                std::getline(std::cin, input);
                if (input == "0") break;
                newNode->startDate = input;

                std::cout << "Enter the date this course registration session ends: ";
                std::getline(std::cin, input);
                if (input == "0") break;
                newNode->endDate = input;

                Semesters* currSem = semestersHead;
                while (currSem != nullptr) {
                    if (currSem->schoolYear == schoolYear && currSem->semester == newNode->semester) {
                        if (isDateLaterThanOrEqualTo(newNode->startDate, currSem->startDate) && isDateEarlierThanOrEqualTo(newNode->endDate, currSem->endDate)) {
                            newNode->nodeNext = nullptr;
                            newNode->nodePrev = curr;
                            if (courseRegHead != nullptr) curr->nodeNext = newNode;
                            else courseRegHead = newNode;
                            readList(courseRegHead, dataFile);
                            std::cout << "Course registration session successfully created\n";
                            system("pause");
                        }
                        else {
                            std::cout << "This course registration session exceeds the time span allowed for semester " << newNode->semester
                            << " of school year " << schoolYear << "-" << schoolYear + 1 << "\n";
                        }
                        break;
                    }
                    currSem = currSem->nodeNext;
                }
                if (currSem == nullptr) {
                    std::cout << "The school year " << schoolYear << "-" << schoolYear + 1 << " has no semester " << newNode->semester << "\n";
                }
                
            }
            else {
                delete newNode;
            }
            break;
        }
        
        if (input != "0") {
            std::cout << "Do you want to continue creating course registration session(s)? \"y\" to continue, \"n\" or anything else to return to previous menu: ";
            std::getline(std::cin, cont);
        }
        else {
            delete newNode;
            break;
        }
    }
    system("cls");
}

bool courseRegSearchBool(CourseReg* courseRegHead, int schoolYear, int semester) {
    CourseReg* curr = courseRegHead;
    while (curr != nullptr) {
        if (curr->schoolYear == schoolYear && curr->semester == semester) return 1;
        curr = curr->nodeNext;
    }
    return 0;
}