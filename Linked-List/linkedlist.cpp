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

void createList(DNode*& nodeHead, std::fstream& dataFile) {
    if (nodeHead == nullptr) {
        DNode* nodeCurr = nullptr;
        int currentValue;
        std::string categories;
        std::getline(dataFile, categories);
        while (!dataFile.eof()) {
            std::string currentLine;
            std::getline(dataFile, currentLine);
            if (currentLine != "") {    //In case there are unneccessary extra empty lines in the file
                if (nodeHead == nullptr) {
                    nodeHead = new DNode;
                    nodeHead->nodePrev = nullptr;
                    nodeHead->value = currentLine;
                    nodeHead->nodeNext = nullptr;
                    nodeCurr = nodeHead;
                }
                else {
                    nodeCurr->nodeNext = new DNode;
                    DNode* nodeTemp = nodeCurr;
                    nodeCurr = nodeCurr->nodeNext;
                    nodeCurr->nodePrev = nodeTemp;
                    nodeCurr->value = currentLine;
                    nodeCurr->nodeNext = nullptr;
                }
            }
        }
    }
}

void createList(SchoolYear*& schoolYearHead, std::fstream& dataFile) {
    if (schoolYearHead == nullptr) {
        SchoolYear* curr = nullptr;
        std::string categories;
        std::getline(dataFile, categories);

        while (!dataFile.eof()) {
            std::string currentLine;
            std::getline(dataFile, currentLine);
            if (currentLine != "") {    //In case there are unneccessary extra empty lines in the file
                if (schoolYearHead == nullptr) {
                    schoolYearHead = new SchoolYear;
                    schoolYearHead->nodePrev = nullptr;
                    schoolYearHead->schoolYear = stoi(currentLine);
                    schoolYearHead->nodeNext = nullptr;
                    curr = schoolYearHead;
                }
                else {
                    curr->nodeNext = new SchoolYear;
                    SchoolYear* prev = curr;
                    curr = curr->nodeNext;
                    curr->nodePrev = prev;
                    curr->schoolYear = stoi(currentLine);
                    curr->nodeNext = nullptr;
                }
            }
        }
    }
    
    dataFile.clear();
    dataFile.seekg(0);      //Reset cursor's position so the file will be more controller the next time it is used (since you will know where the cursor will be)
}

void createList(Classes*& classHead, std::fstream& dataFile) {
    if (classHead == nullptr) {
        Classes* curr = nullptr;
        std::string categories;
        std::getline(dataFile, categories);
        
        std::fstream currentClassStudent;
        while (!dataFile.eof()) {
            std::string currentLine;
            std::getline(dataFile, currentLine);
            if (currentLine != "") {    //In case there are unneccessary extra empty lines in the file
                if (classHead == nullptr) {
                    classHead = new Classes;
                    classHead->nodePrev = nullptr;
                    classHead->classID = currentLine.substr(0, currentLine.size() - 5);
                    if (currentLine.size() - 4 >= 0 && isDigit_w(currentLine.substr(currentLine.size() - 4))) {
                        classHead->startYear = stoi(currentLine.substr(currentLine.size() - 4));
                        
                        //Add current student list to current class node
                        currentClassStudent.open(std::string("data/" + std::to_string(classHead->startYear) + "/classes/" + classHead->classID + "/student.csv"));
                        if (currentClassStudent.is_open()) {
                            Student* currentClassStudentList = nullptr;
                            createList(currentClassStudentList, currentClassStudent, classHead->startYear, classHead->classID);
                            classHead->classStudentHead = currentClassStudentList;
                            currentClassStudent.close();
                        }
                    }
                    classHead->nodeNext = nullptr;
                    curr = classHead;
                }
                else {
                    Classes* prev = curr;
                    curr->nodeNext = new Classes;
                    curr = curr->nodeNext;
                    curr->nodePrev = prev;
                    curr->classID = currentLine.substr(0, currentLine.size() - 5);
                    if (currentLine.size() - 4 >= 0 && isDigit_w(currentLine.substr(currentLine.size() - 4))) {
                        curr->startYear = stoi(currentLine.substr(currentLine.size() - 4));
                        
                        //Add current student list to current class node
                        currentClassStudent.open(std::string("data/" + std::to_string(curr->startYear) + "/classes/" + curr->classID + "/student.csv"));
                        if (currentClassStudent.is_open()) {
                            Student* currentClassStudentList = nullptr;
                            createList(currentClassStudentList, currentClassStudent, curr->startYear, curr->classID);
                            curr->classStudentHead = currentClassStudentList;
                            currentClassStudent.close();
                        }
                    }
                    curr->nodeNext = nullptr;
                }
            }
        }
        currentClassStudent.close();
    }

    dataFile.clear();
    dataFile.seekg(0);      //Reset cursor's position so the file will be more controller the next time it is used (since you will know where the cursor will be)
}

