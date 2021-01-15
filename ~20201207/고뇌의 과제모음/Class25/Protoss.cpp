#include "Protoss.h"

Protoss::Protoss()
	: _hp(70), _atk(10)
{
	cout << "Protoss클래스의 생성자입니다. \n\n";
}

Protoss::~Protoss()
{
	cout << "Protoss클래스의 소멸자입니다. \n\n";
}

void Protoss::racePassive()
{
	cout << "프로토스 종족 패시브 : 실드\n";
}

void Protoss::output()
{
	cout << "프로토스 유닛의 HP : " << _hp << endl;
	cout << "프로토스 유닛의 공격력 : " << _atk << endl;
}

void Protoss::Qskill()
{
	cout << "프로토스의 Q 스킬 : 건물소환\n";
	cout << "건설없이 소환가능\n";
}

void Protoss::Wskill()
{
	cout << "프로토스의 W 스킬 : 순간이동\n";
	cout << "사실은 없는데 다 쓸수 있다고 하자\n\n\n";
}
