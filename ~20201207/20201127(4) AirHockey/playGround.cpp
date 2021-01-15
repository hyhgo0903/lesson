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

	_board = new image; // ����� �ѵ� �׵θ����� (12,8) ~ (789,555) �� Ȱ��
	_board->init("image/board.bmp", 800, 560, false, RGB(0, 0, 0));

	_p1win = new image;
	_p1win->init("image/p1win.bmp", 800, 372, true, RGB(255, 0, 255));

	_p2win = new image;
	_p2win->init("image/p2win.bmp", 747, 560, true, RGB(255, 0, 255));

	_p1img = new image;
	_p1img->init("image/p1.bmp", 40, 40, true, RGB(255, 0, 255));
	_p2img = new image;
	_p2img->init("image/p2.bmp", 40, 40, true, RGB(255, 0, 255));
	_ballimg = new image;
	_ballimg->init("image/ball.bmp", 20, 20, true, RGB(255, 0, 255));

	_scoreP1 = _scoreP2 = _count = _p1isStanding = _p2isStanding = 0;
	_ballSpd = 0.;

	_ball = RectMakeCenter(400, WINSIZEY/2, 2*BALLRADIAN, 2 * BALLRADIAN);
	_p1 = RectMakeCenter(150, WINSIZEY / 2, 2 * PLAYERRADIAN, 2 * PLAYERRADIAN);
	_p2 = RectMakeCenter(650, WINSIZEY / 2, 2 * PLAYERRADIAN, 2 * PLAYERRADIAN);

	_ballAngle = rand() % 4 * PI / 2 + PI/4; // �ʱ� �ޱ۰� �������� (45,135,225,315�� �� �ϳ�)

	char str[256];
	for (int i = 0; i < 10; i++)
	{
		_number[i] = new image;
		sprintf_s(str, "image/number%d.bmp", i);
		_number[i]->init(str, 100, 100, true, RGB(255, 0, 255));
	}

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


	if (_scoreP1 < 10 && _scoreP2 < 10 &&_count < 202) _count++;
	if (_count == 200 && _ball.right > 400 && _ball.left < 400)
	{ // ��ó������ �о��ش� (�ÿ���å..)
		_ballSpd = BALLSPEED; 
	}

	if (_scoreP1 <10 && _scoreP2 <10 && _count>200)
	{

		playerMove();
		collide();
		ballMove();
		collideWall();
		scoring();
	}
}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	
	_board->render(backDC, 0, 0);

	_p1img->render(backDC, _p1.left, _p1.top);
	_p2img->render(backDC, _p2.left, _p2.top);
	_ballimg->render(backDC, _ball.left, _ball.top);

	if (_scoreP1 < 10 && _scoreP2 < 10 && _count < 100)
	{
		_number[2]->render(backDC, 350, WINSIZEY / 2-50);
	}
	else if (_scoreP1 < 10 && _scoreP2 < 10 &&_count < 200)
	{
		_number[1]->render(backDC, 350, WINSIZEY / 2 - 50);
	}
	if (_scoreP1 < 10 && _scoreP2 < 10)
	{
		_number[_scoreP1]->render(backDC, 0, WINSIZEY - 100);
		_number[_scoreP2]->render(backDC, 700, WINSIZEY - 100);
	}

	if (_scoreP1 == 10) _p1win->render(backDC, 0, 75 );
	if (_scoreP2 == 10) _p2win->render(backDC, 25, 0);

	sprintf_s(str, "P1�̵� : WASD");
	TextOut(backDC, 850, 120, str, strlen(str));
	sprintf_s(str, "P2�̵� : (NumPad)8456");
	TextOut(backDC, 820, 140, str, strlen(str));
	sprintf_s(str, "���� ��ġ�� : SPACE");
	TextOut(backDC, 810, 160, str, strlen(str));
	sprintf_s(str, "(���� ������������..)");
	TextOut(backDC, 820, 180, str, strlen(str));

	sprintf_s(str, "�����϶� ġ��");
	TextOut(backDC, 890, 520, str, strlen(str));
	sprintf_s(str, "���� �� ���� ����");
	TextOut(backDC, 865, 540, str, strlen(str));
	
	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::playerMove()
{
	if (KEYMANAGER->isStayKeyDown('W') && _p1.top>9)
	{
		OffsetRect(&_p1, 0, -5);
		if (_p1isStanding > 0) _p1isStanding--; //�ű�� �����ī��Ʈ ����
	}
	if (KEYMANAGER->isStayKeyDown('S') && _p1.bottom < 556)
	{OffsetRect(&_p1, 0, 5); if (_p1isStanding > 0) _p1isStanding--;}
	if (KEYMANAGER->isStayKeyDown('A') && _p1.left > 80)
	{OffsetRect(&_p1, -5, 0); if (_p1isStanding > 0) _p1isStanding--;}
	if (KEYMANAGER->isStayKeyDown('D') && _p1.right < 300)
	{OffsetRect(&_p1, 5, 0); if (_p1isStanding > 0) _p1isStanding--;}

	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD8) && _p2.top > 9)
	{OffsetRect(&_p2, 0, -5); if (_p2isStanding > 0) _p2isStanding--;}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD5) && _p2.bottom < 556)
	{OffsetRect(&_p2, 0, 5); if (_p2isStanding > 0) _p2isStanding--;}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD4) && _p2.left > 500)
	{OffsetRect(&_p2, -5, 0); if (_p2isStanding > 0) _p2isStanding--;}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD6) && _p2.right < 720)
	{OffsetRect(&_p2, 5, 0); if (_p2isStanding > 0) _p2isStanding--;}
	
	if (!KEYMANAGER->isStayKeyDown('W') &&
		!KEYMANAGER->isStayKeyDown('A') &&
		!KEYMANAGER->isStayKeyDown('S') &&
		!KEYMANAGER->isStayKeyDown('D') &&
		_p1isStanding <5) // WASD�ƹ��͵� �ȴ����� �ְ� ���ī��Ʈ�� 5�̸��϶�
	{		_p1isStanding++;	}

	if (!KEYMANAGER->isStayKeyDown(VK_NUMPAD8) &&
		!KEYMANAGER->isStayKeyDown(VK_NUMPAD5) &&
		!KEYMANAGER->isStayKeyDown(VK_NUMPAD4) &&
		!KEYMANAGER->isStayKeyDown(VK_NUMPAD6) &&
		_p2isStanding < 5) // WASD�ƹ��͵� �ȴ����� �ְ� ���ī��Ʈ�� 5�̸��϶�
	{
		_p2isStanding++;
	}


	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{ // ���ʿ� �����ų� �ϸ� ����å���� ���� ħ
		_ballSpd = BALLSPEED;
		_ballAngle = _ballAngle = rand() % 4 * PI / 2 + PI / 4;
	}

}