//For reading all students
void createList(Student*& studentHead, std::fstream& dataFile) {
    if (studentHead == nullptr) {
        Student* curr = nullptr;
        std::string categories;
        std::getline(dataFile, categories);

        Student* prev = nullptr;
        while (!dataFile.eof()) {
            std::string currentLine;
            std::getline(dataFile, currentLine);
            if (currentLine != "") {    //In case there are unneccessary extra empty lines in the file
                if (studentHead == nullptr) {
                    studentHead = new Student;

                    studentHead->nodePrev = nullptr;

                    //Read and store current student data
                    readStudentData(studentHead, currentLine);

                    studentHead->nodeNext = nullptr;
                    curr = studentHead;
                }
                else {
                    Student* prev = curr;
                    curr->nodeNext = new Student;
                    curr = curr->nodeNext;
                    
                    curr->nodePrev = prev;

                    //Read and store current student data
                    readStudentData(curr, currentLine);
                    
                    curr->nodeNext = nullptr;
                }
            }
        }
    }
    
    dataFile.clear();
    dataFile.seekg(0);      //Reset cursor's position so the file will be more controller the next time it is used (since you will know where the cursor will be)
}
//For reading students of a single class (csv format: "")
void createList(Student*& studentHead, std::fstream& dataFile, int schoolYear, std::string currentClass) {
    if (studentHead == nullptr) {
        Student* curr = nullptr;
        std::string categories;
        std::getline(dataFile, categories);

        Student* prev = nullptr;
        while (!dataFile.eof()) {
            std::string currentLine;
            std::getline(dataFile, currentLine);
            if (currentLine != "") {    //In case there are unneccessary extra empty lines in the file
                if (studentHead == nullptr) {
                    studentHead = new Student;

                    studentHead->nodePrev = nullptr;

                    //Read and store current student data
                    readStudentData(studentHead, currentLine, false);
                    studentHead->usr = studentHead->studentID;
                    studentHead->pwd = studentHead->dob;
                    studentHead->startYear = std::to_string(schoolYear);
                    studentHead->classID = currentClass;

                    studentHead->nodeNext = nullptr;
                    curr = studentHead;
                }
                else {
                    Student* prev = curr;
                    curr->nodeNext = new Student;
                    curr = curr->nodeNext;
                    
                    curr->nodePrev = prev;

                    //Read and store current student data
                    readStudentData(curr, currentLine, false);
                    curr->usr = curr->studentID;
                    curr->pwd = curr->dob;
                    curr->startYear = std::to_string(schoolYear);
                    curr->classID = currentClass;
                    
                    curr->nodeNext = nullptr;
                }
            }
        }
    }
    
    dataFile.clear();
    dataFile.seekg(0);      //Reset cursor's position so the file will be more controller the next time it is used (since you will know where the cursor will be)
}

//For reading students of a single course
void createStuCoList(Student*& studentHead, std::fstream& dataFile) {
    if (studentHead == nullptr) {
        Student* curr = nullptr;
        std::string categories;
        std::getline(dataFile, categories);

        Student* prev = nullptr;
        while (!dataFile.eof()) {
            if (studentHead == nullptr) {
                studentHead = new Student;

                studentHead->nodePrev = nullptr;

                std::getline(dataFile, studentHead->studentID, ',');
                std::getline(dataFile, studentHead->firstName, ',');
                std::getline(dataFile, studentHead->lastName, ',');
                std::getline(dataFile, studentHead->dob, ',');
                std::getline(dataFile, studentHead->gender, ',');
                std::getline(dataFile, studentHead->socialID, ',');
                std::getline(dataFile, studentHead->classID);

                studentHead->nodeNext = nullptr;
                curr = studentHead;
            }
            else {
                Student* prev = curr;
                curr->nodeNext = new Student;
                curr = curr->nodeNext;
                
                curr->nodePrev = prev;

                std::getline(dataFile, curr->studentID, ',');
                std::getline(dataFile, curr->firstName, ',');
                std::getline(dataFile, curr->lastName, ',');
                std::getline(dataFile, curr->dob, ',');
                std::getline(dataFile, curr->gender, ',');
                std::getline(dataFile, curr->socialID, ',');
                std::getline(dataFile, curr->classID);
                
                curr->nodeNext = nullptr;
            }
        }
    }
    
    dataFile.clear();
    dataFile.seekg(0);      //Reset cursor's position so the file will be more controller the next time it is used (since you will know where the cursor will be)
}

