#include "stdafx.h"

//API : Application Programming Interface

HINSTANCE	_hInstance;	//�ν��Ͻ� 
HWND		_hWnd;		//������ �ڵ�
LPCTSTR		_lpszClass = TEXT("25��");

//�Լ� ������Ÿ�� ����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowsSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszClass, int cmdShow)
{
	MSG		message;	//������ �޽����� ���� ����ü
	WNDCLASS wndClass;	//������ Ŭ���� ����ü

	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;										//������ Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;										//������ ���� �޸�
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//������ â ��׶��� ����
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//Ŀ�� ���
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//������ ���
	wndClass.hInstance = hInstance;									//�ν��Ͻ� ���
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//������ ���ν���
	wndClass.lpszClassName = WINNAME;								//������ Ŭ���� ���
	wndClass.lpszMenuName = NULL;									//�޴� ����
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//������ ��Ÿ��~

	RegisterClass(&wndClass);										//������ ���� ���

	_hWnd = CreateWindow(				//������ ���� ������ â �����
		WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,			//������ â ��Ÿ��
		WINSTARTX,						//������ ������ǥ X
		WINSTARTY,						//������ ������ǥ Y
		WINSIZEX,						//������ ����ũ��
		WINSIZEY,						//������ ����ũ��
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	setWindowsSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	ShowWindow(_hWnd, cmdShow);			//�갡 �־�� ������ â�� ��Ÿ��

	//GetMessage : �����쿡�� ��� �޽����� �߻��ϸ� �׶� ó����
	//PeekMessage : �޽����� �ֵ� ���� ��� ���� ����
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);	//������ �޽����� �޾ƿ�
		DispatchMessage(&message);	//���� �޾ƿ� �޽����� ���� ��ǻ�Ϳ��� ������
	}

	return message.wParam;
}

RECT _rc;
POINT _ptMouse;
bool _isIn;

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
			// �����ڵ�� �̰� �ȵ�.(�Ӽ����� ��������)
			sprintf_s(str, "���콺 �ִ� : %d", _isIn);
			TextOut(hdc, 15, 30, str, strlen(str));
			

			EndPaint(_hWnd, &ps);
		}
		break;
		//���콺 ���� ��ư ������
		case WM_LBUTTONDOWN:

		break;
		//���콺 ���� ��ư �ô�
		case WM_LBUTTONUP:

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
			PostMessage(_hWnd, WM_DESTROY, 0, 0);
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
