#include "TerranBuilding.h"

TerranBuilding::TerranBuilding()
{
	_hp = 100;
	_atk = 40;
	cout << "TerranBuilding 클래스의 생성자입니다. \n\n";
}

TerranBuilding::~TerranBuilding()
{
	cout << "TerranBuilding 클래스의 소멸자입니다. \n\n";
}

void TerranBuilding::output()
{
	cout << "TerranBuilding의 HP : " << _hp << endl;
	cout << "TerranBuilding의 공격력 : " << _atk << endl;
}

void TerranBuilding::Qskill()
{
	cout << "TerranBuilding의 Q 스킬 : 건물Q\n";
	cout << "네 다음 Q\n";
}

void TerranBuilding::Wskill()
{
	cout << "TerranBuilding의 W 스킬 : 건물W\n";
	cout << "네 다음 W\n\n\n";
}
