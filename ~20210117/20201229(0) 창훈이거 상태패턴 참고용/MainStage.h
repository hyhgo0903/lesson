#pragma once
#pragma warning(disable:4996)
#include "gameNode.h"
#include "Messenger.h"
#include "enemyManager.h"
#include"ItemManager.h"
class MainStage :
    public gameNode
{
private:
    POINT camera;
    image* backGround;
    image* mainMap;
    image* mainCol;
    image* devil;
    enemyManager* EM;
    ItemManager* IM;
    Messenger* messenger;
    int count;
    int index;
    float probeDY;//아래 충돌 탐색
    float probeUY;//위 충돌 탐색
    float EprobeDY;//에너미들 중력을 위한
    float probeX;//좌우측 충돌용
    bool check;
    float passedtime;
    float maintime;
public:
    MainStage();
    ~MainStage();
    HRESULT init();
    HRESULT init(bool Chk);
    void release();
    void update();
    void render();
    void MSRC();
    void MSPC();
};

