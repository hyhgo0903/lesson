#include "Queen.h"

Queen::Queen()
{
	_hp = 180;
	_atk = 0;
	cout << "�� Ŭ������ �������Դϴ�. \n\n";
}

Queen::~Queen()
{
	cout << "�� Ŭ������ �Ҹ����Դϴ�. \n\n";
}

void Queen::output()
{
	cout << "���� HP : " << _hp << endl;
	cout << "���� ���ݷ� : " << _atk << endl;
}

void Queen::Qskill()
{
	cout << "���� Q ��ų : ���鸵 ���\n";
	cout << "���̰� ���鸵 ����\n";
}

void Queen::Wskill()
{
	cout << "���� W ��ų : �ν��׾�\n";
	cout << "������ �����\n\n\n";
}
