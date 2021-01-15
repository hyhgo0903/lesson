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

	_rc1 = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 200, 200);

	

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

	_rc2 = RectMakeCenter(_ptMouse.x, _ptMouse.y, 100, 100);
	
	x = (_rc2.right + _rc2.left) / 2 - (_rc1.right + _rc1.left) / 2;
	y = (_rc2.top + _rc2.bottom) / 2 - (_rc1.top + _rc1.bottom) / 2;
	// if (x<0) x = -x; <<했었는데 어차피 제곱할거라 필요없음
	h = x * x + y * y;

	//비교용 반지름끼리 합의 제곱
	rr = (_rc2.right - _rc2.left)/2 + (_rc1.right - _rc1.left)/2;
	rr *= rr;

}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================

	if (h < rr) // 충돌 한것
	{
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(backDC, brush);
		Ellipse(backDC, _rc1);
		Ellipse(backDC, _rc2);
		SelectObject(backDC, oldBrush);
		DeleteObject(brush);		
	}
	else
	{
		Ellipse(backDC, _rc1);
		Ellipse(backDC, _rc2);
	}


	
	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}
