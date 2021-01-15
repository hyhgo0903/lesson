#include "Queen.h"

Queen::Queen()
{
	_hp = 180;
	_atk = 0;
	cout << "퀸 클래스의 생성자입니다. \n\n";
}

Queen::~Queen()
{
	cout << "퀸 클래스의 소멸자입니다. \n\n";
}

void Queen::output()
{
	cout << "퀸의 HP : " << _hp << endl;
	cout << "퀸의 공격력 : " << _atk << endl;
}

void Queen::Qskill()
{
	cout << "퀸의 Q 스킬 : 브루들링 산란\n";
	cout << "죽이고 브루들링 생성\n";
}

void Queen::Wskill()
{
	cout << "퀸의 W 스킬 : 인스네어\n";
	cout << "범위에 디버프\n\n\n";
}
