#pragma once
#include <iostream>
#include <string>

using namespace std;

class Student
{
	string name;
public:
	Student(string a = "") { name = a; }
	string getName() { return this->name; }
	void setName(string name) { this->name = name; }
};

class MyClass
{
	string className;
	Student * p[3];
	int size;
public:
	void setName2(Student *p,int i) { this->p[i]=p; }
	string getName2(int i) { return p[i]->getName(); }
};
