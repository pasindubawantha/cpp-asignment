#include "Lecturer.h"
#include <iostream>

Lecturer::Lecturer()
{
	if (DEBUG) {
		std::cout << "** Lecturere Constructor **" << std::endl;
	}
	this->teachingSubjects = nullptr;
}

Lecturer::~Lecturer()
{
	if (DEBUG) {
		std::cout << "** Lecturere Destructor **" << std::endl;
	}
	this->teachingSubjects.reset();
}

department_type Lecturer::getDepartment()
{
	return this->department;
}

subjects_type * Lecturer::getTeachingSubjects()
{
	return teachingSubjects.get(); // why use pointer in this case ? https://stackoverflow.com/questions/15648844/using-smart-pointers-for-class-members
}

void Lecturer::setDepartment(department_type department)
{
	this->department = department;
}

void Lecturer::setTeachingSubjects(subjects_type & teachingSubjects) // unable to use move semantics with shared pointer. teachingSubjects pointer parameter used to create class attribute teachingSubjects shared pointer will have a referance to class attribute shared pointer 
//void Lecturer::setTeachingSubjects(std::shared_ptr<subjects_type> & teachingSubjects)
{
	//subjects_type tmp = std::move(teachingSubjects);
	this->teachingSubjects.reset(new subjects_type(teachingSubjects));

	//this->teachingSubjects.reset(std::move(teachingSubjects)); // does not compile
	//this->teachingSubjects.swap(teachingSubjects); // swap
	//teachingSubjects.reset(); // reset parameter to nullptr to prevent data leak with set method
}