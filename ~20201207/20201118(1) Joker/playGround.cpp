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

//�޸� ������ ����� �ϼ���
void playGround::release()
{
	gameNode::release();


}

//����(���)�� ����� �ϼ���
void playGround::update()
{
	gameNode::update();

	//���콺 ���� Ŭ�� �� �� �ϸ�
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

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================

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
			FillRect(backDC, &_box[i].rc, brush); // old_brush��������
			DeleteObject(brush); 
		}
		else Rectangle(backDC, _box[i].rc);
	}


	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}
