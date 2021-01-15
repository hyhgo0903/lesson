#include <Windows.h>

HINSTANCE	_hInstance;
HWND		_hWnd;
LPCTSTR		_lpszClass = TEXT("25±â");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszClass, int cmdShow)
{
	MSG		message;
	WNDCLASS wndClass;

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
		1100,
		500,
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

	switch (iMessage)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		//ÇÏ
		MoveToEx(hdc, 150, 50, NULL);
		LineTo(hdc, 150, 100);
		LineTo(hdc, 50, 100);
		LineTo(hdc, 250, 100);
		Ellipse(hdc, 80, 150, 230, 300);
		MoveToEx(hdc, 300, 50, NULL);
		LineTo(hdc, 300, 375);
		LineTo(hdc, 300, 200);
		LineTo(hdc, 375, 200);
		//À¶
		Ellipse(hdc, 450, 75, 650, 175);
		MoveToEx(hdc, 400, 200, NULL);
		LineTo(hdc, 725, 200);
		LineTo(hdc, 505, 200);
		LineTo(hdc, 505, 275);
		LineTo(hdc, 505, 200);
		LineTo(hdc, 610, 200);
		LineTo(hdc, 610, 275);
		Ellipse(hdc, 450, 275, 650, 375);
		//È£
		MoveToEx(hdc, 780, 100, NULL);
		LineTo(hdc, 1020, 100);
		LineTo(hdc, 900, 100);
		LineTo(hdc, 900, 50);
		Ellipse(hdc, 800, 150, 1000, 250);
		MoveToEx(hdc, 760, 350, NULL);
		LineTo(hdc, 1040, 350);
		LineTo(hdc, 900, 350);
		LineTo(hdc, 900, 280);


		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}