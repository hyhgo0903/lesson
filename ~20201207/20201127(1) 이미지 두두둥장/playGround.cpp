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



	for (int i = 0; i < SNAKEBODY; i++)
	{
		//앵글과 시작위치는 랜덤하게 줘봤음. 굳이 꼭 이렇게 안해도 됩니당
		_snake[i].angle = (i == 0) ? RND->getFloat(PI2) : _snake[i - 1].angle;
		_snake[i].x = (i == 0) ? RND->getFromFloatTo(100, WINSIZEX - 100) : _snake[i - 1].x - cosf(_snake[i].angle) * (_snake[i].radius * 2 + _snake[i - 1].radius * 2);
		_snake[i].y = (i == 0) ? RND->getFromFloatTo(100, WINSIZEY - 100) : _snake[i - 1].y - (-sinf(_snake[i].angle) * (_snake[i].radius * 2 + _snake[i - 1].radius * 2));
		_snake[i].radius = 42;
		_snake[i].speed = 6.0f;
	}

	_background = new image;
	_background->init("메모리빌런.bmp", 614, 768, false, RGB(0, 0, 0));
	// 해당 폴더에 있어야.
	// 해당폴더의 폴더속에 있으면 폴더명\메모리빌런.bmp
	_donut = new image;
	_donut->init("mintDonut.bmp", 92, 84, true, RGB(255, 0, 255));

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

	//배열 0번째 인덱스가 머리겠죠
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _snake[0].angle += 0.08f;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _snake[0].angle -= 0.08f;

	snakeMove();

}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================

	_background->render(backDC, 0, 0);

	for (int i = 0; i < SNAKEBODY; i++)
	{
		_donut->render(backDC, _snake[i].x - _snake[i].radius,
			_snake[i].y - _snake[i].radius);

		//EllipseMakeCenter(backDC, _snake[i].x, _snake[i].y, _snake[i].radius * 2, _snake[i].radius * 2);
	}
	
	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::snakeMove()
{
	for (int i = 0; i < SNAKEBODY; i++)
	{
		//머리면
		if (i == 0)
		{
			_snake[i].x += cosf(_snake[i].angle) * _snake[i].speed;
			_snake[i].y += -sinf(_snake[i].angle) * _snake[i].speed;

			if (_snake[i].x - _snake[i].radius < 0)
			{
				_snake[i].x = _snake[i].radius;
				_snake[i].angle = PI - _snake[i].angle;
			}
			if (_snake[i].x + _snake[i].radius > WINSIZEX)
			{
				_snake[i].x = WINSIZEX - _snake[i].radius;
				_snake[i].angle = PI - _snake[i].angle;
			}
			if (_snake[i].y - _snake[i].radius < 0)
			{
				_snake[i].y = _snake[i].radius;
				_snake[i].angle = PI2 - _snake[i].angle;
			}
			if (_snake[i].y + _snake[i].radius > WINSIZEY)
			{
				_snake[i].y = WINSIZEY - _snake[i].radius;
				_snake[i].angle = PI2 - _snake[i].angle;
			}

		}
		else //몸통이면
		{
			//지름보다 빗변값이 커졌다 == 회전했다
			if (_snake[i].radius * 2 < getDistance(_snake[i].x, _snake[i].y, _snake[i - 1].x, _snake[i - 1].y))
			{
				//바로 내 앞사람의 각도를 가져온다
				_snake[i].angle = getAngle(_snake[i].x, _snake[i].y, _snake[i - 1].x, _snake[i - 1].y);

				//앞에 머리 또는 몸통의 반지름 만큼 더 밀어줘서 값손실 막는다 이 두 줄 주석 처리하고 돌리면 어그러짐
				_snake[i].x = _snake[i - 1].x - (cosf(_snake[i].angle) * (_snake[i].radius + _snake[i - 1].radius));
				_snake[i].y = _snake[i - 1].y - (-sinf(_snake[i].angle) * (_snake[i].radius + _snake[i - 1].radius));
			}
			_snake[i].x += cosf(_snake[i].angle) * _snake[i].speed;
			_snake[i].y += -sinf(_snake[i].angle) * _snake[i].speed;
		}
	}
}
