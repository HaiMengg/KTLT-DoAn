#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>

#include "Linked-List/linkedlist.h"
#include "Create-School-Year/create.h"
#include "Create-Classes/create.h"
#include "Main-Menu/menu.h"

int main() {
	Node allData;
	std::fstream schoolYearData("data/schoolyear.csv", std::ios::app | std::ios::out | std::ios::in);
    std::fstream classData("data/class.csv", std::ios::app | std::ios::out | std::ios::in);
    std::fstream studentData("data/student.csv", std::ios::app | std::ios::out | std::ios::in);

	currentMenu(allData, schoolYearData, classData, studentData);

	destructList(allData);

	system("pause");
	return 0;
}