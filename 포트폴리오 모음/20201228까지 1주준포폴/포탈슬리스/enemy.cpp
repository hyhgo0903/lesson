#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::init()
{
	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
}

void enemy::render()
{
}

void enemy::commomInit()
{
	_frameX = _frameCount = _fireReady = 0;
	_duration = -100 + rand() % 200;
	_alphaValue = 255;
	_appear = true;
	_arrived = false;
}

void enemy::commonUpdate()
{
	if (_duration < 1000 && _arrived && _alphaValue >= 255) _duration++;
	else _duration = 0; // 0~999���� ��� ��(�̰� ���� �����̳� �̵�)
	_hpBar->setPoint(_x, _rc.top - 12);
	_hpBar->setGauge(_currentHP, _maxHP);
	_hpBar->update();

	if (_currentHP <= 0)
	{
		_currentHP = 0;
		_duration = -1; // ���̻� �����̳� �̵� ���ϰ�
		_alphaValue -= 5; // �������ϰ� ���ش�
	}
	if (_alphaValue <= 0) _appear = false;

}

void enemy::commonRender()
{
	_hpBar->render();

	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(getMemDC(), _rc);
	

}
