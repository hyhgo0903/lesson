#include "Zerg.h"

Zerg::Zerg()
	: _hp(50), _atk(5)
{
	cout << "ZergŬ������ �������Դϴ�. \n\n";	
}

Zerg::~Zerg()
{
	cout << "ZergŬ������ �Ҹ����Դϴ�. \n\n";
}

void Zerg::racePassive()
{
	cout << "���� ���� �нú� : �� �� ü���� ȸ���ȴ�.\n";
}

void Zerg::output()
{
	cout << "���� ������ HP : " << _hp << endl;
	cout << "���� ������ ���ݷ� : " << _atk << endl;
}

void Zerg::Qskill()
{
	cout << "������ Q ��ų : ����\n";
	cout << "������ ��Ʈ��\n";
}

void Zerg::Wskill()
{
	cout << "������ W ��ų : ���ο�\n";
	cout << "���� ��� ���ݸ��ϰ�\n\n\n";
}
