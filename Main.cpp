#include <cstdio>

#include <iostream>
#include <limits>
#include <algorithm>
#include <cctype>
#include <sstream> 
#include<iterator>

#include "types.h"
#include "Person.h"
#include "Student.h"
#include "Lecturer.h"
#include "Register.h"
#include "Register.cpp" // to resolve Linked error when using template classes. Referance Method 3 in https://www.codeproject.com/Articles/48575/How-to-Define-a-Template-Class-in-a-h-File-and-Imp

// Global variables and constants
enum TYPE : unsigned short int { LECTURERER = 1, STUDENT = 2 };
wchar_t bullet = L'\x2022'; // bullet charchter in C++. Doesn't get the expected charchter. Referance https://stackoverflow.com/questions/3719979/c-unicode-bullet-point

// Function declarations
void getInputPerson(std::unique_ptr<Register<Lecturer>> &lecturerRegister, std::unique_ptr<Register<Student>> &studentRegister, std::string &inputStringParam, subjects_type &subjectsVectorParam);

void printLecturer(std::string departmentName, std::vector<Lecturer> *departmentVector);

void printStudent(std::string majorName, std::vector<Student> *majorVector);

void stringTokenize(std::string &string, std::vector<std::string> *tockens);

void stringRemoveSpecialCharacters(std::string *string);

bool checkInputInt(unsigned short int input, unsigned short int low, unsigned short int high);

void waitForEnterPress();

// Main entry 
int main() {
	// Getting inputs
	int inputInt;
	std::string inputString;
	subjects_type subjectsVector;
	std::unique_ptr<Register<Student>> studentRegister = std::unique_ptr<Register<Student>>(new Register<Student>());
	std::unique_ptr<Register<Lecturer>> lecturerRegister = std::unique_ptr<Register<Lecturer>>(new Register<Lecturer>());

	bool validInput = false;
	while (!validInput) {
		const unsigned short int entryLow = 1;
		const unsigned short int entryHigh = 100;
		std::cout << "Number of Entries: ";
		std::cin >> inputInt;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input type" << std::endl;
			continue;
		}
		validInput = checkInputInt(inputInt, entryLow, entryHigh);
		if (!validInput) {
			std::cout << "Please enter value in range [" << entryLow << ", " << entryHigh << "]" << std::endl;
		}
	}
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	for (int i = 0; i < inputInt; i++) {
		getInputPerson(lecturerRegister, studentRegister, inputString, subjectsVector);
		std::cout << "---- Entry " << i+1 << " added out of " << inputInt << " ----" << std::endl;
	}
	std::cout << "---- All entries added ! ----" << std::endl;

	// Generating output
	std::cout << "Number of Teachers: " << lecturerRegister->getPersonCount() << std::endl;
	std::cout << "Number of Teachers In Each Department:" << std::endl;
	std::cout << "Mathematics: " << lecturerRegister->getPartition(Dep_Mathematics)->size() << std::endl;
	std::cout << "Engineering: " << lecturerRegister->getPartition(Dep_Engineering)->size() << std::endl;
	std::cout << "Computer Science: " << lecturerRegister->getPartition(Dep_Computer_Science)->size() << std::endl << std::endl;

	std::cout << "Number of Students: " << studentRegister->getPersonCount() << std::endl;
	std::cout << "Number of Students from Each Major:" << std::endl;
	std::cout << "CS: " << studentRegister->getPartition(Maj_CS)->size() << std::endl;
	std::cout << "Engineering: " << studentRegister->getPartition(Maj_Engineering)->size() << std::endl;
	std::cout << "Information Security: " << studentRegister->getPartition(Maj_Information_Security)->size() << std::endl << std::endl;

	std::cout << "Lecturers Per Department:" << std::endl;
	printLecturer("Mathematics", lecturerRegister->getPartition(Dep_Mathematics));
	printLecturer("Engineering", lecturerRegister->getPartition(Dep_Engineering));
	printLecturer("Computer Science", lecturerRegister->getPartition(Dep_Computer_Science));

	std::cout << std::endl << "Student Per Major:" << std::endl;
	printStudent("CS", studentRegister->getPartition(Maj_CS));
	printStudent("Engineering", studentRegister->getPartition(Maj_Engineering));
	printStudent("Information Security", studentRegister->getPartition(Maj_Information_Security));

	std::cout << "---- Done ! ----" << std::endl;
	waitForEnterPress();
}

