#include"ViewClass.h"

void UpString(string& stu)
{
	for (int i = 0; i < stu.size(); i++)
		if (stu[i] >= 97 && stu[i] <= 122)
			stu[i] -= 32;
}

void ReadClassStudent(Classes*& pClass, fstream& fin, string syear) {
	while (!fin.eof())
	{
		char temp;
		pClass = new Classes;
		getline(fin, pClass->classID);
		UpString(pClass->classID);
		if (pClass->classID[0] == '\n')
			pClass->classID.erase(0, 1);
		fstream fstudent(syear + "/classes/" + pClass->classID + "/student.csv");
		if (fstudent.is_open())
		{
			string temp;
			getline(fstudent, temp);
			InputStudent(pClass->classStudentHead, fstudent);
		}
		pClass->nodeNext = nullptr;
		ReadClassStudent(pClass->nodeNext, fin, syear);
	}
}

void ReadClass(Classes*& pClass, fstream& fin) {
	while (!fin.eof())
	{
		char temp;
		pClass = new Classes;
		getline(fin, pClass->classID, ',');
		UpString(pClass->classID);
		if (pClass->classID[0] == '\n')
			pClass->classID.erase(0, 1);
		fin >> pClass->startYear;
		pClass->nodeNext = nullptr;
		ReadClass(pClass->nodeNext, fin);
	}
}

void InputStudent(Student*& pClassS, fstream& fin)
{
	while (!fin.eof())
	{
		pClassS = new Student;
		getline(fin, pClassS->studentID, ',');
		getline(fin, pClassS->firstName, ',');
		getline(fin, pClassS->lastName, ',');
		getline(fin, pClassS->gender, ',');
		getline(fin, pClassS->dob);
		pClassS->nodeNext = nullptr;
		InputStudent(pClassS->nodeNext, fin);
	}
}

void DisplayClass(Classes* pClass)
{
	if (pClass != nullptr)
	{
		cout << pClass->classID << setw(20) << pClass->startYear << endl;
		DisplayClass(pClass->nodeNext);
	}
}

void ChooseDisplayStudent(Classes* pClass)
{
	string choose = "Y", clas = "21CLC09";
	Classes* pCur = pClass;
	do {

		cout << "Input the class you want to view student:"; cin >> clas;
		UpString(clas);
		del;
		pCur = pClass;
		while (pCur != nullptr)
		{
			if (pCur->classID == clas)
			{
				cout << "ID: " << setw(19);
				cout << "Name: " << setw(30);
				cout << "Gender: " << setw(20);
				cout << "Date of birth: " << endl;
				DisplayStudent(pCur->classStudentHead);
				return;
			}
			else
				pCur = pCur->nodeNext;
		}
		cout << "Can't find the class you wanted, please try again\n";
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
	fstream fin("class.csv");
	Classes* pClass = nullptr;
	string temp;
	getline(fin, temp);
	ReadClass(pClass, fin);
	cout << "ClassID:      " << setw(21) << "StartYear:		" << endl;
	DisplayClass(pClass);
	DeleteNode(pClass);

}

void ViewClassStudent()
{
	string syear = "2022";
	bool check = true;
	do {
		cout << "Input school year that you want to view classes: ";	cin >> syear;
		del;
		fstream fin(syear + "/class.csv");
		if (!fin.is_open())
			cout << " Can't find the school year you want, please try again\n";
		else
		{
			Classes* pClass = nullptr;
			string temp;
			getline(fin, temp);
			ReadClassStudent(pClass, fin, syear);
			ChooseDisplayStudent(pClass);
			DeleteNode(pClass);
			check = false;
		}
	} while (check);
}