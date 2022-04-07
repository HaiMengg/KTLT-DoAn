#include "menu.h"

void currentMenu(Node& data, std::fstream& schoolYearData, std::fstream& classData, std::fstream& studentData, std::fstream& semesterData, std::fstream& courseRegData , std::string& currentDate) {
    bool cont = 1;
    do {
        printCurrDate(currentDate, data.semesterHead);
        std::cout << "\n";

        std::cout << "Which action do you want to take?\n"
        << "create school year: create a new school year\n"
        << "create class: create new class/classes\n"
        << "add students: add new students to a class\n"
        << "create semester: create new semester/semesters\n"
        << "add course: add new course/courses to semester\n"
        << "update course: update a course's information\n"
        << "delete course: delete existing course/course\n"
        << "create course registration: create a course registration session\n"
        << "view: get access to the view feature (from which you can perform further actions)\n"
        << "back: return to previous menu\n: ";

        std::string choice;
        std::getline(std::cin, choice);
        choice = toLower_w(choice);

        // if (choice == "view") level = 1;
        if (choice == "create school year")
            createSchoolYearMenu(data.schoolYearHead, schoolYearData, currentDate);
        else if (choice == "create class")
            createClassMenu(data.classesHead, classData, data.schoolYearHead);
        else if (choice == "add students")
            addStudentMenu(data.studentHead, studentData, data.schoolYearHead, data.classesHead);
        else if (choice == "create semester")
            createSemesterMenu(data.semesterHead, semesterData, data.schoolYearHead);
        else if (choice == "add course")
            addCourseMenu(data.semesterHead, data.schoolYearHead);
        else if (choice == "update course")
            updateCourseMenu(data.semesterHead, data.schoolYearHead);
        else if (choice == "delete course")
            deleteCourseMenu(data.semesterHead, data.schoolYearHead);
        else if (choice == "create course registration")
            createCourseRegMenu(data.courseRegHead, courseRegData, data.schoolYearHead, data.semesterHead);
        else if (choice == "view")
            viewMenu(data);
        else if (choice == "back") cont = 0;
        else std::cout << "Invalid action\n";

        std::cout << std::endl << "================================================" << std::endl << std::endl;
        system("pause");
        system("cls");
    } while (cont);
}

void createSchoolYearMenu(SchoolYear*& schoolYearHead, std::fstream& schoolYearData, std::string currentDate) {
    if (getDateData(currentDate, 'm') != 9 || (getDateData(currentDate, 'm') == 8 && getDateData(currentDate, 'd') < 25) || (getDateData(currentDate, 'm') == 10 && getDateData(currentDate, 'd') > 25))
    {
        std::cout << "Not within the time range (usually around September) allowed for school year creation\n";
        return;
    }
    
    std::cout << "\n\n";
    viewSchoolYear(schoolYearHead);

    bool valid = 0;
    std::string inputYear;
	do {
		if (inputYear != "" && !isDigit_w(inputYear)) {
			std::cout << "Invalid year\n";
			valid = 0;
		}
		else {
			if (inputYear != "" && schoolYearSearchBool(schoolYearHead, stoi(inputYear))) {
				std::cout << "You can't create an existing school year.\n";
				valid = 0;
			}
		}

		std::cout << "Enter the start of the new school year (you can't create an existing school year) (enter \"0\" to return to main menu): ";
		std::getline(std::cin, inputYear);
		if (inputYear == "0") return;
		if (inputYear != "" && isDigit_w(inputYear) && !schoolYearSearchBool(schoolYearHead, stoi(inputYear))) valid = 1;
	} while (!valid);

    createSchoolYear(schoolYearHead, schoolYearData, inputYear);
}

