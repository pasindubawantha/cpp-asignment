#include "Person.h"

std::string Person::getFistName()
{
	return this->firstName;
}

std::string Person::getLastName()
{
	return this->lastName;
}

std::string Person::getEmail()
{
	return this->email;
}

age_type Person::getAge()
{
	return this->age;
}

void Person::setFistName(std::string &firstName)
{
	this->firstName = std::move(firstName);
}

void Person::setLastName(std::string &lastName)
{
	this->lastName = std::move(lastName);
}

void Person::setEmail(std::string &email)
{
	this->email = std::move(email);
}

void Person::setAge(age_type age)
{
	this->age = age;
}
