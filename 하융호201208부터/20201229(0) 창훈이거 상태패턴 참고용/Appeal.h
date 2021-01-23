#pragma once
#include "BOSSSTATE.h"
class Boss;
class Appeal :
    public BOSSSTATE
{
public:
    void EnterState();
    void updateState();
    void ExitState();
};

