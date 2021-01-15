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

	for (int i = 0; i < 5; i++)
	{
		_box[i].rc = RectMakeCenter(100 + i * 200, WINSIZEY / 2 - 150, 100, 100);
		_box[i].isCheck = false;
		_box[i].isJoker = false;
	}
	//[0] ~ [4]

	_box[RND->getInt(5)].isJoker = true;



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

	//마우스 왼쪽 클릭 한 번 하면
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 5; i++)
		{
			if (PtInRect(&_box[i].rc, _ptMouse))
			{
				_box[i].isCheck = true;
			}
		}
	}
	
	for (int i = 0; i < 5; i++)
	{
		if (_box[i].isCheck && _box[i].isJoker)
		{
			_box[i].rc.top += 5;
			_box[i].rc.bottom += 5;
		}

		if (_box[i].rc.top > WINSIZEY)
		{
			this->init();
		}
	}

}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================

	for (int i = 0; i < 5; i++)
	{
		if (_box[i].isCheck && !_box[i].isJoker)
		{
			HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));
			FillRect(backDC, &_box[i].rc, brush);
			DeleteObject(brush);
		}
		else if (_box[i].isCheck && _box[i].isJoker)
		{
			HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
			FillRect(backDC, &_box[i].rc, brush); // old_brush귀찮으면
			DeleteObject(brush); 
		}
		else Rectangle(backDC, _box[i].rc);
	}


	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}
