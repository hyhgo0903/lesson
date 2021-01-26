#pragma once
#include "BOSSSTATE.h"
class Boss;
class BJump :
    public BOSSSTATE
{
private:
public:
    void EnterState();
    void updateState();
    void ExitState();

};

