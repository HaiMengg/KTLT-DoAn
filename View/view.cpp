#include "view.h"

// void UpString(std::string& stu)
// {
// 	for (int i = 0; i < stu.size(); i++)
// 		if (stu[i] >= 97 && stu[i] <= 122)
// 			stu[i] -= 32;
// }

// void ReadClassStudent(Classes*& pClass, std::fstream& fin, std::string syear) {
// 	while (!fin.eof())
// 	{
// 		char temp;
// 		pClass = new Classes;
// 		getline(fin, pClass->classID);
// 		UpString(pClass->classID);
// 		if (pClass->classID[0] == '\n')
// 			pClass->classID.erase(0, 1);
// 		std::fstream fstudent("data/" + syear + "/classes/" + pClass->classID + "/student.csv");
// 		if (fstudent.is_open())
// 		{
// 			std::string temp;
// 			std::getline(fstudent, temp);
// 			InputStudent(pClass->classStudentHead, fstudent);
// 		}
// 		pClass->nodeNext = nullptr;
// 		ReadClassStudent(pClass->nodeNext, fin, syear);
// 	}
// }

// void ReadClass(Classes*& pClass, std::fstream& fin) {
// 	while (!fin.eof())
// 	{
// 		char temp;
// 		pClass = new Classes;
// 		std::getline(fin, pClass->classID, ',');
// 		UpString(pClass->classID);
// 		if (pClass->classID[0] == '\n')
// 			pClass->classID.erase(0, 1);
// 		fin >> pClass->startYear;
// 		pClass->nodeNext = nullptr;
// 		ReadClass(pClass->nodeNext, fin);
// 	}
// }

// void DisplayClass(Classes* pClass)
// {
// 	if (pClass != nullptr)
// 	{
// 		std::cout << std::setw(20) << std::left << pClass->classID << pClass->startYear << std::endl;
// 		DisplayClass(pClass->nodeNext);
// 	}
// }

// void ChooseDisplayStudent(Classes* pClass)
// {
// 	std::string choose = "Y", clas = "21CLC09";
// 	Classes* pCur = pClass;
// 	do {

// 		std::cout << "Input the class you want to view student:"; std::cin >> clas;
// 		UpString(clas);
// 		system("cls");
// 		pCur = pClass;
// 		while (pCur != nullptr)
// 		{
// 			if (pCur->classID == clas)
// 			{
// 				std::cout << std::setw(20) << std::left << "ID: ";
// 				std::cout << std::setw(30) << "Name: ";
// 				std::cout << std::setw(20) << "Gender: ";
// 				std::cout << "Date of birth: " << std::endl;
// 				DisplayStudent(pCur->classStudentHead);
// 				return;
// 			}
// 			else
// 				pCur = pCur->nodeNext;
// 		}
// 		std::cout << "Can't find the class you wanted, please try again\n";
// 	} while (choose == "Y" || choose == "YES");
// }

// void DeleteANode(Classes *&pClass)
// {
// 	Classes* pRemove = pClass;
// 	Student* pCur;
// 	while (pClass != nullptr)
// 	{
// 		while (pClass->classStudentHead != nullptr)
// 		{
// 			pCur = pClass->classStudentHead;
// 			pClass->classStudentHead = pClass->classStudentHead->nodeNext;
// 			delete pCur;
// 		}
// 		pRemove = pClass;
// 		pClass = pClass->nodeNext;
// 		delete pRemove;
// 	}
// }
// void DeleteANode(Course*& pCourse)
// {
// 	Course* pRemove = pCourse;
// 	Student* pCur;
// 	while (pCourse != nullptr)
// 	{
// 		while (pCourse->courseStudentHead != nullptr)
// 		{
// 			pCur = pCourse->courseStudentHead;
// 			pCourse->courseStudentHead = pCourse->courseStudentHead->nodeNext;
// 			delete pCur;
// 		}
// 		pRemove = pCourse;
// 		pCourse = pCourse->nodeNext;
// 		delete pRemove;
// 	}
// }

// void ViewClass()
// {
// 	std::fstream fin("data/class.csv");
// 	Classes* pClass = nullptr;
// 	std::string temp;
// 	std::getline(fin, temp);
// 	ReadClass(pClass, fin);
// 	std::cout << std::setw(20) << std::left << "ClassID:      " << "StartYear:		" << std::endl;
// 	DisplayClass(pClass);
// 	DeleteANode(pClass);
// }

