#include "functionView.h"


void UpString(string& stu)
{
	for (int i = 0; i < stu.size(); i++)
		if (stu[i] >= 97 && stu[i] <= 122)
			stu[i] -= 32;
}

void ReadClass(Classes*& pClass, fstream& fin, string syear) {
	string temp;
	Classes* pCur = pClass;
	fin >> temp;
	if (pClass == nullptr && !fin.eof())
	{
		pClass = new Classes;
		pCur = pClass;
		getline(fin, pClass->classID, ',');
		pClass->classID.erase(0, 1);
		UpString(pClass->classID);
		fin >> pClass->startYear;
		fstream fstudent(syear + "/classes/" + pClass->classID + "/student.csv");
		InputStudent(pCur->classStudentHead, fstudent);
		pCur->nodeNext = nullptr;
	}
	while (!fin.eof())
	{

		pCur->nodeNext = new Classes;
		pCur = pCur->nodeNext;
		getline(fin, pCur->classID, ',');
		UpString(pClass->classID);
		fin >> pCur->startYear;
		fstream fstudent(syear + "/class/" + pClass->classID + "/student.csv");
		InputStudent(pCur->classStudentHead, fstudent);
		pCur->classID.erase(0, 1);
		pCur->nodeNext = nullptr;
	}
}

void InputCourse(Student*& pClassS, fstream& fin, string temp)
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
			pClassS->studentCoursesSem1 += temp[i];
			break;
		case 2:
			pClassS->studentCoursesSem2 += temp[i];
			break;
		default:
			pClassS->studentCoursesSem3 += temp[i];
			break;
		}

	}
}

void InputStudent(Student*& pClassS, fstream& fin)
{
	if (!fin.is_open())
		return;
	string temp;
	getline(fin, temp);
	Student* pCur = pClassS = nullptr;
	if (pClassS == nullptr && !fin.eof())
	{
		pClassS = new Student;
		getline(fin, pClassS->usr, ',');
		getline(fin, pClassS->pwd, ',');
		getline(fin, pClassS->studentID, ',');
		getline(fin, pClassS->firstName, ',');
		getline(fin, pClassS->lastName, ',');
		getline(fin, pClassS->gender, ',');
		getline(fin, pClassS->dob, ',');
		getline(fin, pClassS->socialID, ',');
		getline(fin, pClassS->startYear, ',');
		getline(fin, pClassS->classID, ',');
		getline(fin, temp);
		InputCourse(pClassS, fin, temp);
		pCur = pClassS;
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
		InputCourse(pCur, fin, temp);
		pCur->nodeNext = nullptr;
	}
}

void DisplayClass(Classes* pClass)
{
	Classes* pCur = pClass;
	while (pCur != nullptr)
	{
		cout << "ClassID:      " << pCur->classID << setw(20) << "StartYear:		" << pCur->startYear << endl;
		pCur = pCur->nodeNext;
	}
}

void ChooseDisplayStudent(Classes* pClass)
{
	string choose = "Y", clas = "21CLC09";
	Classes* pCur = pClass;
	do {
		cout << "\nDo you want to see all students of a specific class (y/yes to continue): "; cin >> choose;
		UpString(choose);
		del;
		cout << "Input the class you want to see:"; cin >> clas;
		UpString(clas);
		del;
		if (choose == "Y" || choose == "YES")
		{
			pCur = pClass;
			while (pCur != nullptr)
			{
				if (pCur->classID == clas)
				{
					DisplayStudent(pCur->classStudentHead);
					return;
				}
				else
					pCur = pCur->nodeNext;
			}
			cout << "Can't find the class you wanted, please try again\n";
		}
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

void DeleteNode(Classes*& pClass)
{
	Classes* pRemove = pClass;
	Student* pCur;
	while (pClass != nullptr)
	{
		while (pClass->classStudentHead != nullptr)
		{
			pCur = pClass->classStudentHead;
			pClass->classStudentHead = pClass->classStudentHead->nodeNext;
			delete pCur;
		}
		pRemove = pClass;
		pClass = pClass->nodeNext;
		delete pRemove;
	}
}

void ViewClass()
{
	string syear = "2022";
	bool check = true;
	do {
		cout << "Input school year that you want to view classes ";	cin >> syear;
		del;
		fstream fin(syear + "/class.csv");
		if (!fin.is_open())
			cout << " Can't find the school year you want, please try again\n";
		else
		{
			Classes* pClass = nullptr;
			ReadClass(pClass, fin, syear);
			DisplayClass(pClass);
			ChooseDisplayStudent(pClass);
			DeleteNode(pClass);
			check = false;
		}
	} while (check);
}