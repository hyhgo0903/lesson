#include "listTest.h"

listTest::listTest()
{
	_lNum.push_back(1); // {1}
	_lNum.push_front(99); // {99, 1}

	// 리스트 순차접근X. 줄줄이 연결해서 씀
	// 각 값에 노드가 포인터(주소를 가리킴)
	// 중간값 들어내려면 이전값에
	//다음값의 주소를 넘겨주고 사라짐.

	// 얘는 양방향이라 가능(Double Linked List)
	// 참고 : Single LL - SLL
	// Circula LL - CLL(환형)

	for (int i = 0; i < 3; i++)
	{ // {99, 1, 0, 10, 20}
		_lNum.push_back(i*10);
	}

	for (int i = 0; i < 3; i++)
	{ // {20, 10, 0,99, 1, 0, 10, 20}
		_lNum.push_front(i * 10);
	}

	for (_liNum = _lNum.begin(); _liNum != _lNum.end(); ++_liNum)
	{
		// cout << _lNum[i] << " "; << 리스트는 배열이 X
		// for문에서 이터레이터 이용해줘야..
		cout << *_liNum << " ";
	}
	cout << "\n";
}

listTest::~listTest()
{
}