void readStudentData(Student*& studentNode, std::string studentData, bool full) {
    int level;
    level = 0;
    int previousComma = 0;

    //Check if a total student.csv file is being read
    bool readingTotal = 0;
    if (isDigit_w(studentData.substr(0, 8)))
        readingTotal = 1;

    //Only runs when reading a total student.csv file
    int commaCount = 0;
    if (full && readingTotal) {
        for (int i = 0; i < studentData.size(); i++) {
            if (studentData[i] == ',') {
                switch(commaCount) {
                    case 0: {
                        studentNode->usr = studentData.substr(0, i);
                        break;
                    }
                    case 1: {
                        studentNode->pwd = studentData.substr(previousComma + 1, i - previousComma - 1);
                        break;
                    }
                }
                previousComma = i;
                commaCount++;
                if (commaCount == 2) break;
            }
        }
    }

    if (commaCount == 2) previousComma += 1;
    if (countElement(studentData, ',') == 5 || countElement(studentData, ',') == 10) level++;
    for (int i = previousComma; i < studentData.size(); i++) {
        if (studentData[i] == ',') {
            if (level == 0) { 
                studentData = studentData.substr(i + 1);
                level++;
                continue; 
            }
            switch(level) {
                case 1:
                if (commaCount == 0) studentNode->studentID = studentData.substr(0, i);
                else studentNode->studentID = studentData.substr(previousComma, i - previousComma);
                //Skip the "no" category
                if (studentNode->studentID.find(',') != std::string::npos) 
                    studentNode->studentID = studentNode->studentID.substr(studentNode->studentID.find(',') + 1);
                if (full && studentNode->usr == "") studentNode->usr = studentNode->studentID;
                break;
                case 2:
                studentNode->firstName = studentData.substr(previousComma + 1, i - previousComma - 1);
                break;
                case 3:
                studentNode->lastName = studentData.substr(previousComma + 1, i - previousComma - 1);
                break;
                case 4:
                studentNode->gender = studentData.substr(previousComma + 1, i - previousComma - 1);
                break;
                case 5:
                studentNode->dob = studentData.substr(previousComma + 1, i - previousComma - 1);
                if (full && studentNode->pwd == "") studentNode->pwd = studentNode->dob;
                break;
            }
            if (full && readingTotal) {
                switch(level) {
                    case 6:
                    studentNode->socialID = studentData.substr(previousComma + 1, i - previousComma - 1);
                    break;
                    case 7:
                    studentNode->startYear = studentData.substr(previousComma + 1, i - previousComma - 1);
                    break;
                    case 8:
                    studentNode->classID = studentData.substr(previousComma + 1, i - previousComma - 1);
                    break;
                }
            }
            previousComma = i;
            level++;
        }
        if (full && readingTotal && i == studentData.size() - 1) {
            createList(studentNode->studentCourseHead, studentData.substr(previousComma + 1), stoi(studentNode->startYear));
        }
        //Only runs when reading a class' student.csv file
        if (!full && i == studentData.size() - 1) {
            studentNode->socialID = studentData.substr(previousComma + 1, i - previousComma);
        }
    }
}

void createList(Semesters*& semestersHead, std::fstream& dataFile, int schoolYear) {
    if (semestersHead == nullptr) {
        Semesters* curr = nullptr;
        std::string categories;
        std::getline(dataFile, categories);

        while (!dataFile.eof()) {
            std::string currentLine;
            std::getline(dataFile, currentLine);
            if (currentLine != "") {    //In case there are unneccessary extra empty lines in the file
                if (semestersHead == nullptr) {
                    semestersHead = new Semesters;
                    semestersHead->nodePrev = nullptr;

                    if (schoolYear != -1) { 
                        readSemesterData(semestersHead, currentLine, false);
                        semestersHead->schoolYear = schoolYear;
                    }
                    else readSemesterData(semestersHead, currentLine);

                    semestersHead->nodeNext = nullptr;
                    curr = semestersHead;
                }
                else {
                    Semesters* prev = curr;
                    curr->nodeNext = new Semesters;
                    curr = curr->nodeNext;
                    curr->nodePrev = prev;

                    if (schoolYear != -1) { 
                        readSemesterData(curr, currentLine, false);
                        curr->schoolYear = schoolYear;
                    }
                    else readSemesterData(curr, currentLine);
                    
                    curr->nodeNext = nullptr;
                }
            }
        }
    }

    dataFile.clear();
    dataFile.seekg(0);      //Reset cursor's position so the file will be more controller the next time it is used (since you will know where the cursor will be)
}

