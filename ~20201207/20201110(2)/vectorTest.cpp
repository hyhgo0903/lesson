#include "vectorTest.h"
#include <iostream>

using namespace std;

//���� �޸� ũ�� ������ 2�辿��Ҵµ� ������ 1.5�辿

vectorTest::vectorTest()
{
	//1. �����̳ʿ� ���� ���������� �ְ� ������
	// push_back() - ���� �ѹ� ������ ���� �ִ´�
	// ���� : emplace_back() - ���� �������� �ʰ� �ִ´�
	
	// �������� ��������
	// ��������� / �̵�������(move)
	
	_vNum.push_back(1); // {1}

	for (int i=0; i<3; i++)
		_vNum.push_back(i*10); // {1, 0, 10, 20}

	//2. ������ ũ�⸦ �˷��ִ� size()
	cout << "������ ���� ũ�� : " << _vNum.size() << endl; // 4

	//3. ���������� �ڿ������� �����ϴ� pop_back()
	_vNum.pop_back(); // {1, 0, 10}
	_vNum.pop_back(); // {1, 0}

	// cout << _vNum.begin(); <<�ȵȴ�

	//4. ���� �߰��� �� ���� insert()
	_vNum.insert(_vNum.begin() + 1, 777);  // {1, 777, 0}
	// ���� ���ۿ��� 2��°�ڸ����� 777�� �ְ� �������� ��ĭ�� �о

	_vNum.insert(_vNum.end() - 1, 333);  // {1, 777, 333, 0}
	// ���� ������ 2��°�ڸ����� 333�� �ְ� �������� ��ĭ�� �о

	//���� �߰��� ���� �����ҋ� erase()
	_vNum.erase(_vNum.begin() + 2); // {1, 777, 0}
	_vNum.erase(_vNum.end() - 2); // {1, 0}

	_vNum.clear(); // ���� Ŭ�����Ѵٰ� �޸𸮰� ������� ����

	for (int i = 0; i < _vNum.size(); i++)
		cout << _vNum[i] << " ";
	cout << "\n";
}

vectorTest::~vectorTest()
{
}
