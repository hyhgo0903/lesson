#include "HighTemplar.h"

HighTemplar::HighTemplar()
{
	_hp = 100;
	_atk = 0;
	cout << "하이템플러 클래스의 생성자입니다. \n\n";
}

HighTemplar::~HighTemplar()
{
	cout << "하이템플러 클래스의 소멸자입니다. \n\n";
}

void HighTemplar::output()
{
	cout << "하이템플러의 HP : " << _hp << endl;
	cout << "하이템플러의 공격력 : " << _atk << endl;
}

void HighTemplar::Qskill()
{
	cout << "하이템플러의 Q 스킬 : 사이오닉 스톰\n";
	cout << "일꾼을 모조리 죽입니다.\n";
}

void HighTemplar::Wskill()
{
	cout << "하이템플러의 W 스킬 : 할루시네이션\n";
	cout << "솔직히 아무도 안 씀\n\n\n";
}
