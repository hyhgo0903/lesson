#include "TerranUnit.h"

TerranUnit::TerranUnit()
{
	_hp = 100;
	_atk = 40;
	cout << "TerranUnit Ŭ������ �������Դϴ�. \n\n";
}

TerranUnit::~TerranUnit()
{
	cout << "TerranUnit Ŭ������ �Ҹ����Դϴ�. \n\n";
}

void TerranUnit::output()
{
	cout << "TerranUnit�� HP : " << _hp << endl;
	cout << "TerranUnit�� ���ݷ� : " << _atk << endl;
}

void TerranUnit::Qskill()
{
	cout << "TerranUnit�� Q ��ų : QQQQ\n";
	cout << "�� ���� Q\n";
}

void TerranUnit::Wskill()
{
	cout << "TerranUnit�� W ��ų : WWWW\n";
	cout << "�� ���� W\n\n\n";
}
