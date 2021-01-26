#pragma once
#include "BOSSSTATE.h"
class Boss;
class BAttack :
    public BOSSSTATE
{
private:
    RECT _mRc;
    RECT _sRc;
    int index;
public:
    void EnterState();
    void updateState();
    void ExitState();

};

