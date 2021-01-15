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
POINT _ptSave;	//����� ����
// ��������ġ ������ �ϳ� �� �������°� ����Ʈ��
bool _isClick;

enum DIRECTION
{
	DIRECTION_NULL,
	DIRECTION_LT,
	DIRECTION_RT,
	DIRECTION_LB,
	DIRECTION_RB
};

DIRECTION _direction;

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

				

			EndPaint(_hWnd, &ps);
		}
		break;
		//���콺 ���� ��ư ������
		case WM_LBUTTONDOWN:

			if (PtInRect(&_rc, _ptMouse))
			{
				_isClick = true;

				int centerX = (_rc.right + _rc.left) / 2;
				int centerY = (_rc.bottom + _rc.top) / 2;

				if (_ptMouse.x < centerX && _ptMouse.y < centerY)
				{
					_direction = DIRECTION_LT;

					_ptSave.x = LOWORD(lParam) - _rc.left;
					_ptSave.y = HIWORD(lParam) - _rc.top;
				}

				if (_ptMouse.x > centerX && _ptMouse.y < centerY)
				{
					_direction = DIRECTION_RT;

					_ptSave.x = LOWORD(lParam) - _rc.right;
					_ptSave.y = HIWORD(lParam) - _rc.top;
				}

				if (_ptMouse.x < centerX && _ptMouse.y > centerY)
				{
					_direction = DIRECTION_LB;

					_ptSave.x = LOWORD(lParam) - _rc.left;
					_ptSave.y = HIWORD(lParam) - _rc.bottom;
				}

				if (_ptMouse.x > centerX && _ptMouse.y > centerY)
				{
					_direction = DIRECTION_RB;

					_ptSave.x = LOWORD(lParam) - _rc.right;
					_ptSave.y = HIWORD(lParam) - _rc.bottom;
				}

			}

		break;
		//���콺 ���� ��ư �ô�
		case WM_LBUTTONUP:
			_isClick = false;
		break;
		//���콺 �����δ�
		case WM_MOUSEMOVE:
			_ptMouse.x = LOWORD(lParam);
			_ptMouse.y = HIWORD(lParam);

			if (_isClick)
			{
				switch (_direction)
				{
				
					case DIRECTION_LT:
						_rc.left = _ptMouse.x - _ptSave.x;
						_rc.top = _ptMouse.y - _ptSave.y;
					break;
					case DIRECTION_RT:
						_rc.right = _ptMouse.x - _ptSave.x;
						_rc.top = _ptMouse.y - _ptSave.y;
					break;
					case DIRECTION_LB:
						_rc.left = _ptMouse.x - _ptSave.x;
						_rc.bottom = _ptMouse.y - _ptSave.y;
					break;
					case DIRECTION_RB:
						_rc.right = _ptMouse.x - _ptSave.x;
						_rc.bottom = _ptMouse.y - _ptSave.y;
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
