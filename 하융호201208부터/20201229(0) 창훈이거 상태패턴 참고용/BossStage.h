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
    float probeDY;//�Ʒ� �浹 Ž��
    float probeUY;//�� �浹 Ž��
    float EprobeDY;//���ʹ̵� �߷��� ����
    float probeX;//�¿��� �浹��
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

