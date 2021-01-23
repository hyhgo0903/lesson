#pragma once
#include "gameNode.h"
class DeadScene :
    public gameNode
{
private:
    image* devilimg;
    int count;
    int index;
    bool ischeck;
    bool reply;
public:
    HRESULT init();
    HRESULT init(bool check);
    void release();
    void update();
    void render();
};