// Function defeintions

void getInputPerson(std::unique_ptr<Register<Lecturer>> &lecturerRegister, std::unique_ptr<Register<Student>> &studentRegister, std::string &inputStringParam, subjects_type &subjectsVectorParam) {

	unsigned short int inputInt;
	std::string inputString = std::move(inputStringParam); // To avoid allocation and deallocation of memory operations
	subjects_type subjectsVector = std::move(subjectsVectorParam); // To avoid allocation and deallocation of memory operations

	bool validInput = false;

	// Type
	while (!validInput) {
		std::cout << "Type : ";
		std::cout << "(" << LECTURERER << " - Lecturer, " << STUDENT << " - Student) : ";
		std::cin >> inputInt;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input type" << std::endl;
			continue;
		}
		validInput = checkInputInt(inputInt, LECTURERER, STUDENT);
		if (!validInput) {
			std::cout << "Please enter value in range [" << LECTURERER << ", " << STUDENT << "]" << std::endl;
		}
	}

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Type Selected : (" << inputInt << ")" << std::endl;


	switch (inputInt) {
	case LECTURERER: {
		Lecturer lecturer;

		// Fisty name
		std::cout << "Fist name (Digits and Special Charchters are ignored !) : ";
		inputString.clear();
		std::getline(std::cin, inputString);
		stringRemoveSpecialCharacters(&inputString);
		std::cin.clear();
		std::cout << "Fist name : (" << inputString << ")" << std::endl;
		lecturer.setFistName(inputString);

		// Last name
		std::cout << "Last name (Digits and Special Charchters are ignored !) : ";
		inputString.clear();
		std::getline(std::cin, inputString);
		stringRemoveSpecialCharacters(&inputString);
		std::cin.clear();
		std::cout << "Last name : (" << inputString << ")" << std::endl;
		lecturer.setLastName(inputString);

		// Age
		validInput = false;
		while (!validInput) {
			const unsigned short int ageLow = 5;
			const unsigned short int ageHigh = 150;
			std::cout << "Age, ";
			std::cout << "range [" << ageLow << ", " << ageHigh << "] : ";
			std::cin >> inputInt;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid input type" << std::endl;
				continue;
			}
			validInput = checkInputInt(inputInt, ageLow, ageHigh);
			if (!validInput) {
				std::cout << "Please enter value in range [" << ageLow << ", " << ageHigh << "]" << std::endl;
			}
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Age : (" << inputInt << ")" << std::endl;
		lecturer.setAge(inputInt);

		// Teaching Subjects
		std::cout << "Teaching Subjects (Comma seperated valeus) : ";
		inputString.clear();
		std::getline(std::cin, inputString);
		std::cin.clear();

		stringTokenize(inputString, &subjectsVector);
		std::cout << "Teaching Subjects : (" << std::endl;
		for (unsigned int j = 0; j < subjectsVector.size(); j++)
			std::cout << subjectsVector[j] << std::endl;
		std::cout << ")" << std::endl;
		lecturer.setTeachingSubjects(subjectsVector);
		subjectsVector.clear();

		// Department
		validInput = false;

		while (!validInput) {
			std::cout << "Department : ";
			// Dep_Mathematics = 1, Dep_Engineering = 2, Dep_Computer_Science
			std::cout << "(" << Dep_Mathematics << " - Mathematics, " << Dep_Engineering << " - Engineeting, " << Dep_Computer_Science << " - Computer Science ) : ";
			std::cin >> inputInt;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid input type" << std::endl;
				continue;
			}
			validInput = checkInputInt(inputInt, Dep_Mathematics, Dep_Computer_Science);
			if (!validInput) {
				std::cout << "Please enter value in range [" << Dep_Mathematics << ", " << Dep_Computer_Science << "]" << std::endl;
			}
		}

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Department Selected : (" << inputInt << ")" << std::endl;
		lecturer.setDepartment(static_cast<department_type>(inputInt));

		lecturerRegister->insertPerson(inputInt, lecturer);
		
		break;
	}
	case STUDENT: {
		Student student;

		// Fisty name
		std::cout << "Fist name (Digits and Special Charchters are ignored !) : ";
		inputString.clear();
		std::getline(std::cin, inputString);
		stringRemoveSpecialCharacters(&inputString);
		std::cin.clear();
		std::cout << "Fist name : (" << inputString << ")" << std::endl;
		student.setFistName(inputString);

		// Last name
		std::cout << "Last name (Digits and Special Charchters are ignored !) : ";
		inputString.clear();
		inputString.clear();
		std::getline(std::cin, inputString);
		stringRemoveSpecialCharacters(&inputString);
		std::cin.clear();
		std::cout << "Last name : (" << inputString << ")" << std::endl;
		student.setLastName(inputString);

		// Age
		validInput = false;
		while (!validInput) {
			const unsigned short int ageLow = 5;
			const unsigned short int ageHigh = 150;
			std::cout << "Age, ";
			std::cout << "range [" << ageLow << ", " << ageHigh << "] : ";
			std::cin >> inputInt;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid input type" << std::endl;
				continue;
			}
			validInput = checkInputInt(inputInt, ageLow, ageHigh);
			if (!validInput) {
				std::cout << "Please enter value in range [" << ageLow << ", " << ageHigh << "]" << std::endl;
			}
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Age : (" << inputInt << ")" << std::endl;
		student.setAge(inputInt);

		// Major
		validInput = false;

		while (!validInput) {
			std::cout << "Major : ";
			// Maj_CS = 1, Maj_Engineering = 2, Maj_Information_Security = 3
			std::cout << "(" << Maj_CS << " - CS, " << Maj_Engineering << " - Engineeting, " << Maj_Information_Security << " - Information Security ) : ";
			std::cin >> inputInt;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid input type" << std::endl;
				continue;
			}
			validInput = checkInputInt(inputInt, Maj_CS, Maj_Information_Security);
			if (!validInput) {
				std::cout << "Please enter value in range [" << Maj_CS << ", " << Maj_Information_Security << "]" << std::endl;
			}
		}

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Major Selected : (" << inputInt << ")" << std::endl;
		student.setMajor(static_cast<major_type>(inputInt));

		studentRegister->insertPerson(inputInt, student);

		break;
	}
	default:
		break;
	}

};

