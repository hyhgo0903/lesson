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
	// ����������. Ŭ���� �װ��� �����
	// �� for�� ���� �Ҹ��� �װ��� �����°͵� �� ����.
	book[2].print();

	for (Book& c : book)
	{
		c.x = 888;
		c.y = 888;
		c.radius = 888;
	}
	book[2].print();
	// ����. �����ڸ� �־��༭

	return 0;
}