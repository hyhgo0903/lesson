#pragma once
#include "enemy.h"
class worm :
    public enemy
{
public:
    worm() {};
    ~worm() {};
    HRESULT init(const char* imgName, POINT point, int speed, int hp);
    void release();
    void update(float dis);
    void render(POINT camera);
    void move(int speed);
};

