#pragma once
#pragma warning(disable:4996)
#include "gameNode.h"
#define LEFT 1
#define RIGHT 0
#define MAXHP 6
#define MAXMP 3
class STATE;
enum State {
    IDLE,
    JUMP,
    DASH,
    SIT,
    CLIMB,
    ATTACK,
    DAMAGED
};
enum POSITION
{
    GROUND,
    AIR,
    CLIFF
};
class Messenger :
    public gameNode
{
private:
    image* mainImg;
    image* subImg;
    RECT mainRC;
    RECT subRC;
    STATE* MessState;
    int isLeft;
    int _currentIndex;
    float gravity;
    bool needSub;
    POINT MPosi;
    int _count;
    State prevState;
    float jumpPower;
    POSITION nowPosi;
    bool isJump;
    string effecName;
    bool isAttack;
    bool dJump;
    bool isDamaged;
    int alpha;
    int timer;
    int HP;
    int MP;
    bool isDead;
    bool isEnhanced;
    int Enhancetime;
    int damage;
    image* HPFilled[MAXHP];
    image* HPBlanked[MAXHP];
    image* MPFilled[MAXMP];
    image* MPBlanked[MAXMP];
public:
    Messenger();
    ~Messenger();
    HRESULT init();
    HRESULT init(bool check);
    HRESULT init(POINT point);
    void release();
    void update(POINT camera);
    void render(POINT camera);
    void Enhance();

    void animation();
    void checkPosition();
   // void EffectSelec(string strKey);
    //게터,세터들
    image* getMainImg() { return mainImg; }
    image* getSubImg() { return subImg; }
    void setMainImg(string strKey) { mainImg = IMAGEMANAGER->findImage(strKey); }
    void setSubImg(string strKey) { subImg = IMAGEMANAGER->findImage(strKey); }
    void setState(State state);
    POINT getPosi() { return MPosi; }
    void setPosi(int x, int y) { MPosi.x = x, MPosi.y = y; }
    void setNeedSub(bool what) { needSub = what; }
    void setDirec(int direc) { isLeft = direc; }
    void setCurrentIndex(int index) { _currentIndex = index; }
    int getDirec() { return isLeft; }
    int getCurIndex() { return _currentIndex; }
    float getGravity() { return gravity; }
    void setGravity(float x) { gravity = x; }
    void setPrevState(State state) { prevState = state; }
    State getPrevState() { return prevState; }
    void setJumpPower(float x) { jumpPower = x; }
    float getJumpPower() { return jumpPower; }
    void setPosition(POSITION Nposi) { nowPosi = Nposi; }
    POSITION getPosition() { return nowPosi; }
    void setIsJump(bool Jump) { isJump = Jump; }
    bool getIsJump() { return isJump; }
    void seteffecName(string strKey) { effecName = strKey; }
    void setSubRC(int x, int y, int width, int height, int direc);
    void setIsAttack(bool yesno) { isAttack = yesno; }
    bool getIsAttack() { return isAttack; }
    RECT getsubRC() { return subRC; }//가로등을 내가 쳤는가? 판정위한 렉트게터
    RECT getMainRC() { return mainRC; }
    void setDJump(bool yesno) { dJump = yesno; }
    bool getDJump() { return dJump; }
    void setIsDamaged(bool yesno) { isDamaged = yesno; }
    bool getIsDamaged() { return isDamaged; }
    int getHP() { return HP; }
    void setHP(int x) { 
       HP += x;
       if (HP >MAXHP)HP = MAXHP;
    }
    void setDamage(int x) { damage = x; }
    int getDamage() { return damage; }
    int getMP() { return MP; }
    void setMP(int x) { 
        MP += x;
        if (MP > MAXMP)MP = MAXMP;
    }
    bool getIsEnhanced() { return isEnhanced; }
    void setIsDead(bool YN) { isDead = YN; }
    bool getIsDead() { return isDead; }
};