void createClassMenu(Classes*& classHead, std::fstream& classData, SchoolYear* schoolYearHead) {
    bool valid = 0;
    std::string currentSchoolYear = "a";
    while (!valid) {
        std::cout << "Enter the school year to create new class for (enter \"0\" to return to previous menu): ";
        std::getline(std::cin, currentSchoolYear);
        if (currentSchoolYear == "0") return;
        if (currentSchoolYear == "" || !isDigit_w(currentSchoolYear)) { std::cout << "Invalid format for year\n"; continue; }
        if (!schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) std::cout << "School year \"" + currentSchoolYear + "\" doesn't exist in current database\n";
        if (isDigit_w(currentSchoolYear) && schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) valid = 1;
    }

    std::cout << "Existing classes in school year " << currentSchoolYear << ":\n";
    viewClass(classHead, stoi(currentSchoolYear));

    createClass(classHead, classData, stoi(currentSchoolYear));
}

void addStudentMenu(Student*& studentHead, std::fstream& studentData, SchoolYear* schoolYearHead, Classes*& classesHead) {
    bool valid = 0;
    std::string currentSchoolYear = "a";
    while (!valid) {
        std::cout << "Enter the school year in which a class was created (enter \"0\" to return to previous menu): ";
        std::getline(std::cin, currentSchoolYear);
        if (currentSchoolYear == "0") return;
        if (currentSchoolYear == "" || !isDigit_w(currentSchoolYear)) { std::cout << "Invalid format for year\n"; continue; }
        if (!schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) std::cout << "School year \"" + currentSchoolYear + "\" doesn't exist in the current database\n";
        if (isDigit_w(currentSchoolYear) && schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) valid = 1;
    }
    
    std::string currentClass = "";
    while (!classListSearchBool(classesHead, currentClass, stoi(currentSchoolYear))) {
        std::cout << "Enter the class to add new students (enter \"0\" to return to previous menu): ";
        std::getline(std::cin, currentClass);
        if (currentClass == "0") return;
        currentClass = toUpper_w(currentClass);
        if (!classListSearchBool(classesHead, currentClass, stoi(currentSchoolYear))) std::cout << "Class \"" + currentClass + "\" of year \"" + currentSchoolYear + "\" doesn't exist in current database\n";
    }

    std::cout << "\nExisting students of class " << currentClass << ":\n";
    viewClassStudent(classesHead, stoi(currentSchoolYear), currentClass);

    addStudentsToClass(studentHead, studentData, stoi(currentSchoolYear), currentClass, classesHead);
}

void createSemesterMenu(Semesters*& semesterHead, std::fstream& semesterData, SchoolYear* schoolYearHead) {
    bool valid = 0;
    std::string currentSchoolYear = "a";
    while (!valid) {
        std::cout << "Enter the school year to create new semester for (enter \"0\" to return to previous menu): ";
        std::getline(std::cin, currentSchoolYear);
        if (currentSchoolYear == "0") return;
        if (currentSchoolYear == "" || !isDigit_w(currentSchoolYear)) { std::cout << "Invalid format for year\n"; continue; }
        if (!schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) std::cout << "School year \"" + currentSchoolYear + "\" doesn't exist in current database\n";
        if (isDigit_w(currentSchoolYear) && schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) valid = 1;
    }

    std::cout << "\nExisting semesters in school year " << currentSchoolYear << ":\n";
    Semesters* curr = semesterHead;
    while (curr != nullptr) {
        std::cout << "\n" << std::left << std::setw(15) << curr->semester
        << std::setw(15) << curr->schoolYear
        << std::setw(25) << curr->startDate
        << std::setw(25) << curr->endDate;   
        curr = curr->nodeNext;
    }

    createSemester(semesterHead, semesterData, stoi(currentSchoolYear));
}

void addCourseMenu(Semesters*& semesterHead, SchoolYear* schoolYearHead) {
    bool valid = 0;
    std::string currentSchoolYear = "a";
    while (!valid) {
        std::cout << "Enter the school year to create new course for (enter \"0\" to return to previous menu): ";
        std::getline(std::cin, currentSchoolYear);
        if (currentSchoolYear == "0") return;
        if (currentSchoolYear == "" || !isDigit_w(currentSchoolYear)) { std::cout << "Invalid format for year\n"; continue; }
        if (!schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) std::cout << "School year \"" + currentSchoolYear + "\" doesn't exist in current database\n";
        if (isDigit_w(currentSchoolYear) && schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) valid = 1;
    }

    std::cout << "\nExisting courses in school year " << currentSchoolYear << ":\n";
    std::cout << "First semester\n";
    viewCourse(semesterHead, stoi(currentSchoolYear), 1);
    std::cout << "Second semester\n";
    viewCourse(semesterHead, stoi(currentSchoolYear), 2);
    std::cout << "Third semester\n";
    viewCourse(semesterHead, stoi(currentSchoolYear), 3);

    addCourseToSemester(semesterHead, stoi(currentSchoolYear));
}

