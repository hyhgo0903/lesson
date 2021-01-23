#include "stdafx.h"
#include "playerManager.h"
#include "itemManager.h"
#include "bulletManager.h"


HRESULT playerManager::init(int data)
{
	_changeEffect = new effect;
	_changeEffect->init(IMAGEMANAGER->findImage("��ü"), 40, 40, 1, 0.5f);
	EFFECTMANAGER->addEffect("change", "image/effectchange.bmp", 800, 40, 40, 40, 1.0f, 0.2f, 20);	

	_difficulty = data / 10;
	_selectedTank = data % 10;
	

	switch (_selectedTank)
	{
	case 0:_tank.type = CANNON;		break;
	case 1:_tank.type = MISSILE;	break;
	case 2:_tank.type = MULTI;		break;
	}

	_isGameOver = false;
	_tank.x = 50;
	_tank.y = 50;
	_tank.rc = RectMakeCenter(_tank.x, _tank.y, TANKWIDTH, TANKHEIGHT);
	_alphaValue = 255;

	_tank.state = RIGHTIDLE;
	if (_difficulty == 0) { _tank.currentHP = _tank.maxHP = 500; }
	else if (_difficulty == 1) { _tank.currentHP = _tank.maxHP = 100; }
	else if (_difficulty == 2) { _tank.currentHP = _tank.maxHP = 50; }
	stateChange();

	_tank.angle = PI / 4;

	for (int i = 0; i < 4; i++)
	{		
		_usingItem[i] = false;
		_itemDuration[i] = 0;
		_effectFrameX[i] = 0;
	}	 

	_tank.currentDelay = _tank.maxDelay = _tank.maxPower = _tank.currentPower = 100;
	_tank.gravity = _tank.jumpPower = 0.f;
	_tank.angle = PI / 4;
	_tank.frameX = _tank.aniCount = 0;

	_tank.isJump = true;
	_autoChanged = _isBlink = _isInvincible = false;
	_specialCount = _blinkCount = 0;

	return S_OK;
}

void playerManager::release()
{
}

void playerManager::update()
{
	CAMERAMANAGER->focusOnRect(_tank.rc, 2);	// ȭ�鿡 �����ִ� �Լ�
	keyInput();			// Ű�Է�
	tankMove();			// �ȼ��浹 �� �߷µ����� ��ũ�̵�
	delayReduce();
	animationUpdate();

	for (int i = 0; i < 4; ++i) // ������ ���ӽð� ���� �����ӵ� ���� �� �Ӹ��� ����
	{
		if (_usingItem[i])
		{
			if (_itemDuration[i] < ITEMDURATION) ++_itemDuration[i]; // ���ӽð� ä���
			else _usingItem[i] = false;								// á���� ����
			if (_itemDuration[i] % 6 == 0)							// �ִϸ��̼��� 0.1�ʸ��� �����ϴ°ɷ�
			{
				++_effectFrameX[i];
				if ((i == 0 && _effectFrameX[i] > 5) || (i == 1 && _effectFrameX[i] > 3) ||
					(i == 2 && _effectFrameX[i] > 4) || (i == 3 && _effectFrameX[i] > 8)) _effectFrameX[i] = 0;
				// ����Ʈ���� �ִ� ������ ���� ������ �ʱ�ȭ
			}
		}
	}
	if (_usingItem[3]) // ȸ�����̸� ȸ���� �մϴ�
	{
		if (_difficulty == 0) _tank.currentHP += 1.5f;
		_tank.currentHP += 0.5f;
		if (_tank.currentHP >= _tank.maxHP)
		{
			_tank.currentHP = _tank.maxHP;
			_usingItem[3] = false;
		}
	} // ����� ����� ���⼭
	if		(_difficulty == 0)	{ _damageCoefficient = 2;	} // ���̵� ���� ������
	else if (_difficulty == 1)	{ _damageCoefficient = 1;	}
	else if (_difficulty == 2)	{ _damageCoefficient = 0.5f; }
	if (_usingItem[1]) _damageCoefficient *= 2; // �Ŀ��������� ���� ��2��
	if (_im->getStateSlot(0)) _damageCoefficient *= 1.5; // ĳ������� ������ ��1.5��
	if (_usingItem[2] || _isBlink) _isInvincible = true; // �����̰ų� ���������̸� ����
	else _isInvincible = false; // �Ѵ� �ƴϸ� �����ƴ�
	if (_isBlink && _blinkCount % 10 < 5) _alphaValue= 100;
	if (_isBlink && _blinkCount % 10 > 4) _alphaValue = 200;
	if (_isBlink && _blinkCount < 120) _blinkCount++;
	if (_blinkCount >= 120)
	{
		_blinkCount = 0;
		_isBlink = false;
		_alphaValue = 255;
	}
	EFFECTMANAGER->update();
	_changeEffect->update();
	test();
	if (_tank.currentHP <= 0 && _difficulty != 0)
	{ // �ÿ��� ���̵� ���� ���ӿ����� ��ȯ
		_isGameOver = true;
	}
	if (_tank.currentHP < 0) _tank.currentHP = 0;
}

