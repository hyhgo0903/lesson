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
	HDC			hdc;	//<-- �� ��¥ �߿���

	static RECT rc; // �������� �����������
	static RECT rc2;

	switch (iMessage)
	{		
		case WM_CREATE: // ������ â�� �����ɶ� �� �ѹ� �����
			// rc = { 100,100,200,200 }; // ������ ����� �̰͸����� �����δ� �Ⱥ���
			rc = RectMakeCenter(WINSIZEX / 2-100, WINSIZEX / 2, 100, 100);
			rc2 = RectMakeCenter(WINSIZEX / 2 +100, WINSIZEX / 2 , 100, 100);
			break;
		case WM_PAINT:
		{
			//������â�� �ű�ų� ũ�⸦ ���̰ų��Ҷ� �����̵�
			hdc = BeginPaint(hWnd, &ps);

			Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
			// �̰� �־�� �׷���
			Rectangle(hdc, rc2.left, rc2.top, rc2.right, rc2.bottom);

			//LineMake(hdc, 100, 100, 300, 400);
			//RectangleMake(hdc, WINSIZEX / 2, WINSIZEY / 2, 100, 100);
			//RectangleMakeCenter(hdc, WINSIZEX / 2, WINSIZEY / 2, 100, 100);
			
			//EllipseMakeCenter(hdc, WINSIZEX / 2, WINSIZEY / 2, 400, 400);
			//EllipseMakeCenter(hdc, WINSIZEX / 2, WINSIZEY / 2, 350, 350);




			EndPaint(hWnd, &ps);
		}
		break;

		case WM_KEYDOWN: // Ű�� ��������
			switch (wParam)
			{
				case VK_LEFT:
					if (rc.left <= 0) break; // Ż�����
					rc.left -= 5;
					rc.right -= 5;
					InvalidateRect(hWnd, NULL, true);
					// �ڵ�, �����쿡�� ��ŭ����, ���﷡�����﷡
				break;
				case VK_RIGHT:
					rc.left += 5;
					rc.right += 5;
					
					if (rc.right >= rc2.left)
					{
						int width = rc2.right - rc2.left;
						rc2.left = rc.right;
						rc2.right = rc2.left + width;
					}

					InvalidateRect(hWnd, NULL, true);
				break;
				case VK_UP:
					rc.top -= 5;
					rc.bottom -= 5;
					InvalidateRect(hWnd, NULL, true);
				break;
				case VK_DOWN:
					rc.top += 5;
					rc.bottom += 5;
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
// ������ â�� ������ �����Ϸ���(0,0)�̸� ©���� ����
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