void readSemesterData(Semesters*& semestersHead, std::string semesterData, bool full) {
    int level = 1;
    int afterComma;
    for (int i = 0; i < semesterData.size(); i++) {
        if (semesterData[i] == ',') {
            switch(level) {
                case 1: {
                    semestersHead->semester = stoi(semesterData.substr(0, i));
                    afterComma = i + 1;
                    break;
                }
                case 2: {
                    if (full) {
                        semestersHead->schoolYear = stoi(semesterData.substr(afterComma, i - afterComma));
                        afterComma = i + 1;
                    }
                    else {
                        semestersHead->startDate = semesterData.substr(afterComma, i - afterComma);
                        afterComma = i + 1;
                    }
                    break;
                }
                case 3: {
                    semestersHead->startDate = semesterData.substr(afterComma, i - afterComma);
                    semestersHead->endDate = semesterData.substr(i + 1);
                    break;
                }
            }
        
            level++;
        }
        if (!full && i == semesterData.size() - 1) semestersHead->endDate = semesterData.substr(afterComma);
    }

    std::fstream semesterCourseFile(std::string("data/" + std::to_string(semestersHead->schoolYear) + "/semesters/" + std::to_string(semestersHead->semester) + "/course.csv"), std::ios::in);
    std::string courseCatagories;
    std::getline(semesterCourseFile, courseCatagories);
    if (semesterCourseFile.is_open() && courseCatagories != "") {
        semesterCourseFile.seekg(0);
        Course* semesterCourseList = nullptr;
        createList(semesterCourseList, semesterCourseFile, semestersHead->schoolYear, semestersHead->semester);
        semestersHead->semesterCourseHead = semesterCourseList;
    }
    semesterCourseFile.close();
}

void createList(Course*& courseHead, std::fstream& dataFile, int schoolYear, int semester) {
    if (courseHead == nullptr) {
        Course* curr = nullptr;
        std::string categories;
        std::getline(dataFile, categories);
        std::fstream courseStudentFile;

        while (!dataFile.eof()) {
            std::string currentLine;
            std::getline(dataFile, currentLine);
            if (currentLine != "") {    //In case there are unneccessary extra empty lines in the file
                if (courseHead == nullptr) {
                    courseHead = new Course;
                    courseHead->nodePrev = nullptr;

                    readCourseData(courseHead, currentLine);

                    courseHead->nodeNext = nullptr;

                    courseStudentFile.open(std::string("data/" + std::to_string(schoolYear) + "/semesters/" + std::to_string(semester) + "/" + courseHead->courseId + "/student.csv"), std::ios::in);
                    if (courseStudentFile.is_open()) {
                        createStuCoList(courseHead->courseStudentHead, courseStudentFile);
                    }
                    courseStudentFile.close();

                    curr = courseHead;
                }
                else {
                    Course* prev = curr;
                    curr->nodeNext = new Course;
                    curr = curr->nodeNext;
                    curr->nodePrev = prev;

                    readCourseData(curr, currentLine);
                    
                    curr->nodeNext = nullptr;
                    
                    courseStudentFile.open(std::string("data/" + std::to_string(schoolYear) + "/semesters/" + std::to_string(semester) + "/" + curr->courseId + "/student.csv"), std::ios::in);
                    if (courseStudentFile.is_open()) {
                        createStuCoList(curr->courseStudentHead, courseStudentFile);
                    }
                    courseStudentFile.close();
                }
            }
        }
    }

    dataFile.clear();
    dataFile.seekg(0);      //Reset cursor's position so the file will be more controller the next time it is used (since you will know where the cursor will be)
}

