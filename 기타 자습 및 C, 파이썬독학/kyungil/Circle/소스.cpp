#include <iostream>
#include "Book.h"

using namespace std;

int main11()
{
	Book book[4];
	book[1].print();
	Book realBook(100);
	realBook.print();
	Book noRealBook(100, 200);
	noRealBook.print();
	Book unrealBook(100, 200, 300);
	unrealBook.print();
	book[1].print();
	book[1].jojack();
	book[1].print();

	for (Book c : book)
	{
		c.x = 888;
		c.y = 888;
		c.radius = 888;
	}
	// 변하지않음. 클래스 네개가 복사됨
	// 이 for문 다음 소멸자 네개가 나오는것도 그 이유.
	book[2].print();

	for (Book& c : book)
	{
		c.x = 888;
		c.y = 888;
		c.radius = 888;
	}
	book[2].print();
	// 변함. 참조자를 넣어줘서

	return 0;
}