#include "Protoss.h"

Protoss::Protoss()
	: _hp(70), _atk(10)
{
	cout << "ProtossŬ������ �������Դϴ�. \n\n";
}

Protoss::~Protoss()
{
	cout << "ProtossŬ������ �Ҹ����Դϴ�. \n\n";
}

void Protoss::racePassive()
{
	cout << "�����佺 ���� �нú� : �ǵ�\n";
}

void Protoss::output()
{
	cout << "�����佺 ������ HP : " << _hp << endl;
	cout << "�����佺 ������ ���ݷ� : " << _atk << endl;
}

void Protoss::Qskill()
{
	cout << "�����佺�� Q ��ų : �ǹ���ȯ\n";
	cout << "�Ǽ����� ��ȯ����\n";
}

void Protoss::Wskill()
{
	cout << "�����佺�� W ��ų : �����̵�\n";
	cout << "����� ���µ� �� ���� �ִٰ� ����\n\n\n";
}
