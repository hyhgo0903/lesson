#pragma once
#include "Terran.h"
class TerranUnit :
	public Terran
{
public:
	TerranUnit();
	~TerranUnit();

	virtual void output();
	virtual void Qskill();
	virtual void Wskill();
};

