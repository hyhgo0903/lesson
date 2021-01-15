#include <Windows.h>

//API : Application Programming Interface

HINSTANCE	_hInstance;	//�ν��Ͻ� 
HWND		_hWnd;		//������ �ڵ�
LPCTSTR		_lpszClass = TEXT("25��");

//�Լ� ������Ÿ�� ����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszClass, int cmdShow)
{
	MSG		message;	//������ �޽����� ���� ����ü
	WNDCLASS wndClass;	//������ Ŭ���� ����ü

	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = _lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	_hWnd = CreateWindow(
		_lpszClass,
		_lpszClass,
		WS_OVERLAPPEDWINDOW,
		50,
		50,
		800,
		600,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	ShowWindow(_hWnd, cmdShow);

	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC			hdc;
	// dcȯ�濡���� 0,0�� �»�� opengl�� ���ϴ�

	switch (iMessage)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		// pixel �ϳ��� ��� �ʹٸ� -setPixel()
		SetPixel(hdc, 50, 50, RGB(255, 0, 0));

		for (int i = 0; i < 100; i++)
		{
			SetPixel(hdc, 50+i, 50, RGB(255, 0, 0));
		}

		MoveToEx(hdc, 500, 100, NULL);
		LineTo(hdc, 200, 200); // ���� ��Ʈ(��������� ���߱�)

		MoveToEx(hdc, 100, 100, NULL);
		for (int i = 0; i < 6; i++)
		{
			LineTo(hdc, 150, 200); // ���� ��Ʈ(��������� ���߱�)
			LineTo(hdc, 200, 200+ 50 * i);
			LineTo(hdc, 250 + 50 * i, 150 + 50*i);
			LineTo(hdc, 150 + 50 * i, 200);
		}

		// �簢�� �׸��� �Լ� - Rectangle()
		// Left top -> Right Bottom����
		Rectangle(hdc, 100, 100, 500, 500);
		// Rectangle(�׷���DC, left,top,right,bottom)
		// �׸��� �׸����� �����ϸ� ��
		// ���׸��� �Լ� - Ellipse
		Ellipse(hdc, 100, 100, 500, 500); // �Լ� ����ϴ� ���� �簢���� ����
		Ellipse(hdc, 150, 150, 450, 450);
		/*
		HPEN pen = CreatePen(PS_DASHDOT, 1, RGB(255, 0, 0));
		// �潺Ÿ���� F12�̿� (�汽�� 1�϶��� �ǹ�����)
		// �̷��� �ֹ��� �ȵȴ�
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		MoveToEx(hdc, 120, 120, NULL);
		LineTo(hdc, 320, 320);
		SelectObject(hdc, oldPen);
		DeleteObject(pen);
		HBRUSH brush = CreateSolidBrush(RGB(200, 221, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
		Ellipse(hdc, 100, 100, 300, 300);
		SelectObject(hdc, oldBrush);
		DeleteObject(brush);*/

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}