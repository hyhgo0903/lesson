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

	_background = IMAGEMANAGER->addImage("깜장이", "background.bmp", 4725, WINSIZEY, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("시바", "siva_run.bmp", 832, 208, 8, 2, true, RGB(255, 0, 255));
	_siva = new image;
	_siva->init("siva_run.bmp", 832, 208, 8, 2, true, RGB(255, 0, 255));
	_siva->setX(WINSIZEX / 2 - 200);
	_siva->setY(WINSIZEY / 2);
	_siva->setFrameY(0);

	_count = _index = 0;

	_direction = SIVA_RIGHT_IDLE;

	_miniMap = RectMake(0, 0, 200, 200);

	_cameraX = 0;

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
		
		if (_siva->getX() >= WINSIZEX / 2)
		{
			_cameraX -= 5;
		}
		else
		{
			_siva->setX(_siva->getX() + 5);
			_direction = SIVA_RIGHT_RUN;
		}
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
				_index--;
			break;
			case SIVA_RIGHT_IDLE:
				if (_index >= 2) _index = 0;
				_siva->setFrameY(0);
				_siva->setFrameX(_index);
				_index++;
			break;
			case SIVA_LEFT_RUN:
				if (_index <= -1) _index = 5;
				_siva->setFrameY(1);
				_siva->setFrameX(_index);
				_index--;
			break;
			case SIVA_RIGHT_RUN:
				if (_index >= _siva->getMaxFrameX()) _index = 2;
				_siva->setFrameY(0);
				_siva->setFrameX(_index);
				_index++;
			break;
		
		}
		
		
		_count = 0;
	}

	_miniP = RectMake(_siva->getX() / 4,
		_siva->getY() / 4,
		_siva->getFrameWidth() / 4,
		_siva->getFrameHeight() / 4);



	
}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	
	_background->render(backDC, _cameraX, 0);
	_siva->frameRender(backDC, _siva->getX(), _siva->getY());
	
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(backDC, _miniMap);
		Rectangle(backDC, _miniP);
	}


	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

