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

	_ellipse = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);

	_isCollision = false;



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

	_rectangle = RectMakeCenter(_ptMouse.x, _ptMouse.y, 100, 100);

	if (isCollision(_ellipse, _rectangle)) _isCollision = true;
	else _isCollision = false;


}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================

	Rectangle(backDC, _rectangle);
	Ellipse(backDC, _ellipse);

	if (_isCollision)
	{
		TextOut(backDC, WINSIZEX / 2, 100, "�浹��", strlen("�浹��"));
	}
	else
	{

	}


	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

bool playGround::isCollision(RECT & rc1, RECT & rc2)
{
	int x = (rc1.right + rc1.left) / 2; // ��(rc1)����x��ǥ
	int y = (rc1.bottom + rc1.top) / 2; // ������y��ǥ

	int radius = (rc1.right - rc1.left) / 2; // ������

	//�浹 �κ�
	if ((rc2.left <= x && x <= rc2.right) ||
		(rc2.top <= y && y <= rc2.bottom))
	{
		RECT rcTemp; // �簢��(rc2)�������� ��������ŭ �¿���Ϸ� ū ������ �簢���� �����.

		rcTemp.left = rc2.left - radius;
		rcTemp.top = rc2.top - radius;
		rcTemp.right = rc2.right + radius;
		rcTemp.bottom = rc2.bottom + radius;

		//������ ���� ���� ������ ������ ������ ���浹�Ѱ���
		if ((rcTemp.left <= x && x <= rcTemp.right) &&
			(rcTemp.top <= y && y <= rcTemp.bottom))
		{
			return true;
		}
	}
	else
	{
		if (getDistance(rc1, rc2.left, rc2.top)) return true;
		if (getDistance(rc1, rc2.right, rc2.top)) return true;
		if (getDistance(rc1, rc2.left, rc2.bottom)) return true;
		if (getDistance(rc1, rc2.right, rc2.bottom)) return true;
	}

	return false;
}

//� ���� ��Ʈ ���� �Ÿ� �˾ƿ��� �Ծ�
bool playGround::getDistance(RECT & rc, float x, float y)
{
	float deltaX = x - (rc.right + rc.left) / 2;
	float deltaY = y - (rc.bottom + rc.top) / 2;

	float distSquare = deltaX * deltaX + deltaY * deltaY;

	float radius = (rc.right - rc.left) / 2;

	float radiusSquare = radius * radius;

	if (radiusSquare < distSquare) return false; // ��(������)�� ������ ���ؼ� ���������� ������ �浹�Ѱ�.

	return true;
}
