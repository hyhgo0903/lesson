#include "stdafx.h"
#include "droppedItem.h"


droppedItem::droppedItem()
{

}

droppedItem::~droppedItem()
{

}

HRESULT droppedItem::init(bool stateType, float x, float y)
{
	_stateType = stateType;			  
	_x = x;	_y = y;
	_landed = _disappear = false;
	_xSpd = 0;
	
	if (_stateType) // ����Ÿ���̸�
	{
		_ySpd = -5; // ����Ÿ���̸� Ƣ�������
		_itemType = rand() % 3;
		_frameX = _itemType;
		_rc = RectMakeCenter(_x, _y, 45 ,39);
	}
	else // ���Ÿ���̸� �����۹ڽ�
	{
		_itemType = -1;
		_ySpd = 0;
		_frameX= rand()%4;
		_rc = RectMakeCenter(_x, _y, 36, 31);
	}
	_durCount = 0;
	_alphaValue = 255;

	return S_OK;
}

void droppedItem::release()
{
}

void droppedItem::update()
{
	if (_durCount < ITEMDURMAX) _durCount++;
	else _disappear = true;
	if (_durCount > ITEMDURMAX - 50) _alphaValue -= 5; // ������پƾ�
	
	if (_rc.right < GETCAM) _disappear = true;

	if (!_stateType && _durCount % 5 == 0 && !_landed) // �������ѻ��¸� ���ڰ� ���ۺ��� ����
	{
		_frameX++;
		if (_frameX > 3) _frameX = 0;
	}

	move();
}

void droppedItem::render()
{
	if (_stateType)	FINDIMG("������")->alphaFrameRender(getMemDC(), _rc.left, _rc.top, _frameX, 0, _alphaValue);
	else	FINDIMG("�����ۻ���")->alphaFrameRender(getMemDC(), _rc.left, _rc.top, _frameX,0, _alphaValue);
	
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}
}

void droppedItem::move()
{
	if (!_landed)
	{
		_y += _ySpd;
		if (!_stateType) _x += 0.5f * _xSpd; // xspd(�ٶ�����)�� �����۸Ŵ������� �Է¹޽��ϴ�.
		_ySpd += GRAVITY/2;

		if (_stateType) _rc = RectMakeCenter(_x, _y, 45, 39);
		else
		{
			_rc = RectMakeCenter(_x, _y, 36, 31);						
		}

		COLORREF color = GetPixel(FINDIMG("���ȼ�")->getMemDC(), _x, _rc.bottom+1);
		int r = GetRValue(color); int g = GetGValue(color); int b = GetBValue(color);
		if ((r == 0 && g == 255 && b == 0) && _ySpd > 0)
		{
			_landed = true;
		}

	}
	if (_landed) // ���������� ���ڸ� �սǵս�
	{
		if (_durCount % 60 > 29) _y += 0.2f;
		else _y -= 0.2f;
		if (_stateType) _rc = RectMakeCenter(_x, _y, 45, 39);
		else _rc = RectMakeCenter(_x, _y, 36, 31);
	}
}
