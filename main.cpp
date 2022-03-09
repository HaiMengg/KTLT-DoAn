#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>

#include "Linked-List/linkedlist.h"
#include "Create-School-Year/create.h"

int main() {
	Node* schoolYears = nullptr;
	create(schoolYears);
	destructList(schoolYears);

	system("pause");
	return 0;
}