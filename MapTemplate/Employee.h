#include <string>
#include <iostream>

using namespace std;

struct Employee {
	string name;
	string position;
	int age;
	Employee(string name = "-", string position = "-", int age = 0);
}; 

Employee::Employee(string name, string position, int age) {
	this->name = name;
	this->position = position;
	this->age = age;
}

ostream& operator<<(ostream& out, const Employee& emp) {
	out << "Name: " << emp.name << "; Position: " << emp.position << "; Age: " << emp.age;
	return out;
}