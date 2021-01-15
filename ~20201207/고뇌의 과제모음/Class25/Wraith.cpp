#include "Wraith.h"

Wraith::Wraith()
{
	_hp = 120;
	_atk = 12;
	cout << "Wraith 클래스의 생성자입니다. \n\n";
}

Wraith::~Wraith()
{
	cout << "Wraith 클래스의 소멸자입니다. \n\n";
}

void Wraith::output()
{
	cout << "Wraith의 HP : " << _hp << endl;
	cout << "Wraith의 공격력 : " << _atk << endl;
}

void Wraith::Qskill()
{
	cout << "Wraith의 Q 스킬 : 클로킹\n";
	cout << "숨습니다.\n";
}

void Wraith::Wskill()
{
	cout << "Wraith의 W 스킬 : 공중 회전\n";
	cout << "멋있습니다.\n\n\n";
}
