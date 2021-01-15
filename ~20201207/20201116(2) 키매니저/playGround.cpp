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

	_rc = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2, 100, 100);

	return S_OK;
}

//�޸� ������ ����� �ϼ���
void playGround::release()
{
	
}

//����(���)�� ����� �ϼ���
void playGround::update()
{
	gameNode::update();

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_rc.left -= 5;
		_rc.right -= 5;
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_rc.left += 5;
		_rc.right += 5;
	}


	/*
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_rc.left += 5;
		_rc.right += 5;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_rc.left -= 15;
		_rc.right -= 15;
	}*/

}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	
	Rectangle(hdc, _rc);
	
}
