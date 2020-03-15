#pragma once
#include "Person.h"
#include "types.h"

class Student : public Person {
public:
	major_type getMajor();
	void setMajor(major_type);
private:
	major_type major;
};