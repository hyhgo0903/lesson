#include "mapTest.h"


mapTest::mapTest()
{
	//�ʿ��� push_back()�� ����.
	//insert�� �ְ� �Ǿ��ִµ�
	//pair, make_pair �̷��� ����
	//�������� ���� ����

	//map<first, second>
	// �������̳ʿ� �ڷ������ �ڵ����� �������� ���ĵȴ�.

	_mapTest.insert(pair<const char*, int>("����", 7));
	_mapTest.insert(pair<const char*, int>("����", 13));
	_mapTest.insert(pair<const char*, int>("��ȣ", 9));

	_mi = _mapTest.find("����"); // �ش��̸����� �ִ�?

	// �����ͷ����Ͱ� ���� ����� ���� �ʴ�?!?!
	if (_mi != _mapTest.end())
	{ // ���� Ű ���� �����ϸ�
		cout << _mi->first << "�� �����ϴ� ���ڴ� " << _mi->second << "�Դϴ�." << endl;
	}
	else // Ű ���� ������(���忡 ���� = �ش�Ű���� ����.)
	{
		cout << "�׷� �ִ�.. ���µ�.." << endl;
	}
}


mapTest::~mapTest()
{


}
