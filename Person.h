#pragma once
#include <string>
#include "types.h" // custom type definitions

class Person {
public:
	// setters ** could not installed a getter setter generator yet !!
	std::string getFistName();
	std::string getLastName();
	std::string getEmail();
	age_type getAge();

	// getters
	void setFistName(std::string &);
	void setLastName(std::string &);
	void setEmail(std::string &);
	void setAge(age_type );

private:
	std::string firstName;
	std::string lastName;
	std::string email;
	age_type age;
};