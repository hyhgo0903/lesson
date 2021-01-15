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

	_rc = RectMakeCenter(WINSIZEX / 2 - 200, WINSIZEY / 2, 100, 100);
	_count = 0;



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

	_count++;
	// int count�� Ÿ�̸� ����
	// �Ŵ��� Ÿ�̸� �ϳ��� ����

	if (_count > 50)
	{
		_rc.left += 50;
		_rc.right += 50;

		_count = 0;
	}


}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================

	Rectangle(backDC, _rc);


	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}
