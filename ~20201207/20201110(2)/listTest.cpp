#include "listTest.h"

listTest::listTest()
{
	_lNum.push_back(1); // {1}
	_lNum.push_front(99); // {99, 1}

	// ����Ʈ ��������X. ������ �����ؼ� ��
	// �� ���� ��尡 ������(�ּҸ� ����Ŵ)
	// �߰��� ������ ��������
	//�������� �ּҸ� �Ѱ��ְ� �����.

	// ��� ������̶� ����(Double Linked List)
	// ���� : Single LL - SLL
	// Circula LL - CLL(ȯ��)

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
		// cout << _lNum[i] << " "; << ����Ʈ�� �迭�� X
		// for������ ���ͷ����� �̿������..
		cout << *_liNum << " ";
	}
	cout << "\n";
}

listTest::~listTest()
{
}