void printLecturer(std::string departmentName, std::vector<Lecturer> *departmentVector) {
	std::cout << departmentName << ": " << departmentVector->size() << std::endl;
	std::cout << "----------------------------" << std::endl;

	std::vector<Lecturer>::iterator lecturerPointer;
	subjects_type::iterator subjectPointer;
	for (lecturerPointer = departmentVector->begin(); lecturerPointer < departmentVector->end(); lecturerPointer++) {

		std::cout << "Name: " << lecturerPointer->getFistName() << " " << lecturerPointer->getLastName() << std::endl;
		std::cout << "Age: " << lecturerPointer->getAge() << std::endl;
		std::cout << "Teaching Subjects:" << std::endl;

		subjects_type * subjects = lecturerPointer->getTeachingSubjects();
		for (subjectPointer = subjects->begin(); subjectPointer < subjects->end(); subjectPointer++) {
			std::cout << "* " << *subjectPointer << std::endl;
		}
		std::cout << "----------------------------" << std::endl;
	}
}

void printStudent(std::string majorName, std::vector<Student> *majorVector) {
	std::cout << majorName << ": " << majorVector->size() << std::endl;
	std::cout << "----------------------------" << std::endl;

	std::vector<Student>::iterator studentPointer;
	subjects_type::iterator subjectPointer;
	for (studentPointer = majorVector->begin(); studentPointer < majorVector->end(); studentPointer++) {

		std::cout << "Name: " << studentPointer->getFistName() << " " << studentPointer->getLastName() << std::endl;
		std::cout << "Age: " << studentPointer->getAge() << std::endl;
		std::cout << "----------------------------" << std::endl;
	}
}

void stringTokenize(std::string &string, std::vector<std::string> *tockens) {
	std::stringstream stringStream(std::move(string));
	std::string token;
	while (std::getline(stringStream, token, ','))
	{
		//stringRemoveSpecialCharacters(tocken)
		tockens->push_back(token);
	}
}

void stringRemoveSpecialCharacters(std::string *string) {
	string->erase(std::remove_if(string->begin(), string->end(),
		[](char c) { return /*std::isspace(c) || std::isdigit(c) || std::iscntrl(c)*/ !(std::isupper(c) || std::islower(c)); }),
		string->end());
}

bool checkInputInt(unsigned short int input, unsigned short int low, unsigned short int high) {
	return  (input >= low && input <= high);
}

void waitForEnterPress() {
	std::cout << "Press [Enter] to exit !";
	std::cin.get();
	exit(0);
}
