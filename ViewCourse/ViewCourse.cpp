#include "ViewCourse.h"

void UpString(string& stu)
{
	for (int i = 0; i < stu.size(); i++)
		if (stu[i] >= 97 && stu[i] <= 122)
			stu[i] -= 32;
}

void ReadCourse(Course*& pCourse, fstream& fin, string syear, int& max, int& max2, int& max1)
{
	string temp;
	Course* pCur = pCourse;
	getline(fin, temp);
	if (pCourse == nullptr && !fin.eof())
	{
		pCourse = new Course;
		pCur = pCourse;
		getline(fin, pCourse->courseId, ',');
		if (max1 < pCourse->courseId.size())
			max1 = pCourse->courseId.size();
		getline(fin, pCourse->courseName, ',');
		if (max2 < pCourse->courseName.size())			//display ok with it
			max2 = pCourse->courseName.size();
		getline(fin, pCourse->teacherName, ',');
		if (max < pCourse->teacherName.size())
			max = pCourse->teacherName.size();
		getline(fin, pCourse->numOfCredits, ',');
		fin >> pCourse->studentMax;
		getline(fin, pCourse->daySession);
		pCourse->daySession.erase(0, 1);
		fstream fstudent(syear + "/courses/" + pCourse->courseId + "/student.csv");
		InputStudent(pCur->courseStudentHead, fstudent);
		pCur->nodeNext = nullptr;
	}
	while (!fin.eof())
	{

		pCur->nodeNext = new Course;
		pCur = pCur->nodeNext;
		getline(fin, pCur->courseId, ',');
		if (max1 < pCur->courseId.size())
			max1 = pCur->courseId.size();
		getline(fin, pCur->courseName, ',');
		if (max2 < pCur->courseName.size())			//display ok with it
			max2 = pCur->courseName.size();
		getline(fin, pCur->teacherName, ',');
		if (max < pCur->teacherName.size())
			max = pCur->teacherName.size();
		getline(fin, pCur->numOfCredits, ',');
		fin >> pCur->studentMax;
		getline(fin, pCur->daySession);
		pCur->daySession.erase(0, 1);
		fstream fstudent(syear + "/courses/" + pCur->courseId + "/student.csv");
		InputStudent(pCur->courseStudentHead, fstudent);
		pCur->nodeNext = nullptr;
	}
}

void InputStudentCourse(Student*& pCourseS, fstream& fin, string temp)
{
	int k = 0, j = 1;
	for (int i = 0; i < temp.size(); i++)
	{
		if (temp[i] == '|')
		{
			j++;
			continue;
		}
		switch (j)
		{
		case 1:
			pCourseS->studentCoursesSem1 += temp[i];
			break;
		case 2:
			pCourseS->studentCoursesSem2 += temp[i];
			break;
		default:
			pCourseS->studentCoursesSem3 += temp[i];
			break;
		}

	}
}

void InputStudent(Student*& pCourseS, fstream& fin)
{
	if (!fin.is_open())
		return;
	string temp;
	getline(fin, temp);
	Student* pCur = pCourseS = nullptr;
	if (pCourseS == nullptr && !fin.eof())
	{
		pCourseS = new Student;
		getline(fin, pCourseS->usr, ',');
		getline(fin, pCourseS->pwd, ',');
		getline(fin, pCourseS->studentID, ',');
		getline(fin, pCourseS->firstName, ',');
		getline(fin, pCourseS->lastName, ',');
		getline(fin, pCourseS->gender, ',');
		getline(fin, pCourseS->dob, ',');
		getline(fin, pCourseS->socialID, ',');
		getline(fin, pCourseS->startYear, ',');
		getline(fin, pCourseS->classID, ',');
		getline(fin, temp);
		InputStudentCourse(pCourseS, fin, temp);
		pCur = pCourseS;
		pCur->nodeNext = nullptr;
	}
	while (!fin.eof())
	{

		pCur->nodeNext = new Student;
		pCur = pCur->nodeNext;
		getline(fin, pCur->usr, ',');
		getline(fin, pCur->pwd, ',');
		getline(fin, pCur->studentID, ',');
		getline(fin, pCur->firstName, ',');
		getline(fin, pCur->lastName, ',');
		getline(fin, pCur->gender, ',');
		getline(fin, pCur->dob, ',');
		getline(fin, pCur->socialID, ',');
		getline(fin, pCur->startYear, ',');
		getline(fin, pCur->classID, ',');
		getline(fin, temp);
		InputStudentCourse(pCur, fin, temp);
		pCur->nodeNext = nullptr;
	}
}

void DisplayCourse(Course* pCourse, int max, int max2, int max1)
{
	Course* pCur = pCourse;
	while (pCur != nullptr)
	{
		cout << "ID: " << pCur->courseId;
		cout << setw(max1 - pCur->courseId.size() + 10) << "Name : " << pCur->courseName;
		cout << setw(max2 - pCur->courseName.size() + 15) << "Teacher: " << pCur->teacherName;
		cout << setw(max - pCur->teacherName.size() + 15) << "Credits : " << pCur->numOfCredits;
		cout << setw(15) << "Session : " << pCur->daySession << endl;
		pCur = pCur->nodeNext;
	}
}

void ChooseDisplayStudent(Course* pCourse)
{
	string choose = "Y", course = "VTP10002";
	Course* pCur = pCourse;
	do {
		cout << "\nDo you want to see all students of a specific course (y/yes to continue): "; cin >> choose;
		UpString(choose);
		del;
		cout << "Input the course you want to see:"; cin >> course;
		if (choose == "Y" || choose == "YES")
		{
			while (pCur != nullptr)
			{
				if (pCur->courseId == course)
				{
					DisplayStudent(pCur->courseStudentHead);
					return;
				}
				else
					pCur = pCur->nodeNext;
			}
			cout << "			Can't find the course you wanted, please try again\n";
		}
		del;
	} while (choose == "Y" || choose == "YES");
}

void DisplayStudent(Student* pStudent)
{
	Student* pCur = pStudent;
	if (pCur == nullptr)
		cout << "No student in this class";
	while (pCur != nullptr)
	{
		cout << "ID: " << pCur->studentID << setw(10);
		cout << "Name: " << pCur->firstName << " " << pCur->lastName << setw(30 - pCur->firstName.size() - pCur->lastName.size());
		cout << "Gender: " << pCur->gender << setw(20);
		cout << "Date of birth: " << pCur->dob << endl;
		pCur = pCur->nodeNext;
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
	int max = 0, max2 = 0, max1 = 0;
	string syear = "2022", choose;
	cout << "Input schoolyear that you want to view courses: ";	cin >> syear;
	del;
	fstream fin(syear + "/course.csv");
	Course* pCourse = nullptr;
	ReadCourse(pCourse, fin, syear, max, max2, max1);
	DisplayCourse(pCourse, max, max2, max1);
	ChooseDisplayStudent(pCourse);
	DeleteNode(pCourse);
}