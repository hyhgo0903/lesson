#include "stdafx.h"
#include "enemyManager.h"
#include "Messenger.h"
enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
    setGTurtle(PointMake(350,478));
    setGTurtle(PointMake(1185, 910));
    setGTurtle(PointMake(505, 478));
    setGTurtle(PointMake(427, 158));
    setGTurtle(PointMake(2218, 1088));
    setGTurtle(PointMake(2547, 997));
    setWorm(PointMake(286, 300));
    setWorm(PointMake(429, 300));
    setWorm(PointMake(325, 30));
    setWorm(PointMake(1435, 30));
    setRTurtle(PointMake(2871, 997), 0);

    setRTurtle(PointMake(1520, 855), 0);
    setRTurtle(PointMake(903, 162), 0);
    setRTurtle(PointMake(1506, 162), 0);
    setRTurtle(PointMake(1620, 480),1);


    _bullet = new Bullet;
    _bullet->init("ºÒµ¢ÀÌÀÌÆåÆ®", 10, 1000);
    fireTimer = 0;
    _item = new ItemManager;
    return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
    for (viEnemy = vEnemy.begin();viEnemy != vEnemy.end();++viEnemy)
    {
        RECT _rc=(*viEnemy)->getRC();
        //(*viEnemy)->update(getDistance(_mess->getPosi().x,_mess->getPosi().y,(_rc.left+_rc.right)/2,(_rc.bottom+_rc.top)/2));
        (*viEnemy)->update();
    }
    for (viRTurtle = vRTurtle.begin();viRTurtle != vRTurtle.end();++viRTurtle)
    {
        RECT _rc2 = (*viRTurtle)->getRC();
        (*viRTurtle)->update();
    }
    _bullet->update();
    _item->update(_mess);
    RTFire();
    findDirec();
}

void enemyManager::render(POINT camera)
{
    for (viEnemy = vEnemy.begin();viEnemy != vEnemy.end();++viEnemy)
    {
        (*viEnemy)->render(camera);
    }
    for (viRTurtle = vRTurtle.begin();viRTurtle != vRTurtle.end();++viRTurtle)
    {
        (*viRTurtle)->render(camera);
    }
    _bullet->render(camera);
    _item->render(camera);
}

void enemyManager::setGTurtle(POINT point)
{

        enemy* GT;
        GT = new greenTurtle;
        GT->init("³ì»ö°ÅºÏ", point, 1, 3);
        vEnemy.push_back(GT);
}

void enemyManager::setWorm(POINT point)
{
    enemy* Worm;
    Worm = new worm;
    Worm->init("¹ú·¹", point, 2, 1);
    vEnemy.push_back(Worm);
}

void enemyManager::setRTurtle(POINT point,int direction)
{
    rangedTurtle* RTurtle;
    RTurtle = new rangedTurtle;
    RTurtle->init("¿ø°Å¸®°ÅºÏ", point, 0, 1, "¿ø°Å¸®°ÅºÏ°ø°Ý",direction);
    vRTurtle.push_back(RTurtle);
}

void enemyManager::findDirec()
{
    for (int i=0;i<vEnemy.size();i++)
    {
        if (getDistance(_mess->getPosi().x, _mess->getPosi().y, (vEnemy[i]->getRC().left + vEnemy[i]->getRC().right) / 2, (vEnemy[i]->getRC().top + vEnemy[i]->getRC().bottom) / 2)<200)
        {
            if ((vEnemy[i]->getRC().left + vEnemy[i]->getRC().right) / 2 - _mess->getPosi().x > 0)vEnemy[i]->setDirec(RIGHT);
            else if ((vEnemy[i]->getRC().left + vEnemy[i]->getRC().right) / 2 - _mess->getPosi().x < 0)vEnemy[i]->setDirec(LEFT);
        }
    }
}
void enemyManager::removeEnemy(int arrNum)
{
    if (true) 
    { 
        cout << "½ÇÇàÁß";
        _item->ItemDrop((vEnemy[arrNum]->getRC().left + vEnemy[arrNum]->getRC().right) / 2, (vEnemy[arrNum]->getRC().top + vEnemy[arrNum]->getRC().bottom) / 2, RND->getInt(3));
    }
    SAFE_DELETE(vEnemy[arrNum]);
    vEnemy.erase(vEnemy.begin() + arrNum);
}

void enemyManager::removeRT(int arrNum)
{
    if (RND->getInt(100) >= 50)_item->ItemDrop((vRTurtle[arrNum]->getRC().left + vRTurtle[arrNum]->getRC().right) / 2, (vRTurtle[arrNum]->getRC().top + vRTurtle[arrNum]->getRC().bottom) / 2, RND->getInt(3));
    SAFE_DELETE(vRTurtle[arrNum]);
    vRTurtle.erase(vRTurtle.begin() + arrNum);

}

void enemyManager::RTFire()
{
  
    for (viRTurtle = vRTurtle.begin();viRTurtle != vRTurtle.end();++viRTurtle)
    {
        RECT rc = (*viRTurtle)->getRC();
        if ((_mess->getPosi().y < (*viRTurtle)->getRC().bottom + 50 && (_mess->getPosi().y > (*viRTurtle)->getRC().top - 50))
            &&( (*viRTurtle)->getDirec() == 0 && _mess->getPosi().x < rc.left|| ((*viRTurtle)->getDirec() == 1 && _mess->getPosi().x > rc.right))
            &&_mess->getPosi().x-((*viRTurtle)->getRC().left+(*viRTurtle)->getRC().right)/2<WINSIZEX)
        {
            (*viRTurtle)->ChangeImage("¿ø°Å¸®°ÅºÏ°ø°Ý");

            (*viRTurtle)->setIsFire(true);
            fireTimer++;
            if (fireTimer > 140)
            {
                if ((*viRTurtle)->getDirec() == 0)_bullet->fire(rc.left - 5, (rc.bottom + rc.top) / 2, 3, 0);
                if ((*viRTurtle)->getDirec() == 1)_bullet->fire(rc.right + 5, (rc.bottom + rc.top) / 2, 3, 1);
                fireTimer = 0;
            }
        }
        else
        {
            (*viRTurtle)->ChangeImage("¿ø°Å¸®°ÅºÏ");
            (*viRTurtle)->setIsFire(false);
        }
    }
}
