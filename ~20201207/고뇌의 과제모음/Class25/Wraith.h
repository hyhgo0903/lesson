#pragma once
#include "TerranUnit.h"
class Wraith :
	public TerranUnit
{
public:
	Wraith();
	~Wraith();

	virtual void output();
	virtual void Qskill();
	virtual void Wskill();
};

