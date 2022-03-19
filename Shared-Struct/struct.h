// #pragma once

// #include <iostream>
// #include <fstream>
// #include <string>
// #include <direct.h>

// struct SchoolYear {
//     SchoolYear* nodePrev;
//     int schoolYear;
//     SchoolYear* nodeNext;
// };
// struct Classes {
//     Classes* nodePrev;
//     std::string classID;
//     Student* classStudentHead;
//     Classes* nodeNext;
// };
// struct Course {
//     Course* nodePrev;
//     std::string courseId, courseName, teacherName, numOfCredits, daySession;    //Format: MON-S1|SAT-S4|TUE-S2|...
//     int studentMax = 50;
//     Student* courseStudentHead;
//     Course* nodeNext;
// };
// struct Student {
//     Student* nodePrev;
//     std::string usr, pwd, firstName, lastName, gender, dob, socialID, startYear, classID;
//     Course* studentCourse;
//     Student* nodeNext;
// };

// struct Node {
//     SchoolYear* schoolYearHead;
//     Classes* classesHead;
//     Student* studentHead;
//     Course* courseHead;
// };