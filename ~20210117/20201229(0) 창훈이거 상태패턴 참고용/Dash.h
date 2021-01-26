#pragma once
#include "STATE.h"
class Messenger;
class Dash :
    public STATE
{
public:
    void EnterState();
    void updateState();
    void ExitState();
};


