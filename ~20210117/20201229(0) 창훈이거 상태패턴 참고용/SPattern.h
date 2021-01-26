#pragma once
#include "BOSSSTATE.h"
class Boss;
class SPattern :
    public BOSSSTATE
{
public:
    void EnterState();
    void updateState();
    void ExitState();

};

