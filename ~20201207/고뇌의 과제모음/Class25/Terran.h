#pragma once
#include <iostream>

using namespace std;

class Terran
{
protected:
	int _hp;
	int _atk;

public:
	Terran();
	~Terran();
	void racePassive();

	virtual void output();
	virtual void Qskill();
	virtual void Wskill();
};

