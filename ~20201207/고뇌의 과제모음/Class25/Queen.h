#pragma once
#include "Zerg.h"
class Queen :
	public Zerg
{
public:
	Queen();
	~Queen();

	virtual void output();
	virtual void Qskill();
	virtual void Wskill();
};

