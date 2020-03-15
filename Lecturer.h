#pragma once
#include "Person.h"
#include "types.h"
#include <memory>

class Lecturer : public Person {
public:
	Lecturer();
	~Lecturer();

	// getters
	department_type getDepartment();
	subjects_type * getTeachingSubjects();
	
	// setters
	void setDepartment(department_type);
	void setTeachingSubjects(subjects_type &); // see mthod definition why this cannot be used !.
	//void setTeachingSubjects(std::shared_ptr<subjects_type> &);



private:
	department_type department;
	std::shared_ptr<subjects_type> teachingSubjects; // consider about operation=, move constructor, copy constructor
};