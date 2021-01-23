#pragma once
#include "STATE.h"
class Messenger;
class Attack :
    public STATE
{
private:
    bool chainAttack;
public:
    void EnterState();
    void updateState();
    void ExitState();
};


