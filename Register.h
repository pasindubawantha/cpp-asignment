#pragma once
#include <map>
#include <vector>
#include "types.h"
#include "Person.h"

/*
Many template class issues are can be encountered when Linking
Check https://www.codeproject.com/Articles/48575/How-to-Define-a-Template-Class-in-a-h-File-and-Imp
*/

template<class T>
class Register {
public:
	void insertPerson(int, T &);
	void addPartition(int, std::vector<T> &);
	std::vector<T> * getPartition(int);
	bool keyExsists(int);

	unsigned int getPersonCount();
private:
	std::map<int, std::vector<T>> partitions;
	unsigned int personCount;
};