// void ViewClassStudent()
// {
// 	std::string syear = "2022";
// 	bool check = true;
// 	do {
// 		std::cout << "Input school year that you want to view classes: ";	std::cin >> syear;
// 		system("cls");
// 		std::fstream fin("data/" + syear + "/class.csv");
// 		if (!fin.is_open())
// 			std::cout << "Can't find the school year you want, please try again\n";
// 		else
// 		{
// 			Classes* pClass = nullptr;
// 			std::string temp;
// 			std::getline(fin, temp);
// 			ReadClassStudent(pClass, fin, syear);
// 			ChooseDisplayStudent(pClass);
// 			DeleteANode(pClass);
// 			check = false;
// 		}
// 	} while (check);
// }

// void ReadCourse(Course*& pCourse, std::fstream& fin, std::string syear, int i)
// {
// 	while (!fin.eof())
// 	{
// 		pCourse = new Course;
// 		std::getline(fin, pCourse->courseId, ',');
// 		std::getline(fin, pCourse->courseName, ',');
// 		std::getline(fin, pCourse->teacherName, ',');
// 		std::getline(fin, pCourse->numOfCredits, ',');
// 		fin >> pCourse->studentMax;
// 		std::getline(fin, pCourse->daySession);
// 		if (pCourse->daySession[0] == ',')
// 			pCourse->daySession.erase(0, 1);
// 		std::fstream fstudent("data/" + syear + "/semester/" + std::to_string(i) + "/" + pCourse->courseId + "/student.csv");
// 		std::string temp;
// 		std::getline(fstudent, temp);
// 		InputStudent(pCourse->courseStudentHead, fstudent);
// 		pCourse->nodeNext = nullptr;
// 		ReadCourse(pCourse->nodeNext, fin, syear, i);
// 	}
// }

// void ReadCourseSetUp(Course*& pCourse, std::string syear)
// {
// 	std::string temp;
// 	Course* temp2 = nullptr, * temp1 = nullptr;
// 	int i = 1;
// 	std::fstream fin("data/" + syear + "/semester/" + std::to_string(i) + "/course.csv");
// 	std::getline(fin, temp);
// 	ReadCourse(pCourse, fin, syear, i);
// 	fin.close();
// 	fin.open("data/" + syear + "/semester/" + std::to_string(i + 1) + "/course.csv");
// 	if (fin.is_open())
// 	{
// 		std::getline(fin, temp);
// 		ReadCourse(temp2, fin, syear, i + 1);
// 	}
// 	fin.close();
// 	fin.open("data/" + syear + "/semester/" + std::to_string(i + 2) + "/course.csv");
// 	if (fin.is_open())
// 	{
// 		std::getline(fin, temp);
// 		ReadCourse(temp1, fin, syear, i + 2);
// 	}
// 	Course* pCur = pCourse;
// 	if (pCur != nullptr)
// 	{
// 		while (pCur->nodeNext != nullptr)
// 			pCur = pCur->nodeNext;
// 		if (temp2 != nullptr)
// 		{
// 			pCur->nodeNext = temp2;
// 			while (pCur->nodeNext != nullptr)
// 				pCur = pCur->nodeNext;
// 			if (temp1 != nullptr)
// 				pCur->nodeNext = temp1;
// 		}
// 	}
// }

// void InputStudent(Student*& pCourseS, std::fstream& fin)
// {
// 	if (!fin.is_open())
// 		return;
// 	while (!fin.eof())
// 	{
// 		pCourseS = new Student;
// 		std::getline(fin, pCourseS->studentID, ',');
// 		std::getline(fin, pCourseS->firstName, ',');
// 		std::getline(fin, pCourseS->lastName, ',');
// 		std::getline(fin, pCourseS->gender, ',');
// 		std::getline(fin, pCourseS->dob, ',');
// 		std::getline(fin, pCourseS->socialID);
// 		pCourseS->nodeNext = nullptr;
// 		InputStudent(pCourseS->nodeNext, fin);
// 	}
// }

// void DisplayCourse(Course* pCourse)
// {
// 	if (pCourse != nullptr)
// 	{
// 		std::cout << std::setw(20) << std::left << pCourse->courseId;
// 		std::cout << std::setw(30) << pCourse->courseName;
// 		std::cout << std::setw(30) << pCourse->teacherName;
// 		std::cout << std::setw(20) << pCourse->numOfCredits;
// 		std::cout << pCourse->daySession << std::endl;
// 		DisplayCourse(pCourse->nodeNext);
// 	}
// }

