#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>

#include "Linked-List/linkedlist.h"
#include "Create-School-Year/create.h"
#include "Create-Classes/create.h"

int main() {
	Node* schoolYears = nullptr;
	create(schoolYears);

	Node* classes = nullptr;
	std::fstream classData("data/2021/class.csv", std::ios::app);
	createList(classes, classData);
	createClass(classes, classData, 2021);
	
	Node* students = nullptr;
	std::fstream studentData("data/student.csv", std::ios::app);
	createList(students, studentData);
	addStudentsToClass(students, studentData, 2021, "21CLC09");

	destructList(schoolYears);
	destructList(classes);
	destructList(students);

	system("pause");
	return 0;
}