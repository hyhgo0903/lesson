#include "stdafx.h"
#include "bullets.h"


HRESULT bullets::init()
{	// �̰ɷ� ���� ���� ��� �н� (���Ŭ������ �̴�ȣ���)
	return S_OK;
}

void bullets::release()
{
}

void bullets::update()
{

}

void bullets::render()
{
}

void bullets::move() // �ӵ���ŭ �̵��ϰ� �������̾� ���ִ� �Լ�
{
	// �ӵ���ŭ �Ű���
	_x += _xSpd;
	_y += _ySpd;

	// �ȼ��浹�� ����(�ʷϻ���)
	COLORREF color = GetPixel(FINDIMG("���ȼ�")->getMemDC(), _x, _y+1);
	int r = GetRValue(color); int g = GetGValue(color); int b = GetBValue(color);
	if (r == 0 && g == 255 && b == 0) _isFire = false; // �ʷϻ� ������ ����
	   
	// ȭ��� ����. �ȼ��浹 ���ϸ�.. ��� ���� ���ƿü��� �����ϱ� 200��ŭ ���� �ο�
	if (_x+_width/2 < GETCAM-200 || _x-_width / 2 > GETCAM + WINSIZEX+200) _isFire = false;
	if (_y > WINSIZEY+_height / 2) _isFire = false;

	// ���ӽð� ������ ����
	if (_duration < BULLETDURATION) ++_duration;
	else _isFire = false;
}
