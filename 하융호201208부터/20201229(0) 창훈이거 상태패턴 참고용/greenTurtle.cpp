#include "stdafx.h"
#include "greenTurtle.h"

void greenTurtle::draw(POINT camera)
{
	alpha = 255;
	img->alphaframeRender(getMemDC(), rc.left, rc.top, currentX, direc,alpha,camera);
	time++;
	if (time > 3)alpha = 255;
}
