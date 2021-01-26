#pragma once
#include "gameNode.h"
#include <vector>
class Messenger;
enum TYPE
{
    HEAL,
    MANA,
    POWER
};
struct tagItem {
    image* img;
    RECT rc;
    //float angle;
    //float distance;
    TYPE type;
};
class ItemManager :
    public gameNode
{
private:
    Messenger* _messenger;
    vector<tagItem> vItem;
    vector<tagItem>::iterator viItem;
    const char* imgName;
public:
    ItemManager();
    ~ItemManager();
    HRESULT init();
    void release();
    void update(Messenger* mess);
    void render(POINT camera);
    void ItemDrop(int x, int y, int variety);
    void setMessengerMemory(Messenger* mess) { _messenger = mess; }
    void healing(int x, int y);
    void manaRecover(int x, int y);
    void PowerStone(int x,int y);
    void PickupItem(Messenger* mess);
    vector<tagItem> getVitem() { return vItem; }
};