// void ChooseDisplayStudent(Course* pCourse)
// {
// 	std::string choose = "Y", course = "VTP10002";
// 	Course* pCur = pCourse;
// 	do {
// 		std::cout << "Input the course you want to see:"; std::cin >> course;
// 		UpString(course);
// 		system("cls");
// 		pCur = pCourse;
// 		while (pCur != nullptr)
// 		{
// 			if (pCur->courseId == course)
// 			{
// 				std::cout << std::setw(20) << std::left << "ID: ";
// 				std::cout << std::setw(30) << "Name: ";
// 				std::cout << std::setw(20) << "Gender: ";
// 				std::cout << "Date of birth: " << std::endl;
// 				DisplayStudent(pCur->courseStudentHead);
// 				return;
// 			}
// 			else
// 				pCur = pCur->nodeNext;
// 		}
// 		std::cout << "Can't find the course you wanted, please try again\n";
// 	} while (choose == "Y" || choose == "YES");
// }

// void DisplayStudent(Student* pStudent)
// {
// 	if (pStudent != nullptr)
// 	{
// 		std::string name = pStudent->firstName + " " + pStudent->lastName;
// 		std::cout << std::setw(20) << std::left << pStudent->studentID;
// 		std::cout << std::setw(30) << name;
// 		std::cout << std::setw(20) << pStudent->gender;
// 		std::cout << pStudent->dob << std::endl;
// 		DisplayStudent(pStudent->nodeNext);
// 	}
// }

// void ViewCourse()
// {
// 	std::string syear = "2022", choose;
// 	bool check = true;
// 	do {
// 		std::cout << "Input school year that you want to view : "; std::getline(std::cin, syear);
// 		std::fstream fin("data/" + syear + "/semester/1/course.csv");
// 		if (!fin.is_open())
// 			std::cout << "Can't find the school year you want, please try again\n";
// 		else
// 		{
// 			Course* pCourse = nullptr;
// 			ReadCourseSetUp(pCourse, syear);
// 			system("cls");
// 			std::cout << std::setw(20) << std::left << "ID: ";
// 			std::cout << std::setw(30) << "Name : ";
// 			std::cout << std::setw(30) << "Teacher: ";
// 			std::cout << std::setw(20) << "Credits : ";
// 			std::cout << "Session : " << std::endl;
// 			DisplayCourse(pCourse);
// 			DeleteANode(pCourse);
// 			check = false;
// 		}
// 	} while (check);
// }

// void ViewCourseStudent()
// {
// 	int max = 0, max2 = 0, max1 = 0;
// 	std::string syear = "2022", choose;
// 	bool check = true;
// 	do {
// 		std::cout << "Input school year that you want to view : ";	std::cin >> syear;
// 		system("cls");
// 		std::fstream fin("data/" + syear + "/semester/1/course.csv");
// 		if (!fin.is_open())
// 			std::cout << "Can't find the school year you want, please try again\n";
// 		else
// 		{
// 			Course* pCourse = nullptr;
// 			ReadCourseSetUp(pCourse, syear);
// 			ChooseDisplayStudent(pCourse);
// 			DeleteANode(pCourse);
// 			check = false;
// 		}
// 	} while (check);
// }

