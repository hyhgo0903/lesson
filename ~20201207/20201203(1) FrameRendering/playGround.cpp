#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요
HRESULT playGround::init()
{
	gameNode::init();

	_background = IMAGEMANAGER->addImage("깜장이", "img2.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("시바", "siva_run.bmp", 832, 208, 8, 2, true, RGB(255, 0, 255));
	_siva = new image;
	_siva->init("siva_run.bmp", 832, 208, 8, 2, true, RGB(255, 0, 255)); // X 인덱스 는 0,1,2,3,4,5,6,7 Y는 0,1
	_siva->setX(WINSIZEX / 2);
	_siva->setY(WINSIZEY / 2);
	_siva->setFrameY(0);

	_count = _index = 0;

	_direction = SIVA_RIGHT_IDLE;

	return S_OK;
}

//메모리 해제는 여기다 하세요
void playGround::release()
{
	gameNode::release();


}

//연산(계산)은 여기다 하세요
void playGround::update()
{
	gameNode::update();

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_siva->setY(_siva->getY() - 5);
		
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_siva->setY(_siva->getY() + 5);
		
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_siva->setX(_siva->getX() - 5);
		_direction = SIVA_LEFT_RUN;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_direction = SIVA_LEFT_IDLE;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_siva->setX(_siva->getX() + 5);
		_direction = SIVA_RIGHT_RUN;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_direction = SIVA_RIGHT_IDLE;
	}

	_count++;

	if (_count % 10 == 0)
	{

		switch (_direction)
		{
			case SIVA_LEFT_IDLE:
				if (_index <= 5) _index = 7;
				_siva->setFrameY(1);
				_siva->setFrameX(_index);
				_index--; // 프레임 Y는 1인 상태로 프레임 X _index는 7 -> 6 -> 7 -> 6...
			break;
			case SIVA_RIGHT_IDLE:
				if (_index >= 2) _index = 0;
				_siva->setFrameY(0);
				_siva->setFrameX(_index);
				_index++; // 프레임 Y는 0인 상태로 프레임 X _index는 0 -> 1 -> 0 -> 1...
			break;
			case SIVA_LEFT_RUN:
				if (_index <= -1) _index = 5;
				_siva->setFrameY(1);
				_siva->setFrameX(_index);
				_index--; // 프레임 Y는 1인 상태로 프레임 X _index는 5 -> 4 -> 3 -> 2 -> 1 -> 0 -> 5 -> 4 -> 3 ...
			break;
			case SIVA_RIGHT_RUN:
				if (_index >= _siva->getMaxFrameX()) _index = 2;
				_siva->setFrameY(0);
				_siva->setFrameX(_index);
				_index++; // 프레임 Y는 0인 상태로 프레임 X _index는 5 -> 4 -> 3 -> 2 -> 1 -> 0 -> 5 -> 4 -> 3 ...
			break;
		
		}
		
		
		_count = 0;
	}
	
}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	
	_background->render(backDC);
	_siva->frameRender(backDC, _siva->getX(), _siva->getY());
	
	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

