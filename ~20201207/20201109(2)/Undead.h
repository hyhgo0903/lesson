#pragma once
#include <iostream>

using namespace std;

class Undead
{
protected:
	int _hp;
	int _mp;
	int _phyAttack; // 물공
	int _magAttack; // 마공

public:
	Undead();
	Undead(int hp, int mp); // 멤버 이니셜라이즈
	~Undead();

	void racePassive();

	void output();
	void Qskill();
	void Wskill();

};

