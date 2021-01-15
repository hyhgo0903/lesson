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
	tar.rc = { 0,0,0,0 };
	_timeCount = 0;
	_score = 0;
	_leftCount = 20;
	_isStand = _animation = false;
	_randNum = 0;
	_gravity = 0.4f;
	_direction = 1;
	
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
	OffsetRect(&_effect[0], 28, 0);
	OffsetRect(&_effect[1], 0, 28);
	OffsetRect(&_effect[2], 20, 20);
	OffsetRect(&_effect[3], -28, 0);
	OffsetRect(&_effect[4], -20, -20);
	OffsetRect(&_effect[5], 0, -28);
	OffsetRect(&_effect[6], 20, -20);
	OffsetRect(&_effect[7], -20, 20);
	
	if (_leftCount > 0) // ���Ƚ�� ���������
	{
		_timeCount++; // �ð���
		OffsetRect(&tar.rc , tar.x, -tar.y);
		tar.y -= _gravity;
		if (!_isStand && _timeCount >= 100) // 1�� ��ٷ���
		{
			_isStand = true;
			_timeCount = 0;
			_randNum = RND->getFromIntTo(100, 300); // ����
			if (_direction > 0 ) tar.rc = {-50,_randNum,0,_randNum+50};
			else tar.rc = { WINSIZEX,_randNum,WINSIZEX+50,_randNum + 50 };
			_randNum = RND->getFromIntTo(8, 16);  // x�ӵ�
			tar.x = (float)_randNum * _direction;
			_randNum = RND->getFromIntTo(8, 12);  // y�ӵ�
			tar.y = (float)_randNum;

			_direction *= -1;
		}

		if (_isStand && tar.rc.top > WINSIZEY)
		{
			_isStand = false;
			_timeCount = 0;
			_leftCount--;
			if (_leftCount == 0 & _highScore < _score) _highScore = _score;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _isStand)
		{
			_leftCount--;
			_timeCount = 0;
			if (PtInRect(&tar.rc, _ptMouse) && _isStand)
			{
				_animation = true;
				for(int i = 0; i < 8; i++)
				{
					_effect[i] = { tar.rc.left+15,tar.rc.top+15,tar.rc.right-15,tar.rc.bottom-15 };
				}
				_score++;
				tar.rc = { 0,0,0,0 };
			}

			if (_leftCount == 0 & _highScore < _score) _highScore = _score;
			_isStand = false;
		}
	}
	if (_leftCount == 0 && KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{ // �����
		this->init();
	}

}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	
	if (_leftCount > 0) { Rectangle(backDC, tar.rc); }
	for (int i = 0; i < 8; i++)
	{
		Rectangle(backDC,_effect[i]);
	}

	char str[256];	
	sprintf_s(str, "���� ��ȸ : %d (������ ��ȸ ���ư�)", _leftCount);
	TextOut(backDC, WINSIZEX - 300, 20, str, strlen(str));
	if (_leftCount > 0) {
		sprintf_s(str, "�ְ� ��� : %d", _highScore);
		TextOut(backDC, 50, 20, str, strlen(str));
		sprintf_s(str, "���� Ƚ�� : %d", _score);
		TextOut(backDC, 50, 40, str, strlen(str));
	}
	
	if (!_isStand && _leftCount > 0)
	{
		sprintf_s(str, "Ready? : %d", 10-_timeCount/10);
		TextOut(backDC, WINSIZEX/2-50, WINSIZEY/2, str, strlen(str));
	}
	if (_leftCount == 0)
	{
		sprintf_s(str, "���� ��� : %d", _score);
		TextOut(backDC, WINSIZEX / 2 - 60, WINSIZEY / 2 - 40, str, strlen(str));
		sprintf_s(str, "(�ְ� ��� : %d)", _highScore);
		TextOut(backDC, WINSIZEX / 2 - 64, WINSIZEY / 2 - 20, str, strlen(str));
		sprintf_s(str, "������Ϸ��� ENTER");
		TextOut(backDC, WINSIZEX / 2 - 90, WINSIZEY / 2, str, strlen(str));
	}

	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}
