#include "Book.h"
#include <iostream>
using namespace std;

Book::Book()
{
	x = 500;
	y = 600;
	radius = 700;
	cout << "���� ���� ����\n";
}

Book::Book(int xx)
{
	x = xx;
	y = 500;
	radius = 600;
	cout << "���� 1���� ����\n";
}
Book::Book(int xx, int yy, int zz)
{
	x = xx;
	y = yy;
	radius = zz;
	cout << "���� 3���� ����\n";

}

Book::~Book()
{
	cout << "�Ҹ��ڻ���\n";
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
