#include "Zergling.h"

Zergling::Zergling()
//	: _hp(50), _atk(5) << �̰� �����µ�
{
	_hp = 60;
	_atk = 5;
	cout << "���۸� Ŭ������ �������Դϴ�. \n\n";
}

Zergling::~Zergling()
{
	cout << "���۸� Ŭ������ �Ҹ����Դϴ�. \n\n";
}

void Zergling::output()
{
	cout << "���۸��� HP : " << _hp << endl;
	cout << "���۸��� ���ݷ� : " << _atk << endl;
}

void Zergling::Qskill()
{
	cout << "���۸��� Q ��ų : �ֵѷ�ġ��\n";
	cout << "��Ÿ��4�� �ֺ�1��\n";
}

void Zergling::Wskill()
{
	cout << "���۸��� W ��ų : �Ƶ巹����\n";
	cout << "�ϴÿ� ����\n\n\n";
}
