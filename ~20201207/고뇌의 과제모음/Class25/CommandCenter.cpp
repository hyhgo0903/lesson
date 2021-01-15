#include "CommandCenter.h"

CommandCenter::CommandCenter()
{
	_hp = 800;
	_atk = 0;
	cout << "CommandCenter 클래스의 생성자입니다. \n\n";
}

CommandCenter::~CommandCenter()
{
	cout << "CommandCenter 클래스의 소멸자입니다. \n\n";
}

void CommandCenter::output()
{
	cout << "CommandCenter의 HP : " << _hp << endl;
	cout << "CommandCenter의 공격력 : " << _atk << endl;
}

void CommandCenter::Qskill()
{
	cout << "CommandCenter의 Q 스킬 : SCV 만들기\n";
	cout << "잡코리아에 들어가서 SCV를 구인합니다.\n";
}

void CommandCenter::Wskill()
{
	cout << "CommandCenter의 W 스킬 : 커맨드 띄우기\n";
	cout << "나머지야 죽든 말든 알바 아닙니다.\n\n\n";
}
