#include "stdafx.h"
#include "playGround.h"

siva::siva()
{
}


siva::~siva()
{
}

//�ʱ�ȭ�� ����� �ϼ���
HRESULT siva::init()
{
	_background = IMAGEMANAGER->addImage("������", "background.bmp", 1440, 2096, false, RGB(255, 0, 255));
	// ���ŷӰ����� �ʻ����� stdafx.h���� �°� �������ּ���

	_siva = IMAGEMANAGER->addFrameImage("�ù�", "siva_run.bmp", 832, 208, 8, 2, true, RGB(255, 0, 255));
	_siva->setFrameY(0);
	_sivaRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);
	_enemy = RectMake(WINSIZEX - 110, WINSIZEY - 110, 100, 100);
	_count = _index = _vibrateCount = 0;

	_direction = SIVA_RIGHT_IDLE;

	return S_OK;
}

//�޸� ������ ����� �ϼ���
void siva::release()
{
}

//����(���)�� ����� �ϼ���
void siva::update()
{
	sivaaa(); // �盏�� �ۼ��Ͻ� �ù�. ������ �ؿ� ����

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


	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		if (CAMERAMANAGER->getCameraLock()) CAMERAMANAGER->cameraLockOff();
		else CAMERAMANAGER->cameraLock();
	}
}

//���� ����� �׷��� ��...
void siva::render()
{
	_background->render(getMemDC(), 0, 0);
	_siva->frameRender(getMemDC(), _sivaRc.left, _sivaRc.top);
	Rectangle(getMemDC(), _enemy);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _sivaRc);
	} // ���� ���� �ùٸ� �׸��ϴ�


	CAMERAMANAGER->minimap(getMemDC(), 20, 20, 150, 150); // �̴ϸ� Ʋ �׸���(�̴ϸ��� ������â ����)
	//CAMERAMANAGER->minimap(backDC, 20, 20, 150, 150, true); // �� ��� �̰��ϸ� �̴ϸ��� ��ü�ʱ�����
	CAMERAMANAGER->minimapObject(getMemDC(), _sivaRc); // �̴ϸ� Ʋ �׸��°� ���ٸ� �۵����� ����
	CAMERAMANAGER->minimapObject(getMemDC(), _enemy); // �̴ϸ� Ʋ �׸��°� ���ٸ� �۵����� ����

	/* �̴ϸʿ� �� �߰��ϰ� ������ ������ ���� �׷��ݽô�
	for (int i = 0; i < ENEMYMAX; i++)
	{
		CAMERAMANAGER->miniMapObject(backDC, _enemy[i]);
	}
	*/
}


// �盏�� �ۼ��Ͻ� �ù�
void siva::sivaaa()
{

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _sivaRc.top > 0)
	{
		_sivaRc.top -= 3;
		_sivaRc.bottom = _sivaRc.top + 100;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _sivaRc.bottom < MAPSIZEY)
	{
		_sivaRc.top += 3;
		_sivaRc.bottom = _sivaRc.top + 100;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _sivaRc.left > 0)
	{
		_sivaRc.left -= 3;
		_sivaRc.right = _sivaRc.left + 100;
		_direction = SIVA_LEFT_RUN;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_direction = SIVA_LEFT_IDLE;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _sivaRc.right < MAPSIZEX)
	{
		_sivaRc.left += 3;
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