void readCourseData(Course*& courseHead, std::string courseData) {
    int level = 0;
    int afterComma;
    for (int i = 0; i < courseData.size(); i++) {
        if (courseData[i] == ',') {
            switch(level) {
                case 0: {
                    courseHead->courseId = toUpper_w(courseData.substr(0, i));
                    break;
                }
                case 1: {
                    courseHead->courseName = courseData.substr(afterComma + 1, i - afterComma - 1);
                    break;
                }
                case 2: {
                    courseHead->teacherName = courseData.substr(afterComma + 1, i - afterComma - 1);
                    break;
                }
                case 3: {
                    courseHead->numOfCredits = courseData.substr(afterComma + 1, i - afterComma - 1);
                    break;
                }
                case 4: {
                    courseHead->studentMax = stoi(courseData.substr(afterComma + 1, i - afterComma - 1));
                    break;
                }
            }
            afterComma = i;
            level++;
        }
        if (level == 5 && i == courseData.size() - 1) courseHead->daySession = courseData.substr(afterComma + 1);
    }
}

void readList(Course* courseHead, std::fstream& courseFile) {
    Course* curr = courseHead;
    courseFile << "courseid,coursename,teachername,numberofcredits,studentmax,daySession (ex: MON-S1|TUE-S4|....)";
    while (curr != nullptr) {
        courseFile << "\n" << curr->courseId << "," << curr->courseName << "," << curr->teacherName << "," << curr->numOfCredits << "," << curr->studentMax << "," << curr->daySession;
        curr = curr->nodeNext;
    }

    courseFile.flush();

    courseFile.clear();
    courseFile.seekg(0);
}

void createList(StudentCourse*& studentCourseHead, std::string courseData, int schoolYear) {
    int count = 3;
    StudentCourse* headCourse = new StudentCourse;
    StudentCourse* curCourse = headCourse;

    std::istringstream iss(courseData);
    std::string item;
    while (getline(iss, item, '|'))
    {
        if (count % 3 == 0)
        {
            if (count != 3)
            {
                curCourse -> nodeNext = new StudentCourse;
                curCourse -> nodeNext -> nodePrev = curCourse;
                curCourse = curCourse -> nodeNext;
            }

            curCourse -> schoolYear = schoolYear;
            curCourse -> sem1Courses = item;
        }

        if (count % 3 == 1) {
            curCourse -> sem2Courses = item;
            curCourse->schoolYear = schoolYear;
        }

        if (count % 3 == 2) {
            curCourse -> sem3Courses = item;
            curCourse->schoolYear = schoolYear;
        }

        count++;
    }

    curCourse -> schoolYear = schoolYear;
    curCourse -> nodeNext = nullptr;
    studentCourseHead = headCourse;
}

void createList(CourseReg*& courseRegHead, std::fstream& dataFile) {
    if (courseRegHead == nullptr) {
        CourseReg* curr = nullptr;
        std::string categories;
        std::getline(dataFile, categories);

        while (!dataFile.eof()) {
            std::string currentLine;
            std::getline(dataFile, currentLine);
            if (currentLine != "") {    //In case there are unneccessary extra empty lines in the file
                if (courseRegHead == nullptr) {
                    courseRegHead = new CourseReg;
                    courseRegHead->nodePrev = nullptr;

                    readCourseRegData(courseRegHead, currentLine);

                    courseRegHead->nodeNext = nullptr;
                    curr = courseRegHead;
                }
                else {
                    CourseReg* prev = curr;
                    curr->nodeNext = new CourseReg;
                    curr = curr->nodeNext;
                    curr->nodePrev = prev;

                    readCourseRegData(curr, currentLine);
                    
                    curr->nodeNext = nullptr;
                }
            }
        }
    }

    dataFile.clear();
    dataFile.seekg(0);      //Reset cursor's position so the file will be more controller the next time it is used (since you will know where the cursor will be)
}

void readCourseRegData(CourseReg*& courseRegHead, std::string courseRegData) {
    int level = 1;
    int afterComma;
    for (int i = 0; i < courseRegData.size(); i++) {
        if (courseRegData[i] == ',') {
            switch(level) {
                case 1: {
                    courseRegHead->semester = stoi(courseRegData.substr(0, i));
                    afterComma = i + 1;
                    break;
                }
                case 2: {
                    courseRegHead->schoolYear = stoi(courseRegData.substr(afterComma, i - afterComma));
                    afterComma = i + 1;
                }
                case 3: {
                    courseRegHead->startDate = courseRegData.substr(afterComma, i - afterComma);
                    courseRegHead->endDate = courseRegData.substr(i + 1);
                    break;
                }
            }
        
            level++;
        }
    }
}

