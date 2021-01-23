#include "stdafx.h"
#include "battle.h"

HRESULT battle::init(const char* imageName, int x, int y)
{
	ship::init(imageName, x, y);
	// 부모클래스 함수를 쓰되 개성을 넣어서 초기화시키려면 이렇게
	return S_OK;
}

void battle::release()
{
	ship::release();

}

void battle::update()
{
	ship::update();

	keyControl();
}

void battle::render()
{
	ship::render();

}

void battle::keyControl()
{ // 가상함수(virtual void keycontrol)니까 
  // 상속받은 클래스의 함수인 wasd로 움직이게 됨
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_angle += 0.02f;
		if (_angle >= PI2) _angle -= PI2;
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_angle -= 0.02f;
		if (_angle <= 0) _angle += PI2;
	}

	if (KEYMANAGER->isStayKeyDown('W')) _speed += 0.02f;
	if (KEYMANAGER->isStayKeyDown('S')) _speed -= 0.02f;

}
