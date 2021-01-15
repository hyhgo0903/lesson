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

	_degree = 180.0f;
	_radian = PI;
	

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

	
}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================

	char strRadian[256];
	char strDegree[256];

	sprintf_s(strRadian, "%.2f ���� ���� %.2f ��׸� ���� ����",
		_radian, _radian * (180 / PI)); // %.2f : �Ҽ��� ��°�ڸ����� ����
	TextOut(backDC, 50, 50, strRadian, strlen(strRadian));

	sprintf_s(strDegree, "%.2f ��׸� ���� %.2f ���� ���� ����",
		_degree, _degree * (PI / 180));
	TextOut(backDC, 50, 50, strDegree, strlen(strDegree));

	// sqrt() ������ ������ �Ⱦ�
	// r1+r2 > h�� �浹(�̰� (2)�������Ұ�
	// AABB / OBB�浹



	
	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}
