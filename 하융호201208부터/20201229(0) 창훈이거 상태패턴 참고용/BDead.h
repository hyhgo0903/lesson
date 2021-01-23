#pragma once
#include "BOSSSTATE.h"
class Boss;
class BDead :
    public BOSSSTATE
{
public:
    void EnterState();
    void updateState();
    void ExitState();
};