void updateCourseMenu(Semesters*& semesterHead, SchoolYear* schoolYearHead) {
    bool valid = 0;
    std::string currentSchoolYear = "a";
    while (!valid) {
        std::cout << "Enter the school year to update course (enter \"0\" to return to previous menu): ";
        std::getline(std::cin, currentSchoolYear);
        if (currentSchoolYear == "0") return;
        if (currentSchoolYear == "" || !isDigit_w(currentSchoolYear)) { std::cout << "Invalid format for year\n"; continue; }
        if (!schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) std::cout << "School year \"" + currentSchoolYear + "\" doesn't exist in current database\n";
        if (isDigit_w(currentSchoolYear) && schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) valid = 1;
    }

    std::cout << "\nExisting courses in school year " << currentSchoolYear << ":\n";
    std::cout << "First semester\n";
    viewCourse(semesterHead, stoi(currentSchoolYear), 1);
    std::cout << "Second semester\n";
    viewCourse(semesterHead, stoi(currentSchoolYear), 2);
    std::cout << "Third semester\n";
    viewCourse(semesterHead, stoi(currentSchoolYear), 3);

    updateCourse(semesterHead, stoi(currentSchoolYear));
}

void deleteCourseMenu(Semesters*& semesterHead, SchoolYear* schoolYearHead) {
    bool valid = 0;
    std::string currentSchoolYear = "a";
    while (!valid) {
        std::cout << "Enter the school year to delete course (enter \"0\" to return to previous menu): ";
        std::getline(std::cin, currentSchoolYear);
        if (currentSchoolYear == "0") return;
        if (currentSchoolYear == "" || !isDigit_w(currentSchoolYear)) { std::cout << "Invalid format for year\n"; continue; }
        if (!schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) std::cout << "School year \"" + currentSchoolYear + "\" doesn't exist in current database\n";
        if (isDigit_w(currentSchoolYear) && schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) valid = 1;
    }

    std::cout << "\nExisting courses in school year " << currentSchoolYear << ":\n";
    std::cout << "First semester\n";
    viewCourse(semesterHead, stoi(currentSchoolYear), 1);
    std::cout << "Second semester\n";
    viewCourse(semesterHead, stoi(currentSchoolYear), 2);
    std::cout << "Third semester\n";
    viewCourse(semesterHead, stoi(currentSchoolYear), 3);

    deleteCourse(semesterHead, stoi(currentSchoolYear));
}

void createCourseRegMenu(CourseReg*& courseRegHead, std::fstream& courseRegData, SchoolYear* schoolYearHead, Semesters* semestersHead) {
    std::cout << "\nExisting course registration sessions" << ":\n";
    CourseReg* curr = courseRegHead;
    while (curr != nullptr) {
        std::cout << "\n" << std::left << std::setw(15) << curr->semester
        << std::setw(15) << curr->schoolYear
        << std::setw(25) << curr->startDate
        << std::setw(25) << curr->endDate;   
        curr = curr->nodeNext;
    }

    bool valid = 0;
    std::string currentSchoolYear = "a";
    while (!valid) {
        std::cout << "Enter the school year to create new course for (enter \"0\" to return to previous menu): ";
        std::getline(std::cin, currentSchoolYear);
        if (currentSchoolYear == "0") return;
        if (currentSchoolYear == "" || !isDigit_w(currentSchoolYear)) { std::cout << "Invalid format for year\n"; continue; }
        if (!schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) std::cout << "School year \"" + currentSchoolYear + "\" doesn't exist in current database\n";
        if (isDigit_w(currentSchoolYear) && schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) valid = 1;
    }
    createCourseReg(courseRegHead, courseRegData, stoi(currentSchoolYear) , semestersHead);
}

