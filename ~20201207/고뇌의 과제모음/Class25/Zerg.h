#pragma once
#include <iostream>

using namespace std;

class Zerg
{
protected:
	int _hp;
	int _atk;

public:
	Zerg();
	~Zerg();
	void racePassive();

	virtual void output();
	virtual void Qskill();
	virtual void Wskill();
};

