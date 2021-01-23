#include "Book.h"
#include <iostream>
using namespace std;

Book::Book()
{
	x = 500;
	y = 600;
	radius = 700;
	cout << "변수 없이 생성\n";
}

Book::Book(int xx)
{
	x = xx;
	y = 500;
	radius = 600;
	cout << "변수 1개로 생성\n";
}
Book::Book(int xx, int yy, int zz)
{
	x = xx;
	y = yy;
	radius = zz;
	cout << "변수 3개로 생성\n";

}

Book::~Book()
{
	cout << "소멸자생성\n";
}

void Book::print()
{
	cout << x << "\n" << y << "\n" << radius << "\n";
}

void Book::jojack()
{
	x = 777;
	y = 777;
	radius = 777;
}
