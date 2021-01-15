#pragma once
#include "Zerg.h"
class Zergling :
	public Zerg
{
public:
	Zergling();
	~Zergling();

	virtual void output();
	virtual void Qskill();
	virtual void Wskill();
};

