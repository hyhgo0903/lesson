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

	_ellipse = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);

	_isCollision = false;



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

	_rectangle = RectMakeCenter(_ptMouse.x, _ptMouse.y, 100, 100);

	if (isCollision(_ellipse, _rectangle)) _isCollision = true;
	else _isCollision = false;


}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================

	Rectangle(backDC, _rectangle);
	Ellipse(backDC, _ellipse);

	if (_isCollision)
	{
		TextOut(backDC, WINSIZEX / 2, 100, "충돌쓰", strlen("충돌쓰"));
	}
	else
	{

	}


	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

bool playGround::isCollision(RECT & rc1, RECT & rc2)
{
	int x = (rc1.right + rc1.left) / 2; // 원(rc1)중점x좌표
	int y = (rc1.bottom + rc1.top) / 2; // 원중점y좌표

	int radius = (rc1.right - rc1.left) / 2; // 반지름

	//충돌 부분
	if ((rc2.left <= x && x <= rc2.right) ||
		(rc2.top <= y && y <= rc2.bottom))
	{
		RECT rcTemp; // 사각형(rc2)기준으로 반지름만큼 좌우상하로 큰 가상의 사각형을 만든다.

		rcTemp.left = rc2.left - radius;
		rcTemp.top = rc2.top - radius;
		rcTemp.right = rc2.right + radius;
		rcTemp.bottom = rc2.bottom + radius;

		//임의의 넓힌 영역 안으로 중점이 들어오면 면충돌한거임
		if ((rcTemp.left <= x && x <= rcTemp.right) &&
			(rcTemp.top <= y && y <= rcTemp.bottom))
		{
			return true;
		}
	}
	else
	{
		if (getDistance(rc1, rc2.left, rc2.top)) return true;
		if (getDistance(rc1, rc2.right, rc2.top)) return true;
		if (getDistance(rc1, rc2.left, rc2.bottom)) return true;
		if (getDistance(rc1, rc2.right, rc2.bottom)) return true;
	}

	return false;
}

//어떤 점과 렉트 간의 거리 알아오는 함쑤
bool playGround::getDistance(RECT & rc, float x, float y)
{
	float deltaX = x - (rc.right + rc.left) / 2;
	float deltaY = y - (rc.bottom + rc.top) / 2;

	float distSquare = deltaX * deltaX + deltaY * deltaY;

	float radius = (rc.right - rc.left) / 2;

	float radiusSquare = radius * radius;

	if (radiusSquare < distSquare) return false; // 점(꼭지점)과 반지름 비교해서 반지름보다 작으면 충돌한것.

	return true;
}
