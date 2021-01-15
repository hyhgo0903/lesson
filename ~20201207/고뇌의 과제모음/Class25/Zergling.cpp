#include "Zergling.h"

Zergling::Zergling()
//	: _hp(50), _atk(5) << 이건 못쓰는듯
{
	_hp = 60;
	_atk = 5;
	cout << "저글링 클래스의 생성자입니다. \n\n";
}

Zergling::~Zergling()
{
	cout << "저글링 클래스의 소멸자입니다. \n\n";
}

void Zergling::output()
{
	cout << "저글링의 HP : " << _hp << endl;
	cout << "저글링의 공격력 : " << _atk << endl;
}

void Zergling::Qskill()
{
	cout << "저글링의 Q 스킬 : 휘둘러치기\n";
	cout << "주타겟4딜 주변1딜\n";
}

void Zergling::Wskill()
{
	cout << "저글링의 W 스킬 : 아드레날린\n";
	cout << "하늘에 날린\n\n\n";
}
