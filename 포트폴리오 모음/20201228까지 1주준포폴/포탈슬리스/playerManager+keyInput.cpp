#include "stdafx.h"
#include "playerManager.h"
#include "itemManager.h"

// Ű �Է��� ���⿡
void playerManager::keyInput()
{
	// �¿� �̵�
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)
		&& _tank.rc.right <= MAPSIZEX && _tank.rc.right <= GETCAM + WINSIZEX) // ī�޶� ������������ �ۿ� �ȳ�����
	{
		COLORREF color = GetPixel(FINDIMG("���ȼ�")->getMemDC(), _tank.rc.right + 1, _tank.y);
		int r = GetRValue(color); int g = GetGValue(color); int b = GetBValue(color);
		if (r == 0 && g == 255 && b == 255) {} // ���� ���θ������ ����
		else
		{
			if (_tank.state == LEFTATTACK || _tank.state == LEFTRUN ||
				_tank.state == LEFTIDLE)
			{
				_tank.state = RIGHTRUN;
				_tank.angle = PI - _tank.angle;
				stateChange();
			}
			else if (_tank.state == RIGHTIDLE)
			{
				_tank.state = RIGHTRUN;
				stateChange();
			}
			if (_im->getStateSlot(1)) _tank.x += 4.5f; // ���� ������
			else _tank.x += 3;
			_tank.rc = RectMakeCenter(_tank.x, _tank.y, TANKWIDTH, TANKHEIGHT);
		}

	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)
		&& !KEYMANAGER->isStayKeyDown(VK_RIGHT)
		&& _tank.rc.left > GETCAM)
	{
		COLORREF color = GetPixel(FINDIMG("���ȼ�")->getMemDC(), _tank.rc.left - 1, _tank.y);
		int r = GetRValue(color); int g = GetGValue(color); int b = GetBValue(color);
		if (r == 0 && g == 255 && b == 0) {}
		else
		{
			if (_tank.state == RIGHTATTACK || _tank.state == RIGHTRUN ||
				_tank.state == RIGHTIDLE)
			{
				_tank.state = LEFTRUN;
				_tank.angle = PI - _tank.angle;
				stateChange();
			}
			else if (_tank.state == LEFTIDLE)
			{
				_tank.state = LEFTRUN;
				stateChange();
			}
			if (_im->getStateSlot(1)) _tank.x -= 4.5f; // ���� ������
			else _tank.x -= 3;
			if (_tank.x < GETCAM + TANKWIDTH / 2)
			{
				_tank.x = GETCAM + TANKWIDTH / 2;
			}
			_tank.rc = RectMakeCenter(_tank.x, _tank.y, TANKWIDTH, TANKHEIGHT);
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		if (_tank.state == LEFTRUN)		{	_tank.state = LEFTIDLE;		stateChange();	}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		if (_tank.state == RIGHTRUN)	{	_tank.state = RIGHTIDLE;	stateChange();	}
	}

	// ����
	if (KEYMANAGER->isStayKeyDown(VK_UP) && !_tank.isJump)
	{
		_tank.isJump = true;
		if (_im->getStateSlot(1)) _tank.jumpPower = 6.5f; // ���� ������
		else _tank.jumpPower = 6;
	}

	// �Ŀ�����
	if (KEYMANAGER->isStayKeyDown('A')
		&& _tank.currentPower > 10) // �ּ� �Ŀ���
	{
		_tank.currentPower -= 1;
	}
	if (KEYMANAGER->isStayKeyDown('D')
		&& _tank.currentPower < 100)
	{
		_tank.currentPower += 1;
		if (_tank.currentPower > 100) _tank.currentPower = 100;
	}

	// �߻�� �������̾�(Q)�ų� �����̽� ���� ���¸�
	if (KEYMANAGER->isToggleKey('Q')
		&& _tank.currentDelay <= 0)
	{
		fire();
	}
	if (KEYMANAGER->isStayKeyDown(VK_SPACE)
		&& _tank.currentDelay <= 0)
	{
		fire();
	}

	// ��������
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (_tank.angle < 1.3963f) // 80�� ���� ������
		{
			_tank.angle += 0.015f;
			if (_tank.angle > 1.3963f) _tank.angle = 1.3963f;
		}
		else if (_tank.angle > 1.7453f) // 100�� ���� Ŭ��
		{
			_tank.angle -= 0.015f;
			if (_tank.angle < 1.7453f) _tank.angle = 1.7453f;
		}
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (_tank.angle < PI / 2 && _tank.angle > 0.1745f)
		{//  10��
			_tank.angle -= 0.015f;
			if (_tank.angle < 0.17453f) _tank.angle = 0.17453f;
		}
		else if (_tank.angle > PI / 2 && _tank.angle < 2.967f)
		{//  170��
			_tank.angle += 0.015f;
			if (_tank.angle > 2.967f) _tank.angle = 2.967f;
		}
	}

	// ��ũ��ü
	if (KEYMANAGER->isOnceKeyDown(VK_F1) && _tank.type != CANNON && _im->getStateSlot(0))
	{
		EFFECTMANAGER->play("change", _tank.x, _tank.y);
		_tank.type = CANNON;
		if (_tank.state == RIGHTATTACK) _tank.state = RIGHTIDLE;
		else if (_tank.state == LEFTATTACK) _tank.state = LEFTIDLE;
		stateChange();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2) && _tank.type != MISSILE && _im->getStateSlot(1))
	{
		EFFECTMANAGER->play("change", _tank.x, _tank.y);
		_tank.type = MISSILE;
		if (_tank.state == RIGHTATTACK) _tank.state = RIGHTIDLE;
		else if (_tank.state == LEFTATTACK) _tank.state = LEFTIDLE;
		stateChange();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3) && _tank.type != MULTI && _im->getStateSlot(2))
	{
		EFFECTMANAGER->play("change", _tank.x, _tank.y);
		_tank.type = MULTI;
		if (_tank.state == RIGHTATTACK) _tank.state = RIGHTIDLE;
		else if (_tank.state == LEFTATTACK) _tank.state = LEFTIDLE;
		stateChange();
	}
	if (((KEYMANAGER->isOnceKeyDown(VK_F4) && _tank.type != SUPER) || !_autoChanged) && _im->getStateSlot(3))
	{ // �����ѻ��¿���(���Կ� ������) && ���۰� �ƴҶ� F4�� �����ų� ����ü������ �����ִٸ�
		_autoChanged = true;
		EFFECTMANAGER->play("change", _tank.x, _tank.y);
		_tank.type = SUPER;
		if (_tank.state == RIGHTATTACK) _tank.state = RIGHTIDLE;
		else if (_tank.state == LEFTATTACK) _tank.state = LEFTIDLE;
		stateChange();
	}

	// �� ���
	if (KEYMANAGER->isOnceKeyDown('1') && _im->getUsingSlot(0) != EMPTY)
	{ // ������ �̳Ѱ��̶� ��������� ����ϰ� ���ڷ� ó����
		_usingItem[_im->getUsingSlot(0)] = true;
		_itemDuration[_im->getUsingSlot(0)] = 0;
		_effectFrameX[_im->getUsingSlot(0)] = 0;
		_im->getUsingSlot(0) = EMPTY;
	}
	if (KEYMANAGER->isOnceKeyDown('2') && _im->getUsingSlot(1) != EMPTY)
	{
		_usingItem[_im->getUsingSlot(1)] = true;
		_itemDuration[_im->getUsingSlot(1)] = 0;
		_effectFrameX[_im->getUsingSlot(1)] = 0;
		_im->getUsingSlot(1) = EMPTY;
	}
	if (KEYMANAGER->isOnceKeyDown('3') && _im->getUsingSlot(2) != EMPTY)
	{
		_usingItem[_im->getUsingSlot(2)] = true;
		_itemDuration[_im->getUsingSlot(2)] = 0;
		_effectFrameX[_im->getUsingSlot(2)] = 0;
		_im->getUsingSlot(2) = EMPTY;
	}
	if (KEYMANAGER->isOnceKeyDown('4') && _im->getUsingSlot(3) != EMPTY)
	{
		_usingItem[_im->getUsingSlot(3)] = true;
		_itemDuration[_im->getUsingSlot(3)] = 0;
		_effectFrameX[_im->getUsingSlot(3)] = 0;
		_im->getUsingSlot(3) = EMPTY;
	}	
}