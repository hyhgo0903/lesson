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

	_day = new image;
	_day->init("image/day.bmp", 500, 889, false, RGB(0, 0, 0));

	_night = new image;
	_night->init("image/night.bmp", 500, 889, false, RGB(0, 0, 0));

	_background = _day;

	_count = 0;
	_isNight = false;

	_bird.x = WINSIZEX / 2 - 100;
	_bird.y = WINSIZEY / 2;
	_bird.rc = RectMakeCenter(_bird.x, _bird.y, 85, 60);
	_bird.jumpPower = _bird.gravity = 0;
	_bird.img = new image;
	_bird.img->init("������.bmp", 85, 60, true, RGB(255, 0, 255));

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

	{
		_count++;

		if (_count > 100)
		{
			_isNight == false ? _isNight = true : _isNight = false;

			_count = 0;
		}

		if (!_isNight) _background = _day;
		else _background = _night;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_bird.gravity = 0.1;
		_bird.jumpPower = 5;
	}

	_bird.y -= _bird.jumpPower;
	_bird.jumpPower -= _bird.gravity;
	
	_bird.rc = RectMakeCenter(_bird.x, _bird.y, 85, 60);

}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	
	_background->render(backDC, 0, 0);
	_bird.img->render(backDC, _bird.rc.left, _bird.rc.top);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(backDC, _bird.rc);
	}
	
	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}
