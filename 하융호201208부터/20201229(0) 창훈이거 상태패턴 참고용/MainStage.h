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
    float probeDY;//�Ʒ� �浹 Ž��
    float probeUY;//�� �浹 Ž��
    float EprobeDY;//���ʹ̵� �߷��� ����
    float probeX;//�¿��� �浹��
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

