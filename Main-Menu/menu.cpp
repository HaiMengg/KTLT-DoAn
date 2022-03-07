#include "menu.h"

// void root() {
// 	std::string command;
// 	std::cout << "What action to take: ";
// 	std::cin >> command;

// 	void* (*action)(void*, std::string& command) = emptyFunc;

// 	while (command != "exit") {
// 		if (command == "create") action = createMenu;

// 		std::cin.ignore(10000, '\n');
// 		std::cout << "What action to take next: ";
// 		std::getline(std::cin, command);

// 		void* (*action)(void*, std::string & command) = action(action, command);
// 	}
// }

// //Placeholder function to assign to *action so that IntelliSense won't throw an exception at compile time
// void* emptyFunc(void* action, std::string& command) { return action; }

// void* createMenu(void* action, std::string& command) {
// 	if (command == "create school year") action = createSchoolYear;
// 	return action;
// }

// void* createSchoolYear(void* action, std::string& command) {
// 	std::cout << "ga`";
// 	return action;
// }