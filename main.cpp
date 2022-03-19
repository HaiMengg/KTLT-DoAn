#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>

#include "Linked-List/linkedlist.h"
#include "Create-School-Year/create.h"
#include "Create-Classes/create.h"

int main() {
	Node allData;
	SchoolYear* schoolYears = allData.schoolYearHead;
	std::fstream schoolYearData("data/schoolyear.csv", std::ios::app | std::ios::out | std::ios::in);
	createList(schoolYears, schoolYearData);
	createSchoolYear(schoolYears, schoolYearData);

	std::cout << std::endl;

	Classes* classes = allData.classesHead;
	std::fstream classData("data/class.csv", std::ios::app | std::ios::out | std::ios::in);
	createList(classes, classData);
	createClass(classes, classData, 2021);

	std::cout << std::endl;
	
	Student* students = allData.studentHead;
	std::fstream studentData("data/student.csv", std::ios::app | std::ios::out | std::ios::in);
	createList(students, studentData);
	addStudentsToClass(students, studentData, 2021, "21CLC09");

	destructList(allData);

	system("pause");
	return 0;
}