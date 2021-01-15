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

	_day = new image;
	_day->init("image/day500600.bmp", 500, 600, false, RGB(0, 0, 0));

	_night = new image;
	_night->init("image/night500600.bmp", 500, 600, false, RGB(0, 0, 0));

	_background = _day;

	_count = _score = 0;
	_isNight = _isDead = false;

	_bird.x = WINSIZEX / 2 - 100;
	_bird.y = WINSIZEY / 2;
	_bird.jumpPower = 0;
	_bird.gravity = 0.1;
	_alki = new image;
	_alki->init("image/alki.bmp", 100, 100, true, RGB(255, 0, 255));
	_alki2 = new image;
	_alki2->init("image/alki2.bmp", 100, 100, true, RGB(255, 0, 255));
	_restart = new image;
	_restart->init("image/restart.bmp", 251, 201, false, RGB(0, 0, 0));

	char str[256];
	for (int i = 0; i < 10; i++)
	{
		_number[i] = new image;
		sprintf_s(str, "image/number%d.bmp", i);
		_number[i]->init(str, 100, 100, true, RGB(255, 0, 255));
	}

	_uppipe = new image;
	_uppipe->init("image/uppipe100600.bmp", 100, 600, true, RGB(255, 0, 255));
	_downpipe = new image;
	_downpipe->init("image/downpipe100600.bmp", 100, 600, true, RGB(255, 0, 255));

	_upPipeWitch = rand() % 300 - 600;
	_upPipeRc[0] = RectMake(WINSIZEX, _upPipeWitch, 100, 600); // -600~-299�̹Ƿ� ȭ�鿣 0~300����
	_downPipeRc[0] = RectMake(WINSIZEX, _upPipeWitch + 900, 100, 600); // ���� 300���ݵΰ� �̰�
	_upPipeWitch = rand() % 300 - 600;
	_upPipeRc[1] = RectMake(WINSIZEX+300, _upPipeWitch, 100, 600);
	_downPipeRc[1] = RectMake(WINSIZEX+300, _upPipeWitch + 900, 100, 600);

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
	if (_isDead && KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{ // �׾����� ���ͷ� �ʱ�ȭ
		this->init();
	}

	if (!_isDead)
	{
		_count++;

		if (_count > 300)
		{ // �����ð��� �����Ͻ� ����
			_isNight == false ? _isNight = true : _isNight = false;

			_count = 0;
		}

		if (!_isNight) _background = _day;
		else _background = _night;



		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{ // ����
			_bird.jumpPower = 5;
		}

		_bird.y -= _bird.jumpPower;		_bird.jumpPower -= _bird.gravity;
		// y�� �̵����� + �߷�����

		_bird.rc = RectMakeCenter(_bird.x, _bird.y, 77, 57);
		_bird.rc2 = RectMakeCenter(_bird.x, _bird.y, 57, 77);
		// ���� ��������(���簢�浹�Ⱦ���) �簢�� �ΰ��� �̿�
		// ���� ��������(���簢�浹�Ⱦ���) �簢�� �ΰ��� �̿�

		for (int i = 0; i < 2; i++)
		{ // ��� ����
			_upPipeRc[i].left -= 3; _upPipeRc[i].right -= 3;
			_downPipeRc[i].left -= 3; _downPipeRc[i].right -= 3;
			if (_upPipeRc[i].right < 0)
			{
				_score++;
				if (_score > 99) _score -= 100; // Ȥ�� ������� 0���� �ʱ�ȭ
				_upPipeWitch = rand() % 300 - 600; // -600~-299�̹Ƿ� ȭ�鿣 0~300����
				_upPipeRc[i] = RectMake(WINSIZEX, _upPipeWitch, 100, 600);
				_downPipeRc[i] = RectMake(WINSIZEX, _upPipeWitch + 900, 100, 600); // ����300�̰�
			}
		}
		
		if (_bird.rc.top > WINSIZEY) _isDead = true;
		for (int i = 0; i < 2; i++)
		{ // �ε�����
			if (IntersectRect(&_temp, &_upPipeRc[i], &_bird.rc)) _isDead = true;
			if (IntersectRect(&_temp, &_downPipeRc[i], &_bird.rc)) _isDead = true;
			if (IntersectRect(&_temp, &_upPipeRc[i], &_bird.rc2)) _isDead = true;
			if (IntersectRect(&_temp, &_downPipeRc[i], &_bird.rc2)) _isDead = true;
		}
	}
}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	
	_background->render(backDC, 0, 0);
	if (_bird.jumpPower > 0)
	{ // ���ΰ��� ��Ű�� ����
		_alki->render(backDC, _bird.rc.left-12, _bird.rc.top-20);	}
	else
	{ // �ƴϸ� ��ǥ��
		_alki2->render(backDC, _bird.rc.left - 12, _bird.rc.top - 20);	}

	for (int i = 0; i < 2; i++)
	{		_uppipe->render(backDC, _upPipeRc[i].left, _upPipeRc[i].top);
		_downpipe->render(backDC, _downPipeRc[i].left, _downPipeRc[i].top);	}
	// �����ڸ��� 10���� �� 1�� �ڸ��� 10���� ������. 100�� �ڸ��� �׷��Ű��� �ʾƼ� �ȸ���
	_number[_score / 10]->render(backDC, WINSIZEX - 200, 20);
	_number[_score % 10]->render(backDC, WINSIZEX - 100, 20);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{ // �浹����
		Rectangle(backDC, _bird.rc);		Rectangle(backDC, _bird.rc2);
	}

	if (_isDead)
	{ // �׿���
		_restart->render(backDC, WINSIZEX/2 - 125, WINSIZEY/2 -100);
	}
	
	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}
