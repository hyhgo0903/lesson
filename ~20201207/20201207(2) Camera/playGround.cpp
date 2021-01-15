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

	_background = IMAGEMANAGER->addImage("������", "background.bmp", 1440, 2096, false, RGB(255, 0, 255));	
	// ���ŷӰ����� �ʻ����� stdafx.h���� �°� �������ּ���

	_siva = IMAGEMANAGER->addFrameImage("�ù�", "siva_run.bmp", 832, 208, 8, 2, true, RGB(255, 0, 255));
	_siva->setFrameY(0);
	_sivaRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100,100);
	_enemy = RectMake(WINSIZEX - 110, WINSIZEY - 110, 100, 100);
	_count = _index = _vibrateCount = 0;

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
	siva(); // �盏�� �ۼ��Ͻ� �ù�. ������ �ؿ� ����

	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		CAMERAMANAGER->vibrate();
	}
	// �����̽� �������¸� ��鸲

	// �����Լ� Ȱ�� �� (���ؾȰ��� ��ŵ)
	if (IntersectRect(&_temp, &_sivaRc, &_enemy))
	{
		_enemy = { 0,0,0,0 }; // �ε����� ���� ġ�쵵�� ����
		_vibrateOn = true; // ���� on
		_vibrateCount = 0; // ���� ī��Ʈ �ʱ�ȭ
	}
	if (_vibrateOn) // ���� on�̸�
	{
		_vibrateCount++; // ����ī��Ʈ�� �ö�
		CAMERAMANAGER->vibrate(); // �����Լ�
		if (_vibrateCount > 50) _vibrateOn = false; // ������ �̻��̸� ���ش�
	}
	// ��� : �����Ⱓ �����Ϸ��� ���̶� ī��Ʈ�� ����� ���ͼ�Ʈ��Ʈ�Ǹ� �Ұ��� ���ְ�
	// ī��Ʈ �ʱ�ȭ�� -> ī��Ʈ ��� �ö󰡼� ���� �̻�Ǹ� �ٽ� ���� ����


	//CAMERAMANAGER->focusOnRect(_sivaRc); // �� �̷��� ���� �߾����� ������(�⺻�� 2,2)
	CAMERAMANAGER->focusOnRect(_sivaRc, 3, 4); // ȭ���� x������ 1/3���� y������ 1/4�������� ��ũ�ѵ˴ϴ�
}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	
	_background->render(backDC, 0, 0);
	_siva->frameRender(backDC, _sivaRc.left, _sivaRc.top);
	Rectangle(backDC, _enemy);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(backDC, _sivaRc);
	} // ���� ���� �ùٸ� �׸��ϴ�


	CAMERAMANAGER->minimap(backDC, 20, 20, 150, 150); // �̴ϸ� Ʋ �׸���(�̴ϸ��� ������â ����)
	//CAMERAMANAGER->minimap(backDC, 20, 20, 150, 150, true); // �� ��� �̰��ϸ� �̴ϸ��� ��ü�ʱ�����
	CAMERAMANAGER->minimapObject(backDC, _sivaRc); // �̴ϸ� Ʋ �׸��°� ���ٸ� �۵����� ����
	CAMERAMANAGER->minimapObject(backDC, _enemy); // �̴ϸ� Ʋ �׸��°� ���ٸ� �۵����� ����

	/* �̴ϸʿ� �� �߰��ϰ� ������ ������ ���� �׷��ݽô�
	for (int i = 0; i < ENEMYMAX; i++)
	{
		CAMERAMANAGER->miniMapObject(backDC, _enemy[i]);
	}
	*/


	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc,0, 0, CAMERAMANAGER->getCameraX() , CAMERAMANAGER->getCameraY(),WINSIZEX,WINSIZEY);
}


// �盏�� �ۼ��Ͻ� �ù�
void playGround::siva()
{

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _sivaRc.top > 0)
	{
		_sivaRc.top -= 5;
		_sivaRc.bottom = _sivaRc.top + 100;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _sivaRc.bottom < MAPSIZEY)
	{
		_sivaRc.top += 5;
		_sivaRc.bottom = _sivaRc.top + 100;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _sivaRc.left > 0)
	{
		_sivaRc.left -= 5;
		_sivaRc.right = _sivaRc.left + 100;
		_direction = SIVA_LEFT_RUN;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_direction = SIVA_LEFT_IDLE;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _sivaRc.right < MAPSIZEX)
	{
		_sivaRc.left += 5;
		_sivaRc.right = _sivaRc.left + 100;
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
			_index--;
			break;
		case SIVA_RIGHT_IDLE:
			if (_index >= 2) _index = 0;
			_siva->setFrameY(0);
			_siva->setFrameX(_index);
			_index++;
			break;
		case SIVA_LEFT_RUN:
			if (_index <= -1) _index = 5;
			_siva->setFrameY(1);
			_siva->setFrameX(_index);
			_index--;
			break;
		case SIVA_RIGHT_RUN:
			if (_index >= _siva->getMaxFrameX()) _index = 2;
			_siva->setFrameY(0);
			_siva->setFrameX(_index);
			_index++;
			break;
		}
		_count = 0;
	}
}

