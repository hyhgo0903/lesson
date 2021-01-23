#pragma once
#include "enemy.h"
class greenTurtle :
    public enemy
{
private:
    int alpha;
    int time;
public:
    void draw(POINT camera);
    void setAlpha(int x) { alpha = x; }
};

