#pragma once
#include "Terran.h"
class TerranBuilding :
	public Terran
{
public:
	TerranBuilding();
	~TerranBuilding();

	virtual void output();
	virtual void Qskill();
	virtual void Wskill();
};

