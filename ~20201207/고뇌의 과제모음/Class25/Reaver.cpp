#include "Reaver.h"

Reaver::Reaver()
{
	_hp = 200;
	_atk = 100;
	cout << "Reaver 클래스의 생성자입니다. \n\n";
}

Reaver::~Reaver()
{
	cout << "Reaver 클래스의 소멸자입니다. \n\n";
}

void Reaver::output()
{
	cout << "Reaver의 HP : " << _hp << endl;
	cout << "Reaver의 공격력 : " << _atk << endl;
}

void Reaver::Qskill()
{
	cout << "Reaver의 Q 스킬 : 스캐럽 생성\n";
	cout << "공격 장전\n";
}

void Reaver::Wskill()
{
	cout << "Reaver의 W 스킬 : 스캐럽 발사\n";
	cout << "공격\n\n\n";
}
