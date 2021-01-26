#pragma once
#include "STATE.h"
class Messenger;
class Climb :
    public STATE
{
public:
    void EnterState();
    void updateState();
    void ExitState();
};

