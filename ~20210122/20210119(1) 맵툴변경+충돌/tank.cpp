#include "stdafx.h"
#include "tank.h"


tank::tank()
{
}


tank::~tank()
{
}

HRESULT tank::init()
{
	_direction = TANKDIRECTION_RIGHT;

	_image = IMAGEMANAGER->addFrameImage("tank", "tank.bmp", 0, 0, 256, 128, 8, 4, true, RGB(255, 0, 255));
	_speed = 100.0f;
	_x = _y = 16;
	return S_OK;
}

void tank::release()
{
}

void tank::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_direction = TANKDIRECTION_LEFT;
		tankMove();
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_direction = TANKDIRECTION_RIGHT;
		tankMove();
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_direction = TANKDIRECTION_UP;
		tankMove();
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_direction = TANKDIRECTION_DOWN;
		tankMove();
	}

	//tankMove();

}

void tank::render()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top);
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(getMemDC(), _rc);
}

void tank::tankMove()
{

	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = elapsedTime * _speed;

	switch (_direction)
	{
		case TANKDIRECTION_LEFT:
			_image->setFrameX(0);
			_image->setFrameY(3);
			if (_rc.left > 0) _x -= moveSpeed;
			_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
			collisionCheck(0, 2);
		break;
		case TANKDIRECTION_UP:
			_image->setFrameX(0);
			_image->setFrameY(0);
			if (_rc.top > 0) _y -= moveSpeed;
			_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
			collisionCheck(0, 1);
		break;
		case TANKDIRECTION_RIGHT:
			_image->setFrameX(0);
			_image->setFrameY(2);
			if (_rc.right < WINSIZEX) _x += moveSpeed;
			_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
			collisionCheck(1, 3);
		break;
		case TANKDIRECTION_DOWN:
			_image->setFrameX(0);
			_image->setFrameY(1);
			if (_rc.bottom < WINSIZEY) _y += moveSpeed;
			_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
			collisionCheck(2, 3);
		break;
	}
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(),_image->getFrameHeight());
}

void tank::setTankPosition()
{
	_rc = _tankMap->getTile()[_tankMap->getPosFirst()].rc;

	_x = (_rc.left + _rc.right) / 2;
	_y = (_rc.top + _rc.bottom) / 2;
}

void tank::collisionCheck(int x, int y)
{
	RECT rcCollision;	//임의의 충돌판정용 렉트
	int tileIndex;	//이동방향에 따라 타일속성 검출계산용(몇 바이 몇에 있다)
	int tileX, tileY;	//실제 탱크가 어느 타일에 위치하는지 계산용(left, top 기준일때)
	tileX = _rc.left / TILESIZE;
	tileY = _rc.top / TILESIZE;
	tileIndex = tileY * 20 + tileX;
	RECT temp;
	switch (x)
	{
	case 0:
		temp = _tankMap->getTile()[tileIndex].rc;
		if (IntersectRect(&rcCollision, &_rc, &temp) && _tankMap->getAttribute()[tileIndex] == ATTR_UNMOVE)
		{ // 왼쪽위
			int width = rcCollision.right - rcCollision.left;
			int height = rcCollision.bottom - rcCollision.top;
			if (width > height) _y += height;
			else _x += width;
			return;
		}
		break;
	case 1:
		if (tileIndex < 399)
		{ // 오른쪽위
			temp = _tankMap->getTile()[tileIndex + 1].rc;
			if (IntersectRect(&rcCollision, &_rc, &temp) && _tankMap->getAttribute()[tileIndex + 1] == ATTR_UNMOVE)
			{
				int width = rcCollision.right - rcCollision.left;
				int height = rcCollision.bottom - rcCollision.top;
				if (width > height) _y += height;
				else _x -= width;
				return;
			}
		}
		break;
	case 2:
		if (tileIndex < 380)
		{ // 왼쪽아래
			temp = _tankMap->getTile()[tileIndex + 20].rc;
			if (IntersectRect(&rcCollision, &_rc, &temp) && _tankMap->getAttribute()[tileIndex + 20] == ATTR_UNMOVE)
			{
				int width = rcCollision.right - rcCollision.left;
				int height = rcCollision.bottom - rcCollision.top;
				if (width > height) _y -= height;
				else _x += width;
				return;
			}
		}
		break;
	case 3:
		if (tileIndex < 379)
		{ // 오른쪽아래
			temp = _tankMap->getTile()[tileIndex + 21].rc;
			if (IntersectRect(&rcCollision, &_rc, &temp) && _tankMap->getAttribute()[tileIndex + 21] == ATTR_UNMOVE)
			{
				int width = rcCollision.right - rcCollision.left;
				int height = rcCollision.bottom - rcCollision.top;
				if (width > height) _y -= height;
				else _x -= width;
				return;
			}
		}
		break;
	}
	switch (y) // 위랑같음. 단, 어차피 0은 y로 안넣을거니까 없음
	{
	case 1:
		if (tileIndex < 399)
		{ // 오른쪽위
			temp = _tankMap->getTile()[tileIndex + 1].rc;
			if (IntersectRect(&rcCollision, &_rc, &temp) && _tankMap->getAttribute()[tileIndex + 1] == ATTR_UNMOVE)
			{
				int width = rcCollision.right - rcCollision.left;
				int height = rcCollision.bottom - rcCollision.top;
				if (width > height) _y += height;
				else _x -= width;
				return;
			}
		}
		break;
	case 2:
		if (tileIndex < 380)
		{ // 왼쪽아래
			temp = _tankMap->getTile()[tileIndex + 20].rc;
			if (IntersectRect(&rcCollision, &_rc, &temp) && _tankMap->getAttribute()[tileIndex + 20] == ATTR_UNMOVE)
			{
				int width = rcCollision.right - rcCollision.left;
				int height = rcCollision.bottom - rcCollision.top;
				if (width > height) _y -= height;
				else _x += width;
				return;
			}
		}
		break;
	case 3:
		if (tileIndex < 379)
		{ // 오른쪽아래
			temp = _tankMap->getTile()[tileIndex + 21].rc;
			if (IntersectRect(&rcCollision, &_rc, &temp) && _tankMap->getAttribute()[tileIndex + 21] == ATTR_UNMOVE)
			{
				int width = rcCollision.right - rcCollision.left;
				int height = rcCollision.bottom - rcCollision.top;
				if (width > height) _y -= height;
				else _x -= width;
				return;
			}
		}
		break;
	}
}
