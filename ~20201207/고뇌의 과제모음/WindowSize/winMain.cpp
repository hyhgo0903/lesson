#include "stdafx.h"

HINSTANCE	_hInstance;	//�ν��Ͻ� 
HWND		_hWnd;		//������ �ڵ�


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowsSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszClass, int cmdShow)
{
	MSG			message;	//������ �޽����� ���� ����ü
	WNDCLASS	wndClass;	//������ Ŭ���� ����ü

	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = WINNAME;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	_hWnd = CreateWindow(
		WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,
		WINSTARTX,
		WINSTARTY,
		WINSIZEX,
		WINSIZEY,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);

	setWindowsSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	ShowWindow(_hWnd, cmdShow);

	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	UnregisterClass(WINNAME, _hInstance);

	return message.wParam;
}

RECT _rc;
POINT _ptMouse;
bool _isIn;
bool _isClick;
int x, y;
long temp;
int halfHeight, halfWidth;

enum Bunmyeon
{
	NONE,
	ONE,
	TWO,
	THREE,
	FOUR
};
Bunmyeon a;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//WPARAM : Ű���� ������ ���̵�, ���콺 ��,��,�� Ŭ���ϸ� �갡 ������
	//LPARAM : ���콺 ��ǥ�� ������

	PAINTSTRUCT ps;
	HDC			hdc;	//<-- �� ��¥ �߿���

	char str[128];

	switch (iMessage)
	{
		//������ â�� �����ɶ� ����~ �� �� �����
		case WM_CREATE:
			_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);
		break;
		case WM_PAINT:
		{
			hdc = BeginPaint(_hWnd, &ps);

			Rectangle(hdc, _rc.left, _rc.top, _rc.right, _rc.bottom);

			sprintf_s(str, "���콺 X : %d, ���콺 Y : %d", _ptMouse.x, _ptMouse.y);
			TextOut(hdc, 15, 15, str, strlen(str));

			sprintf_s(str, "���콺 �ִ� : %d", _isIn);
			TextOut(hdc, 15, 30, str, strlen(str));

			sprintf_s(str, "â �ٲٴ� �� : %d��и�", a);
			TextOut(hdc, 15, 45, str, strlen(str));

			sprintf_s(str, "(0��и��� �ٲٴ� ���� �ƴ�. ���� �۵�����)", a);
			TextOut(hdc, 15, 60, str, strlen(str));
			

			EndPaint(_hWnd, &ps);
		}
		break;
		//���콺 ���� ��ư ������
		case WM_LBUTTONDOWN:
			if (_isIn==true)
			{
				halfHeight = (_rc.bottom - _rc.top) / 2;
				halfWidth = (_rc.right - _rc.left) / 2;
				x = _ptMouse.x- (_rc.right + _rc.left)/ 2 ;
				y = _ptMouse.y - (_rc.top + _rc.bottom)/2;
				if (x < 0)
				{
					if (y > 0)	a = THREE;
					else if (y < 0) a = TWO;
					else break;
				}
				else if (x > 0)
				{
					if (y > 0)	a = FOUR;
					else if (y < 0) a = ONE;
					else break;
				}
				else break;
				_isClick = true;
			}
			InvalidateRect(_hWnd, NULL, true);

		break;
		//���콺 ���� ��ư �ô�
		case WM_LBUTTONUP:
			_isClick = false;
			x = 0;
			y = 0;
			a = NONE;
			if (_rc.right < _rc.left)
			{
				temp = _rc.left;
				_rc.left = _rc.right;
				_rc.right = temp;
			}
			if (_rc.bottom < _rc.top)
			{
				temp = _rc.bottom;
				_rc.bottom = _rc.top;
				_rc.top = temp;
			}
			InvalidateRect(_hWnd, NULL, true);
		break;
		//���콺 �����δ�
		case WM_MOUSEMOVE:
			_ptMouse.x = LOWORD(lParam);
			_ptMouse.y = HIWORD(lParam);

			if (_rc.left < _ptMouse.x && _ptMouse.x < _rc.right &&
				_rc.top < _ptMouse.y && _ptMouse.y < _rc.bottom)
			{
				_isIn = true;
			}
			else _isIn = false;

			if (_isClick)
			{
				switch (a)
				{
				case NONE: break;
				case ONE:
					_rc.right = _ptMouse.x +halfWidth-x;
					_rc.top = _ptMouse.y - halfHeight - y;
					break;
				case TWO:
					_rc.left = _ptMouse.x - halfWidth-x;
					_rc.top = _ptMouse.y - halfHeight - y;
					break;
				case THREE:
					_rc.left = _ptMouse.x - halfWidth-x;
					_rc.bottom = _ptMouse.y + halfHeight - y;
					break;
				case FOUR:
					_rc.right = _ptMouse.x +halfWidth-x;
					_rc.bottom = _ptMouse.y + halfHeight - y;
					break;
				}
			}

			InvalidateRect(_hWnd, NULL, true);
		break;


		case WM_KEYDOWN:
			switch (wParam)
			{
				
				case VK_ESCAPE:
					PostQuitMessage(0);
				break;
			}
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

//Ŭ���̾�Ʈ ���� �������� ����!!!!
void setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	AdjustWindowRect(&winRect, WINSTYLE, false);

	//���������� Ŭ���̾�Ʈ ���� ũ�� ���� ���ִ� �Լ�
	SetWindowPos(_hWnd, NULL, x, y,
		(winRect.right - winRect.left),
		(winRect.bottom - winRect.top),
		SWP_NOZORDER | SWP_NOMOVE);

}
