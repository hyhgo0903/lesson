#include "Terran.h"

Terran::Terran()
	: _hp(60), _atk(6)
{
	cout << "Terran클래스의 생성자입니다. \n\n";
}

Terran::~Terran()
{
	cout << "Terran클래스의 소멸자입니다. \n\n";
}

void Terran::racePassive()
{
	cout << "테란 종족 패시브 : 건물 체력이 일정 이하면 도트뎀\n";
}

void Terran::output()
{
	cout << "테란 유닛의 HP : " << _hp << endl;
	cout << "테란 유닛의 공격력 : " << _atk << endl;
}

void Terran::Qskill()
{
	cout << "테란의 Q 스킬 : 수리\n";
	cout << "건물 수리\n";
}

void Terran::Wskill()
{
	cout << "테란의 W 스킬 : 벙커에 숨기\n";
	cout << "홍진호에게 GG를 받아냅니다.\n\n\n";
}