void playerManager::render()
{
	if (_usingItem[0])	FINDIMG("�ٶ�����Ʈ")->frameRender(getMemDC(), _tank.rc.left-2, _tank.rc.top-25, _effectFrameX[0], 0);
	if (_usingItem[1])	FINDIMG("������Ʈ")->frameRender(getMemDC(), _tank.rc.left-16, _tank.rc.top-12, _effectFrameX[1], 0);
	if (_usingItem[2])	FINDIMG("��������Ʈ")->frameRender(getMemDC(), _tank.rc.left-21, _tank.rc.top-20, _effectFrameX[2], 0);
	if (_usingItem[3])	FINDIMG("������Ʈ")->frameRender(getMemDC(), _tank.rc.left - 14, _tank.rc.top-12, _effectFrameX[3], 0);

	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(getMemDC(), _tank.rc);
	stateRender();	interfaceRender();
	for (int i = 0; i < 4; i++) // �̿����̸� ǥ������
	{
		if (_usingItem[i])
		{ // �������� �����Ÿ��� ȿ���� �ַ��� ���� ī��Ʈ ���º��� ������� ����
			if (_itemDuration[i] > ITEMDURATION - 120 && _itemDuration[i] % 20 > 9)	{}
			else FINDIMG("����۹���ǥ��")->alphaFrameRender(getMemDC(), GETCAM+63*i, 0, i, 0, 150);
		}
	}
	EFFECTMANAGER->render();
	_changeEffect->render();
}

// ��ũ �̵�(�ȼ��浹, �߷¿���)
void playerManager::tankMove()
{
	_tank.probeY = _tank.rc.bottom;
	for (int i = _tank.probeY - 4; i < _tank.probeY + 8; ++i)
	{
		COLORREF color = GetPixel(FINDIMG("���ȼ�")->getMemDC(), _tank.x, i);
		int r = GetRValue(color); int g = GetGValue(color); int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255) && _tank.y > 0) // ������ ���¸�
		{
			//���� Y���� �ش� �ȼ������� ���� ��������ŭ ����
			if (_tank.jumpPower <= 0)
			{
				_tank.isJump = false;
				_tank.jumpPower = 0;
				_tank.y = i - TANKHEIGHT / 2;
				break;
			}
		}
		if (_tank.probeY + 7 == i) // ������ ���µ� �������Ѱ�
		{
			_tank.jumpPower -= GRAVITY;
			if (_tank.jumpPower < -2) _tank.isJump = true; // ���� �ӵ� �̻�(���� ��ٷ���) �������������� ���� ����
		}
	}
	_tank.y -= _tank.jumpPower;
	_tank.rc = RectMakeCenter(_tank.x, _tank.y, TANKWIDTH, TANKHEIGHT);
}

void playerManager::delayReduce()
{
	if (_tank.currentDelay > 0)
	{	_tank.currentDelay -= 1.75f;	}
	if (_im->getStateSlot(2) && _tank.currentDelay > 0) // �߰��� ������ ����
	{	_tank.currentDelay -= 0.75f;	}
	if (_usingItem[0] && _tank.currentDelay > 0) // �������̾� ���¸� �߰��� ������ ����
	{	_tank.currentDelay -= 0.5f;	}
	if (_tank.currentDelay < 0) _tank.currentDelay = 0;
}

void playerManager::test() // �׽�Ʈ�� ġƮŰ - ����� �����
{
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4)) _tank.currentHP = _tank.maxHP * 0.2f;
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5)) _tank.currentHP = _tank.maxHP;
}
