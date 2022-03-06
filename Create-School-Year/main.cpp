#include "menu.h"

int main() {
	std::ifstream fin("test.txt", std::ios::in);
	std::string str;
	fin >> str;
	std::cout << str << std::endl;

	system("pause");
	return 0;
}