#include "Register.h"

template <class T>
void Register<T>::insertPerson(int key, T & person)
{
	if (this->keyExsists(key)) {
		this->getPartition(key)->push_back(std::move(person));
	}
	else {
		std::vector<T> tmpPersonVector;
		tmpPersonVector.push_back(std::move(person));
		this->addPartition(key, tmpPersonVector);
	}

	this->personCount++;
}

template <class T>
void Register<T>::addPartition(int key, std::vector<T> &partition)
{
	this->partitions.insert(std::pair<int, std::vector<T>>(key, std::move(partition)));
}

template <class T>
std::vector<T>* Register<T>::getPartition(int key)
{
	if (!this->keyExsists(key)) {
		std::vector<T> tmpPersonVector;
		this->addPartition(key, tmpPersonVector);
	}

	return &this->partitions.at(key);
}

template <class T>
bool Register<T>::keyExsists(int key)
{
	return !(this->partitions.find(key) == this->partitions.end());
}

template <class T>
unsigned int Register<T>::getPersonCount()
{
	return this->personCount;
}
