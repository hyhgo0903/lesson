#pragma once
#include <iostream>

using namespace std;

class Protoss
{
protected:
	int _hp;
	int _atk;

public:
	Protoss();
	~Protoss();
	void racePassive();

	virtual void output();
	virtual void Qskill();
	virtual void Wskill();
};

