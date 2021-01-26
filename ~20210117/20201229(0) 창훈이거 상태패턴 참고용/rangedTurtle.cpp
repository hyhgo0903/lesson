#include "stdafx.h"
#include "rangedTurtle.h"

HRESULT rangedTurtle::init(const char* imgName, POINT point, int speed, int hp,const char* imgName2,int direction)
{
	enemy::init(imgName, point, speed, hp);
	img2 = IMAGEMANAGER->findImage(imgName2);
    fireCount = 0;
    direc = direction;
	return S_OK;
}

void rangedTurtle::release()
{
	enemy::release();
}

void rangedTurtle::update()
{
	image* temp;
	if (isFire)
	{
		temp = img;
		img = img2;
		img2 = img;
	}
    count++;
    if (count % 35 == 0)
    {
        if (direc == RIGHT)
        {
            img->setFrameX(currentX);
            currentX++;
            if (currentX >= img->getMaxFrameX())
            {
                fireCount++;
                currentX = 0;
            }
        }
        if (direc == LEFT)
        {
            img->setFrameX(currentX);
            currentX--;
            if (currentX <= 0)
            {
                if(isFire)fireCount++;
                currentX = img->getMaxFrameX();

            }
        }

    }
}

void rangedTurtle::render(POINT camera)
{
	enemy::render(camera);
}

void rangedTurtle::move()
{
	enemy::move(0);
}


