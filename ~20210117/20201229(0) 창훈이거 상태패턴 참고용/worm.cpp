#include "stdafx.h"
#include "worm.h"

HRESULT worm::init(const char* imgName, POINT point, int speed, int hp)
{
    enemy::init(imgName, point, speed, hp);
    return S_OK;
}

void worm::release()
{
    enemy::release();
}

void worm::update(float dis)
{
    enemy::update();
    distance = dis;
    move(Espeed);

}

void worm::render(POINT camera)
{
    enemy::render(camera);
}

void worm::move(int speed)
{
	if (distance < 300)
	{
		OffsetRect(&rc, 0, gravity);
	}
    if (direc == RIGHT)
    {
        OffsetRect(&rc, -speed, gravity);
    }
    if (direc == LEFT)
    {
        OffsetRect(&rc, speed, gravity);
    }

}
