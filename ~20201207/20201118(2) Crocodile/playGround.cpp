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

	upperItmom = RectMake(25, WINSIZEY / 2-75, 500, 50);

	for (int i = 0; i < 20; i++)
	{
		if (i<10) _tooth[i].rc = RectMakeCenter(50 + i * 50, WINSIZEY / 2, 50, 50);
		else _tooth[i].rc = RectMakeCenter(50 + (i-10) * 50, WINSIZEY / 2+200, 50, 50);	
		_tooth[i].isClicked = false;
		_tooth[i].isRotten = false;
	}
	_isAngry = false;
	_down = 1;

	_tooth[RND->getInt(20)].isRotten = true;



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
		
	if (!_isAngry)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{//���콺 ���� Ŭ�� �� �� �ϸ�
			for (int i = 0; i < 20; i++)
			{
				if (PtInRect(&_tooth[i].rc, _ptMouse))
				{
					_tooth[i].isClicked = true;
				}
			}
		}
		for (int i = 0; i < 20; i++)
		{
			if (_tooth[i].isClicked && !_tooth[i].isRotten)
			{
				if (i < 10 && _tooth[i].rc.bottom > WINSIZEY / 2)
				{
					_tooth[i].rc.bottom -= 5;
				}
				else if (i >= 10 && _tooth[i].rc.top < WINSIZEY / 2 + 200)
				{
					_tooth[i].rc.top += 5;
				}
			}
			else if (_tooth[i].isClicked && _tooth[i].isRotten)
			{
				_isAngry = true;
			}
		}
	}
	if (_isAngry)
	{
		upperItmom.top += _down * 5;
		upperItmom.bottom += _down * 5;
		for (int i = 0; i < 10; i++)
		{
			_tooth[i].rc.top += _down * 5;
			_tooth[i].rc.bottom += _down * 5;
		}
		if (upperItmom.bottom <= WINSIZEY / 2 && _down==-1)
		{
			_down *= -1;
		}
		else if (upperItmom.bottom >= WINSIZEY / 2 + 125 && _down == 1)
		{
			_down *= -1;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_isAngry = false;
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

	for (int i = 0; i < 20; i++)
	{
		if (_tooth[i].isClicked && !_tooth[i].isRotten)
		{
			Rectangle(backDC, _tooth[i].rc);
		}
		else if (_tooth[i].isClicked && _tooth[i].isRotten)
		{
			HBRUSH brush = CreateSolidBrush(RGB(100, 100, 100));
			FillRect(backDC, &_tooth[i].rc, brush);
			DeleteObject(brush);
		}
		else Rectangle(backDC, _tooth[i].rc);
	}
	Rectangle(backDC, upperItmom);
	Rectangle(backDC, 25, WINSIZEY / 2 + 225, 525, WINSIZEY / 2 + 275);
	
	MoveToEx(backDC, upperItmom.left, upperItmom.top, NULL);
	LineTo(backDC, 600, WINSIZEY / 2 - 200);
	LineTo(backDC, 1000, WINSIZEY / 2 - 200); // ������ �� ��
	LineTo(backDC, upperItmom.right, upperItmom.top);
	LineTo(backDC, 1000, WINSIZEY / 2 - 200);
	LineTo(backDC, upperItmom.right, upperItmom.bottom);
	LineTo(backDC, 1000, WINSIZEY / 2 - 200);
	LineTo(backDC, upperItmom.right, WINSIZEY / 2 + 275);
	LineTo(backDC, 1000, WINSIZEY / 2 - 200);
	LineTo(backDC, upperItmom.right, WINSIZEY / 2 + 225);

	Ellipse(backDC, 550, WINSIZEY / 2 - 175, 650, WINSIZEY / 2 - 275);
	Ellipse(backDC, 950, WINSIZEY / 2 - 175, 1050, WINSIZEY / 2 - 275);
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(backDC, brush);
	Ellipse(backDC, 555, WINSIZEY / 2 - 185, 605, WINSIZEY / 2 - 235);
	Ellipse(backDC, 955, WINSIZEY / 2 - 185, 1005, WINSIZEY / 2 - 235);
	SelectObject(backDC, oldBrush);
	DeleteObject(brush);

	char str[256];
	sprintf_s(str, "�Ⱬ�� ����. ESC�� �� �� �ֽ��ϴ�.");
	TextOut(backDC, 50, 50, str, strlen(str));

	sprintf_s(str, "�丮���� �Ǿ�");
	TextOut(backDC, upperItmom.left+10, upperItmom.top+10, str, strlen(str));
	sprintf_s(str, "�������� �Ǿ�");
	TextOut(backDC, upperItmom.right-110, upperItmom.top+10, str, strlen(str));
	sprintf_s(str, "�������� �Ǿ�");
	TextOut(backDC, 500, upperItmom.top-70, str, strlen(str));

	if (_isAngry)
	{
		sprintf_s(str, "�����Ϸ��� ENTER");
		TextOut(backDC, WINSIZEX/2, WINSIZEY/ 2, str, strlen(str));
	}

	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}
