#include "Wraith.h"

Wraith::Wraith()
{
	_hp = 120;
	_atk = 12;
	cout << "Wraith Ŭ������ �������Դϴ�. \n\n";
}

Wraith::~Wraith()
{
	cout << "Wraith Ŭ������ �Ҹ����Դϴ�. \n\n";
}

void Wraith::output()
{
	cout << "Wraith�� HP : " << _hp << endl;
	cout << "Wraith�� ���ݷ� : " << _atk << endl;
}

void Wraith::Qskill()
{
	cout << "Wraith�� Q ��ų : Ŭ��ŷ\n";
	cout << "�����ϴ�.\n";
}

void Wraith::Wskill()
{
	cout << "Wraith�� W ��ų : ���� ȸ��\n";
	cout << "���ֽ��ϴ�.\n\n\n";
}
