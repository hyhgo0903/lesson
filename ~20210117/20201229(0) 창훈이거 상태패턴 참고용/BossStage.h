#pragma once
#include "gameNode.h"
#include "Messenger.h"
#include "Boss.h"
class BossStage :
    public gameNode
{
private:
    image* backGround;
    image* BossMap;
    image* BossCol;
    POINT camera;
    Messenger* _messenger;
    Boss* _boss;
    float probeDY;//아래 충돌 탐색
    float probeUY;//위 충돌 탐색
    float EprobeDY;//에너미들 중력을 위한
    float probeX;//좌우측 충돌용
    bool check;
    float passedtime;
    float maintime;
public:
    BossStage();
    ~BossStage();
    HRESULT init();
    HRESULT init(bool chk);
    void release();
    void update();
    void render();
    void BSRC();
    void BSPC();
};

