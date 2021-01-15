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

	_rc = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2, 100, 100);
	_speed = 0;

	_r = RND->getInt(255);
	_g = RND->getInt(255);
	_b = RND->getInt(255);

	return S_OK;
}

//�޸� ������ ����� �ϼ���
void playGround::release()
{
	
}

//����(���)�� ����� �ϼ���
void playGround::update()
{
	gameNode::update();

	_speed += 0.1f;


	if (_rc.right >= WINSIZEX - 50)
	{
		_isCrash = true;
		_r = RND->getInt(255);
		_g = RND->getInt(255);
		_b = RND->getInt(255);
	}
	if (_rc.left < 50)
	{	
		_isCrash = false;
		_r = RND->getInt(255);
		_g = RND->getInt(255);
		_b = RND->getInt(255);
		
	}

	if (!_isCrash)
	{
		_rc.left += _speed;
		_rc.right += _speed;
	}
	else
	{
		_rc.left -= _speed;
		_rc.right -= _speed;
	}
	

}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HBRUSH brush = CreateSolidBrush(RGB(_r, _g, _b));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
	Rectangle(hdc, _rc);
	SelectObject(hdc, oldBrush);
	DeleteObject(brush);
}
