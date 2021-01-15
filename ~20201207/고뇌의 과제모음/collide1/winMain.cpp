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


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//WPARAM : Ű���� ������ ���̵�, ���콺 ��,��,�� Ŭ���ϸ� �갡 ������
	//LPARAM : ���콺 ��ǥ�� ������

	PAINTSTRUCT ps;
	HDC			hdc;

	static RECT rc;
	static RECT rc2;
	static RECT rc3;

	switch (iMessage)
	{		
		case WM_CREATE:
			rc = RectMakeCenter(WINSIZEX / 2-100, WINSIZEX / 2, 100, 100);
			rc2 = RectMakeCenter(WINSIZEX / 2 +100, WINSIZEX / 2 , 100, 100);
			rc3 = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEX / 2, 50, 50);
			break;
		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
			Rectangle(hdc, rc2.left, rc2.top, rc2.right, rc2.bottom);
			Rectangle(hdc, rc3.left, rc3.top, rc3.right, rc3.bottom);
			EndPaint(hWnd, &ps);
		}
		break;

		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_LEFT:
					if (rc.left <= 0) break; // Ż�����
					if (rc2.left <= 0 && rc2.right >= rc.left
						&& (((rc.top < rc2.top && rc.bottom > rc2.top)
						|| (rc.top < rc2.bottom && rc.bottom > rc2.bottom))
						|| (rc.top == rc2.top))) break;
					rc.left -= 5;
					rc.right -= 5;
					if (rc.right <= rc3.right)
					{
						int width = rc3.right - rc3.left;
						rc3.right = rc.right;
						rc3.left = rc3.right - width;
					}
					if (rc.left < rc2.right && rc.right > rc2.left
						&& (((rc.top < rc2.top && rc.bottom > rc2.top)
						|| (rc.top < rc2.bottom && rc.bottom > rc2.bottom))
						|| (rc.top == rc2.top)))
					{
						int width = rc2.right - rc2.left;
						rc2.right = rc.left;
						rc2.left = rc2.right - width;
					}

					InvalidateRect(hWnd, NULL, true);
				break;
				case VK_RIGHT:
					if (rc.right >= WINSIZEX) break;
					if (rc2.right >= WINSIZEX && rc2.left <= rc.right
						&& (((rc.top < rc2.top && rc.bottom > rc2.top)
						|| (rc.top < rc2.bottom && rc.bottom > rc2.bottom))
						|| (rc.top == rc2.top))) break;
					rc.left += 5;
					rc.right += 5;
					if (rc.left >= rc3.left)
					{
						int width = rc3.right - rc3.left;
						rc3.left = rc.left;
						rc3.right = rc3.left + width;
					}
					
					if (rc.right > rc2.left && rc.left < rc2.left
						&& ((rc.top < rc2.top && rc.bottom > rc2.top)
						|| (rc.top < rc2.bottom && rc.bottom > rc2.bottom)
						|| (rc.top == rc2.top)))
					{
						int width = rc2.right - rc2.left;
						rc2.left = rc.right;
						rc2.right = rc2.left + width;
					}

					InvalidateRect(hWnd, NULL, true);
				break;
				case VK_UP:
					if (rc.top <= 0) break;
					if (rc2.top <= 0 && rc2.bottom >= rc.top
						&& ((rc.left < rc2.left && rc2.left < rc.right)
						|| (rc.left < rc2.right && rc2.right < rc.right)
						|| (rc.left == rc2.left))) break;
					rc.top -= 5;
					rc.bottom -= 5;
					if (rc.bottom <= rc3.bottom)
					{
						int height = rc3.top - rc3.bottom;
						rc3.bottom = rc.bottom;
						rc3.top = rc.bottom + height;
					}

					if (rc.top < rc2.bottom && rc.bottom > rc2.bottom
						&& ((rc.left < rc2.left && rc2.left < rc.right)
						|| (rc.left < rc2.right && rc2.right < rc.right)
						|| (rc.left == rc2.left)))
					{
						int height = rc2.bottom - rc2.top;
						rc2.bottom = rc.top;
						rc2.top = rc2.bottom - height;
					}

					InvalidateRect(hWnd, NULL, true);
				break;
				case VK_DOWN:
					if (rc.bottom >= WINSIZEY) break;
					if (rc2.bottom >= WINSIZEY && rc2.top <= rc.bottom
						&& ((rc.left < rc2.left && rc2.left < rc.right)
						|| (rc.left < rc2.right && rc2.right < rc.right)
						|| (rc.left == rc2.left))) break;
					rc.top += 5;
					rc.bottom += 5;
					if (rc.top >= rc3.top)
					{
						int height = rc3.top - rc3.bottom;
						rc3.top = rc.top;
						rc3.bottom = rc3.top - height;
					}

					if (rc.bottom > rc2.top && rc.top < rc2.top
						&& ((rc.left < rc2.left && rc2.left < rc.right)
						|| (rc.left < rc2.right && rc2.right < rc.right)
						|| (rc.left == rc2.left)))
					{
						int height = rc2.bottom - rc2.top;
						rc2.top = rc.bottom;
						rc2.bottom = rc2.top + height;
					}
					InvalidateRect(hWnd, NULL, true);
				break;
			}

		break;

		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
void setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	AdjustWindowRect(&winRect, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);

}
