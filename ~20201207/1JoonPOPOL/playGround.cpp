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

	srand(time(NULL));
	setImage();

	_ambul = RectMake(220 - 41, 550, 82, 156);

	_appearCount = _speed = _regenCount = _sideSpeed = _score = _loopX = _loopY = 0;
	_oil = 20.;

	for (int i = 0; i < 5; i++)
	{
		_taxi[i].appear = false;
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

	if (_oil <= 0 && KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{//���ͷ� �����
		this->init();
	}

	if (_oil > 0)
	{
		_oil -= 0.005f;// ���ϴ���
		if (_speed < 20) _speed += 0.05f; // 20���� ����
		if (_regenCount < REGENTIME) _regenCount++; // ����ī��Ʈ
		else taxiRegen(); // ����Ÿ�� ������ �ýø���

		for (int i = 0; i < 5; i++)
		{ // �ý� �̵�
			if (!_taxi[i].appear) continue; // �����Ѱ͸�
			_taxi[i].rc.top += _speed - _taxi[i].speed; // �����ǵ�-�ýý��ǵ� ���ӵ���ŭ �ٰ���
			_taxi[i].rc.bottom = _taxi[i].rc.top + 155;
			if (_taxi[i].rc.top > WINSIZEY)
			{// �ʹ����� �Ѿ����
				if (_score < 99) _score++;
				_taxi[i].appear = false; // �����ø��� �ٽ� �����ְ� ����
			}
		}

		if (_ambul.top > 550) // ���ڸ��� ������� ���ڸ��� �ڱ� �ӵ���ŭ ����.
		{
			_ambul.top -= _speed;
			_ambul.bottom = _ambul.top + 156;
		}

		if (_sideSpeed >= 0.2) // ���̵� ���ǵ尡 ������ �Ű��ش�(�����ߵ��� ���)
		{
			_ambul.left += _sideSpeed;
			_ambul.right = _ambul.left + 82;
			_sideSpeed -= 0.5f;
		}
		else if (_sideSpeed <= -0.2) // ���̵� ���ǵ尡 ������ �Ű��ش�(�����ߵ��� ���)
		{
			_ambul.left += _sideSpeed;
			_ambul.right = _ambul.left + 82;
			_sideSpeed += 0.5f;
		}

		if (_ambul.top <= 550) // �ں��� ���ڸ��� �ִٸ� �����ϴ¸��� ���ǵ常ŭ �Ű���
		{
			_loopY -= _speed;
		}		


		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _sideSpeed < 0.3 && _sideSpeed >-0.3 && _speed > 0 && _ambul.left > 22)
		{ // ���̵彺�ǵ尡 ���� ���� ���ǵ尡 ������ + ���ʹ� �������� ������ �������¸�
			_ambul.left -= 5;
			_ambul.right = _ambul.left + 82;
		} // ���̵彺�ǵ尡 ���� ���� ���ǵ尡 ������ + �����ʹ� �������� ������ �������¸�
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _sideSpeed < 0.3 && _sideSpeed>-0.3 && _speed > 0 && _ambul.right < 426)
		{
			_ambul.left += 5;
			_ambul.right = _ambul.left + 82;
		}


		collision();
		taxiTaxiCollision();
		gaugeAngle();
	}
	
}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================

	_backgroundImg->loopRender(backDC, &RectMake(0, 0, 450, 1466), _loopX, _loopY); // ���
	_ambulImg->render(backDC, _ambul.left, _ambul.top); // �ں�׸�
	for (int i = 0; i < 5; i++)
	{ // ��Ÿ���͸� �ý� �׷���
		if (!_taxi[i].appear) continue;
		_taxiImg->render(backDC, _taxi[i].rc.left, _taxi[i].rc.top);
	}
	_gauge->render(backDC, 470, 50); // ������

	HPEN pen = CreatePen(PS_DASHDOT, 1, RGB(255, 255, 255));
	HPEN oldPen = (HPEN)SelectObject(backDC, pen);
	LineMake(backDC, 595, 180, 595 + 100 * cosf(_speedAngle), 180 - 100 * sinf(_speedAngle));
	LineMake(backDC, 595, 270, 595 + 40 * cosf(_oilAngle), 270 - 40 * sinf(_oilAngle));
	SelectObject(backDC, oldPen);
	DeleteObject(pen); // ������ �ٴ�

	if (_oil <= 0)
	{ // ���Ͼ�����(���ӿ���) ���Ǿ��� ���̴� ���ͱ׸��� ����� �ݱ��
		_restartImg->render(backDC, 100, WINSIZEY/2 - 100);
	}
	_number[_score / 10]->render(backDC, 490, 400); // ���ھ�
	_number[_score % 10]->render(backDC, 590, 400);

	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::setImage() // �̹�������
{
	_backgroundImg = IMAGEMANAGER->addImage("����", "image/background.bmp", 450, 1466, false, RGB(255, 0, 255));
	_gauge = IMAGEMANAGER->addImage("������", "image/gauge.bmp", 262, 262, true, RGB(255, 0, 255));
	_taxiImg = IMAGEMANAGER->addImage("�ý�", "image/taxi.bmp", 87, 155, true, RGB(255, 0, 255));
	_ambulImg = IMAGEMANAGER->addImage("�ں�", "image/ambul.bmp", 82, 156, true, RGB(255, 0, 255));
	_restartImg = IMAGEMANAGER->addImage("���ӿ���", "image/restart.bmp", 251, 201, false, RGB(0,0,0));

	for (int i = 0; i < 10; i++) // ����
	{
		char str[256];
		sprintf_s(str, "image/number%d.bmp", i);
		_number[i] = IMAGEMANAGER->addImage(str, str, 100, 100, true, RGB(255, 0, 255));
	}
}

