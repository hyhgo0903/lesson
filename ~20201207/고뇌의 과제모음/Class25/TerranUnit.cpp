#include "TerranUnit.h"

TerranUnit::TerranUnit()
{
	_hp = 100;
	_atk = 40;
	cout << "TerranUnit 클래스의 생성자입니다. \n\n";
}

TerranUnit::~TerranUnit()
{
	cout << "TerranUnit 클래스의 소멸자입니다. \n\n";
}

void TerranUnit::output()
{
	cout << "TerranUnit의 HP : " << _hp << endl;
	cout << "TerranUnit의 공격력 : " << _atk << endl;
}

void TerranUnit::Qskill()
{
	cout << "TerranUnit의 Q 스킬 : QQQQ\n";
	cout << "네 다음 Q\n";
}

void TerranUnit::Wskill()
{
	cout << "TerranUnit의 W 스킬 : WWWW\n";
	cout << "네 다음 W\n\n\n";
}
