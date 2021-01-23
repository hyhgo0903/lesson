#pragma once
#include "STATE.h"
class Messenger;
class Damaged :
    public STATE
{
    void EnterState();
    void updateState();
    void ExitState();
};

