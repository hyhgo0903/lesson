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

//���� ���� ���������� ��
enum BOX
{
	BOX_FIRST,	//0
	BOX_SECOND,	//1
	BOX_END		//2
};

BOX CURRENTBOX;		//�̳ѹ��� CURRENTBOX�� �θ�����

//rc[2]��
RECT rc[BOX_END], rcIN;


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//WPARAM : Ű���� ������ ���̵�, ���콺 ��,��,�� Ŭ���ϸ� �갡 ������
	//LPARAM : ���콺 ��ǥ�� ������

	PAINTSTRUCT ps;
	HDC			hdc;	//<-- �� ��¥ �߿���

	switch (iMessage)
	{
		//������ â�� �����ɶ� ����~ �� �� �����
		case WM_CREATE:
			rc[BOX_FIRST] = RectMakeCenter(WINSIZEX / 2 - 150, WINSIZEY / 2, 100, 100);
			rc[BOX_SECOND] = RectMakeCenter(WINSIZEX / 2 + 150, WINSIZEY / 2, 100, 100);
			rcIN = RectMakeCenter(WINSIZEX / 2 - 150, WINSIZEY / 2, 50, 50);

			CURRENTBOX = BOX_FIRST;
		break;
		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);

			for (int i = 0; i < BOX_END; ++i)
			{
				Rectangle(hdc, rc[i].left, rc[i].top, rc[i].right, rc[i].bottom);
			}
			Rectangle(hdc, rcIN.left, rcIN.top, rcIN.right, rcIN.bottom);
		

			EndPaint(hWnd, &ps);
		}
		break;

		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_LEFT:
					rc[CURRENTBOX].left -= 5;
					rc[CURRENTBOX].right -= 5;

					if (rcIN.right > rc[CURRENTBOX].right)
					{
						int width = rcIN.right - rcIN.left;

						rcIN.right = rc[CURRENTBOX].right;
						rcIN.left = rcIN.right - width;
					}

				break;
				case VK_RIGHT:
					rc[CURRENTBOX].left += 5;
					rc[CURRENTBOX].right += 5;

					if (rcIN.left < rc[CURRENTBOX].left)
					{
						int width = rcIN.right - rcIN.left;

						rcIN.left = rc[CURRENTBOX].left;
						rcIN.right = rcIN.left + width;
					}
				break;
				case VK_UP:
					rc[CURRENTBOX].top -= 5;
					rc[CURRENTBOX].bottom -= 5;

					if (rcIN.bottom > rc[CURRENTBOX].bottom)
					{
						int height = rcIN.bottom - rcIN.top;

						rcIN.bottom = rc[CURRENTBOX].bottom;
						rcIN.top = rcIN.bottom - height;
					}

				break;
				case VK_DOWN:
					rc[CURRENTBOX].top += 5;
					rc[CURRENTBOX].bottom += 5;

					if (rcIN.top < rc[CURRENTBOX].top)
					{
						int height = rcIN.bottom - rcIN.top;

						rcIN.top = rc[CURRENTBOX].top;
						rcIN.bottom = rcIN.top + height;		
					}
				break;
				case VK_ESCAPE:
					PostQuitMessage(0);
					// esc������ ��������
				break;
			}
			RECT temp;
			if (IntersectRect(&temp, &rc[BOX_FIRST], &rc[BOX_SECOND]))
			{ // temp�� �� �簢�� �������� ����
				switch (CURRENTBOX)
				{
					case BOX_FIRST:
						CURRENTBOX = BOX_SECOND;
					break;
					case BOX_SECOND:
						CURRENTBOX = BOX_FIRST;
					break;

				}

				rcIN = RectMakeCenter((rc[CURRENTBOX].right + rc[CURRENTBOX].left) / 2,
					(rc[CURRENTBOX].bottom + rc[CURRENTBOX].top) / 2, 50, 50);
			}

				/*
			if (rc[BOX_FIRST].right > rc[BOX_SECOND].left &&
				rc[BOX_FIRST].left  < rc[BOX_SECOND].right &&
				rc[BOX_FIRST].top   < rc[BOX_SECOND].bottom &&
				rc[BOX_FIRST].bottom > rc[BOX_SECOND].top)
			{
				switch (CURRENTBOX)
				{
					case BOX_FIRST:
						CURRENTBOX = BOX_SECOND;
					break;
					case BOX_SECOND:
						CURRENTBOX = BOX_FIRST;
					break;				
				}

				rcIN = RectMakeCenter((rc[CURRENTBOX].right + rc[CURRENTBOX].left) / 2,
					(rc[CURRENTBOX].bottom + rc[CURRENTBOX].top) / 2, 50, 50);
			}*/
			
			InvalidateRect(hWnd, NULL, true);
		break;


		case WM_DESTROY:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
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

	//�갡 ������ ���� �����ϴ� ����
	AdjustWindowRect(&winRect, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);

}
