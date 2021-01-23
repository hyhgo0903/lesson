#pragma once
#define RIGHT 0
#define LEFT 1
#include "gameNode.h"
class enemy :
    public gameNode
{
protected:
    image* img;//에너미 이미지
    RECT rc;//에너미 렉트
    POINT EP;// 에너미 좌표(예정)
    int currentX;//몹프레임X
    int direc;//몹방향 0이면right 1이면 left
    int count;
    int Espeed;
    int timer;
    int HP;
    float gravity;
    bool isGround;
    float distance;
    int alpha;
    int check;
    bool isFire;

public:
    HRESULT init();
    HRESULT init(const char* imgName, POINT point,int speed,int hp);
    void release();
    void update();
    void render(POINT camera);
    virtual void move(int speed);
    void draw(POINT camera);
    RECT getRC() { return rc; }
    void setIsGravity(bool boool) { isGround = boool; }
    void setDirec(int direction) { direc = direction; }
    void setHP(int damage) { HP -= damage; }
    int getHP() { return HP; }
    int getDirec() { return direc; }
    inline void setRECT(int x) { rc.left = x; rc.right = rc.left+img->getFrameWidth(); }
    void setAlpha(int x) { alpha = x; }
    void setIsFire(bool fire) { isFire = fire; }
    bool getIsFire() { return isFire; }
    void ChangeImage(const char* img1);
};

