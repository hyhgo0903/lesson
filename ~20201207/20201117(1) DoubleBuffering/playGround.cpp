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

	_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);


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

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_rc.left -= 5;
		_rc.right -= 5;
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_rc.left += 5;
		_rc.right += 5;
	}

}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//whiteness : 순백색의 도화지. backDC를 가려주는것

	//================ 위에 건들지 마라 ==============================

	HBRUSH brush = CreateSolidBrush(RGB(128, 83, 100));
	HBRUSH oldBrush = (HBRUSH)SelectObject(backDC, brush);
	Rectangle(backDC, _rc);
	SelectObject(backDC, oldBrush);
	DeleteObject(brush);


	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}
