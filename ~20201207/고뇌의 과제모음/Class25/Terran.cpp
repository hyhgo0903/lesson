#include "Terran.h"

Terran::Terran()
	: _hp(60), _atk(6)
{
	cout << "TerranŬ������ �������Դϴ�. \n\n";
}

Terran::~Terran()
{
	cout << "TerranŬ������ �Ҹ����Դϴ�. \n\n";
}

void Terran::racePassive()
{
	cout << "�׶� ���� �нú� : �ǹ� ü���� ���� ���ϸ� ��Ʈ��\n";
}

void Terran::output()
{
	cout << "�׶� ������ HP : " << _hp << endl;
	cout << "�׶� ������ ���ݷ� : " << _atk << endl;
}

void Terran::Qskill()
{
	cout << "�׶��� Q ��ų : ����\n";
	cout << "�ǹ� ����\n";
}

void Terran::Wskill()
{
	cout << "�׶��� W ��ų : ��Ŀ�� ����\n";
	cout << "ȫ��ȣ���� GG�� �޾Ƴ��ϴ�.\n\n\n";
}
