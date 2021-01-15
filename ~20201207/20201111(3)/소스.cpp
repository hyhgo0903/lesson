#include <Windows.h>

//API : Application Programming Interface

HINSTANCE	_hInstance;	//인스턴스 
HWND		_hWnd;		//윈도우 핸들
LPCTSTR		_lpszClass = TEXT("25기");

//함수 프로토타입 선언
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszClass, int cmdShow)
{
	MSG		message;	//윈도우 메시지를 담은 구조체
	WNDCLASS wndClass;	//윈도우 클래스 구조체

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
	// dc환경에서는 0,0이 좌상단 opengl은 좌하단

	switch (iMessage)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		// pixel 하나를 찍고 싶다면 -setPixel()
		SetPixel(hdc, 50, 50, RGB(255, 0, 0));

		for (int i = 0; i < 100; i++)
		{
			SetPixel(hdc, 50+i, 50, RGB(255, 0, 0));
		}

		MoveToEx(hdc, 500, 100, NULL);
		LineTo(hdc, 200, 200); // 둘이 셋트(시작점찍고 선긋기)

		MoveToEx(hdc, 100, 100, NULL);
		for (int i = 0; i < 6; i++)
		{
			LineTo(hdc, 150, 200); // 둘이 셋트(시작점찍고 선긋기)
			LineTo(hdc, 200, 200+ 50 * i);
			LineTo(hdc, 250 + 50 * i, 150 + 50*i);
			LineTo(hdc, 150 + 50 * i, 200);
		}

		// 사각형 그리는 함수 - Rectangle()
		// Left top -> Right Bottom인자
		Rectangle(hdc, 100, 100, 500, 500);
		// Rectangle(그려줄DC, left,top,right,bottom)
		// 그림판 그릴떄를 생각하면 됨
		// 원그리는 함수 - Ellipse
		Ellipse(hdc, 100, 100, 500, 500); // 함수 사용하는 법은 사각형과 같음
		Ellipse(hdc, 150, 150, 450, 450);
		/*
		HPEN pen = CreatePen(PS_DASHDOT, 1, RGB(255, 0, 0));
		// 펜스타일은 F12이용 (펜굵기 1일때만 의미있음)
		// 이래야 휘발이 안된다
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