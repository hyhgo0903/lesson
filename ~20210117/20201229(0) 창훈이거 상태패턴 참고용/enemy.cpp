#include "stdafx.h"
#include "enemy.h"



HRESULT enemy::init()
{
    return S_OK;
}

HRESULT enemy::init(const char* imgName, POINT point,int speed,int hp)
{
    img = IMAGEMANAGER->findImage(imgName);
    rc = RectMakeCenter(point.x, point.y, img->getFrameWidth(), img->getFrameHeight());
    count = 0;
    direc = 0;
    currentX = 0;
    timer = 100;
    Espeed = speed;
    HP = hp;
    gravity = 1;
    check = 3;
    alpha = 255;
    return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
    count++;
    if (count % 10 == 0)
    {
        if (direc == RIGHT)
        {
            img->setFrameX(currentX);
            currentX++;
            if (currentX > img->getMaxFrameX())
            {
                currentX = 0;
            }
        }
        if (direc == LEFT)
        {
            img->setFrameX(currentX);
            currentX--;
            if (currentX < 0)
            {
                currentX = img->getMaxFrameX();
            }
        }

    }
    timer--;
    if (timer < 0)
    {
        if (direc == RIGHT)direc = LEFT;
        else direc = RIGHT;
        timer = 100;
    }
    if (isGround)
    {
        gravity = 0;
    }
    if (!isGround)
    {
        gravity = 2;
    }
    check--;
    if (check < 0)
    {
        alpha = 255;
        check = 0;
    }
    move(Espeed);
}

void enemy::render(POINT camera)
{
    draw(camera);
}

void enemy::move(int speed)
{
    if (direc == RIGHT)
    {
        OffsetRect(&rc, -speed, gravity);
    }
    if (direc == LEFT)
    {
        OffsetRect(&rc, speed, gravity);
    }
}

void enemy::draw(POINT camera)
{
    img->alphaframeRender(getMemDC(), rc.left, rc.top,
        currentX, direc,alpha,camera);
    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
        Rectangle(getMemDC(),rc,camera);
    }
}

void enemy::ChangeImage(const char* img1)
{
    img = IMAGEMANAGER->findImage(img1);
}
