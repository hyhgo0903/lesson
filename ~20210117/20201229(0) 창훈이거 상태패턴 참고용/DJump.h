#pragma once
#include "BOSSSTATE.h"
class DJump :
    public BOSSSTATE
{
public:
    void EnterState();
    void updateState();
    void ExitState();

};

