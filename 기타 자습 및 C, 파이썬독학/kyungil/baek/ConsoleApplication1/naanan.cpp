#include <iostream>
#include <string>
#include "Student.h"
using namespace std;

int main11()
{
	MyClass special;
	Student* aa=new Student("±è");
	Student* bb = new Student("ÀÌ");
	Student* cc = new Student("¹Ú");
	Student dd("³»±Í¿¡Äµµð");
	cout << dd.getName() << "\n";
	special.setName2(aa,0);
	special.setName2(bb,1);
	special.setName2(cc,2);
	cout << special.getName2(0) << special.getName2(1) << special.getName2(2);
	delete aa;
	delete bb;
	delete cc;
	return 0;
}