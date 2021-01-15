#pragma once
#include <iostream>

using namespace std;

class Undead
{
protected:
	int _hp;
	int _mp;
	int _phyAttack; // ����
	int _magAttack; // ����

public:
	Undead();
	Undead(int hp, int mp); // ��� �̴ϼȶ�����
	~Undead();

	void racePassive();

	void output();
	void Qskill();
	void Wskill();

};

