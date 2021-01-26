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
	RECT rcCollision;	//������ �浹������ ��Ʈ
	int tileIndex;	//�̵����⿡ ���� Ÿ�ϼӼ� �������(�� ���� � �ִ�)
	int tileX, tileY;	//���� ��ũ�� ��� Ÿ�Ͽ� ��ġ�ϴ��� ����(left, top �����϶�)
	tileX = _rc.left / TILESIZE;
	tileY = _rc.top / TILESIZE;
	tileIndex = tileY * 20 + tileX;
	RECT temp;
	switch (x)
	{
	case 0:
		temp = _tankMap->getTile()[tileIndex].rc;
		if (IntersectRect(&rcCollision, &_rc, &temp) && _tankMap->getAttribute()[tileIndex] == ATTR_UNMOVE)
		{ // ������
			int width = rcCollision.right - rcCollision.left;
			int height = rcCollision.bottom - rcCollision.top;
			if (width > height) _y += height;
			else _x += width;
			return;
		}
		break;
	case 1:
		if (tileIndex < 399)
		{ // ��������
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
		{ // ���ʾƷ�
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
		{ // �����ʾƷ�
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
	switch (y) // ��������. ��, ������ 0�� y�� �ȳ����Ŵϱ� ����
	{
	case 1:
		if (tileIndex < 399)
		{ // ��������
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
		{ // ���ʾƷ�
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
		{ // �����ʾƷ�
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
