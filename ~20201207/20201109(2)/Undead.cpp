#include "Undead.h"

Undead::Undead()
	: _hp(250), _mp(80)
{
	_phyAttack = 30;
	_magAttack = 8;
}

Undead::Undead(int hp, int mp)
	: _hp(hp), _mp(mp)
{
}

Undead::~Undead()
{
	cout << "언데드의 소멸자\n";
}

void Undead::racePassive()
{
	cout << "패시브 스킬" << endl;
}

void Undead::output()
{
	cout << "hp" << _hp << endl;
	cout << "mp" << _mp << endl;
	cout << "phyAttack" << _phyAttack << endl;
	cout << "magAttack" << _magAttack << endl;
}

void Undead::Qskill()
{
	cout << "Q스킬" << endl;
}

void Undead::Wskill()
{
	cout << "W스킬" << endl;
}
