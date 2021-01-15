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

	_background = IMAGEMANAGER->addImage("������", "img2.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ù�", "siva_run.bmp", 832, 208, 8, 2, true, RGB(255, 0, 255));
	_siva = new image;
	_siva->init("siva_run.bmp", 832, 208, 8, 2, true, RGB(255, 0, 255)); // X �ε��� �� 0,1,2,3,4,5,6,7 Y�� 0,1
	_siva->setX(WINSIZEX / 2);
	_siva->setY(WINSIZEY / 2);
	_siva->setFrameY(0);

	_count = _index = 0;

	_direction = SIVA_RIGHT_IDLE;

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

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_siva->setY(_siva->getY() - 5);
		
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_siva->setY(_siva->getY() + 5);
		
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_siva->setX(_siva->getX() - 5);
		_direction = SIVA_LEFT_RUN;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_direction = SIVA_LEFT_IDLE;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_siva->setX(_siva->getX() + 5);
		_direction = SIVA_RIGHT_RUN;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_direction = SIVA_RIGHT_IDLE;
	}

	_count++;

	if (_count % 10 == 0)
	{

		switch (_direction)
		{
			case SIVA_LEFT_IDLE:
				if (_index <= 5) _index = 7;
				_siva->setFrameY(1);
				_siva->setFrameX(_index);
				_index--; // ������ Y�� 1�� ���·� ������ X _index�� 7 -> 6 -> 7 -> 6...
			break;
			case SIVA_RIGHT_IDLE:
				if (_index >= 2) _index = 0;
				_siva->setFrameY(0);
				_siva->setFrameX(_index);
				_index++; // ������ Y�� 0�� ���·� ������ X _index�� 0 -> 1 -> 0 -> 1...
			break;
			case SIVA_LEFT_RUN:
				if (_index <= -1) _index = 5;
				_siva->setFrameY(1);
				_siva->setFrameX(_index);
				_index--; // ������ Y�� 1�� ���·� ������ X _index�� 5 -> 4 -> 3 -> 2 -> 1 -> 0 -> 5 -> 4 -> 3 ...
			break;
			case SIVA_RIGHT_RUN:
				if (_index >= _siva->getMaxFrameX()) _index = 2;
				_siva->setFrameY(0);
				_siva->setFrameX(_index);
				_index++; // ������ Y�� 0�� ���·� ������ X _index�� 5 -> 4 -> 3 -> 2 -> 1 -> 0 -> 5 -> 4 -> 3 ...
			break;
		
		}
		
		
		_count = 0;
	}
	
}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	
	_background->render(backDC);
	_siva->frameRender(backDC, _siva->getX(), _siva->getY());
	
	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

