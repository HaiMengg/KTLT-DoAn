#include "ViewCourse.h"

void UpString(string& stu)
{
	for (int i = 0; i < stu.size(); i++)
		if (stu[i] >= 97 && stu[i] <= 122)
			stu[i] -= 32;
}

void ReadCourse(Course*& pCourse, fstream& fin, string syear, int i)
{
	while (!fin.eof())
	{
		pCourse = new Course;
		getline(fin, pCourse->courseId, ',');
		getline(fin, pCourse->courseName, ',');
		getline(fin, pCourse->teacherName, ',');
		getline(fin, pCourse->numOfCredits, ',');
		fin >> pCourse->studentMax;
		getline(fin, pCourse->daySession);
		if (pCourse->daySession[0] == ',')
			pCourse->daySession.erase(0, 1);
		fstream fstudent(syear + "/semester/" + to_string(i) + "/" + pCourse->courseId + "/student.csv");
		string temp;
		getline(fstudent, temp);
		InputStudent(pCourse->courseStudentHead, fstudent);
		pCourse->nodeNext = nullptr;
		ReadCourse(pCourse->nodeNext, fin, syear, i);
	}
}

void ReadCourseSetUp(Course*& pCourse, string syear)
{
	string temp;
	Course* temp2 = nullptr, * temp1 = nullptr;
	int i = 1;
	fstream fin(syear + "/semester/" + to_string(i) + "/course.csv");
	getline(fin, temp);
	ReadCourse(pCourse, fin, syear, i);
	fin.close();
	fin.open(syear + "/semester/" + to_string(i + 1) + "/course.csv");
	if (fin.is_open())
	{
		getline(fin, temp);
		ReadCourse(temp2, fin, syear, i + 1);
	}
	fin.close();
	fin.open(syear + "/semester/" + to_string(i + 2) + "/course.csv");
	if (fin.is_open())
	{
		getline(fin, temp);
		ReadCourse(temp1, fin, syear, i + 2);
	}
	Course* pCur = pCourse;
	if (pCur != nullptr)
	{
		while (pCur->nodeNext != nullptr)
			pCur = pCur->nodeNext;
		if (temp2 != nullptr)
		{
			pCur->nodeNext = temp2;
			while (pCur->nodeNext != nullptr)
				pCur = pCur->nodeNext;
			if (temp1 != nullptr)
				pCur->nodeNext = temp1;
		}
	}
}

void InputStudent(Student*& pCourseS, fstream& fin)
{
	if (!fin.is_open())
		return;
	while (!fin.eof())
	{
		pCourseS = new Student;
		getline(fin, pCourseS->studentID, ',');
		getline(fin, pCourseS->firstName, ',');
		getline(fin, pCourseS->lastName, ',');
		getline(fin, pCourseS->gender, ',');
		getline(fin, pCourseS->dob);
		pCourseS->nodeNext = nullptr;
		InputStudent(pCourseS->nodeNext, fin);
	}
}

void DisplayCourse(Course* pCourse)
{
	if (pCourse != nullptr)
	{
		cout << setw(17) << left << pCourse->courseId;
		cout << setw(28) << left << pCourse->courseName;
		cout << setw(29) << left << pCourse->teacherName;
		cout << setw(20) << left << pCourse->numOfCredits;
		cout << pCourse->daySession << endl;
		DisplayCourse(pCourse->nodeNext);
	}
}

void ChooseDisplayStudent(Course* pCourse)
{
	string choose = "Y", course = "VTP10002";
	Course* pCur = pCourse;
	do {
		//cout << "Input the course you want to see:"; cin >> course;
		UpString(course);
		del;
		pCur = pCourse;
		while (pCur != nullptr)
		{
			if (pCur->courseId == course)
			{
				cout << "ID: " << setw(20);
				cout << "Name: " << setw(30);
				cout << "Gender: " << setw(20);
				cout << "Date of birth: " << endl;
				DisplayStudent(pCur->courseStudentHead);
				return;
			}
			else
				pCur = pCur->nodeNext;
		}
		cout << "Can't find the course you wanted, please try again\n";
	} while (choose == "Y" || choose == "YES");
}

void DisplayStudent(Student* pStudent)
{
	if (pStudent != nullptr)
	{
		cout << setw(18) << left << pStudent->studentID;
		cout << pStudent->firstName << " " << setw(21) << left << pStudent->lastName;
		cout << setw(13) << left << pStudent->gender;
		cout << pStudent->dob << endl;
		DisplayStudent(pStudent->nodeNext);
	}
}

void DeleteNode(Course*& pCourse)
{
	Course* pRemove = pCourse;
	Student* pCur;
	while (pCourse != nullptr)
	{
		while (pCourse->courseStudentHead != nullptr)
		{
			pCur = pCourse->courseStudentHead;
			pCourse->courseStudentHead = pCourse->courseStudentHead->nodeNext;
			delete pCur;
		}
		pRemove = pCourse;
		pCourse = pCourse->nodeNext;
		delete pRemove;
	}
}

void ViewCourse()
{
	string syear = "2022", choose;
	bool check = true;
	do {
		//cout << "Input school year that you want to view courses: ";	cin >> syear;
		del;
		fstream fin(syear + "/semester/1/course.csv");
		if (!fin.is_open())
			cout << " Can't find the school year you want, please try again\n";
		else
		{
			Course* pCourse = nullptr;
			ReadCourseSetUp(pCourse, syear);
			del;
			cout << "ID: ";
			cout << setw(20) << "Name : ";
			cout << setw(30) << "Teacher: ";
			cout << setw(30) << "Credits : ";
			cout << setw(20) << "Session : " << endl;
			DisplayCourse(pCourse);
			DeleteNode(pCourse);
			check = false;
		}
	} while (check);
}

void ViewCourseStudent()
{
	int max = 0, max2 = 0, max1 = 0;
	string syear = "2022", choose;
	bool check = true;
	do {
		//cout << "Input school year that you want to view courses: ";	cin >> syear;
		del;
		fstream fin(syear + "/semester/1/course.csv");
		if (!fin.is_open())
			cout << " Can't find the school year you want, please try again\n";
		else
		{
			Course* pCourse = nullptr;
			ReadCourseSetUp(pCourse, syear);
			ChooseDisplayStudent(pCourse);
			DeleteNode(pCourse);
			check = false;
		}
	} while (check);
}