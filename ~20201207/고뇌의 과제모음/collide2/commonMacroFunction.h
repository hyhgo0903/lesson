#pragma once
//======================================
// ## 20.11.12 ## CommonMacroFunction ##
//======================================

//Line
//       ���߱��Լ� (�Ѹ�DC, ����X, ����Y, ��X, ��Y)
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

//RECT
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x,y,x + width,y + height };

	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x-(width/2),y-(height /2),x + width/2,y + height/2 };

	return rc;
}

//Rectangle
//x,y��ǥ�� �������� ũ�⸸ŭ �簢���� ������

// inline �Լ� : ª������(�ڵ� ��������)->�ӵ� �ſ� �ö�
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

//Ellipse
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

// �ε����� ��� �ڸ��ٲٱ�
inline void Collide1(RECT &a, RECT &b, RECT &c)
{
	int temp;
	temp = a.right;
	a.right = b.right;
	b.right = temp;
	temp = a.left;
	a.left = b.left;
	b.left = temp;
	temp = a.top;
	a.top = b.top;
	b.top = temp;
	temp = a.bottom;
	a.bottom = b.bottom;
	b.bottom = temp;
	
	int length;
	length = c.right - c.left;
	c.left = (a.right + a.left) / 2 - length / 2;
	c.right = (a.right + a.left) / 2 + length / 2;
	length = c.bottom - c.top;
	c.top = (a.top + a.bottom) / 2 - length / 2;
	c.bottom = (a.top + a.bottom) / 2 + length / 2;
}