void playGround::taxiRegen()
{
	_appearCount = 0;
	for (int i = 0; i < 5; i++)
	{ // ȭ�鿡 �� � �����ִ��� ����
		if (_taxi[i].appear) _appearCount++;
	}
	if (_appearCount < 3) // 3�������� ��������
	{
		for (int i = 0; i < 5; i++)
		{
			if (_taxi[i].appear) continue; // �������̾����
			_taxi[i].appear = true;
			_taxi[i].speed = 9 + rand() % 6; // �ӵ� 9~14
			_randNum = (_randNum + 1 + rand() % 2 ) % 3; // �̷��� �ϸ� ���޾� �Ȼ���(2������ 3�̳� 4�� �Ǿ� 3�������� 0�̳� 1�� ��)
			switch (_randNum)
			{ // ���� �߰� ������ ��Ʈ����
			case 0: _taxi[i].rc = RectMake(36, -155, 87, 155);
				break;
			case 1: _taxi[i].rc = RectMake(180, -155, 87, 155);
				break;
			case 2: _taxi[i].rc = RectMake(325, -155, 87, 155);
				break;
			}
			_regenCount = 0; // ��������� ī��Ʈ ������ �극��ũ
			break;
		}
	}
}

void playGround::collision()
{
	for (int i = 0; i < 5; i++)
	{
		if (!_taxi[i].appear) continue; // �������̾����
		if (IntersectRect(&_temp, &_ambul, &_taxi[i].rc))
		{ // �ε�
			_oil-=2.; // ���ϰ���
			if (_temp.right - _temp.left <= _temp.bottom - _temp.top)
			{ // ���� �� ������ ������ ������
				_speed /= 3.0; // ����
				if (_ambul.left < _taxi[i].rc.left) // �ں��� ����
				{
					_sideSpeed = -7.; // ���ӵ� �������
				}
				else
				{//�ں��� ������
					_sideSpeed = 7.; // ���ӵ� �������
				}
				continue;
			}
			else
			{ // ���Ʒ��� ������
				_speed = -4.;
				_ambul.top = 551; // ������ �����༭ ���̵����ϰ� + ���ǵ� ����ް�
				_ambul.bottom = _ambul.top + 156;
			}
		}
	}
}

void playGround::taxiTaxiCollision()
{
	for (int i = 0; i < 5; i++)
	{
		if (!_taxi[i].appear) continue;
		for (int j = i + 1; j < 5; j++)
		{
			if (!_taxi[j].appear) continue;
			if (IntersectRect(&_temp, &_taxi[i].rc, &_taxi[j].rc))
			{ // �ý� ���鳢�� �������� �����ϱ�
				if (_taxi[i].speed > _taxi[j].speed) // i�� �� ������(�ڿ��� ������)
				{
					_taxi[i].speed -= 7; // ������ ������ �� ���δ�
					_taxi[i].rc.top = _taxi[j].rc.bottom + 1; // �����Ÿ� 1
					_taxi[i].rc.bottom = _taxi[i].rc.top + 155;
				}
				else // j�� �� ������(�ڿ��� ���� ��)
				{
					_taxi[j].speed -= 7;
					_taxi[j].rc.top = _taxi[i].rc.bottom + 1;
					_taxi[j].rc.bottom = _taxi[j].rc.top + 155;
				}
			}
		}

	}
}

void playGround::gaugeAngle()
{ // ���������� ���� ���
	if (_speed > 0)
	{
		_speedAngle = 7.0 / 6.0 * PI - PI*_speed/15.0;
	}
	else _speedAngle = 7.0 /6.0 * PI;
	_oilAngle = PI - PI / 6.0 - PI*(float)_oil / 30.0;
}