int getCurrSemester(std::string givenDate, Semesters* semesterHead) {
    Semesters* curr = semesterHead;
    while (curr != nullptr) {
        if (getDateData(givenDate, 'y') == curr->schoolYear) {
            if (getDateData(curr->startDate, 'y') == getDateData(curr->endDate, 'y') + 1) return curr->semester;
            
            if (getDateData(curr->startDate, 'y') == getDateData(curr->endDate, 'y')) {
                if (getDateData(givenDate, 'm') >= getDateData(curr->startDate, 'm') && getDateData(givenDate, 'm') <= getDateData(curr->endDate, 'm')) {
                    if (getDateData(curr->startDate, 'm') < getDateData(curr->endDate, 'm')) return curr->semester;
                    else if ((getDateData(curr->startDate, 'm') == getDateData(curr->endDate, 'm'))) {
                        if (getDateData(givenDate, 'd') >= getDateData(curr->startDate, 'd') && getDateData(givenDate, 'd') <= getDateData(curr->endDate, 'd')) return curr->semester;
                    }
                }
            }
        }
        curr = curr->nodeNext;
    }

    return -1;
}

void printCurrDate(std::string givenDate, Semesters* semesterHead) {
    std::cout << "Today is " << givenDate << std::endl;
    if (getCurrSemester(givenDate, semesterHead) != -1) {
        std::cout << "It is currently semester " << getCurrSemester(givenDate, semesterHead) << " of the school year " 
        << getDateData(givenDate, 'y') << "-" << getDateData(givenDate, 'y') + 1 << std::endl;
    }
}

void viewMenu(Node allData) {
    bool back = 0;

    do {
        std::cout << "Which do you want to view?\n"
        << "school year: view all school years\n"
        << "class: view single class/classes\n"
        << "class student: view all students of a class\n"
        << "course: view single course/courses\n"
        << "course student: view all students of a course\n"
        << "back: back to previous menu\n: ";
        std::string choice;
        std::getline(std::cin, choice);
        choice = toLower_w(choice);
        if (choice == "school year") viewSchoolYear(allData.schoolYearHead);
        else if (choice == "class") viewClassMenu(allData.classesHead, allData.schoolYearHead);
        else if (choice == "class student") viewClassStudentMenu(allData.classesHead, allData.schoolYearHead);
        else if (choice == "course") viewCourseMenu(allData.semesterHead, allData.schoolYearHead);
        else if (choice == "course students") viewCourseStudentMenu(allData.semesterHead, allData.schoolYearHead);
        else if (choice == "back") back = 1;
        else std::cout << "Invalid choice\n";
        system("pause");
        system("cls");
        std::cout << std::endl;
    } while (!back);
}

void viewClassMenu(Classes* classesHead, SchoolYear* schoolYearHead) {
    bool valid = 0;
    std::string currentSchoolYear = "a";
    while (!valid) {
        std::cout << "Enter the school year to create new course for (enter \"0\" to return to previous menu): ";
        std::getline(std::cin, currentSchoolYear);
        if (currentSchoolYear == "0") return;
        if (currentSchoolYear == "" || !isDigit_w(currentSchoolYear)) { std::cout << "Invalid format for year\n"; continue; }
        if (!schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) std::cout << "School year \"" + currentSchoolYear + "\" doesn't exist in current database\n";
        if (isDigit_w(currentSchoolYear) && schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) valid = 1;
    }
    viewClass(classesHead, stoi(currentSchoolYear));
}