void playGround::ballMove()
{
	_ball.left += _ballSpd * cosf(_ballAngle);
	_ball.right += _ballSpd * cosf(_ballAngle);
	_ball.top += -_ballSpd*sinf(_ballAngle);
	_ball.bottom += -_ballSpd * sinf(_ballAngle);
}

void playGround::collide()
{
	if (getDistance((_p1.left + _p1.right) / 2, (_p1.top + _p1.bottom) / 2,
		(_ball.left + _ball.right) / 2, (_ball.top + _ball.bottom) / 2)
		<= BALLRADIAN + PLAYERRADIAN) // p1�̶� ���̶� �ε������
	{
		_ballSpd = BALLSPEED - _p1isStanding * 2; // ���ĵ����θ�ŭ ����� ħ
		_ballAngle = getAngle((_p1.left + _p1.right) / 2, (_p1.top + _p1.bottom) / 2,
			(_ball.left + _ball.right) / 2, (_ball.top + _ball.bottom) / 2);
	}

	if (getDistance((_p2.left + _p2.right) / 2, (_p2.top + _p2.bottom) / 2,
		(_ball.left + _ball.right) / 2, (_ball.top + _ball.bottom) / 2)
		<= BALLRADIAN + PLAYERRADIAN) // p2�� ���̶� �ε������
	{
		_ballSpd = BALLSPEED - _p2isStanding * 2;
		_ballAngle = getAngle((_p2.left + _p2.right) / 2, (_p2.top + _p2.bottom) / 2,
			(_ball.left + _ball.right) / 2, (_ball.top + _ball.bottom) / 2);
	}

}

void playGround::collideWall()
{
	if (_ball.top < 9)
	{
		_ball.top = 9; _ball.bottom = _ball.top + 2 * BALLRADIAN;
		_ballSpd *= 0.8; // 20%�� �ӵ��� ����
		_ballAngle = 2 * PI - _ballAngle;
	}
	if (_ball.bottom > 556)
	{
		_ball.bottom = 556; _ball.top = _ball.bottom - 2 * BALLRADIAN;
		_ballSpd *= 0.8;
		_ballAngle = 2 * PI - _ballAngle;
	}
	if (_ball.left < 13)
	{
		_ball.left = 13; _ball.right = _ball.left + 2 * BALLRADIAN;
		_ballSpd *= 0.8;
		_ballAngle = PI - _ballAngle;
	}
	if (_ball.right > 789)
	{
		_ball.right = 789; _ball.left = _ball.right - 2 * BALLRADIAN;
		_ballSpd *= 0.8;
		_ballAngle = PI - _ballAngle;
	}



}

void playGround::scoring()
{	
	//��(���) �ȿ� ��������

	if (getDistance(13,280,	(_ball.left+_ball.right)/2,
		(_ball.top + _ball.bottom) / 2)
		< BALLRADIAN+80)
	{
		_count = 0;
		_scoreP2++;
		_ball = RectMakeCenter(200, WINSIZEY / 2, 2 * BALLRADIAN, 2 * BALLRADIAN);
		_ballSpd = 0;
		_p1 = RectMakeCenter(150, WINSIZEY / 2, 2 * PLAYERRADIAN, 2 * PLAYERRADIAN);
		_p2 = RectMakeCenter(650, WINSIZEY / 2, 2 * PLAYERRADIAN, 2 * PLAYERRADIAN);
	}

	if (getDistance(789, 280,
		(_ball.left + _ball.right) / 2, (_ball.top + _ball.bottom) / 2)
		< BALLRADIAN + 80)
	{
		_count = 0;
		_scoreP1++;
		_ball = RectMakeCenter(600, WINSIZEY / 2, 2 * BALLRADIAN, 2 * BALLRADIAN);
		_ballSpd = 0;
		_p1 = RectMakeCenter(150, WINSIZEY / 2, 2 * PLAYERRADIAN, 2 * PLAYERRADIAN);
		_p2 = RectMakeCenter(650, WINSIZEY / 2, 2 * PLAYERRADIAN, 2 * PLAYERRADIAN);
	}


}