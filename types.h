#pragma once
#define DEBUG false
#include <string>
#include <vector>
//#include <memory>

typedef enum : unsigned short int { Dep_None = 0,  Dep_Mathematics = 1, Dep_Engineering = 2, Dep_Computer_Science = 3 } department_type; // Dep_None is default depratment when initializing an int
typedef enum : unsigned short int {	Maj_None = 0, Maj_CS = 1, Maj_Engineering = 2, Maj_Information_Security = 3 } major_type; // Maj_None is default depratment when initializing an int
typedef unsigned short int age_type;
typedef std::vector<std::string> subjects_type; // For this application only one referance to this private field is requred, maybe make this shared in a multi threaded application.
