#pragma once
#include "BOSSSTATE.h"
class Boss;
class Move :
    public BOSSSTATE
{
public:
    void EnterState();
    void updateState();
    void ExitState();
};

