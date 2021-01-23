#pragma once
#include "gameNode.h"
#include "BOSSSTATE.h"
#include "Bullet.h"
enum BState
{
    APPEAL,
    MOVE,
    BATTACK,
    BJUMP,
    SPATTERN,
    BDJUMP,
    DEAD
};
class Boss :
    public gameNode
{
private:
    image* BossImg;
    image* AtkImg;
    image* subAtk;
    RECT _rc;
    BState prevState;
    BOSSSTATE* BossSta;
    POINT bossLoc;
    RECT ATTRC;
    RECT subATTRC;
    int _currentX;
    int _subIdx;
    int direc;//0Àº Left, 1Àº Right
    int count;
    int timer;
    int Dtimer;
    bool canAtt;
    bool Fire;
    bool comeback;
    int HP;
    bool damaged;
    int alpha;
    float JumpPower;
    float gravity;
    bool SPtrn;
    bool isdead;
public:
    Boss();
    ~Boss();
    HRESULT init();
    void release();
    void update();
    void render(POINT camera);

    void animaiton(int x);
    void NPattern();
    void FIRE();
    void atkAni();
    void Bdamaged();
    void Jump();
    void PStart();
    void PMove();
    void PtAni();

    POINT getPosi() { return bossLoc; }
    void setPosi(int x, int y) { bossLoc.x = x, bossLoc.y = y; }
    void setRC(RECT rc) { _rc = rc; }
    void setState(BState BS);
    void setImg(const char* strKey) { BossImg = IMAGEMANAGER->findImage(strKey); }
    image* getImg() { return BossImg; }
    void setIndex(int index) { _currentX = index; }
    int getIndex() { return _currentX; }
    void setDirec(int direction) { direc = direction; }
    int getDirec() { return direc; }
    RECT getRC() { return _rc; }
    RECT getMAttRC() { return ATTRC; }
    RECT getSAttRC() { return subATTRC; }
    void setMAttRC(RECT rc) { ATTRC = rc; }
    void setSubRC(RECT rc) { subATTRC = rc; }
    bool getCanAtt() { return canAtt; }
    void setCanAtt(bool yesno) { canAtt = yesno; }
    void setFire(bool yesno) { Fire = yesno; }
    bool getFire() { return Fire; }
    int getHP() { return HP; }
    void setHP(int x) { HP -= x; }
    void setDamaged(bool YN) { damaged = YN; }
    void setDtimer(int x) { Dtimer = x; }
    BState getPrev() { return prevState; }
    void setPrev(BState prevS) { prevState = prevS; }
    float getJPower() { return JumpPower; }
    float getGravity() { return gravity; }
    void setJPower(float JP) { JumpPower = JP; }
    void setGravity(float gra) { gravity = gra; }
    void setSP(bool YN) { SPtrn = YN; }
    void setIsdead(bool YN) { isdead = YN; }
};

