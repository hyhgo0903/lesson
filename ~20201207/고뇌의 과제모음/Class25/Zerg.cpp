#include "Zerg.h"

Zerg::Zerg()
	: _hp(50), _atk(5)
{
	cout << "Zerg클래스의 생성자입니다. \n\n";	
}

Zerg::~Zerg()
{
	cout << "Zerg클래스의 소멸자입니다. \n\n";
}

void Zerg::racePassive()
{
	cout << "저그 종족 패시브 : 매 초 체력이 회복된다.\n";
}

void Zerg::output()
{
	cout << "저그 유닛의 HP : " << _hp << endl;
	cout << "저그 유닛의 공격력 : " << _atk << endl;
}

void Zerg::Qskill()
{
	cout << "저그의 Q 스킬 : 감염\n";
	cout << "적에게 도트뎀\n";
}

void Zerg::Wskill()
{
	cout << "저그의 W 스킬 : 버로우\n";
	cout << "땅에 숨어서 공격못하게\n\n\n";
}
