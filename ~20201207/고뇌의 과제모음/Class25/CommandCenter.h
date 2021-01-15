#pragma once
#include "TerranBuilding.h"
class CommandCenter :
	public TerranBuilding
{
public:
	CommandCenter();
	~CommandCenter();

	virtual void output();
	virtual void Qskill();
	virtual void Wskill();
};

