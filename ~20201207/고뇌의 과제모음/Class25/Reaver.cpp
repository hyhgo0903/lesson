#include "Reaver.h"

Reaver::Reaver()
{
	_hp = 200;
	_atk = 100;
	cout << "Reaver Ŭ������ �������Դϴ�. \n\n";
}

Reaver::~Reaver()
{
	cout << "Reaver Ŭ������ �Ҹ����Դϴ�. \n\n";
}

void Reaver::output()
{
	cout << "Reaver�� HP : " << _hp << endl;
	cout << "Reaver�� ���ݷ� : " << _atk << endl;
}

void Reaver::Qskill()
{
	cout << "Reaver�� Q ��ų : ��ĳ�� ����\n";
	cout << "���� ����\n";
}

void Reaver::Wskill()
{
	cout << "Reaver�� W ��ų : ��ĳ�� �߻�\n";
	cout << "����\n\n\n";
}
