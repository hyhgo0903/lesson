#include "TerranBuilding.h"

TerranBuilding::TerranBuilding()
{
	_hp = 100;
	_atk = 40;
	cout << "TerranBuilding Ŭ������ �������Դϴ�. \n\n";
}

TerranBuilding::~TerranBuilding()
{
	cout << "TerranBuilding Ŭ������ �Ҹ����Դϴ�. \n\n";
}

void TerranBuilding::output()
{
	cout << "TerranBuilding�� HP : " << _hp << endl;
	cout << "TerranBuilding�� ���ݷ� : " << _atk << endl;
}

void TerranBuilding::Qskill()
{
	cout << "TerranBuilding�� Q ��ų : �ǹ�Q\n";
	cout << "�� ���� Q\n";
}

void TerranBuilding::Wskill()
{
	cout << "TerranBuilding�� W ��ų : �ǹ�W\n";
	cout << "�� ���� W\n\n\n";
}
