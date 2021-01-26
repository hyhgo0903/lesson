#pragma once
#include "STATE.h"
class Messenger;
class Jump :
    public STATE
{
private:
	float jumpPower;
public:
	void EnterState();
	void updateState();
	void ExitState();
};

