#pragma once
#include "STATE.h"
class Messenger;
class Sit :
    public STATE
{
public:
	void EnterState();
	void updateState();
	void ExitState();
};