void readList(CourseReg* courseRegHead, std::fstream& dataFile) {
    CourseReg* curr = courseRegHead;
    dataFile << "1/2/3,schoolyear,startdate,enddate";
    while (curr != nullptr) {
        dataFile << "\n" << curr->semester << "," << curr->schoolYear << "," << curr->startDate << "," << curr->endDate;
        curr = curr->nodeNext;
    }

    dataFile.flush();

    dataFile.clear();
    dataFile.seekg(0);
}

//Returns true on search found, false otherwise
bool listSearchBool(SchoolYear* schoolYearHead, int searchSchoolYear) {
    while (schoolYearHead != nullptr) {
        if (schoolYearHead->schoolYear == searchSchoolYear) return 1;
        schoolYearHead = schoolYearHead->nodeNext;
    }
    return 0;
}
bool listSearchBool(Classes* classesHead, std::string searchClass, int startYear) {
    while (classesHead != nullptr) {
        if (classesHead->classID == searchClass && classesHead->startYear == startYear) return 1;
        classesHead = classesHead->nodeNext;
    }
    return 0;
}
bool listSearchBool(Student* studentHead, std::string searchStudentClass, std::string searchStudentID) {
    while (studentHead != nullptr) {
        if (studentHead->classID == searchStudentClass || studentHead->studentID == searchStudentID) return 1;
        studentHead = studentHead->nodeNext;
    }
    return 0;
}

// //Print the entire string contained in each node of the list
// void printListSingle(Node* nodeHead, bool reverse) {
//     Node* nodeCurr = nodeHead;
//     while (nodeHead != nullptr) {
//         if (reverse) {
//             nodeCurr = nodeCurr->nodePrev;        //Move nodeCurr to last node in the list before printing starts
//             std::cout << nodeCurr->value << std::endl;
//         }
//         else {
//             std::cout << nodeCurr->value << std::endl;
//             nodeCurr = nodeCurr->nodeNext;
//         }
//         if (nodeCurr == nodeHead) break;
//     }
//     std::cout << std::endl;
// }

// //Print a segment of a given string
// void printStringSegment(std::string str, int segmentStart, int segmentEnd) {

// }

// int listLength(Node* nodeHead) {
//     Node* nodeCurr = nodeHead;
//     int nodeCount = 0;
//     while (nodeHead != nullptr) {
//         nodeCurr = nodeCurr->nodeNext;
//         nodeCount++;
//         if (nodeCurr == nodeHead) {
//             break;
//         }
//     }

//     return nodeCount;
// }

//Destruct the list
void destructList(Node& node) {
    SchoolYear* sy = node.schoolYearHead;
    Classes* cl = node.classesHead;
    Semesters* sem = node.semesterHead;
    while (sy != nullptr || cl != nullptr || sem != nullptr) {
        if (sy != nullptr) {
            SchoolYear* rmv = sy;
            sy = sy->nodeNext;
            delete rmv;
        }
        if (cl != nullptr) {
            Classes* rmv = cl;
            cl = cl->nodeNext;
            delete rmv;
        }
        if (sem != nullptr) {
            Semesters* rmv = sem;
            sem = sem->nodeNext;
            delete rmv;
        }
    }
    sy, cl, sem = nullptr;
}
void destructList(SNode*& nodeHead) {
    while (nodeHead != nullptr) {
        SNode* temp = nodeHead;
        nodeHead = nodeHead->nodeNext;
        delete temp;
    }
}
void destructList(DNode*& nodeHead) {
    while (nodeHead != nullptr) {
        DNode* temp = nodeHead;
        nodeHead = nodeHead->nodeNext;
        delete temp;
    }
}
void destructList(Classes*& nodeHead) {
    while (nodeHead != nullptr) {
        Classes* temp = nodeHead;
        nodeHead = nodeHead->nodeNext;
        delete temp;
    }
}
void destructList(Student*& nodeHead) {
    while (nodeHead != nullptr) {
        Student* temp = nodeHead;
        nodeHead = nodeHead->nodeNext;
        delete temp;
    }
}
void destructList(Semesters*& nodeHead) {
    while (nodeHead != nullptr) {
        Semesters* temp = nodeHead;
        nodeHead = nodeHead->nodeNext;
        delete temp;
    }
}