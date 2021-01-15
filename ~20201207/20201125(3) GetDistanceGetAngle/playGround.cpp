#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ����� �ϼ���
HRESULT playGround::init()
{
	gameNode::init();

	_cannon.angle = PI / 2;
	_cannon.cannon = 100;
	_cannon.radius = 100;
	_cannon.center.x = WINSIZEX / 2;
	_cannon.center.y = WINSIZEY;

	for (int i = 0; i < BULLETMAX; i++)
	{
		_bullet[i].speed = 5;
		_bullet[i].radius = 20;
		_bullet[i].isFire = false;
		_bullet[i].gravity = 0;
	}


	return S_OK;
}

//�޸� ������ ����� �ϼ���
void playGround::release()
{
	gameNode::release();


}

//����(���)�� ����� �ϼ���
void playGround::update()
{
	gameNode::update();

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _cannon.angle <= 3.04) _cannon.angle += 0.04f;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _cannon.angle >= 0.08) _cannon.angle -= 0.04f;
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) bulletFire();

	//���� ���� (���� ��ȣ�� �񿡼� �ǳ����� �����ϸ鼭 ���ƴٴϴ� �װ�)
	_cannon.cannonEnd.x = cosf(_cannon.angle) * _cannon.cannon + _cannon.center.x;
	_cannon.cannonEnd.y = -sinf(_cannon.angle) * _cannon.cannon + _cannon.center.y;


	bulletMove();

	collision();

}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================

	EllipseMakeCenter(backDC, _cannon.center.x, _cannon.center.y, 100, 100);
	LineMake(backDC, _cannon.center.x, _cannon.center.y, _cannon.cannonEnd.x, _cannon.cannonEnd.y);

	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bullet[i].isFire) continue;
		EllipseMakeCenter(backDC, _bullet[i].x, _bullet[i].y, _bullet[i].radius * 2, _bullet[i].radius * 2);
		
	}
	
	
	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::bulletFire()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (_bullet[i].isFire) continue;

		_bullet[i].isFire = true;
		_bullet[i].x = cosf(_cannon.angle) * (_cannon.cannon + 3) + _cannon.center.x;
		_bullet[i].y = -sinf(_cannon.angle) * (_cannon.cannon + 3) + _cannon.center.y;
		_bullet[i].angle = _cannon.angle;

		break;
	}
}


void playGround::bulletMove()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bullet[i].isFire) continue;
		
		_bullet[i].x += cosf(_bullet[i].angle) * _bullet[i].speed;
		_bullet[i].y += -sinf(_bullet[i].angle) * _bullet[i].speed;

		//ȭ�� �������� ������
		if (_bullet[i].x - _bullet[i].radius < 0)
		{
			_bullet[i].x = _bullet[i].radius;
			_bullet[i].angle = PI - _bullet[i].angle;
		}

		//ȭ�� ���������� ������
		if (_bullet[i].x + _bullet[i].radius > WINSIZEX)
		{
			_bullet[i].x = WINSIZEX - _bullet[i].radius;
			_bullet[i].angle = PI - _bullet[i].angle;
		}

		//ȭ�� �������� ������
		if (_bullet[i].y - _bullet[i].radius < 0)
		{
			_bullet[i].y = _bullet[i].radius;
			_bullet[i].angle = 2 * PI - _bullet[i].angle;
		}

		//ȭ�� �Ʒ������� ������
		if (_bullet[i].y + _bullet[i].radius > WINSIZEY)
		{
			_bullet[i].y = WINSIZEY - _bullet[i].radius;
			_bullet[i].angle = 2 * PI - _bullet[i].angle;
		}

	}
}

void playGround::collision()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		for (int j = i + 1; j < BULLETMAX; j++)
		{
			if (_bullet[i].radius * 2 < getDistance(_bullet[i].x, _bullet[i].y, _bullet[j].x, _bullet[j].y)) continue;

			_bullet[i].angle = getAngle(_bullet[j].x, _bullet[j].y, _bullet[i].x, _bullet[i].y);
			_bullet[j].angle = getAngle(_bullet[i].x, _bullet[i].y, _bullet[j].x, _bullet[j].y);
			// get�ޱ� ���� �߿�
		}
	}
}
