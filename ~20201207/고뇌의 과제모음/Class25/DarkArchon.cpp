#include "DarkArchon.h"

DarkArchon::DarkArchon()
{
	_hp = 20;
	_atk = 0;
	cout << "DarkArchon 클래스의 생성자입니다. \n\n";
}

DarkArchon::~DarkArchon()
{
	cout << "DarkArchon 클래스의 소멸자입니다. \n\n";
}

void DarkArchon::output()
{
	cout << "DarkArchon의 HP : " << _hp << endl;
	cout << "DarkArchon의 공격력 : " << _atk << endl;
}

void DarkArchon::Qskill()
{
	cout << "DarkArchon의 Q 스킬 : 피드백\n";
	cout << "마나태우고 그만큼 데미지.\n";
}

void DarkArchon::Wskill()
{
	cout << "DarkArchon의 W 스킬 : 마인드 컨트롤\n";
	cout << "갖고 옴\n\n\n";
}
