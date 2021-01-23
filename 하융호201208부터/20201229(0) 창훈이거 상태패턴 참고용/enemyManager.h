#pragma once
#include "gameNode.h"
#include "greenTurtle.h"
#include "rangedTurtle.h"
#include "worm.h"
#include <vector>
#include"Bullet.h"
#include"ItemManager.h"
class Messenger;
class enemyManager :
    public gameNode
{
private:
    Messenger* _mess;
    Bullet* _bullet;
    int fireTimer;
    ItemManager* _item;
private:
    vector<enemy*> vEnemy;
    vector<enemy*>::iterator viEnemy;

    vector<rangedTurtle*>vRTurtle;
    vector<rangedTurtle*>::iterator viRTurtle;
public:
    enemyManager();
    ~enemyManager();
    HRESULT init();
    void release();
    void update();
    void render(POINT camera);
    void setGTurtle(POINT point);
    void setWorm(POINT point);
    void setRTurtle(POINT point,int direction);
    vector<enemy*> getEneVector() { return vEnemy; }
    vector<enemy*>::iterator getEveIter() { return viEnemy; }
    vector<rangedTurtle*> getRTvector() { return vRTurtle; }
    vector<rangedTurtle*>::iterator getRTviter() { return viRTurtle; }
    void findDirec();
    void setMessengerMemory(Messenger* mess) { _mess = mess; }
    void removeEnemy(int arrNum);
    void removeRT(int arrNum);
    void RTFire();
    Bullet* getBullet() { return _bullet; }
};

