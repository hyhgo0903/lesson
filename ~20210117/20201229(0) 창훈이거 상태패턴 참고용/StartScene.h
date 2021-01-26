#pragma once
#include "gameNode.h"
class StartScene :
    public gameNode
{
private:
    image* start;
    bool reply;
    float passedtime;
    float maintime;
public:
    HRESULT init();
    void release();
    void update();
    void render();
    
};

