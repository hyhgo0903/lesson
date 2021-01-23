#pragma once
#include "enemy.h"
class rangedTurtle :
    public enemy
{
private:
    image* img2;
    int fireCount;
public:
    rangedTurtle() {};
    ~rangedTurtle() {};
    HRESULT init(const char* imgName, POINT point, int speed, int hp,const char* imgName2,int direction);
    void release();
    void update();
    void render(POINT camera);
    void move();
    void fire(POINT point);
};

