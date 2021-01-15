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

	_rc = RectMakeCenter(WINSIZEX / 2 - 200, WINSIZEY / 2, 100, 100);
	_count = 0;



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

	_count++;
	// int count로 타이머 역할
	// 거대한 타이머 하나로 쓰자

	if (_count > 50)
	{
		_rc.left += 50;
		_rc.right += 50;

		_count = 0;
	}


}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================

	Rectangle(backDC, _rc);


	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}
