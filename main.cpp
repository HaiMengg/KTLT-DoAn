#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>

#include "Linked-List/linkedlist.h"
#include "Create-School-Year/create.h"
#include "Create-Classes/create.h"

int main() {
	// Node* schoolYears = nullptr;
	// create(schoolYears);

	Node* classes = nullptr;
	std::fstream classData("data/2021/class.csv", std::ios::app);
	createList(classes, classData);
	createClass(classes, classData);
	
	// destructList(schoolYears);
	destructList(classes);

	system("pause");
	return 0;
}