#include "HighTemplar.h"

HighTemplar::HighTemplar()
{
	_hp = 100;
	_atk = 0;
	cout << "�������÷� Ŭ������ �������Դϴ�. \n\n";
}

HighTemplar::~HighTemplar()
{
	cout << "�������÷� Ŭ������ �Ҹ����Դϴ�. \n\n";
}

void HighTemplar::output()
{
	cout << "�������÷��� HP : " << _hp << endl;
	cout << "�������÷��� ���ݷ� : " << _atk << endl;
}

void HighTemplar::Qskill()
{
	cout << "�������÷��� Q ��ų : ���̿��� ����\n";
	cout << "�ϲ��� ������ ���Դϴ�.\n";
}

void HighTemplar::Wskill()
{
	cout << "�������÷��� W ��ų : �ҷ�ó��̼�\n";
	cout << "������ �ƹ��� �� ��\n\n\n";
}