// Replace all same substrings with another string
void replaceeAll(std::string& str, const std::string& from, const std::string& to) {
    if (from.empty()) return;

    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

void viewClass(Classes* classesHead, int schoolYear) {
	std::ios_base::fmtflags f(std::cout.flags());
	bool found = 0;
    std::cout  << std::setfill(' ') << "\n";
	std::cout << std::left << std::setw(25) << "Class ID" << std::setw(25) << "Starting year\n";
	while (classesHead != nullptr) {
		if (classesHead->startYear == schoolYear) {
			std::cout << "\n" << std::left << std::setw(25) << classesHead->classID << std::setw(25) << classesHead->startYear;
			found = 1;
		}
		classesHead = classesHead->nodeNext;
	}
	if (!found) std::cout << std::left << std::setw(0) << "No class data found\n";
	std::cout.flags(f);
	
    std::cout << "\n";
}
void viewClassStudent(Classes* classesHead, int schoolYear, std::string classID) {
	std::ios_base::fmtflags f(std::cout.flags());
	bool found = 0;
    std::cout << std::setfill('_') << std::setw(getTerminalWidth()) << std::setfill(' ') << "\n";
	std::cout << std::left << std::setw(15) << "Student ID" 
	<< std::setw(15) << "First name" 
	<< std::setw(25) << "Last name" 
	<< std::setw(25) << "Date of birth" 
	<< std::setw(15) << "Gender" 
	<< std::setw(15) << "Social ID" 
	<< std::setw(15) << "Class ID" << "\n";
	while (classesHead != nullptr) {
		if (classesHead->classID == classID && classesHead->startYear == schoolYear) {
			Student* classStudent = classesHead->classStudentHead;
			while (classStudent != nullptr) {
				found = 1;
				std::cout << "\n" << std::left << std::setw(15) << classStudent->studentID 
				<< std::setw(15) << classStudent->firstName 
				<< std::setw(25) << classStudent->lastName 
				<< std::setw(25) << classStudent->dob 
				<< std::setw(15) << classStudent->gender 
				<< std::setw(15) << classStudent->socialID 
				<< std::setw(15) << classStudent->classID;
				classStudent = classStudent->nodeNext;
			}
			break;
		}
		classesHead = classesHead->nodeNext;
	}
	std::cout.flags(f);
	if (!found) std::cout << "No student found in this class\n";
	std::cout << std::setw(0);
    std::cout << std::setfill('_') << std::setw(getTerminalWidth()) << std::setfill(' ') << "\n";
}
void viewCourse(Semesters* semestersHead, int schoolYear, int semester)
{
	std::ios_base::fmtflags f(std::cout.flags());
    Semesters* semestersCurr = semestersHead;

	bool found = 0;
	while (semestersCurr != nullptr) {
		if (semestersCurr->semester == semester && semestersCurr->schoolYear == schoolYear) {
			found = 1;
			break;
		}
		semestersCurr = semestersCurr->nodeNext;
	}
	if (!found) {
		std::cout << "No matching school year and semester data found\n";
		return;
	}

    std::cout << std::setfill(' ') << std::left
    << std::setw(15) << "Course ID"
    << std::setw(22) << "Course name"
    << std::setw(25) << "Teacher name"
    << std::setw(30) << "Number of credits"
	<< std::setw(30) << "Maximum amount of students"
    << std::setw(20) << "Sessions" << std::endl;

	Course* courseHead = semestersCurr->semesterCourseHead;

	while (courseHead != nullptr) {
		std::string daySession = courseHead->daySession;
		replaceeAll(daySession, "|", ", ");
		replaceeAll(daySession, "-S1", " (07:30-09:10)");
		replaceeAll(daySession, "-S2", " (09:30-11:10)");
		replaceeAll(daySession, "-S3", " (13:30-15:10)");
		replaceeAll(daySession, "-S4", " (15:30-17:10)");

		std::cout << std::setw(15) << courseHead -> courseId;
		std::cout << std::setw(22) << courseHead -> courseName;
		std::cout << std::setw(25) << courseHead -> teacherName;
		std::cout << std::setw(30) << courseHead -> numOfCredits;
		std::cout << std::setw(30) << courseHead -> studentMax;
		std::cout << std::setw(20) << daySession << std::endl;

		courseHead = courseHead->nodeNext;
	}
	std::cout.flags(f);
}

void viewCourseStudent(Semesters* semestersHead, int schoolYear, int semester, std::string courseID) {
	std::ios_base::fmtflags f(std::cout.flags());
	Semesters* semestersCurr = semestersHead;

	bool found = 0;
	while (semestersCurr != nullptr) {
		if (semestersCurr->semester == semester && semestersCurr->schoolYear == schoolYear) {
			found = 1;
			break;
		}
		semestersCurr = semestersCurr->nodeNext;
	}
	if (!found) {
		std::cout << "No matching school year and semester data found\n";
		return;
	}

    std::cout << std::setfill('_') << std::setw(getTerminalWidth()) << std::setfill(' ') << "\n";
    std::cout << std::left << std::setw(15) << "Student ID" 
	<< std::setw(15) << "First name" 
	<< std::setw(25) << "Last name" 
	<< std::setw(25) << "Date of birth" 
	<< std::setw(15) << "Gender" 
	<< std::setw(15) << "Social ID" 
	<< std::setw(15) << "Class ID";

	Course* courseHead = semestersCurr->semesterCourseHead;
	found = 0;
	while (courseHead != nullptr) {
		if (courseHead->courseId == courseID) {
			found = 1;
			break;
		}
		courseHead = courseHead->nodeNext;
	}
	std::cout.flags(f);
	if (!found) {
		std::cout << "\nNo course with matching ID found\n";
		return;
	}

	found = 0;
	Student* courseStudentHead = courseHead->courseStudentHead;
	while (courseStudentHead != nullptr) {
		found = 1;
		std::cout << "\n" << std::left << std::setw(15) << courseStudentHead->studentID 
		<< std::setw(15) << courseStudentHead->firstName 
		<< std::setw(25) << courseStudentHead->lastName 
		<< std::setw(25) << courseStudentHead->dob 
		<< std::setw(15) << courseStudentHead->gender 
		<< std::setw(15) << courseStudentHead->socialID 
		<< std::setw(15) << courseStudentHead->classID;

		courseStudentHead = courseStudentHead->nodeNext;
	}
	if (!found) std::cout << "No student found in this course\n";
	std::cout << std::setw(0);

    std::cout << std::setfill('_') << std::setw(getTerminalWidth()) << std::setfill(' ') << "\n";
	std::cout.flags(f);
}