void viewClassStudentMenu(Classes* classesHead, SchoolYear* schoolYearHead) {
    bool valid = 0;
    std::string currentSchoolYear = "a";
    while (!valid) {
        std::cout << "Enter the school year in which a class was created (enter \"0\" to return to previous menu): ";
        std::getline(std::cin, currentSchoolYear);
        if (currentSchoolYear == "0") return;
        if (currentSchoolYear == "" || !isDigit_w(currentSchoolYear)) { std::cout << "Invalid format for year\n"; continue; }
        if (!schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) std::cout << "School year \"" + currentSchoolYear + "\" doesn't exist in current database\n";
        if (isDigit_w(currentSchoolYear) && schoolYearSearchBool(schoolYearHead, stoi(currentSchoolYear))) valid = 1;
    }
    
    std::string currentClass = "";
    while (!classListSearchBool(classesHead, currentClass, stoi(currentSchoolYear))) {
        std::cout << "Enter the class to add new students (enter \"0\" to return to previous menu): ";
        std::getline(std::cin, currentClass);
        if (currentClass == "0") return;
        currentClass = toUpper_w(currentClass);
        if (!classListSearchBool(classesHead, currentClass, stoi(currentSchoolYear))) std::cout << "Class \"" + currentClass + "\" of year \"" + currentSchoolYear + "\" doesn't exist in current database\n";
    }

    viewClassStudent(classesHead, stoi(currentSchoolYear), currentClass);
}

void viewCourseMenu(Semesters* semestersHead, SchoolYear* schoolYearHead) {
    bool valid = 0;
    std::string currentSchoolYear = "a";
    while (!valid) {
        std::cout << "Enter a school year (enter \"0\" to return to previous menu): ";
        std::getline(std::cin, currentSchoolYear);
        if (currentSchoolYear == "0") return;
        if (currentSchoolYear == "" || !isDigit_w(currentSchoolYear)) { std::cout << "Invalid format for year\n"; continue; }
    }

    std::string semester = "a";
    while (semester == "" || !isDigit_w(semester)) {
        std::cout << "Enter the semester from which to view the courses: ";
        std::getline(std::cin, semester);
        if (semester == "0") return;
        if (semester == "" || !isDigit_w(semester)) { std::cout << "Invalid format for semester\n"; continue;}
    }
    
    std::string currentClass = "";
    while (!semesterListSearchBool(semestersHead, stoi(semester), stoi(currentSchoolYear))) {
        std::cout << "Enter the class to add new students (enter \"0\" to return to previous menu): ";
        std::getline(std::cin, currentClass);
        if (currentClass == "0") return;
        currentClass = toUpper_w(currentClass);
        if (!semesterListSearchBool(semestersHead, stoi(semester), stoi(currentSchoolYear))) std::cout << "Class \"" + currentClass + "\" of year \"" + currentSchoolYear + "\" doesn't exist in current database\n";
    }
    viewCourse(semestersHead, stoi(currentSchoolYear), stoi(semester));
}

void viewCourseStudentMenu(Semesters* semestersHead, SchoolYear* schoolYearHead) {
    bool valid = 0;
    std::string currentSchoolYear = "a";
    while (!valid) {
        std::cout << "Enter a school year (enter \"0\" to return to previous menu): ";
        std::getline(std::cin, currentSchoolYear);
        if (currentSchoolYear == "0") return;
        if (currentSchoolYear == "" || !isDigit_w(currentSchoolYear)) { std::cout << "Invalid format for year\n"; continue; }
    }

    std::string semester = "a";
    while (semester == "" || !isDigit_w(semester)) {
        std::cout << "Enter the semester from which to view the courses: ";
        std::getline(std::cin, semester);
        if (semester == "0") return;
        if (semester == "" || !isDigit_w(semester)) { std::cout << "Invalid format for semester\n"; continue;}
    }
    
    std::string currentClass = "";
    while (!semesterListSearchBool(semestersHead, stoi(semester), stoi(currentSchoolYear))) {
        std::cout << "Enter the class to add new students (enter \"0\" to return to previous menu): ";
        std::getline(std::cin, currentClass);
        if (currentClass == "0") return;
        currentClass = toUpper_w(currentClass);
        if (!semesterListSearchBool(semestersHead, stoi(semester), stoi(currentSchoolYear))) std::cout << "Class \"" + currentClass + "\" of year \"" + currentSchoolYear + "\" doesn't exist in current database\n";
    }

    std::string courseID = "";
    std::getline(std::cin, courseID);

    viewCourseStudent(semestersHead, stoi(currentSchoolYear), stoi(semester), courseID);
}